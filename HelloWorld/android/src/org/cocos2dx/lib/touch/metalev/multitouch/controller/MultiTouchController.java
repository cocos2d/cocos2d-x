package org.cocos2dx.lib.touch.metalev.multitouch.controller;

/**
 * MultiTouchController.java
 * 
 * Author: Luke Hutchison (luke.hutch@mit.edu)
 *   Please drop me an email if you use this code so I can list your project here!
 * 
 * Usage:
 *   <code>
 *   public class MyMTView extends View implements MultiTouchObjectCanvas<PinchWidgetType> {
 *
 *       private MultiTouchController<PinchWidgetType> multiTouchController = new MultiTouchController<PinchWidgetType>(this);
 *  
 *       // Pass touch events to the MT controller
 *       public boolean onTouchEvent(MotionEvent event) {
 *           return multiTouchController.onTouchEvent(event);
 *       }
 *     
 *       // ... then implement the MultiTouchObjectCanvas interface here, see details in the comments of that interface.
 *   }
 *   </code>
 * 
 * Changelog:
 *   2010-06-09 v1.5.1  Some API changes to make it possible to selectively update or not update scale / rotation.
 *                      Fixed anisotropic zoom.  Cleaned up rotation code.  Added more comments.  Better var names. (LH)
 *   2010-06-09 v1.4    Added ability to track pinch rotation (Mickael Despesse, author of "Face Frenzy") and anisotropic pinch-zoom (LH)
 *   2010-06-09 v1.3.3  Bugfixes for Android-2.1; added optional debug info (LH)
 *   2010-06-09 v1.3    Ported to Android-2.2 (handle ACTION_POINTER_* actions); fixed several bugs; refactoring; documentation (LH) 
 *   2010-05-17 v1.2.1  Dual-licensed under Apache and GPL licenses
 *   2010-02-18 v1.2    Support for compilation under Android 1.5/1.6 using introspection (mmin, author of handyCalc)
 *   2010-01-08 v1.1.1  Bugfixes to Cyanogen's patch that only showed up in more complex uses of controller (LH) 
 *   2010-01-06 v1.1    Modified for official level 5 MT API (Cyanogen)
 *   2009-01-25 v1.0    Original MT controller, released for hacked G1 kernel (LH) 
 * 
 * Planned features:
 * - Add inertia (flick-pinch-zoom or flick-scroll)
 * 
 * Known usages:
 * - Mickael Despesse's "Face Frenzy" face distortion app, to be published to the Market soon
 * - Yuan Chin's fork of ADW Launcher to support multitouch
 * - David Byrne's fractal viewing app Fractoid
 * - mmin's handyCalc calculator
 * - My own "MultiTouch Visualizer 2" in the Market
 * - Formerly: The browser in cyanogenmod (and before that, JesusFreke), and other firmwares like dwang5.  This usage has been
 *   replaced with official pinch/zoom in Maps, Browser and Gallery[3D] as of API level 5.
 * 
 * License:
 *   Dual-licensed under the Apache License v2 and the GPL v2.
 */

import java.lang.reflect.Method;

import android.util.Log;
import android.view.MotionEvent;

/**
 * A class that simplifies the implementation of multitouch in applications. Subclass this and read the fields here as needed in subclasses.
 * 
 * @author Luke Hutchison
 */
public class MultiTouchController<T> {

	/**
	 * Time in ms required after a change in event status (e.g. putting down or lifting off the second finger) before events actually do anything --
	 * helps eliminate noisy jumps that happen on change of status
	 */
	private static final long EVENT_SETTLE_TIME_INTERVAL = 20;

	/**
	 * The biggest possible abs val of the change in x or y between multitouch events (larger dx/dy events are ignored) -- helps eliminate jumps in
	 * pointer position on finger 2 up/down.
	 */
	private static final float MAX_MULTITOUCH_POS_JUMP_SIZE = 30.0f;

	/**
	 * The biggest possible abs val of the change in multitouchWidth or multitouchHeight between multitouch events (larger-jump events are ignored) --
	 * helps eliminate jumps in pointer position on finger 2 up/down.
	 */
	private static final float MAX_MULTITOUCH_DIM_JUMP_SIZE = 40.0f;

	/** The smallest possible distance between multitouch points (used to avoid div-by-zero errors and display glitches) */
	private static final float MIN_MULTITOUCH_SEPARATION = 30.0f;

	/** The max number of touch points that can be present on the screen at once */
	public static final int MAX_TOUCH_POINTS = 5;

	/** Generate tons of log entries for debugging */
	public static final boolean DEBUG = false;

