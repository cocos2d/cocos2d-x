/****************************************************************************
Copyright (c) 2016 cocos2d-x.org
Copyright (c) 2016 Chukong Technologies Inc.

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
package org.cocos2dx.lib;

import android.util.Log;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class Cocos2dxReflectionHelper {
    public static <T> T getConstantValue(final Class aClass, final String constantName) {
        try {
            return (T)aClass.getDeclaredField(constantName).get(null);
        } catch (NoSuchFieldException e) {
            Log.e("error", "can not find " + constantName + " in " + aClass.getName());
        }
        catch (IllegalAccessException e) {
            Log.e("error", constantName + " is not accessable");
        }
        catch (IllegalArgumentException e) {
            Log.e("error", "arguments error when get " + constantName);
        }
        catch (Exception e) {
            Log.e("error", "can not get constant" + constantName);
        }

        return null;
    }

    public static <T> T invokeInstanceMethod(final Object instance, final String methodName,
                                             final Class[] parameterTypes, final Object[] parameters) {

        final Class aClass = instance.getClass();
        try {
            final Method method = aClass.getMethod(methodName, parameterTypes);
            return (T)method.invoke(instance, parameters);
        } catch (NoSuchMethodException e) {
            Log.e("error", "can not find " + methodName + " in " + aClass.getName());
        }
        catch (IllegalAccessException e) {
            Log.e("error", methodName + " is not accessible");
        }
        catch (IllegalArgumentException e) {
            Log.e("error", "arguments are error when invoking " + methodName);
        }
        catch (InvocationTargetException e) {
            Log.e("error", "an exception was thrown by the invoked method when invoking " + methodName);
        }

        return null;
    }
}
