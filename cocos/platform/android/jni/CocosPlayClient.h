/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.

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
#ifndef __COCOSPLAYCLIENT_H__
#define __COCOSPLAYCLIENT_H__

#include <string>

namespace cocosplay {

void lazyInit();

/**
 *  Checks whether CocosPlay is enabled
 */
bool isEnabled();

/**
 *  Checks whether CocosPlay is in demo mode
 */
bool isDemo();

/**
 *  Updates assets by filePath, if the file doesn't exist, CocosPlay will show a progress page of downloading.
 *  And this interface will be hung up until the scene package was downloaded.
 */
void updateAssets(const std::string& filePath);

/**
 *  Checks whether the file exists
 */
bool fileExists(const std::string& filePath);

/**
 *  Notifies to Cocos Play SDK that a file was loaded
 *  It will do nothing if game doesn't run on Cocos Play
 */
void notifyFileLoaded(const std::string& filePath);

/**
 *  Gets the resource root path of current game
 *  @return A writable path of current game
 */
std::string getGameRoot();

/**
 *  Purges the file searching cache.
 *
 *  @note It should be invoked after the resources were updated.
 *        For instance, it could be used when there is a small update in games.
 */
void purgeCachedEntries();

/**
 * Purges the file searching cache by giving file path.
 */
void purgeCachedByFile(const std::string& filePath);

/**
 *  Notifies that the game demo was ended
 */
void notifyDemoEnded();

} // namespace cocosplay {

#endif // __COCOSPLAYCLIENT_H__