	// ----------------------------------------------------------------------------------------------------------------------

	MultiTouchObjectCanvas<T> objectCanvas;

	/** The current touch point */
	public PointInfo mCurrPt;

	/** The previous touch point */
	private PointInfo mPrevPt;

	/** Fields extracted from mCurrPt */
	private float mCurrPtX, mCurrPtY, mCurrPtDiam, mCurrPtWidth, mCurrPtHeight, mCurrPtAng;

	/**
	 * Extract fields from mCurrPt, respecting the update* fields of mCurrPt. This just avoids code duplication. I hate that Java doesn't support
	 * higher-order functions, tuples or multiple return values from functions.
	 */
	private void extractCurrPtInfo() {
		// Get new drag/pinch params. Only read multitouch fields that are needed,
		// to avoid unnecessary computation (diameter and angle are expensive operations).
		mCurrPtX = mCurrPt.getX();
		mCurrPtY = mCurrPt.getY();
		mCurrPtDiam = Math.max(MIN_MULTITOUCH_SEPARATION * .71f, !mCurrXform.updateScale ? 0.0f : mCurrPt.getMultiTouchDiameter());
		mCurrPtWidth = Math.max(MIN_MULTITOUCH_SEPARATION, !mCurrXform.updateScaleXY ? 0.0f : mCurrPt.getMultiTouchWidth());
		mCurrPtHeight = Math.max(MIN_MULTITOUCH_SEPARATION, !mCurrXform.updateScaleXY ? 0.0f : mCurrPt.getMultiTouchHeight());
		mCurrPtAng = !mCurrXform.updateAngle ? 0.0f : mCurrPt.getMultiTouchAngle();
	}

	// ----------------------------------------------------------------------------------------------------------------------

	/** Whether to handle single-touch events/drags before multi-touch is initiated or not; if not, they are handled by subclasses */
	private boolean handleSingleTouchEvents;

	/** The object being dragged/stretched */
	private T selectedObject = null;

	/** Current position and scale of the dragged object */
	private PositionAndScale mCurrXform = new PositionAndScale();

	/** Drag/pinch start time and time to ignore spurious events until (to smooth over event noise) */
	private long mSettleStartTime, mSettleEndTime;

	/** Conversion from object coords to screen coords */
	private float startPosX, startPosY;

	/** Conversion between scale and width, and object angle and start pinch angle */
	private float startScaleOverPinchDiam, startAngleMinusPinchAngle;

	/** Conversion between X scale and width, and Y scale and height */
	private float startScaleXOverPinchWidth, startScaleYOverPinchHeight;

	// ----------------------------------------------------------------------------------------------------------------------

	/** No touch points down. */
	private static final int MODE_NOTHING = 0;

	/** One touch point down, dragging an object. */
	private static final int MODE_DRAG = 1;

	/** Two or more touch points down, stretching/rotating an object using the first two touch points. */
	private static final int MODE_PINCH = 2;

	/** Current drag mode */
	private int mMode = MODE_NOTHING;

	// ----------------------------------------------------------------------------------------------------------------------

	/** Constructor that sets handleSingleTouchEvents to true */
	public MultiTouchController(MultiTouchObjectCanvas<T> objectCanvas) {
		this(objectCanvas, true);
	}

	/** Full constructor */
	public MultiTouchController(MultiTouchObjectCanvas<T> objectCanvas, boolean handleSingleTouchEvents) {
		this.mCurrPt = new PointInfo();
		this.mPrevPt = new PointInfo();
		this.handleSingleTouchEvents = handleSingleTouchEvents;
		this.objectCanvas = objectCanvas;
	}

	// ------------------------------------------------------------------------------------

	/**
	 * Whether to handle single-touch events/drags before multi-touch is initiated or not; if not, they are handled by subclasses. Default: true
	 */
	protected void setHandleSingleTouchEvents(boolean handleSingleTouchEvents) {
		this.handleSingleTouchEvents = handleSingleTouchEvents;
	}

	/**
	 * Whether to handle single-touch events/drags before multi-touch is initiated or not; if not, they are handled by subclasses. Default: true
	 */
	protected boolean getHandleSingleTouchEvents() {
		return handleSingleTouchEvents;
	}

	// ------------------------------------------------------------------------------------

	public static final boolean multiTouchSupported;
	private static Method m_getPointerCount;
	private static Method m_getPointerId;
	private static Method m_getPressure;
	private static Method m_getHistoricalX;
	private static Method m_getHistoricalY;
	private static Method m_getHistoricalPressure;
	private static Method m_getX;
	private static Method m_getY;
	private static int ACTION_POINTER_UP = 6;
	private static int ACTION_POINTER_INDEX_SHIFT = 8;

