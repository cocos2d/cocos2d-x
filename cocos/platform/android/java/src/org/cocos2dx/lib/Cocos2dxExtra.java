
package org.cocos2dx.lib;

import android.content.Intent;
import android.net.Uri;

public class Cocos2dxExtra
{
	public static void openURL(final String url)
	{
		Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse("http://www.google.com"));
		Cocos2dxActivity.getContext().startActivity(browserIntent);
	}
}
