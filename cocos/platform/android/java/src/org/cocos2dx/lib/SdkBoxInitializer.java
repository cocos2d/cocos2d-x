package org.cocos2dx.lib;

import android.content.Context;
import android.content.Intent;
import java.lang.Class;
import java.lang.reflect.Method;

public class SdkBoxInitializer {
    private boolean isSdkBoxInClassPath = false;
    private Class sdkBoxClass;

    public SdkBoxInitializer() {
        try {
            sdkBoxClass = Class.forName("com.sdkbox.plugin.SDKBox");
            isSdkBoxInClassPath = true;
        } catch (Exception ex) {

        }
    }

    public void init(Context context) {
        if (isSdkBoxInClassPath) {
            try {
                Method method = sdkBoxClass.getMethod("init", Context.class);
                method.invoke(null, context);
            } catch (Exception ex) {

            }
        }
    }

    public void onStart() {
        if (isSdkBoxInClassPath) {
            try {
                Method method = sdkBoxClass.getMethod("onStart");
                method.invoke(null, new Object[]{});
            } catch (Exception ex) {

            }
        }
    }

    public void onStop() {
        if (isSdkBoxInClassPath) {
            try {
                Method method = sdkBoxClass.getMethod("onStop");
                method.invoke(null, new Object[]{});
            } catch (Exception ex) {

            }
        }
    }

    public void onResume() {
        if (isSdkBoxInClassPath) {
            try {
                Method method = sdkBoxClass.getMethod("onResume");
                method.invoke(null, new Object[]{});
            } catch (Exception ex) {

            }
        }
    }

    public void onPause() {
        if (isSdkBoxInClassPath) {
            try {
                Method method = sdkBoxClass.getMethod("onPause");
                method.invoke(null, new Object[]{});
            } catch (Exception ex) {

            }
        }
    }

    public boolean onBackPressed() {
        boolean result = false;
        if (isSdkBoxInClassPath) {
            try {
                Method method = sdkBoxClass.getMethod("onBackPressed");
                method.invoke(null, new Object[]{});
                result = true;
            } catch (Exception ex) {

            }
        }
        return result;
    }

    public boolean onActivityResult(int requestCode, int resultCode, Intent data) {
        boolean result = false;
        if (isSdkBoxInClassPath) {
            try {
                Method method = sdkBoxClass.getMethod("onActivityResult", Integer.class, Integer.class, Intent.class);
                method.invoke(null, requestCode, resultCode, data);
                result = true;
            } catch (Exception ex) {

            }
        }
        return result;
    }
}
