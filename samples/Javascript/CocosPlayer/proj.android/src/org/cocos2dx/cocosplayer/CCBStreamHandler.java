package org.cocos2dx.cocosplayer;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import java.util.Arrays;
import java.io.IOException;
import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;
import android.content.ContextWrapper;
import android.content.Context;
import android.os.Environment;
import java.io.InputStream;
import com.dd.plist.NSDictionary;
import com.dd.plist.NSData;
import com.dd.plist.UID;
import com.dd.plist.PropertyListParser;
import com.dd.plist.BinaryPropertyListParser;
import com.dd.plist.BinaryPropertyListWriter;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class CCBStreamHandler {

    private static String resolution = "xlarge";
    public static final String TAG = CocosPlayerSocket.class.getSimpleName();
    
    public static NSDictionary parseBinaryPLIST(InputStream is) {
	try {

	    NSDictionary rootDict = (NSDictionary)BinaryPropertyListParser.parse(is);
	    String name = rootDict.objectForKey("cmd").toString();
	    Log.i(TAG, "Cmd: "+name);

	    return rootDict;	    

	} catch(Exception ex) {
	    Log.i(TAG, "ERROR: "+ex.toString());
	    ex.printStackTrace();
	}
	return null;
    }

    public static NSDictionary parseBinaryPLIST(byte[] is) {
	try {
	    NSDictionary rootDict = (NSDictionary)BinaryPropertyListParser.parse(is);
	    String name = rootDict.objectForKey("cmd").toString();
	    Log.i(TAG, "Cmd: "+name);
	    return rootDict;

	} catch(Exception ex) {
	    Log.i(TAG, "Error parsing BinaryPLIST: "+ex.toString());
	    ex.printStackTrace();
	}
	return null;
    }

    private static boolean isKeepAlive(byte[] header) {
	for(int i = 0; i < header.length; ++i) {
	    if((header[i] & 0xff) != 0) {
		return false;
	    }
	}
	return true;
    }

    public static int processHeader(byte[] header) {

	int length = 0;

	if(isKeepAlive(header)) {
	    Log.v(TAG, "Keepalive Recieved");
	    return length;
	}

	try {	    
	    ByteBuffer bb = ByteBuffer.wrap(header);
	    bb.order(ByteOrder.BIG_ENDIAN); // CocosBuilder transmits in Little Endian
	    
	    length = bb.getInt();

	} catch (Exception e) {
	    Log.i(TAG, "Exception: "+e.toString());
	    e.printStackTrace();
	}

	Log.i(TAG, "Payload Length: "+length);
	return length;
    }


    public static String getDeviceInfo() {
	try {
	    NSDictionary root = new NSDictionary();
	    root.put("cmd", "deviceinfo");
	    root.put("devicename", android.os.Build.MODEL);
	    root.put("devicetype", "Android");
	    root.put("preferredresourcetype", resolution);
	    String payload = root.toXMLPropertyList();
	    
	    //		String data = new String(header, 0 , header.length);
	    return payload;
	} catch(Exception e) {
	}
	return null;
    }

    public static void setDeviceResolution(String res) {
	CocosPlayerSocket server = new CocosPlayerSocket();
	Log.i(TAG, "Starting with resolution: "+res);
	resolution = res;
	server.setContext(CocosPlayer.c);
	server.createServer();
    }

}