package org.cocos2dx.lib;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.FontMetricsInt;

public class Cocos2dxBitmap{
    public static void createTextBitmap(String content, int fontSize){
    	Paint paint = new Paint();
    	paint.setColor(Color.WHITE);
        paint.setTextSize(fontSize);
        
        FontMetricsInt fm = paint.getFontMetricsInt();
        int h = (int)Math.ceil(fm.descent - fm.ascent) + 2;
        int w = (int)Math.ceil(paint.measureText(content, 0, content.length()));
        
        Bitmap bitmap = Bitmap.createBitmap(w, h, Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(bitmap);
        canvas.drawText(content, 0, h, paint);
        
        initNativeObject(bitmap);
    }
    
    private static void initNativeObject(Bitmap bitmap){
    	byte[] pixels = getPixels(bitmap);
    	if (pixels == null){
    		return;
    	}
    	
    	nativeInitBitmapDC(bitmap.getWidth(), bitmap.getHeight(), pixels);
    }
    
    private static byte[] getPixels(Bitmap bitmap){
    	if (bitmap != null){
    		byte[] pixels = new byte[bitmap.getWidth() * bitmap.getHeight() * 4];
    		ByteBuffer buf = ByteBuffer.wrap(pixels);
    		buf.order(ByteOrder.nativeOrder());
    		bitmap.copyPixelsToBuffer(buf);
    		return pixels;
    	}
    	
    	return null;
    }
    
    private static native void nativeInitBitmapDC(int width, int height, byte[] pixels);
}
