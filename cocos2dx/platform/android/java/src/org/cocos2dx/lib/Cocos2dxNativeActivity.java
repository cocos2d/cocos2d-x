package org.cocos2dx.lib;

import android.app.NativeActivity;
import android.content.Intent;
import org.cocos2dx.lib.Cocos2dxHelper;
import android.preference.PreferenceManager.OnActivityResultListener;

public class Cocos2dxNativeActivity extends NativeActivity
{
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        for (OnActivityResultListener listener : Cocos2dxHelper.getOnActivityResultListeners()) {
            listener.onActivityResult(requestCode, resultCode, data);
        }

        super.onActivityResult(requestCode, resultCode, data);
    }
}
