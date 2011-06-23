package org.cocos2dx.lib;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.FontMetricsInt;
import android.view.Gravity;
import android.widget.TextView;

public class Cocos2dxBitmap{
	/*
	 * The values are the same as cocos2dx/platform/CCImage.h.
	 * I think three alignments are ok.
	 */
	private static final int ALIGNCENTER = 0x33;
	private static final int ALIGNLEFT	 = 0x31;
	private static final int ALIGNRIGHT	 = 0x32;
	
    public static void createTextBitmap(String content, int fontSize, int alignment){
    	TextProperty textProperty = getTextWidthAndHeight(content, fontSize);   
    	
        // create TextView and set corresponding property
        TextView tv = new TextView(Cocos2dxActivity.context);
    	tv.setText(content);
        tv.measure(textProperty.maxWidth, textProperty.height);
        tv.setTextSize(fontSize);
        tv.layout(0, 0, textProperty.maxWidth, textProperty.height);
        setTextViewAlignment(tv, alignment);
      
        // draw text to bitmap
        Bitmap bitmap = Bitmap.createBitmap(textProperty.maxWidth, textProperty.height, 
        		Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(bitmap);
        tv.draw(canvas);
        
        initNativeObject(bitmap);
    }
    
    private static void setTextViewAlignment(TextView tv, int alignment){
    	switch (alignment){
    	case ALIGNCENTER:
    		tv.setGravity(Gravity.CENTER);
    		break;
    		
    	case ALIGNLEFT:
    		tv.setGravity(Gravity.LEFT);
    		break;
    		
    	case ALIGNRIGHT:
    		tv.setGravity(Gravity.RIGHT);
    		break;
    		
    	default:
    		tv.setGravity(Gravity.CENTER);
    		break;
    	}
    }
    
    private static class TextProperty{
    	int maxWidth;
    	int height;

    	TextProperty(int w, int h){
    		this.maxWidth = w;
    		this.height = h;
    	}
    }
    
    private static TextProperty getTextWidthAndHeight(String content, int fontSize){
    	Paint paint = new Paint();
    	paint.setColor(Color.WHITE);
        paint.setTextSize(fontSize);
        
        FontMetricsInt fm = paint.getFontMetricsInt();
        int h = (int)Math.ceil(fm.descent - fm.ascent) + 2;
        
        String[] lines = content.split("\\n");
        
        /*
         * Compute the max width
         */
        int w = 0;
        int temp = 0;
        for (String line : lines){
        	temp = (int)Math.ceil(paint.measureText(line, 0, line.length()));
        	if (temp > w){
        		w = temp;
        	}
        }
        
        return new TextProperty(w, h * lines.length);
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
