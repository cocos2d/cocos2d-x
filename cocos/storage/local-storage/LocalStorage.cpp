/*
 
 Copyright (c) 2012 - Zynga Inc.
 
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
 
 */

/*
 Local Storage support for the JS Bindings for iOS.
 Works on cocos2d-iphone and cocos2d-x.
 */

#include "LocalStorage.h"
#include "base/CCPlatformMacros.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sqlite3.h>

static int _initialized = 0;
static sqlite3 *_db;
static sqlite3_stmt *_stmt_select;
static sqlite3_stmt *_stmt_remove;
static sqlite3_stmt *_stmt_update;


static void localStorageCreateTable()
{
	const char *sql_createtable = "CREATE TABLE IF NOT EXISTS data(key TEXT PRIMARY KEY,value TEXT);";
	sqlite3_stmt *stmt;
	int ok=sqlite3_prepare_v2(_db, sql_createtable, -1, &stmt, nullptr);
	ok |= sqlite3_step(stmt);
	ok |= sqlite3_finalize(stmt);
	
	if( ok != SQLITE_OK && ok != SQLITE_DONE)
		printf("Error in CREATE TABLE\n");
}

void localStorageInit( const std::string& fullpath/* = "" */)
{
	if( ! _initialized ) {

		int ret = 0;
		
		if (fullpath.empty())
			ret = sqlite3_open(":memory:",&_db);
		else
			ret = sqlite3_open(fullpath.c_str(), &_db);

		localStorageCreateTable();

		// SELECT
		const char *sql_select = "SELECT value FROM data WHERE key=?;";
		ret |= sqlite3_prepare_v2(_db, sql_select, -1, &_stmt_select, nullptr);

		// REPLACE
		const char *sql_update = "REPLACE INTO data (key, value) VALUES (?,?);";
		ret |= sqlite3_prepare_v2(_db, sql_update, -1, &_stmt_update, nullptr);

		// DELETE
		const char *sql_remove = "DELETE FROM data WHERE key=?;";
		ret |= sqlite3_prepare_v2(_db, sql_remove, -1, &_stmt_remove, nullptr);

		if( ret != SQLITE_OK ) {
			printf("Error initializing DB\n");
			// report error
		}
		
		_initialized = 1;
	}
}

void localStorageFree()
{
	if( _initialized ) {
		sqlite3_finalize(_stmt_select);
		sqlite3_finalize(_stmt_remove);
		sqlite3_finalize(_stmt_update);		

		sqlite3_close(_db);
		
		_initialized = 0;
	}
}

/** sets an item in the LS */
void localStorageSetItem( const std::string& key, const std::string& value)
{
	assert( _initialized );
	
	int ok = sqlite3_bind_text(_stmt_update, 1, key.c_str(), -1, SQLITE_TRANSIENT);
	ok |= sqlite3_bind_text(_stmt_update, 2, value.c_str(), -1, SQLITE_TRANSIENT);

	ok |= sqlite3_step(_stmt_update);
	
	ok |= sqlite3_reset(_stmt_update);
	
	if( ok != SQLITE_OK && ok != SQLITE_DONE)
		printf("Error in localStorage.setItem()\n");
}

/** gets an item from the LS */
std::string localStorageGetItem( const std::string& key )
{
	assert( _initialized );

	std::string ret;
	int ok = sqlite3_reset(_stmt_select);

	ok |= sqlite3_bind_text(_stmt_select, 1, key.c_str(), -1, SQLITE_TRANSIENT);
	ok |= sqlite3_step(_stmt_select);
	const unsigned char *text = sqlite3_column_text(_stmt_select, 0);
	if (text)
		ret = (const char*)text;

	if( ok != SQLITE_OK && ok != SQLITE_DONE && ok != SQLITE_ROW)
		printf("Error in localStorage.getItem()\n");

	return ret;
}

/** removes an item from the LS */
void localStorageRemoveItem( const std::string& key )
{
	assert( _initialized );

	int ok = sqlite3_bind_text(_stmt_remove, 1, key.c_str(), -1, SQLITE_TRANSIENT);
	
	ok |= sqlite3_step(_stmt_remove);
	
	ok |= sqlite3_reset(_stmt_remove);

	if( ok != SQLITE_OK && ok != SQLITE_DONE)
		printf("Error in localStorage.removeItem()\n");
}

#endif // #if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
