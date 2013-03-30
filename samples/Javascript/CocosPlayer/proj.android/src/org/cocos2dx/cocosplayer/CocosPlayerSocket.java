package org.cocos2dx.cocosplayer;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.cocosplayer.CocosPlayer;

import java.util.Arrays;
import java.io.BufferedReader;
import java.io.PrintWriter;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;
import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;
import android.content.ContextWrapper;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.os.Environment;
import android.os.AsyncTask;
import java.io.OutputStream;

import java.io.InputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;

import com.dd.plist.NSArray;
import com.dd.plist.NSDictionary;
import com.dd.plist.NSData;
import com.dd.plist.UID;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class CocosPlayerSocket {

	public static final String TAG = CocosPlayerSocket.class.getSimpleName();
	private static boolean running = false;
	private static Context cw = null;

	private HashMap<Socket, String> mConnections;
	private static ServerSocket server;
	private static int mPairingCode = -1;
	private static CocosPlayerPresence presence = null;

	private void runCCB() {
		Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable() {
			@Override
			public void run() {
				nativeRunCCB();
			}
		});
	}

	private void handleConnected() {
		nativeConnected();
	}

	private void handleDisconnected() {
		nativeDisconnected();
	}

	private void stopCCB() {
		nativeStopCCB();
	}

	private void runScript(String script) {
		nativeRunScript(script);
	}

	private static native void nativeRunCCB();
	private static native void nativeConnected();
	private static native void nativeDisconnected();
	private static native void nativeStopCCB();
	private static native void nativeRunScript(final String script);

	private static void setOrientation(String isPortrait) {
		CocosPlayer.setOrientation(isPortrait.equalsIgnoreCase("true") ? 
				ActivityInfo.SCREEN_ORIENTATION_PORTRAIT : ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
	}
	
	private void switchCmd(NSDictionary data) {
		try {
			String cmd = data.objectForKey("cmd").toString();
			String [] keys = data.allKeys();
			for(int i =0 ; i < keys.length; ++i ) {
			}
			if(cmd.equalsIgnoreCase("zip")) {
				cleanCache();
				try {
					Log.i(TAG, "Size of NSDATA payload: "+((NSData)data.objectForKey("data")).bytes().length);
					CCBFileUtilsHelper.unzipCCB(((NSData)data.objectForKey("data")).bytes(), cw);
				} catch(Exception e) {
					Log.i(TAG, "Size of UID payload: "+((UID)data.objectForKey("data")).getBytes().length);
					CCBFileUtilsHelper.unzipCCB(((UID)data.objectForKey("data")).getBytes(), cw);
				}
			} else if(cmd.equalsIgnoreCase("run")) {
				runCCB();
			} else if(cmd.equalsIgnoreCase("stop")) {
				stopCCB();
			} else if(cmd.equalsIgnoreCase("script")) {
				runScript(data.objectForKey("script").toString());
			} else if(cmd.equalsIgnoreCase("settings")) {
				NSArray orient = (NSArray)data.objectForKey("orientations");
				setOrientation(orient.objectAtIndex(0).toString());
			}
		} catch(Exception e) {
			Log.i(TAG, "JSON Error: "+e.toString());
			e.printStackTrace();
		}
	}

	private static void cleanDir(File dir) {

		long bytesDeleted = 0;
		File[] files = dir.listFiles();

		for (File file : files) {
			if(file.isDirectory()) {
				cleanDir(file);
				continue;
			}
			Log.i(TAG, "Deleting file: "+file.getName());
			bytesDeleted += file.length();
			file.delete();
		}
	}

	public static void cleanCache() {
		File path = new File(CCBFileUtilsHelper.getBaseDirectory(cw));
		cleanDir(path);
	}

	private void parsePayload(byte[] b) {
		try {
			NSDictionary rootDict = CCBStreamHandler.parseBinaryPLIST(b);
			switchCmd(rootDict);
		} catch(Exception e) {
			Log.d(TAG, "Error writing payload to file");
		}
	}

	private class StreamHandler extends AsyncTask<ServerSocket, ByteArrayOutputStream, Void> {

		private void processPayload(final Socket client,final int length) {

			try {
				final ByteArrayOutputStream buffer = new ByteArrayOutputStream();

				int dataLength = ((length/4) > 16000) ? 16000 : (length/4);
				byte[] data = new byte[dataLength];

				int totalRead = 0, nRead;
				while ((nRead = client.getInputStream().read(data, 0, ((length - totalRead) > data.length) ? data.length : (length - totalRead))) != -1 && totalRead < length) {
					totalRead += nRead;
					buffer.write(data, 0, nRead);
				}

				Log.i(TAG, "Parsing payload. Totaly bytes read: "+totalRead);

				data = null;

				publishProgress(buffer);

				buffer.flush();
				buffer.close();

			} catch (Exception e) {
				Log.i(TAG, "Exception: "+e.toString());
				e.printStackTrace();
			}

		}

		protected Void doInBackground(ServerSocket... args) {
			try {

				handleDisconnected();
				ServerSocket server = args[0];
				while(true) {

					Socket client = server.accept();

					Log.i(TAG,"New connection from "+ client.getInetAddress());
					handleConnected();

					if(client == null) {
						Log.i(TAG, "Client null");
						break;
					}
					try {

						// Send deviceInfo and filelist
						PrintWriter out = new PrintWriter(client.getOutputStream(), true);
						CCBStreamHandler.sendString(CCBStreamHandler.getDeviceInfo(), client, out);
						CCBStreamHandler.sendString(CCBStreamHandler.getFileSystem(), client, out);
						//out.close();

						// Process CocosBuilder input data stream
						processStream(client);

					} catch (Exception e) {
						Log.i(TAG, "Server socket start fail!");
						e.printStackTrace();		
					}
				}
				Log.i(TAG, "Server Closing");
				server.close();

			} catch(Exception e) {
			}
			return null;
		}

		private void processStream(Socket client) {
			try {

				int nRead, count = 0;

				byte[] header = new byte[4];

				while ((nRead = client.getInputStream().read(header, 0, header.length)) != -1) {

					int lengthToRead = CCBStreamHandler.processHeader(header);

					if(lengthToRead > 0) {
						processPayload(client, lengthToRead);
					}
				}

			} catch (Exception e) {
				Log.i(TAG, "Exception: "+e.toString());
				e.printStackTrace();
			}
		}

		/** The system calls this to perform work in the UI thread and delivers
		 * the result from doInBackground() */
		protected void onPostExecute() {
			try {
				server.close();
			} catch(Exception e) {
			}
		}

		protected void onProgressUpdate(ByteArrayOutputStream... buffer) {
			try {
				byte[] b = buffer[0].toByteArray();
				buffer[0].close();
				System.gc();
				parsePayload(b);
			} catch(Exception e) {
			}
		}
	}


	public void setContext(Context c) {
		cw = c;
	}

	public static void setPairingCode(int code) {
		//mPresenceAsync.cancel(true);
		if(presence != null) {
			presence.unregisterService();
		}
		mPairingCode = code;


		presence = new CocosPlayerPresence();
		Log.i("CocosPlayerSocket", "Registering Bonjour on Port: "+server.getLocalPort()+" With pairing code: "+code);
		presence.setContext(cw);
		presence.startPresence(server.getLocalPort(), mPairingCode);

		//new PresenceStarter().execute(server.getLocalPort(), mPairingCode);
	}

	public void createServer() {

		Log.i(TAG, "Creating server "+running);
		try {
			server = new ServerSocket(0);
			Log.i(TAG, "IP " + server.getInetAddress()
					+ ", running on port " + server.getLocalPort());

			presence = new CocosPlayerPresence();
			presence.setContext(cw);
			presence.startPresence(server.getLocalPort(), mPairingCode);
			new StreamHandler().execute(server);

		} catch(Exception e) {
		}
	}

}