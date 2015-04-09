package org.cocos2dx.lib;

import java.io.ByteArrayOutputStream;

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
        byte[] byteArray = {0};
        if (resultCode == Activity.RESULT_OK) {
            Uri imageUri = data.getData();  
            try {
                Bitmap bmp = MediaStore.Images.Media.getBitmap(Cocos2dxHelper.getActivity().getContentResolver(), imageUri);
                ByteArrayOutputStream stream = new ByteArrayOutputStream();
                bmp.compress(Bitmap.CompressFormat.PNG, 100, stream);
                byteArray = stream.toByteArray();
            } catch (Exception e) {
            }
        }
        ImagePickerResult(byteArray);
        return true;
    }

    public native void ImagePickerResult(final byte[] imagedata);
}