	static {
		boolean succeeded = false;
		try {
			// Android 2.0.1 stuff:
			m_getPointerCount = MotionEvent.class.getMethod("getPointerCount");
			m_getPointerId = MotionEvent.class.getMethod("getPointerId", Integer.TYPE);
			m_getPressure = MotionEvent.class.getMethod("getPressure", Integer.TYPE);
			m_getHistoricalX = MotionEvent.class.getMethod("getHistoricalX", Integer.TYPE, Integer.TYPE);
			m_getHistoricalY = MotionEvent.class.getMethod("getHistoricalY", Integer.TYPE, Integer.TYPE);
			m_getHistoricalPressure = MotionEvent.class.getMethod("getHistoricalPressure", Integer.TYPE, Integer.TYPE);
			m_getX = MotionEvent.class.getMethod("getX", Integer.TYPE);
			m_getY = MotionEvent.class.getMethod("getY", Integer.TYPE);
			succeeded = true;
		} catch (Exception e) {
			Log.e("MultiTouchController", "static initializer failed", e);
		}
		multiTouchSupported = succeeded;
		if (multiTouchSupported) {
			// Android 2.2+ stuff (the original Android 2.2 consts are declared above,
			// and these actions aren't used previous to Android 2.2):
			try {
				ACTION_POINTER_UP = MotionEvent.class.getField("ACTION_POINTER_UP").getInt(null);
				ACTION_POINTER_INDEX_SHIFT = MotionEvent.class.getField("ACTION_POINTER_INDEX_SHIFT").getInt(null);
			} catch (Exception e) {
			}
		}
	}

	// ------------------------------------------------------------------------------------

	private static final float[] xVals = new float[MAX_TOUCH_POINTS];
	private static final float[] yVals = new float[MAX_TOUCH_POINTS];
	private static final float[] pressureVals = new float[MAX_TOUCH_POINTS];
	private static final int[] pointerIds = new int[MAX_TOUCH_POINTS];

	/** Process incoming touch events */
	public boolean onTouchEvent(MotionEvent event) {
		try {
			int pointerCount = multiTouchSupported ? (Integer) m_getPointerCount.invoke(event) : 1;
			if (DEBUG)
				Log.i("MultiTouch", "Got here 1 - " + multiTouchSupported + " " + mMode + " " + handleSingleTouchEvents + " " + pointerCount);
			if (mMode == MODE_NOTHING && !handleSingleTouchEvents && pointerCount == 1)
				// Not handling initial single touch events, just pass them on
				return false;
			if (DEBUG)
				Log.i("MultiTouch", "Got here 2");

			// Handle history first (we sometimes get history with ACTION_MOVE events)
			int action = event.getAction();
			int histLen = event.getHistorySize() / pointerCount;
			for (int histIdx = 0; histIdx <= histLen; histIdx++) {
				// Read from history entries until histIdx == histLen, then read from current event
				boolean processingHist = histIdx < histLen;
				if (!multiTouchSupported || pointerCount == 1) {
					// Use single-pointer methods -- these are needed as a special case (for some weird reason) even if
					// multitouch is supported but there's only one touch point down currently -- event.getX(0) etc. throw
					// an exception if there's only one point down.
					if (DEBUG)
						Log.i("MultiTouch", "Got here 3");
					xVals[0] = processingHist ? event.getHistoricalX(histIdx) : event.getX();
					yVals[0] = processingHist ? event.getHistoricalY(histIdx) : event.getY();
					pressureVals[0] = processingHist ? event.getHistoricalPressure(histIdx) : event.getPressure();
				} else {
					// Read x, y and pressure of each pointer
					if (DEBUG)
						Log.i("MultiTouch", "Got here 4");
					int numPointers = Math.min(pointerCount, MAX_TOUCH_POINTS);
					if (DEBUG && pointerCount > MAX_TOUCH_POINTS)
						Log.i("MultiTouch", "Got more pointers than MAX_TOUCH_POINTS");
					for (int ptrIdx = 0; ptrIdx < numPointers; ptrIdx++) {
						int ptrId = (Integer) m_getPointerId.invoke(event, ptrIdx);
						pointerIds[ptrIdx] = ptrId;
						// N.B. if pointerCount == 1, then the following methods throw an array index out of range exception,
						// and the code above is therefore required not just for Android 1.5/1.6 but also for when there is
						// only one touch point on the screen -- pointlessly inconsistent :(
						xVals[ptrIdx] = (Float) (processingHist ? m_getHistoricalX.invoke(event, ptrIdx, histIdx) : m_getX.invoke(event, ptrIdx));
						yVals[ptrIdx] = (Float) (processingHist ? m_getHistoricalY.invoke(event, ptrIdx, histIdx) : m_getY.invoke(event, ptrIdx));
						pressureVals[ptrIdx] = (Float) (processingHist ? m_getHistoricalPressure.invoke(event, ptrIdx, histIdx) : m_getPressure
								.invoke(event, ptrIdx));
					}
				}
				// Decode event
				decodeTouchEvent(pointerCount, xVals, yVals, pressureVals, pointerIds, //
						/* action = */processingHist ? MotionEvent.ACTION_MOVE : action, //
						/* down = */processingHist ? true : action != MotionEvent.ACTION_UP //
								&& (action & ((1 << ACTION_POINTER_INDEX_SHIFT) - 1)) != ACTION_POINTER_UP //
								&& action != MotionEvent.ACTION_CANCEL, //
						processingHist ? event.getHistoricalEventTime(histIdx) : event.getEventTime());
			}

			return true;
		} catch (Exception e) {
			// In case any of the introspection stuff fails (it shouldn't)
			Log.e("MultiTouchController", "onTouchEvent() failed", e);
			return false;
		}
	}

