package org.cocos2dx.LuaGameControllerTest;

import org.cocos2dx.lib.GameControllerActivity;

import android.os.Bundle;

public class AppActivity extends GameControllerActivity {
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {		
		super.onCreate(savedInstanceState);
        // Workaround in https://stackoverflow.com/questions/16283079/re-launch-of-activity-on-home-button-but-only-the-first-time/16447508
        if (!isTaskRoot()) {
            // Android launched another instance of the root activity into an existing task
            //  so just quietly finish and go away, dropping the user back into the activity
            //  at the top of the stack (ie: the last state of this task)
            // Don't need to finish it again since it's finished in super.onCreate .
            return;
        }
        // DO OTHER INITIALIZATION BELOW
		
		//The standard controller,without doing anything special. e.g: Amazon Fire TV
		
		//Manually specify an adapter.
		this.connectController(DRIVERTYPE_NIBIRU);
		//this.connectController(DRIVERTYPE_MOGA);
		//this.connectController(DRIVERTYPE_OUYA);
	}
}
