package org.cocos2dx.lib;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.preference.PreferenceManager.OnActivityResultListener;
import android.provider.MediaStore;

public class Cocos2dxImagePicker implements OnActivityResultListener{    
    private static final int IMAGE_PICKER_ACTIVITY = 31;    //Magic Number
    private static boolean initialized = false;
    
    public static void openImage()  {
        if(!initialized) {
            initialized = true;
            Cocos2dxHelper.addOnActivityResultListener(new Cocos2dxImagePicker());
        }

        Intent intent = new Intent();
        intent.setType("image/*");
        intent.setAction(Intent.ACTION_GET_CONTENT);
              
        Cocos2dxHelper.getActivity().startActivityForResult(intent, IMAGE_PICKER_ACTIVITY);
    }

    @Override
    public boolean onActivityResult(int requestCode, int resultCode, Intent data)
    {
        if (requestCode != IMAGE_PICKER_ACTIVITY)
            return false;
        if (resultCode == Activity.RESULT_OK) {
            Uri imageUri = data.getData();  
            try {
                InputStream is = Cocos2dxHelper.getActivity().getContentResolver().openInputStream(imageUri);
                ByteArrayOutputStream byteBuffer = new ByteArrayOutputStream();
                int bufferSize = 10240;
                byte[] buffer = new byte[bufferSize];

                int len = 0;
                while ((len = is.read(buffer)) != -1) {
                    byteBuffer.write(buffer, 0, len);
                }
                is.close();
                ImagePickerResult(byteBuffer.toByteArray());
                return true;
            } catch (Exception e) {
            }
        }
        ImagePickerResult(null);
        return false;
    }

    public native void ImagePickerResult(final byte[] imagedata);
}