	private void decodeTouchEvent(int pointerCount, float[] x, float[] y, float[] pressure, int[] pointerIds, int action, boolean down, long eventTime) {
		if (DEBUG)
			Log.i("MultiTouch", "Got here 5 - " + pointerCount + " " + action + " " + down);

		// Swap curr/prev points
		PointInfo tmp = mPrevPt;
		mPrevPt = mCurrPt;
		mCurrPt = tmp;
		// Overwrite old prev point
		mCurrPt.set(pointerCount, x, y, pressure, pointerIds, action, down, eventTime);
		multiTouchController();
	}

	// ------------------------------------------------------------------------------------

	/** Start dragging/pinching, or reset drag/pinch to current point if something goes out of range */
	private void anchorAtThisPositionAndScale() {
		if (selectedObject == null)
			return;

		// Get selected object's current position and scale
		objectCanvas.getPositionAndScale(selectedObject, mCurrXform);

		// Figure out the object coords of the drag start point's screen coords.
		// All stretching should be around this point in object-coord-space.
		// Also figure out out ratio between object scale factor and multitouch
		// diameter at beginning of drag; same for angle and optional anisotropic
		// scale.
		float currScaleInv = 1.0f / (!mCurrXform.updateScale ? 1.0f : mCurrXform.scale == 0.0f ? 1.0f : mCurrXform.scale);
		extractCurrPtInfo();
		startPosX = (mCurrPtX - mCurrXform.xOff) * currScaleInv;
		startPosY = (mCurrPtY - mCurrXform.yOff) * currScaleInv;
		startScaleOverPinchDiam = mCurrXform.scale / mCurrPtDiam;
		startScaleXOverPinchWidth = mCurrXform.scaleX / mCurrPtWidth;
		startScaleYOverPinchHeight = mCurrXform.scaleY / mCurrPtHeight;
		startAngleMinusPinchAngle = mCurrXform.angle - mCurrPtAng;
	}

	/** Drag/stretch/rotate the selected object using the current touch position(s) relative to the anchor position(s). */
	private void performDragOrPinch() {
		// Don't do anything if we're not dragging anything
		if (selectedObject == null)
			return;

		// Calc new position of dragged object
		float currScale = !mCurrXform.updateScale ? 1.0f : mCurrXform.scale == 0.0f ? 1.0f : mCurrXform.scale;
		extractCurrPtInfo();
		float newPosX = mCurrPtX - startPosX * currScale;
		float newPosY = mCurrPtY - startPosY * currScale;
		float newScale = startScaleOverPinchDiam * mCurrPtDiam;
		float newScaleX = startScaleXOverPinchWidth * mCurrPtWidth;
		float newScaleY = startScaleYOverPinchHeight * mCurrPtHeight;
		float newAngle = startAngleMinusPinchAngle + mCurrPtAng;

		// Set the new obj coords, scale, and angle as appropriate (notifying the subclass of the change).
		mCurrXform.set(newPosX, newPosY, newScale, newScaleX, newScaleY, newAngle);

		boolean success = objectCanvas.setPositionAndScale(selectedObject, mCurrXform, mCurrPt);
		if (!success)
			; // If we could't set those params, do nothing currently
	}

