package org.cocos2dx.cocosplayer;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxHelper;

import java.util.Arrays;
import java.util.Enumeration;
import java.io.IOException;
import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;
import android.content.ContextWrapper;
import android.content.Context;
import android.os.Environment;
import java.io.OutputStream;
import java.util.zip.ZipInputStream;
import java.util.zip.ZipEntry;

import java.util.zip.ZipFile;
import java.util.zip.ZipException;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.FileOutputStream;
import java.io.ByteArrayInputStream;
import java.io.File;

public class CCBFileUtilsHelper {

	public static final String TAG = CocosPlayerSocket.class.getSimpleName();
	private static boolean isValid(final File file) {

		ZipFile zipfile = null;
		try {
			zipfile = new ZipFile(file);
			return true;
		} catch (ZipException e) {
			Log.i(TAG, "ERROR: "+e.toString());
			return false;
		} catch (IOException e) {
			Log.i(TAG, "ERROR: "+e.toString());
			return false;
		} finally {
			try {
				if (zipfile != null) {
					zipfile.close();
					zipfile = null;
				}
			} catch (IOException e) {
				Log.i(TAG, "ERROR: "+e.toString());
			}
		}
	}

	private static boolean containsDirectory(String name) {
		if(name.contains("/")) {
			return true;
		} return false;
	}

	private static void unzip(InputStream is, Context cw) { 
		try  { 

			File path = new File(CCBFileUtilsHelper.getBaseDirectory(cw));

			ZipInputStream zin = new ZipInputStream(is); 
			ZipEntry ze = null; 
			byte[] buffer = new byte[1024];
			int length;
			while ((ze = zin.getNextEntry()) != null) { 
				Log.v(TAG, "Unzipping " + ze.getName()); 

				if(ze.isDirectory()) { 
					_dirChecker(path, ze.getName()); 
				} else { 
					File fileToWrite = new File(path, ze.getName());
					File parent = fileToWrite.getParentFile();
					if(!parent.exists() && !parent.mkdirs()){
						throw new IllegalStateException("Couldn't create dir: " + parent);
					}
					FileOutputStream fout = new FileOutputStream(fileToWrite); 

					while ((length = zin.read(buffer))>0) {
						fout.write(buffer, 0, length);
					} 
					zin.closeEntry(); 
					fout.close(); 
				} 

			} 
			zin.close(); 
		} catch(Exception e) { 
			Log.e(TAG, "unzip", e); 
		} 

	} 


	private static void _dirChecker(File path, String dir) { 

		File f = new File(path, dir); 

		if(!f.isDirectory()) { 
			f.mkdirs(); 
		} 
	} 

	private static void list( String path ) {

		File root = new File( path );
		File[] list = root.listFiles();

		for ( File f : list ) {
			if ( f.isDirectory() ) {
				list( f.getAbsolutePath() );
				Log.i(TAG, "Dir:" + f.getAbsoluteFile() );
			}
			else {
				Log.i(TAG, "File:" + f.getAbsoluteFile() );
			}
		}
	}

	public static void unzipCCB(byte[] data, Context cw) {
		String zipname = "ccb.zip";
		File path = new File(CCBFileUtilsHelper.getBaseDirectory(cw));
		unzip(new ByteArrayInputStream(data), cw);
	}

	public static String getBaseDirectory(Context cw) {
		return Cocos2dxHelper.getCocos2dxWritablePath();
	}

	private static File getBasePath() {
		return android.os.Environment.getExternalStorageDirectory();
	}

}
