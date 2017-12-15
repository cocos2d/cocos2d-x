/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 
package org.cocos2dx.plugin;

import java.io.File;
import java.util.Arrays;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.util.Log;

import com.facebook.FacebookException;
import com.facebook.model.GraphObject;
import com.facebook.model.OpenGraphAction;
import com.facebook.model.OpenGraphObject;
import com.facebook.widget.FacebookDialog;
import com.facebook.widget.FacebookDialog.MessageDialogFeature;
import com.facebook.widget.FacebookDialog.OpenGraphActionDialogFeature;
import com.facebook.widget.FacebookDialog.OpenGraphMessageDialogFeature;
import com.facebook.widget.FacebookDialog.PendingCall;
import com.facebook.widget.FacebookDialog.ShareDialogBuilder;
import com.facebook.widget.FacebookDialog.ShareDialogFeature;
import com.facebook.widget.WebDialog;
import com.facebook.widget.WebDialog.FeedDialogBuilder;
import com.facebook.widget.WebDialog.OnCompleteListener;
import com.facebook.widget.WebDialog.RequestsDialogBuilder;
import com.facebook.Settings;

public class ShareFacebook implements InterfaceShare{

	private static Activity mContext = null;
	private static InterfaceShare mAdapter = null;
	private static boolean bDebug = true;
	private final static String LOG_TAG = "ShareFacebook";
	
	protected static void LogE(String msg, Exception e) {
        Log.e(LOG_TAG, msg, e);
        e.printStackTrace();
    }

    protected static void LogD(String msg) {
        if (bDebug) {
            Log.d(LOG_TAG, msg);
        }
    }
    
    public ShareFacebook(Context context) {
		mContext = (Activity)context;		
		mAdapter = this;
		FacebookWrapper.setDialogCallback(new FacebookDialogCallback());
	}
    
	@Override
	public void configDeveloperInfo(Hashtable<String, String> cpInfo) {
		LogD("not supported in Facebook pluign");
	}

	@Override
	public void share(final Hashtable<String, String> cpInfo) {
		LogD("share invoked " + cpInfo.toString());
		if (networkReachable()) {
			PluginWrapper.runOnMainThread(new Runnable() {
				@Override
				public void run() {
					String caption = cpInfo.get("title");
					String url = cpInfo.get("link");
					String text = cpInfo.get("description");
					String picture = cpInfo.get("imageUrl");
					FacebookDialog shareDialog = new FacebookDialog.ShareDialogBuilder(mContext)
						.setCaption(caption)
						.setPicture(picture)
						.setLink(url)
						.setDescription(text)
				        .build();
					
					FacebookWrapper.track(shareDialog.present());
				}
			});
		}		
	}

	@Override
	public void setDebugMode(boolean debug) {
		bDebug = debug;		
	}

	@Override
	public String getPluginVersion() {
		return "0.2.0";
	}

	@Override
	public String getSDKVersion() {
		return Settings.getSDKVersion();
	}

	public void setSDKVersion(String version){
        Settings.setSDKVersion(version);
    }

	private boolean networkReachable() {
		boolean bRet = false;
		try {
			ConnectivityManager conn = (ConnectivityManager)mContext.getSystemService(Context.CONNECTIVITY_SERVICE);
			NetworkInfo netInfo = conn.getActiveNetworkInfo();
			bRet = (null == netInfo) ? false : netInfo.isAvailable();
		} catch (Exception e) {
			LogE("Fail to check network status", e);
		}
		LogD("NetWork reachable : " + bRet);
		return bRet;
	}
	
	public boolean canPresentDialogWithParams(final JSONObject cpInfo){ 
		try {
			String dialogType = cpInfo.getString("dialog");
			if("shareLink".equals(dialogType)){
				return FacebookDialog.canPresentShareDialog(mContext, ShareDialogFeature.SHARE_DIALOG);
			}
			else if("shareOpenGraph".equals(dialogType)){
				return FacebookDialog.canPresentOpenGraphActionDialog(mContext, OpenGraphActionDialogFeature.OG_ACTION_DIALOG);
				
			}
			else if("sharePhoto".equals(dialogType)){
				return FacebookDialog.canPresentShareDialog(mContext, ShareDialogFeature.PHOTOS);
				
			}
			else if("apprequests".equals(dialogType)){
				return true;
			}
			else if("messageLink".equals(dialogType)){
				return FacebookDialog.canPresentMessageDialog(mContext, MessageDialogFeature.MESSAGE_DIALOG);
			}
			else if("messageOpenGraph".equals(dialogType)){
				return FacebookDialog.canPresentOpenGraphMessageDialog(mContext, OpenGraphMessageDialogFeature.OG_MESSAGE_DIALOG);
			}
			else if("messagePhoto".equals(dialogType)){
				return FacebookDialog.canPresentMessageDialog(mContext, MessageDialogFeature.PHOTOS);
			}
		} catch (JSONException e) {
			e.printStackTrace();
		}
		return false;
	}

