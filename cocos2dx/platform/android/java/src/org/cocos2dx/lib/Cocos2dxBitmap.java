/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.lib;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.LinkedList;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.Align;
import android.graphics.Paint.FontMetricsInt;
import android.graphics.Rect;
import android.graphics.Typeface;
import android.text.TextPaint;
import android.text.TextUtils;
import android.util.FloatMath;
import android.util.Log;

public class Cocos2dxBitmap {
	// ===========================================================
	// Constants
	// ===========================================================

	/* The values are the same as cocos2dx/platform/CCImage.h. */
	private static final int HORIZONTALALIGN_LEFT = 1;
	private static final int HORIZONTALALIGN_RIGHT = 2;
	private static final int HORIZONTALALIGN_CENTER = 3;
	private static final int VERTICALALIGN_TOP = 1;
	private static final int VERTICALALIGN_BOTTOM = 2;
	private static final int VERTICALALIGN_CENTER = 3;

	// ===========================================================
	// Fields
	// ===========================================================

	private static Context sContext;

	// ===========================================================
	// Constructors
	// ===========================================================

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	public static void setContext(final Context pContext) {
		Cocos2dxBitmap.sContext = pContext;
	}

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	// ===========================================================
	// Methods
	// ===========================================================

	private static native void nativeInitBitmapDC(final int pWidth, final int pHeight, final byte[] pPixels);

	/**
	 * @param pWidth
	 *            the width to draw, it can be 0
	 * @param pHeight
	 *            the height to draw, it can be 0
	 */
	public static void createTextBitmap(String pString, final String pFontName, final int pFontSize, final int pAlignment, final int pWidth, final int pHeight) {
		final int horizontalAlignment = pAlignment & 0x0F;
		final int verticalAlignment = (pAlignment >> 4) & 0x0F;

		pString = Cocos2dxBitmap.refactorString(pString);
		final Paint paint = Cocos2dxBitmap.newPaint(pFontName, pFontSize, horizontalAlignment);

		final TextProperty textProperty = Cocos2dxBitmap.computeTextProperty(pString, pWidth, pHeight, paint);

		final int bitmapTotalHeight = (pHeight == 0 ? textProperty.mTotalHeight : pHeight);

		final Bitmap bitmap = Bitmap.createBitmap(textProperty.mMaxWidth, bitmapTotalHeight, Bitmap.Config.ARGB_8888);
		final Canvas canvas = new Canvas(bitmap);

		/* Draw string. */
		final FontMetricsInt fontMetricsInt = paint.getFontMetricsInt();
		int x = 0;
		int y = Cocos2dxBitmap.computeY(fontMetricsInt, pHeight, textProperty.mTotalHeight, verticalAlignment);
		final String[] lines = textProperty.mLines;
		for (final String line : lines) {
			x = Cocos2dxBitmap.computeX(line, textProperty.mMaxWidth, horizontalAlignment);
			canvas.drawText(line, x, y, paint);
			y += textProperty.mHeightPerLine;
		}

		Cocos2dxBitmap.initNativeObject(bitmap);
	}

	private static Paint newPaint(final String pFontName, final int pFontSize, final int pHorizontalAlignment) {
		final Paint paint = new Paint();
		paint.setColor(Color.WHITE);
		paint.setTextSize(pFontSize);
		paint.setAntiAlias(true);

		/* Set type face for paint, now it support .ttf file. */
		if (pFontName.endsWith(".ttf")) {
			try {
				final Typeface typeFace = Cocos2dxTypefaces.get(Cocos2dxBitmap.sContext, pFontName);
				paint.setTypeface(typeFace);
			} catch (final Exception e) {
				Log.e("Cocos2dxBitmap", "error to create ttf type face: " + pFontName);

				/* The file may not find, use system font. */
				paint.setTypeface(Typeface.create(pFontName, Typeface.NORMAL));
			}
		} else {
			paint.setTypeface(Typeface.create(pFontName, Typeface.NORMAL));
		}

		switch (pHorizontalAlignment) {
			case HORIZONTALALIGN_CENTER:
				paint.setTextAlign(Align.CENTER);
				break;
			case HORIZONTALALIGN_RIGHT:
				paint.setTextAlign(Align.RIGHT);
				break;
			case HORIZONTALALIGN_LEFT:
			default:
				paint.setTextAlign(Align.LEFT);
				break;
		}

		return paint;
	}

