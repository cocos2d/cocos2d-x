package org.cocos2dx.lib;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.graphics.Paint.Align;
import android.graphics.Paint.FontMetricsInt;

public class Cocos2dxBitmap{
	/*
	 * The values are the same as cocos2dx/platform/CCImage.h.
	 * I think three alignments are ok.
	 */
	private static final int ALIGNCENTER = 0x33;
	private static final int ALIGNLEFT	 = 0x31;
	private static final int ALIGNRIGHT	 = 0x32;
	
    public static void createTextBitmap(String content, String fontName, 
    		int fontSize, int alignment){
    	// avoid error when content is ""
    	if (content.compareTo("") == 0){
    		content = " ";
    	}
    	
    	Paint paint = newPaint(fontName, fontSize, alignment);
    	
    	TextProperty textProperty = getTextWidthAndHeight(content, paint);      	
      
        // draw text to bitmap
        Bitmap bitmap = Bitmap.createBitmap(textProperty.maxWidth, 
        		textProperty.height * textProperty.numberLines, Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(bitmap);
        
        // draw string
        FontMetricsInt fm = paint.getFontMetricsInt();
        int x = 0;
        int y = -fm.ascent;
        String[] lines = content.split("\\n");
        for (String line : lines){
        	x = computeX(paint, line, textProperty.maxWidth, alignment);
        	canvas.drawText(line, x, y, paint);
        	y += textProperty.height;
        }
        
        initNativeObject(bitmap);
    }
    
    private static int computeX(Paint paint, String content, int w, int alignment){
    	int ret = 0;
    	
    	switch (alignment){
    	case ALIGNCENTER:
    		ret = w / 2;
    		break;
    	
        // ret = 0
    	case ALIGNLEFT:   		
    		break;
    		
    	case ALIGNRIGHT:
    		ret = w;
    		break;
    	
    	// default is align left ret = 0
    	default:
    		break;
    	}
    	
    	return ret;
    }
    
    private static class TextProperty{
    	int maxWidth;
    	int height;
    	int numberLines;

    	TextProperty(int w, int h, int n){
    		this.maxWidth = w;
    		this.height = h;
    		this.numberLines = n;
    	}
    }
    
    private static TextProperty getTextWidthAndHeight(String content, Paint paint){              
        FontMetricsInt fm = paint.getFontMetricsInt();
        int h = (int)Math.ceil(fm.descent - fm.ascent);
        
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
        
        return new TextProperty(w, h, lines.length);
    }
    
    private static Paint newPaint(String fontName, int fontSize, int alignment){
    	Paint paint = new Paint();
    	paint.setColor(Color.WHITE);
        paint.setTextSize(fontSize);
        paint.setTypeface(Typeface.create(fontName, Typeface.NORMAL));
        paint.setAntiAlias(true);
        
        switch (alignment){
    	case ALIGNCENTER:
    		paint.setTextAlign(Align.CENTER);
    		break;
    	
    	case ALIGNLEFT:  
    		paint.setTextAlign(Align.LEFT);
    		break;
    		
    	case ALIGNRIGHT:
    		paint.setTextAlign(Align.RIGHT);
    		break;
    	
    	default:
    		paint.setTextAlign(Align.LEFT);
    		break;
    	}
        
        return paint;
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