	public void webDialog(final JSONObject cpInfo){ 
		PluginWrapper.runOnMainThread(new Runnable(){
			@Override
			public void run() {
				try {
					String dialogType = cpInfo.getString("dialog");
					if("shareLink".equals(dialogType)){
						WebFeedDialog(cpInfo);
					}
					else if("shareOpenGraph".equals(dialogType)){
						WebShareOpenGraphDialog(cpInfo);
					}
					else {
						String errMsgString = "{\"error_message\" : \"do not support this type!\"}";
						ShareWrapper.onShareResult(mAdapter, ShareWrapper.SHARERESULT_FAIL, errMsgString);
					}
				} catch (JSONException e) {
					e.printStackTrace();
				}
			}
			
		});
	}

	public void dialog(final JSONObject cpInfo){
		PluginWrapper.runOnMainThread(new Runnable(){

			@Override
			public void run() {
				try {
					String dialogType = cpInfo.getString("dialog");
					if("shareLink".equals(dialogType)){
						FBShareDialog(cpInfo);
					}
					else if("feedDialog".equals(dialogType)){
						WebFeedDialog(cpInfo);
					}
					else if("shareOpenGraph".equals(dialogType)){
						FBShareOpenGraphDialog(cpInfo);
					}
					else if("sharePhoto".equals(dialogType)){
						FBSharePhotoDialog(cpInfo);
					}
					else if("apprequests".equals(dialogType)){
						WebRequestDialog(cpInfo);
					}
					else if("messageLink".equals(dialogType)){
						FBMessageDialog(cpInfo);
					}
					else if("messageOpenGraph".equals(dialogType)){
						FBMessageOpenGraphDialog(cpInfo);
					}
					else if("messagePhoto".equals(dialogType)){
						FBMessagePhotoDialog(cpInfo);
					}
				} catch (JSONException e) {
					e.printStackTrace();
				}
			}
			
		});
	}
	
	private void FBShareOpenGraphDialog(JSONObject info) throws JSONException{
		String type = info.has("action_type")?info.getString("action_type"):info.getString("actionType");
		String previewProperty = info.has("preview_property_name")?info.getString("preview_property_name"):info.getString("previewPropertyName");

		OpenGraphObject obj = OpenGraphObject.Factory.createForPost(OpenGraphObject.class, type, info.getString("title"),
                        info.getString("image"), info.getString("url"),
                        info.getString("description"));
        OpenGraphAction action = GraphObject.Factory.create(OpenGraphAction.class);
        action.setProperty(previewProperty, obj);
        action.setType(type);
        //action.setType(type);
        FacebookDialog shareDialog = new FacebookDialog.OpenGraphActionDialogBuilder(mContext, action, previewProperty).build();
        FacebookWrapper.track(shareDialog.present());
	}
	
	private void FBSharePhotoDialog(JSONObject info) throws JSONException{
		String filepath = info.getString("photo");
		if("".equals(filepath)){
			LogD("Must specify one photo");
			return;
		}
		
		File file = new File(filepath);
		//Bitmap image = BitmapFactory.decodeFile(cpInfo.getString("photos"));
		FacebookDialog dialog = new FacebookDialog.PhotoShareDialogBuilder(mContext)
									.addPhotoFiles(Arrays.asList(file))	
									//.addPhotos(Arrays.asList(image))
									.build();
		FacebookWrapper.track(dialog.present());
	}
	public void appRequest(final JSONObject info){
		PluginWrapper.runOnMainThread(new Runnable(){

			@Override
			public void run() {
				try{
					WebRequestDialog(info);
				}catch(JSONException e){
					e.printStackTrace();
				}
				
			}
			
		});
	}
	