	private static TextProperty computeTextProperty(final String pString, final int pWidth, final int pHeight, final Paint pPaint) {
		final FontMetricsInt fm = pPaint.getFontMetricsInt();
		final int h = (int) Math.ceil(fm.bottom - fm.top);
		int maxContentWidth = 0;

		final String[] lines = Cocos2dxBitmap.splitString(pString, pWidth, pHeight, pPaint);

		if (pWidth != 0) {
			maxContentWidth = pWidth;
		} else {
			/* Compute the max width. */
			int temp = 0;
			for (final String line : lines) {
				temp = (int) FloatMath.ceil(pPaint.measureText(line, 0, line.length()));
				if (temp > maxContentWidth) {
					maxContentWidth = temp;
				}
			}
		}

		return new TextProperty(maxContentWidth, h, lines);
	}

	private static int computeX(final String pText, final int pMaxWidth, final int pHorizontalAlignment) {
		int ret = 0;

		switch (pHorizontalAlignment) {
			case HORIZONTALALIGN_CENTER:
				ret = pMaxWidth / 2;
				break;
			case HORIZONTALALIGN_RIGHT:
				ret = pMaxWidth;
				break;
			case HORIZONTALALIGN_LEFT:
			default:
				break;
		}

		return ret;
	}

	private static int computeY(final FontMetricsInt pFontMetricsInt, final int pConstrainHeight, final int pTotalHeight, final int pVerticalAlignment) {
		int y = -pFontMetricsInt.top;

		if (pConstrainHeight > pTotalHeight) {
			switch (pVerticalAlignment) {
				case VERTICALALIGN_TOP:
					y = -pFontMetricsInt.top;
					break;
				case VERTICALALIGN_CENTER:
					y = -pFontMetricsInt.top + (pConstrainHeight - pTotalHeight) / 2;
					break;
				case VERTICALALIGN_BOTTOM:
					y = -pFontMetricsInt.top + (pConstrainHeight - pTotalHeight);
					break;
				default:
					break;
			}
		}

		return y;
	}

	/*
	 * If maxWidth or maxHeight is not 0, split the string to fix the maxWidth and maxHeight.
	 */
	private static String[] splitString(final String pString, final int pMaxWidth, final int pMaxHeight, final Paint pPaint) {
		final String[] lines = pString.split("\\n");
		String[] ret = null;
		final FontMetricsInt fm = pPaint.getFontMetricsInt();
		final int heightPerLine = (int) Math.ceil(fm.bottom - fm.top);
		final int maxLines = pMaxHeight / heightPerLine;

		if (pMaxWidth != 0) {
			final LinkedList<String> strList = new LinkedList<String>();
			for (final String line : lines) {
				/* The width of line is exceed maxWidth, should divide it into two or more lines. */
				final int lineWidth = (int) FloatMath.ceil(pPaint.measureText(line));
				if (lineWidth > pMaxWidth) {
					strList.addAll(Cocos2dxBitmap.divideStringWithMaxWidth(line, pMaxWidth, pPaint));
				} else {
					strList.add(line);
				}

				/* Should not exceed the max height. */
				if (maxLines > 0 && strList.size() >= maxLines) {
					break;
				}
			}

			/* Remove exceeding lines. */
			if (maxLines > 0 && strList.size() > maxLines) {
				while (strList.size() > maxLines) {
					strList.removeLast();
				}
			}

			ret = new String[strList.size()];
			strList.toArray(ret);
		} else if (pMaxHeight != 0 && lines.length > maxLines) {
			/* Remove exceeding lines. */
			final LinkedList<String> strList = new LinkedList<String>();
			for (int i = 0; i < maxLines; i++) {
				strList.add(lines[i]);
			}
			ret = new String[strList.size()];
			strList.toArray(ret);
		} else {
			ret = lines;
		}

		return ret;
	}

