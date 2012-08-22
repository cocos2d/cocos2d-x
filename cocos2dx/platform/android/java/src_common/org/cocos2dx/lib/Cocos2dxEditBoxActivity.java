package org.cocos2dx.lib;

import org.cocos2dx.testcpp.R;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.os.Handler;
import android.text.InputFilter;
import android.text.InputType;
import android.text.Layout;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnKeyListener;
import android.view.Window;
import android.view.WindowManager;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class Cocos2dxEditBoxActivity extends Activity {

	public static final int ID_EDITBOX_RESULT_OK     = 101;
	public static final int ID_EDITBOX_RESULT_CANCEL = 102;
    /**
     * The user is allowed to enter any text, including line breaks.
     */
	private final int kEditBoxInputModeAny = 0;
    
    /**
     * The user is allowed to enter an e-mail address.
     */
	private final int kEditBoxInputModeEmailAddr = 1;

    /**
     * The user is allowed to enter an integer value.
     */
	private final int kEditBoxInputModeNumeric = 2;

    /**
     * The user is allowed to enter a phone number.
     */
	private final int kEditBoxInputModePhoneNumber = 3;

    /**
     * The user is allowed to enter a URL.
     */
	private final int kEditBoxInputModeUrl = 4;

    /**
     * The user is allowed to enter a real number value.
     * This extends kEditBoxInputModeNumeric by allowing a decimal point.
     */
	private final int kEditBoxInputModeDecimal = 5;

    /**
     * The user is allowed to enter any text, except for line breaks.
     */
	private final int kEditBoxInputModeSingleLine = 6;


    /**
     * Indicates that the text entered is confidential data that should be
     * obscured whenever possible. This implies EDIT_BOX_INPUT_FLAG_SENSITIVE.
     */
    private final int kEditBoxInputFlagPassword = 0;

    /**
     * Indicates that the text entered is sensitive data that the
     * implementation must never store into a dictionary or table for use
     * in predictive, auto-completing, or other accelerated input schemes.
     * A credit card number is an example of sensitive data.
     */
    private final int kEditBoxInputFlagSensitive = 1;

    /**
     * This flag is a hint to the implementation that during text editing,
     * the initial letter of each word should be capitalized.
     */
    private final int kEditBoxInputFlagInitialCapsWord = 2;

    /**
     * This flag is a hint to the implementation that during text editing,
     * the initial letter of each sentence should be capitalized.
     */
    private final int kEditBoxInputFlagInitialCapsSentence = 3;

    /**
     * Capitalize all characters automatically.
     */
    private final int kEditBoxInputFlagInitialCapsAllCharacters = 4;
	
    private final int kKeyboardReturnTypeDefault = 0;
    private final int kKeyboardReturnTypeDone = 1;
    private final int kKeyboardReturnTypeSend = 2;
    private final int kKeyboardReturnTypeSearch = 3;
    private final int kKeyboardReturnTypeGo = 4;

	//
	private EditText mInputEditText = null;
	private TextView mTextViewTitle = null;
	private int mInputMode = 0;
	private int mInputFlag = 0;
	private int mReturnType = 0;
	private int mMaxLength = -1;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		getWindow().requestFeature(Window.FEATURE_NO_TITLE);

		View view = View.inflate(this, R.layout.keyboard, null);
		setContentView(view);

		getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
		
		Bundle bundle = this.getIntent().getExtras();
		mInputMode = bundle.getInt("editbox_input_mode");
		mInputFlag = bundle.getInt("editbox_input_flag");
		mReturnType = bundle.getInt("editbox_return_type");
		mMaxLength = bundle.getInt("editbox_max_length");

		mTextViewTitle = (TextView) findViewById(R.id.title);
		mTextViewTitle.setText(bundle.getString("editbox_title"));

		mInputEditText = (EditText) findViewById(R.id.editbox);
		mInputEditText.setText(bundle.getString("editbox_content"));
		mInputEditText.setImeOptions(EditorInfo.IME_FLAG_NO_EXTRACT_UI);
		int inputType = InputType.TYPE_CLASS_TEXT;
		
	    switch (mInputMode)
	    {
	        case kEditBoxInputModeEmailAddr:
	            
	            break;
	        case kEditBoxInputModeNumeric:

	            break;
	        case kEditBoxInputModePhoneNumber:

	            break;
	        case kEditBoxInputModeUrl:

	            break;
	        case kEditBoxInputModeDecimal:

	            break;
	        case kEditBoxInputModeSingleLine:

	            break;
	        default:

	            break;
	    }
	    
		mInputEditText.setInputType(inputType);
		
	    switch (mInputFlag)
	    {
	        case kEditBoxInputFlagPassword:

	            break;
	        case kEditBoxInputFlagInitialCapsWord:

	            break;
	        case kEditBoxInputFlagInitialCapsSentence:

	            break;
	        case kEditBoxInputFlagInitialCapsAllCharacters:

	            break;
	        default:
	            break;
	    }
	    
	    
	    switch (mReturnType) {
	        case kKeyboardReturnTypeDefault:

	            break;
	        case kKeyboardReturnTypeDone:

	            break;
	        case kKeyboardReturnTypeSend:

	            break;
	        case kKeyboardReturnTypeSearch:

	            break;
	        case kKeyboardReturnTypeGo:

	            break;
	        default:

	            break;
    	}
//		mInputEditText.setFilters(
//				new InputFilter[] {
//						new InputFilter.LengthFilter(mLimit)
//						}
//				);
/*
		Handler initHandler = new Handler();
		initHandler.postDelayed(new Runnable() {
			public void run() {
				mInputEditText.requestFocus();
				mInputEditText.setSelection(mInputEditText.length());
				InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
				imm.showSoftInput(mInputEditText,InputMethodManager.SHOW_FORCED);
			}
		}, 200);
*/
		final Button buttonFinish = (Button) findViewById(R.id.button_finish);
		buttonFinish.setOnClickListener(new Button.OnClickListener() {
			public void onClick(View v) {
				Intent intent = new Intent();
				intent.setClass(Cocos2dxEditBoxActivity.this,
						Cocos2dxEditBoxActivity.class);
				Bundle bundle = new Bundle();
				bundle.putString("editbox_content", mInputEditText.getText().toString());
				intent.putExtras(bundle);
				setResult(ID_EDITBOX_RESULT_OK, intent);
				closeKeyboard();
				finish();
			}
		});

		final Button buttonCancel = (Button) findViewById(R.id.button_cancel);
		buttonCancel.setOnClickListener(new Button.OnClickListener() {
			public void onClick(View v) {
				Intent intent = new Intent();
				intent.setClass(Cocos2dxEditBoxActivity.this,
						Cocos2dxEditBoxActivity.class);
				setResult(ID_EDITBOX_RESULT_CANCEL, intent);
				closeKeyboard();
				finish();
			}
		});

	}

	private void closeKeyboard() {
		InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.hideSoftInputFromWindow(mInputEditText.getWindowToken(), 0);
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
	}

}