	/**
	 * State-based controller for tracking switches between no-touch, single-touch and multi-touch situations. Includes logic for cleaning up the
	 * event stream, as events around touch up/down are noisy at least on early Synaptics sensors.
	 */
	private void multiTouchController() {
		if (DEBUG)
			Log.i("MultiTouch", "Got here 6 - " + mMode + " " + mCurrPt.getNumTouchPoints() + " " + mCurrPt.isDown() + mCurrPt.isMultiTouch());

		switch (mMode) {
		case MODE_NOTHING:
			// Not doing anything currently
			if (mCurrPt.isDown()) {
				// Start a new single-point drag
				selectedObject = objectCanvas.getDraggableObjectAtPoint(mCurrPt);
				if (selectedObject != null) {
					// Started a new single-point drag
					mMode = MODE_DRAG;
					objectCanvas.selectObject(selectedObject, mCurrPt);
					anchorAtThisPositionAndScale();
					// Don't need any settling time if just placing one finger, there is no noise
					mSettleStartTime = mSettleEndTime = mCurrPt.getEventTime();
				}
			}
			break;

		case MODE_DRAG:
			// Currently in a single-point drag
			if (!mCurrPt.isDown()) {
				// First finger was released, stop dragging
				mMode = MODE_NOTHING;
				objectCanvas.selectObject((selectedObject = null), mCurrPt);

			} else if (mCurrPt.isMultiTouch()) {
				// Point 1 was already down and point 2 was just placed down
				mMode = MODE_PINCH;
				// Restart the drag with the new drag position (that is at the midpoint between the touchpoints)
				anchorAtThisPositionAndScale();
				// Need to let events settle before moving things, to help with event noise on touchdown
				mSettleStartTime = mCurrPt.getEventTime();
				mSettleEndTime = mSettleStartTime + EVENT_SETTLE_TIME_INTERVAL;

			} else {
				// Point 1 is still down and point 2 did not change state, just do single-point drag to new location
				if (mCurrPt.getEventTime() < mSettleEndTime) {
					// Ignore the first few events if we just stopped stretching, because if finger 2 was kept down while
					// finger 1 is lifted, then point 1 gets mapped to finger 2. Restart the drag from the new position.
					anchorAtThisPositionAndScale();
				} else {
					// Keep dragging, move to new point
					performDragOrPinch();
				}
			}
			break;

		case MODE_PINCH:
			// Two-point pinch-scale/rotate/translate
			if (!mCurrPt.isMultiTouch() || !mCurrPt.isDown()) {
				// Dropped one or both points, stop stretching

				if (!mCurrPt.isDown()) {
					// Dropped both points, go back to doing nothing
					mMode = MODE_NOTHING;
					objectCanvas.selectObject((selectedObject = null), mCurrPt);

				} else {
					// Just dropped point 2, downgrade to a single-point drag
					mMode = MODE_DRAG;
					// Restart the pinch with the single-finger position
					anchorAtThisPositionAndScale();
					// Ignore the first few events after the drop, in case we dropped finger 1 and left finger 2 down
					mSettleStartTime = mCurrPt.getEventTime();
					mSettleEndTime = mSettleStartTime + EVENT_SETTLE_TIME_INTERVAL;
				}

			} else {
				// Still pinching
				if (Math.abs(mCurrPt.getX() - mPrevPt.getX()) > MAX_MULTITOUCH_POS_JUMP_SIZE
						|| Math.abs(mCurrPt.getY() - mPrevPt.getY()) > MAX_MULTITOUCH_POS_JUMP_SIZE
						|| Math.abs(mCurrPt.getMultiTouchWidth() - mPrevPt.getMultiTouchWidth()) * .5f > MAX_MULTITOUCH_DIM_JUMP_SIZE
						|| Math.abs(mCurrPt.getMultiTouchHeight() - mPrevPt.getMultiTouchHeight()) * .5f > MAX_MULTITOUCH_DIM_JUMP_SIZE) {
					// Jumped too far, probably event noise, reset and ignore events for a bit
					anchorAtThisPositionAndScale();
					mSettleStartTime = mCurrPt.getEventTime();
					mSettleEndTime = mSettleStartTime + EVENT_SETTLE_TIME_INTERVAL;

				} else if (mCurrPt.eventTime < mSettleEndTime) {
					// Events have not yet settled, reset
					anchorAtThisPositionAndScale();
				} else {
					// Stretch to new position and size
					performDragOrPinch();
				}
			}
			break;
		}
		if (DEBUG)
			Log.i("MultiTouch", "Got here 7 - " + mMode + " " + mCurrPt.getNumTouchPoints() + " " + mCurrPt.isDown() + mCurrPt.isMultiTouch());
	}