	private static LinkedList<String> divideStringWithMaxWidth(final String pString, final int pMaxWidth, final Paint pPaint) {
		final int charLength = pString.length();
		int start = 0;
		int tempWidth = 0;
		final LinkedList<String> strList = new LinkedList<String>();

		/* Break a String into String[] by the width & should wrap the word. */
		for (int i = 1; i <= charLength; ++i) {
			tempWidth = (int) FloatMath.ceil(pPaint.measureText(pString, start, i));
			if (tempWidth >= pMaxWidth) {
				final int lastIndexOfSpace = pString.substring(0, i).lastIndexOf(" ");

				if (lastIndexOfSpace != -1 && lastIndexOfSpace > start) {
					/* Should wrap the word. */
					strList.add(pString.substring(start, lastIndexOfSpace));
					i = lastIndexOfSpace;
				} else {
					/* Should not exceed the width. */
					if (tempWidth > pMaxWidth) {
						strList.add(pString.substring(start, i - 1));
						/* Compute from previous char. */
						--i;
					} else {
						strList.add(pString.substring(start, i));
					}
				}

				/* Remove spaces at the beginning of a new line. */
				while (pString.indexOf(i) == ' ') {
					++i;
				}

				start = i;
			}
		}

		/* Add the last chars. */
		if (start < charLength) {
			strList.add(pString.substring(start));
		}

		return strList;
	}

	private static String refactorString(final String pString) {
		/* Avoid error when content is "". */
		if (pString.compareTo("") == 0) {
			return " ";
		}

		/*
		 * If the font of "\n" is "" or "\n", insert " " in front of it. For example: "\nabc" -> " \nabc" "\nabc\n\n" -> " \nabc\n \n".
		 */
		final StringBuilder strBuilder = new StringBuilder(pString);
		int start = 0;
		int index = strBuilder.indexOf("\n");
		while (index != -1) {
			if (index == 0 || strBuilder.charAt(index - 1) == '\n') {
				strBuilder.insert(start, " ");
				start = index + 2;
			} else {
				start = index + 1;
			}

			if (start > strBuilder.length() || index == strBuilder.length()) {
				break;
			}

			index = strBuilder.indexOf("\n", start);
		}

		return strBuilder.toString();
	}

	private static void initNativeObject(final Bitmap pBitmap) {
		final byte[] pixels = Cocos2dxBitmap.getPixels(pBitmap);
		if (pixels == null) {
			return;
		}

		Cocos2dxBitmap.nativeInitBitmapDC(pBitmap.getWidth(), pBitmap.getHeight(), pixels);
	}

	private static byte[] getPixels(final Bitmap pBitmap) {
		if (pBitmap != null) {
			final byte[] pixels = new byte[pBitmap.getWidth() * pBitmap.getHeight() * 4];
			final ByteBuffer buf = ByteBuffer.wrap(pixels);
			buf.order(ByteOrder.nativeOrder());
			pBitmap.copyPixelsToBuffer(buf);
			return pixels;
		}

		return null;
	}

	private static int getFontSizeAccordingHeight(int height) {
		Paint paint = new Paint();
		Rect bounds = new Rect();

		paint.setTypeface(Typeface.DEFAULT);
		int incr_text_size = 1;
		boolean found_desired_size = false;

		while (!found_desired_size) {

			paint.setTextSize(incr_text_size);
			String text = "SghMNy";
			paint.getTextBounds(text, 0, text.length(), bounds);

			incr_text_size++;

			if (height - bounds.height() <= 2) {
				found_desired_size = true;
			}
			Log.d("font size", "incr size:" + incr_text_size);
		}
		return incr_text_size;
	}

	private static String getStringWithEllipsis(String pString, float width, float fontSize) {
		if (TextUtils.isEmpty(pString)) {
			return "";
		}

		TextPaint paint = new TextPaint();
		paint.setTypeface(Typeface.DEFAULT);
		paint.setTextSize(fontSize);

		return TextUtils.ellipsize(pString, paint, width, TextUtils.TruncateAt.END).toString();
	}

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================

	private static class TextProperty {
		/** The max width of lines. */
		private final int mMaxWidth;
		/** The height of all lines. */
		private final int mTotalHeight;
		private final int mHeightPerLine;
		private final String[] mLines;

		TextProperty(final int pMaxWidth, final int pHeightPerLine, final String[] pLines) {
			this.mMaxWidth = pMaxWidth;
			this.mHeightPerLine = pHeightPerLine;
			this.mTotalHeight = pHeightPerLine * pLines.length;
			this.mLines = pLines;
		}
	}
}
