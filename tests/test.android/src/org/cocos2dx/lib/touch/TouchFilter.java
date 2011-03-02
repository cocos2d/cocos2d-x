package org.cocos2dx.lib.touch;

import android.content.Context;
import android.view.MotionEvent;

public abstract class TouchFilter {

    public abstract boolean updateTouch(MotionEvent event);
    
    public boolean supportsMultitouch(Context context) {
        return false;
    }
}