	// ------------------------------------------------------------------------------------

	/** A class that packages up all MotionEvent information with all derived multitouch information (if available) */
	public static class PointInfo {
		// Multitouch information
		private int numPoints;
		private float[] xs = new float[MAX_TOUCH_POINTS];
		private float[] ys = new float[MAX_TOUCH_POINTS];
		private float[] pressures = new float[MAX_TOUCH_POINTS];
		private int[] pointerIds = new int[MAX_TOUCH_POINTS];

		// Midpoint of pinch operations
		private float xMid, yMid, pressureMid;

		// Width/diameter/angle of pinch operations
		private float dx, dy, diameter, diameterSq, angle;

		// Whether or not there is at least one finger down (isDown) and/or at least two fingers down (isMultiTouch)
		private boolean isDown, isMultiTouch;

		// Whether or not these fields have already been calculated, for caching purposes
		private boolean diameterSqIsCalculated, diameterIsCalculated, angleIsCalculated;

		// Event action code and event time
		private int action;
		private long eventTime;

		// -------------------------------------------------------------------------------------------------------------------------------------------

		/** Set all point info */
		private void set(int numPoints, float[] x, float[] y, float[] pressure, int[] pointerIds, int action, boolean isDown, long eventTime) {
			if (DEBUG)
				Log.i("MultiTouch", "Got here 8 - " + +numPoints + " " + x[0] + " " + y[0] + " " + (numPoints > 1 ? x[1] : x[0]) + " "
						+ (numPoints > 1 ? y[1] : y[0]) + " " + action + " " + isDown);
			this.eventTime = eventTime;
			this.action = action;
			this.numPoints = numPoints;
			for (int i = 0; i < numPoints; i++) {
				this.xs[i] = x[i];
				this.ys[i] = y[i];
				this.pressures[i] = pressure[i];
				this.pointerIds[i] = pointerIds[i];
			}
			this.isDown = isDown;
			this.isMultiTouch = numPoints >= 2;

			if (isMultiTouch) {
				xMid = (x[0] + x[1]) * .5f;
				yMid = (y[0] + y[1]) * .5f;
				pressureMid = (pressure[0] + pressure[1]) * .5f;
				dx = Math.abs(x[1] - x[0]);
				dy = Math.abs(y[1] - y[0]);

			} else {
				// Single-touch event
				xMid = x[0];
				yMid = y[0];
				pressureMid = pressure[0];
				dx = dy = 0.0f;
			}
			// Need to re-calculate the expensive params if they're needed
			diameterSqIsCalculated = diameterIsCalculated = angleIsCalculated = false;
		}

		/**
		 * Copy all fields from one PointInfo class to another. PointInfo objects are volatile so you should use this if you want to keep track of the
		 * last touch event in your own code.
		 */
		public void set(PointInfo other) {
			this.numPoints = other.numPoints;
			for (int i = 0; i < numPoints; i++) {
				this.xs[i] = other.xs[i];
				this.ys[i] = other.ys[i];
				this.pressures[i] = other.pressures[i];
				this.pointerIds[i] = other.pointerIds[i];
			}
			this.xMid = other.xMid;
			this.yMid = other.yMid;
			this.pressureMid = other.pressureMid;
			this.dx = other.dx;
			this.dy = other.dy;
			this.diameter = other.diameter;
			this.diameterSq = other.diameterSq;
			this.angle = other.angle;
			this.isDown = other.isDown;
			this.action = other.action;
			this.isMultiTouch = other.isMultiTouch;
			this.diameterIsCalculated = other.diameterIsCalculated;
			this.diameterSqIsCalculated = other.diameterSqIsCalculated;
			this.angleIsCalculated = other.angleIsCalculated;
			this.eventTime = other.eventTime;
		}

		// -------------------------------------------------------------------------------------------------------------------------------------------

		/** True if number of touch points >= 2. */
		public boolean isMultiTouch() {
			return isMultiTouch;
		}

		/** Difference between x coords of touchpoint 0 and 1. */
		public float getMultiTouchWidth() {
			return isMultiTouch ? dx : 0.0f;
		}

		/** Difference between y coords of touchpoint 0 and 1. */
		public float getMultiTouchHeight() {
			return isMultiTouch ? dy : 0.0f;
		}

