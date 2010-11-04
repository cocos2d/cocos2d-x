package org.cocos2dx.lib;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.FontMetricsInt;

public class Cocos2dxJNI {
    public static Bitmap createTextBitmap(String content, int fontSize){
    	Paint paint = new Paint();
    	paint.setColor(Color.WHITE);
        paint.setTextSize(fontSize);
        
        FontMetricsInt fm = paint.getFontMetricsInt();
        int h = (int)Math.ceil(fm.descent - fm.ascent) + 2;
        int w = (int)Math.ceil(paint.measureText(content, 0, content.length()));
        
        Bitmap bitmap = Bitmap.createBitmap(w, h, Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(bitmap);
        canvas.drawText(content, 0, h, paint);
        
		return bitmap;   	
    }
}
