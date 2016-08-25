/****************************************************************************
Copyright (c) 2013-2014 Chukong Technologies Inc.

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

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;


public class Cocos2dxLocalStorage {

    private static final String TAG = "Cocos2dxLocalStorage";

    private static String DATABASE_NAME = "jsb.sqlite";
    private static String TABLE_NAME = "data";
    private static final int DATABASE_VERSION = 1;
    
    private static DBOpenHelper mDatabaseOpenHelper = null;
    private static SQLiteDatabase mDatabase = null;
    /**
     * Constructor
     * @param context The Context within which to work, used to create the DB
     * @return 
     */
    public static boolean init(String dbName, String tableName) {
        if (Cocos2dxActivity.getContext() != null) {
            DATABASE_NAME = dbName;
            TABLE_NAME = tableName;
            mDatabaseOpenHelper = new DBOpenHelper(Cocos2dxActivity.getContext());
            mDatabase = mDatabaseOpenHelper.getWritableDatabase();
            return true;
        }
        return false;
    }
    
    public static void destroy() {
        if (mDatabase != null) {
            mDatabase.close();
        }
    }
    
    public static void setItem(String key, String value) {
        try {
            String sql = "replace into "+TABLE_NAME+"(key,value)values(?,?)";
            mDatabase.execSQL(sql, new Object[] { key, value });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    public static String getItem(String key) {
        String ret = null;
        try {
        String sql = "select value from "+TABLE_NAME+" where key=?";
        Cursor c = mDatabase.rawQuery(sql, new String[]{key});  
        while (c.moveToNext()) {
            // only return the first value
            if (ret != null) 
            {
                Log.e(TAG, "The key contains more than one value.");
                break;
            }
            ret = c.getString(c.getColumnIndex("value"));  
        }  
        c.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return ret;
    }
    
    public static void removeItem(String key) {
        try {
            String sql = "delete from "+TABLE_NAME+" where key=?";
            mDatabase.execSQL(sql, new Object[] {key});
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    public static void clear() {
        try {
            String sql = "delete from "+TABLE_NAME;
            mDatabase.execSQL(sql);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    

    /**
     * This creates/opens the database.
     */
    private static class DBOpenHelper extends SQLiteOpenHelper {

        DBOpenHelper(Context context) {
            super(context, DATABASE_NAME, null, DATABASE_VERSION);
        }

        @Override
        public void onCreate(SQLiteDatabase db) {
            db.execSQL("CREATE TABLE IF NOT EXISTS "+TABLE_NAME+"(key TEXT PRIMARY KEY,value TEXT);");
        }
        
        @Override
        public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
            Log.w(TAG, "Upgrading database from version " + oldVersion + " to "
                    + newVersion + ", which will destroy all old data");
            //db.execSQL("DROP TABLE IF EXISTS " + VIRTUAL_TABLE);
            //onCreate(db);
        }
    }
}