		/** Fast integer sqrt, by Jim Ulery. Much faster than Math.sqrt() for integers. */
		private int julery_isqrt(int val) {
			int temp, g = 0, b = 0x8000, bshft = 15;
			do {
				if (val >= (temp = (((g << 1) + b) << bshft--))) {
					g += b;
					val -= temp;
				}
			} while ((b >>= 1) > 0);
			return g;
		}

		/** Calculate the squared diameter of the multitouch event, and cache it. Use this if you don't need to perform the sqrt. */
		public float getMultiTouchDiameterSq() {
			if (!diameterSqIsCalculated) {
				diameterSq = (isMultiTouch ? dx * dx + dy * dy : 0.0f);
				diameterSqIsCalculated = true;
			}
			return diameterSq;
		}

		/** Calculate the diameter of the multitouch event, and cache it. Uses fast int sqrt but gives accuracy to 1/16px. */
		public float getMultiTouchDiameter() {
			if (!diameterIsCalculated) {
				if (!isMultiTouch) {
					diameter = 0.0f;
				} else {
					// Get 1/16 pixel's worth of subpixel accuracy, works on screens up to 2048x2048
					// before we get overflow (at which point you can reduce or eliminate subpix
					// accuracy, or use longs in julery_isqrt())
					float diamSq = getMultiTouchDiameterSq();
					diameter = (diamSq == 0.0f ? 0.0f : (float) julery_isqrt((int) (256 * diamSq)) / 16.0f);
					// Make sure diameter is never less than dx or dy, for trig purposes
					if (diameter < dx)
						diameter = dx;
					if (diameter < dy)
						diameter = dy;
				}
				diameterIsCalculated = true;
			}
			return diameter;
		}

		/**
		 * Calculate the angle of a multitouch event, and cache it. Actually gives the smaller of the two angles between the x axis and the line
		 * between the two touchpoints, so range is [0,Math.PI/2]. Uses Math.atan2().
		 */
		public float getMultiTouchAngle() {
			if (!angleIsCalculated) {
				if (!isMultiTouch)
					angle = 0.0f;
				else
					angle = (float) Math.atan2(ys[1] - ys[0], xs[1] - xs[0]);
				angleIsCalculated = true;
			}
			return angle;
		}

		// -------------------------------------------------------------------------------------------------------------------------------------------

		/** Return the total number of touch points */
		public int getNumTouchPoints() {
			return numPoints;
		}

		/** Return the X coord of the first touch point if there's only one, or the midpoint between first and second touch points if two or more. */
		public float getX() {
			return xMid;
		}

		/** Return the array of X coords -- only the first getNumTouchPoints() of these is defined. */
		public float[] getXs() {
			return xs;
		}

		/** Return the X coord of the first touch point if there's only one, or the midpoint between first and second touch points if two or more. */
		public float getY() {
			return yMid;
		}

		/** Return the array of Y coords -- only the first getNumTouchPoints() of these is defined. */
		public float[] getYs() {
			return ys;
		}

		/**
		 * Return the array of pointer ids -- only the first getNumTouchPoints() of these is defined. These don't have to be all the numbers from 0 to
		 * getNumTouchPoints()-1 inclusive, numbers can be skipped if a finger is lifted and the touch sensor is capable of detecting that that
		 * particular touch point is no longer down. Note that a lot of sensors do not have this capability: when finger 1 is lifted up finger 2
		 * becomes the new finger 1.  However in theory these IDs can correct for that.  Convert back to indices using MotionEvent.findPointerIndex().
		 */
		public int[] getPointerIds() {
			return pointerIds;
		}

		/** Return the pressure the first touch point if there's only one, or the average pressure of first and second touch points if two or more. */
		public float getPressure() {
			return pressureMid;
		}

		/** Return the array of pressures -- only the first getNumTouchPoints() of these is defined. */
		public float[] getPressures() {
			return pressures;
		}

		// -------------------------------------------------------------------------------------------------------------------------------------------

		public boolean isDown() {
			return isDown;
		}

		public int getAction() {
			return action;
		}

		public long getEventTime() {
			return eventTime;
		}
	}

	// ------------------------------------------------------------------------------------

	/**
	 * A class that is used to store scroll offsets and scale information for objects that are managed by the multitouch controller
	 */
	public static class PositionAndScale {
		private float xOff, yOff, scale, scaleX, scaleY, angle;
		private boolean updateScale, updateScaleXY, updateAngle;

