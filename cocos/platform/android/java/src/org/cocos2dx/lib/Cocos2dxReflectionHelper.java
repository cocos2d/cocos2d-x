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