	private void WebRequestDialog(JSONObject info) throws JSONException{
		String message = null;
		String app_id = null;
		RequestsDialogBuilder requestDialogBuilder = new WebDialog.RequestsDialogBuilder(mContext);
		// some property need to add
		
		if ((message = safeGetJsonString(info, "message")) == null)
		{
			ShareWrapper.onShareResult(mAdapter, ShareWrapper.SHARERESULT_FAIL, "{ \"error_message\" : \" need to add property 'message' \"}");
			return;
		}
		
		requestDialogBuilder.setMessage(message);
		
		// some property can be choose
		String to = null;
		if ((to = safeGetJsonString(info, "to")) != null)
			requestDialogBuilder.setTo(to);
		
		String title = null;
		if ((title = safeGetJsonString(info, "title")) != null)
			requestDialogBuilder.setTitle(title);
		
		String data = null;
		if ((data = safeGetJsonString(info, "data")) != null)
			requestDialogBuilder.setData(data);
		
		requestDialogBuilder.setOnCompleteListener(new OnCompleteListener(){
			@Override
			public void onComplete(Bundle values,	FacebookException error) {
				if(null != error){
					StringBuffer buffer = new StringBuffer();
					buffer.append("{\"error_message\":\"")
						.append(error.getMessage())
						.append("\"}");
					
					ShareWrapper.onShareResult(mAdapter, ShareWrapper.SHARERESULT_FAIL, buffer.toString());
				}else{
					StringBuffer buffer = new StringBuffer();
					buffer.append("{\"request\":\"");
					buffer.append(values.getString("request"));
					buffer.append("\", \"to\":[");
					
					Set<String> keys = values.keySet();
					Iterator<String> it = keys.iterator();
					while(it.hasNext()){
						String key = it.next();
						if(!"request".equals(key)){
							
							buffer.append("\"");
							buffer.append(values.getString(it.next()));
							buffer.append("\",");
						}
					}
					//remove the last ,
					buffer.deleteCharAt(buffer.length() - 1);
					buffer.append("]}");
					
					ShareWrapper.onShareResult(mAdapter, ShareWrapper.SHARERESULT_SUCCESS, buffer.toString());
				}
			}
		});
		requestDialogBuilder.build().show();
	}
	
	private String safeGetJsonString(JSONObject info, String key) {
		try {
			return info.getString(key);
		} catch (Exception e) {
			return null;
		}
	}
	
	private void FBShareDialog(JSONObject info) throws JSONException{
		String link = null;
		
		// some property need to add
		if ((link = safeGetJsonString(info, "link")) == null)
		{
			ShareWrapper.onShareResult(mAdapter, ShareWrapper.SHARERESULT_FAIL, "{ \"error_message\" : \" need to add property 'link' \"}");
			return;
		}
		
		ShareDialogBuilder shareDialogBuilder = new FacebookDialog.ShareDialogBuilder(mContext);
		shareDialogBuilder.setLink(link);
		
		// some property can be choose
		String name = null;
		if ((name = safeGetJsonString(info, "name")) != null)
			shareDialogBuilder.setName(name);
		
		String caption = null;
		if ((caption = safeGetJsonString(info, "caption")) != null)
			shareDialogBuilder.setCaption(caption);
		
		String description = null;
		if ((description = safeGetJsonString(info, "description")) != null)
			shareDialogBuilder.setDescription(description);
		
		String picture = null;
		if ((picture = safeGetJsonString(info, "picture")) != null)
			shareDialogBuilder.setPicture(picture);
		
		String friendStr = null;
		if ((friendStr = safeGetJsonString(info, "to")) != null)
		{
			String []arr = friendStr.split(",");
			List<String> list=Arrays.asList(arr); 
			shareDialogBuilder.setFriends(list);
		}
		
		String place = null;
		if ((place = safeGetJsonString(info, "place")) != null)
		{
			shareDialogBuilder.setPlace(place);
		}
		
		String ref = null;
		if ((ref = safeGetJsonString(info, "reference")) != null)
		{
			shareDialogBuilder.setRef(ref);
		}
		
		FacebookWrapper.track(shareDialogBuilder.build().present());
	}
	
	private void WebFeedDialog(JSONObject info) throws JSONException{
		String link = null;
		
		// some property need to add
		if ((link = safeGetJsonString(info, "link")) == null)
		{
			ShareWrapper.onShareResult(mAdapter, ShareWrapper.SHARERESULT_FAIL, "{ \"error_message\" : \" need to add property 'link' \"}");
			return;
		}
		
		FeedDialogBuilder feedDialogBuilder = new WebDialog.FeedDialogBuilder(mContext);
		feedDialogBuilder.setLink(link);
		feedDialogBuilder.setOnCompleteListener(new OnCompleteListener(){
				@Override
				public void onComplete(Bundle arg0,
						FacebookException arg1) {
					ShareWrapper.onShareResult(mAdapter, ShareWrapper.SHARERESULT_SUCCESS, "share success");
					
				}
			}
		);
		
		// some property can be choose
		String name = null;
		if ((name = safeGetJsonString(info, "name")) != null)
			feedDialogBuilder.setName(name);
		
		String caption = null;
		if ((caption = safeGetJsonString(info, "caption")) != null)
			feedDialogBuilder.setCaption(caption);
		
		String description = null;
		if ((description = safeGetJsonString(info, "description")) != null)
			feedDialogBuilder.setDescription(description);
		
		String picture = null;
		if ((picture = safeGetJsonString(info, "picture")) != null)
			feedDialogBuilder.setPicture(picture);

		String media_source = null;
		if ((media_source = safeGetJsonString(info, "media_source")) != null)
			feedDialogBuilder.setSource(media_source);

		String to = null;
		if ((to = safeGetJsonString(info, "to")) != null)
			feedDialogBuilder.setTo(to);
		
		feedDialogBuilder.build().show();
	}
	