		/**
		 * Set position and optionally scale, anisotropic scale, and/or angle. Where if the corresponding "update" flag is set to false, the field's
		 * value will not be changed during a pinch operation. If the value is not being updated *and* the value is not used by the client
		 * application, then the value can just be zero. However if the value is not being updated but the value *is* being used by the client
		 * application, the value should still be specified and the update flag should be false (e.g. angle of the object being dragged should still
		 * be specified even if the program is in "resize" mode rather than "rotate" mode).
		 */
		public void set(float xOff, float yOff, boolean updateScale, float scale, boolean updateScaleXY, float scaleX, float scaleY,
				boolean updateAngle, float angle) {
			this.xOff = xOff;
			this.yOff = yOff;
			this.updateScale = updateScale;
			this.scale = scale == 0.0f ? 1.0f : scale;
			this.updateScaleXY = updateScaleXY;
			this.scaleX = scaleX == 0.0f ? 1.0f : scaleX;
			this.scaleY = scaleY == 0.0f ? 1.0f : scaleY;
			this.updateAngle = updateAngle;
			this.angle = angle;
		}

		/** Set position and optionally scale, anisotropic scale, and/or angle, without changing the "update" flags. */
		protected void set(float xOff, float yOff, float scale, float scaleX, float scaleY, float angle) {
			this.xOff = xOff;
			this.yOff = yOff;
			this.scale = scale == 0.0f ? 1.0f : scale;
			this.scaleX = scaleX == 0.0f ? 1.0f : scaleX;
			this.scaleY = scaleY == 0.0f ? 1.0f : scaleY;
			this.angle = angle;
		}

		public float getXOff() {
			return xOff;
		}

		public float getYOff() {
			return yOff;
		}

		public float getScale() {
			return !updateScale ? 1.0f : scale;
		}

		/** Included in case you want to support anisotropic scaling */
		public float getScaleX() {
			return !updateScaleXY ? 1.0f : scaleX;
		}

		/** Included in case you want to support anisotropic scaling */
		public float getScaleY() {
			return !updateScaleXY ? 1.0f : scaleY;
		}

		public float getAngle() {
			return !updateAngle ? 0.0f : angle;
		}
	}

	// ------------------------------------------------------------------------------------

	public static interface MultiTouchObjectCanvas<T> {

		/**
		 * See if there is a draggable object at the current point. Returns the object at the point, or null if nothing to drag. To start a multitouch
		 * drag/stretch operation, this routine must return some non-null reference to an object. This object is passed into the other methods in this
		 * interface when they are called.
		 * 
		 * @param touchPoint
		 *            The point being tested (in object coordinates). Return the topmost object under this point, or if dragging/stretching the whole
		 *            canvas, just return a reference to the canvas.
		 * @return a reference to the object under the point being tested, or null to cancel the drag operation. If dragging/stretching the whole
		 *         canvas (e.g. in a photo viewer), always return non-null, otherwise the stretch operation won't work.
		 */
		public T getDraggableObjectAtPoint(PointInfo touchPoint);

		/**
		 * Get the screen coords of the dragged object's origin, and scale multiplier to convert screen coords to obj coords. The job of this routine
		 * is to call the .set() method on the passed PositionAndScale object to record the initial position and scale of the object (in object
		 * coordinates) before any dragging/stretching takes place.
		 * 
		 * @param obj
		 *            The object being dragged/stretched.
		 * @param objPosAndScaleOut
		 *            Output parameter: You need to call objPosAndScaleOut.set() to record the current position and scale of obj.
		 */
		public void getPositionAndScale(T obj, PositionAndScale objPosAndScaleOut);

		/**
		 * Callback to update the position and scale (in object coords) of the currently-dragged object.
		 * 
		 * @param obj
		 *            The object being dragged/stretched.
		 * @param newObjPosAndScale
		 *            The new position and scale of the object, in object coordinates. Use this to move/resize the object before returning.
		 * @param touchPoint
		 *            Info about the current touch point, including multitouch information and utilities to calculate and cache multitouch pinch
		 *            diameter etc. (Note: touchPoint is volatile, if you want to keep any fields of touchPoint, you must copy them before the method
		 *            body exits.)
		 * @return true if setting the position and scale of the object was successful, or false if the position or scale parameters are out of range
		 *         for this object.
		 */
		public boolean setPositionAndScale(T obj, PositionAndScale newObjPosAndScale, PointInfo touchPoint);

		/**
		 * Select an object at the given point. Can be used to bring the object to top etc. Only called when first touchpoint goes down, not when
		 * multitouch is initiated. Also called with null on touch-up.
		 * 
		 * @param obj
		 *            The object being selected by single-touch, or null on touch-up.
		 * @param touchPoint
		 *            The current touch point.
		 */
		public void selectObject(T obj, PointInfo touchPoint);
	}
}
