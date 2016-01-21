/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

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
package org.cocos2dx.cpp_tests;

import android.util.Log;
import java.lang.StringBuilder;

public class JNITest {
	private static final String TAG = "JNITest";

	public static void voidMethod1() {
		Log.v(TAG, "Called voidMethod1");
	}

	public static void voidMethod2(final String str) {
		StringBuilder message = new StringBuilder();
		message.append("Called voidMethod2 with str = ");
		message.append(str);
		Log.v(TAG, message.toString());
	}

	public static void voidMethod3(int n, float x, final String str) {
		StringBuilder message = new StringBuilder();
		message.append("Called voidMethod3 with n = ");
		message.append(n);
		message.append(", x = ");
		message.append(x);
		message.append(", str = ");
		message.append(str);
		Log.v(TAG, message.toString());
	}

	public static void voidMethod4(final String str) {
		// Used to test garbage collection
	}

	public static boolean booleanMethod(int n) {
		boolean ret = n > 0;
		StringBuilder message = new StringBuilder();
		message.append("Called booleanMethod with n = ");
		message.append(n);
		message.append("\nReturning ");
		message.append(ret);
		Log.v(TAG, message.toString());
		return ret;
	}

	public static int intMethod(int a, int b) {
		int ret = a + b;
		StringBuilder message = new StringBuilder();
		message.append("Called intMethod with a = ");
		message.append(a);
		message.append(", b = ");
		message.append(b);
		message.append("\nReturning ");
		message.append(ret);
		Log.v(TAG, message.toString());
		return ret;
	}

	public static float floatMethod(float x, float y) {
		float ret = x + y;
		StringBuilder message = new StringBuilder();
		message.append("Called floatMethod with x = ");
		message.append(x);
		message.append(", y = ");
		message.append(y);
		message.append("\nReturning ");
		message.append(ret);
		Log.v(TAG, message.toString());
		return ret;
	}

	public static double doubleMethod(double x, int n) {
		double ret = x*n;
		StringBuilder message = new StringBuilder();
		message.append("Called doubleMethod with x = ");
		message.append(x);
		message.append(", n = ");
		message.append(n);
		message.append("\nReturning ");
		message.append(ret);
		Log.v(TAG, message.toString());
		return ret;
	}

	public static String stringMethod(final String str, boolean reverse) {
		String ret = reverse ? new StringBuilder(str).reverse().toString() : str;
		StringBuilder message = new StringBuilder();
		message.append("Called stringMethod with str = ");
		message.append(str);
		message.append(", reverse = ");
		message.append(reverse);
		message.append("\nReturning ");
		message.append(ret);
		Log.v(TAG, message.toString());
		return ret;
	}
}