	private void WebShareOpenGraphDialog(JSONObject info) throws JSONException{
		String caption = info.has("title")?info.getString("title"):info.getString("caption");
		String link = info.has("siteUrl")?info.getString("siteUrl"):info.getString("url");
		String description = info.has("text")?info.getString("text"):info.getString("description");
		String picture = info.has("imageUrl")?info.getString("imageUrl"):info.getString("image");
		
		WebDialog dialog = new WebDialog.FeedDialogBuilder(mContext)
								.setCaption(caption)
								.setLink(link)
								.setDescription(description)
								.setPicture(picture)
								//.setTo(info.getString("to"))
								.setOnCompleteListener(new OnCompleteListener(){

									@Override
									public void onComplete(Bundle arg0,
											FacebookException arg1) {
										ShareWrapper.onShareResult(mAdapter, ShareWrapper.SHARERESULT_SUCCESS, "share success");
										
									}})
								.build();
		dialog.show();
		//WebDialog dialog = new WebDialog.WebDialog(mContext).build();
	}
	
	private void FBMessageDialog(JSONObject info) throws JSONException{
		String caption = info.has("title")?info.getString("title"):info.getString("caption");
		String link = info.has("siteUrl")?info.getString("siteUrl"):info.getString("link");
		String description = info.has("text")?info.getString("text"):info.getString("description");
		String picture = info.has("imageUrl")?info.getString("imageUrl"):info.getString("picture");
		
		//String name = info.getString("site");
		
		FacebookDialog dialog = new FacebookDialog.MessageDialogBuilder(mContext)
				.setCaption(caption)
				.setLink(link)
				//.setName(name)
				.setDescription(description)
				.setPicture(picture)
		    	.build();
		FacebookWrapper.track(dialog.present());
	}
	
	

	private void FBMessageOpenGraphDialog(JSONObject info) throws JSONException{
		String type = info.has("action_type")?info.getString("action_type"):info.getString("actionType");
		String previewProperty = info.has("preview_property_name")?info.getString("preview_property_name"):info.getString("previewPropertyName");
	
		OpenGraphObject obj = OpenGraphObject.Factory.createForPost(OpenGraphObject.class, type, info.getString("title"),
                        info.getString("image"), info.getString("url"),
                        info.getString("description"));
        OpenGraphAction action = GraphObject.Factory.create(OpenGraphAction.class);
        action.setType(type);
        action.setProperty(previewProperty, obj);
        
		FacebookDialog dialog = new FacebookDialog.OpenGraphMessageDialogBuilder(mContext, action, previewProperty)
				.build();
		FacebookWrapper.track(dialog.present());
	}
	
	private void FBMessagePhotoDialog(JSONObject info) throws JSONException{
		String filepath = info.getString("photo");
		if("".equals(filepath)){
			LogD("Must specify one photo");
			return;
		}
		
		File file = new File(filepath);
		
		FacebookDialog dialog = new FacebookDialog.PhotoMessageDialogBuilder(mContext)
									.addPhotoFiles(Arrays.asList(file))
									.build();
		FacebookWrapper.track(dialog.present());
	}
	
	private class FacebookDialogCallback implements FacebookDialog.Callback{

		@Override
		public void onComplete(PendingCall arg0, Bundle arg1) {
			ShareWrapper.onShareResult(mAdapter, ShareWrapper.SHARERESULT_SUCCESS, "{\"didComplete\":true}");			
		}

		@Override
		public void onError(PendingCall arg0, Exception arg1, Bundle arg2) {
			ShareWrapper.onShareResult(mAdapter, ShareWrapper.SHARERESULT_FAIL, "{ \"error_message\" : \"" + arg1.getMessage() + "\"}");			
		}
		
	}
}
