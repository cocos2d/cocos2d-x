package org.cocos2dx.LuaGameControllerTest;

import org.cocos2dx.lib.GameControllerActivity;

import android.os.Bundle;

public class AppActivity extends GameControllerActivity {
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {		
		super.onCreate(savedInstanceState);
		
		//The standard controller,without doing anything special. e.g: Amazon Fire TV
		
		//Manually specify an adapter.
		this.connectController(DRIVERTYPE_NIBIRU);
		//this.connectController(DRIVERTYPE_MOGA);
		//this.connectController(DRIVERTYPE_OUYA);
	}
}
