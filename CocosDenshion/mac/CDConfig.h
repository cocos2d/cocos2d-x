/*
 Copyright (c) 2010 Steve Oldmeadow
 
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
 
 $Id$
 */
#define COCOSDENSHION_VERSION "Aphex.rc"


/**
 If enabled code useful for debugging such as parameter check assertions will be performed.
 If you experience any problems you should enable this and test your code with a debug build.
 */
//#define CD_DEBUG 1

/**
 The total number of sounds/buffers that can be loaded assuming memory is sufficient
 */
//Number of buffers slots that will be initially created
#define CD_BUFFERS_START 64
//Number of buffers that will be added 
#define CD_BUFFERS_INCREMENT 16

/**
 If enabled, OpenAL code will use static buffers. When static buffers are used the audio
 data is managed outside of OpenAL, this eliminates a memcpy operation which leads to 
 higher performance when loading sounds.
 
 However, the downside is that when the audio data is freed you must
 be certain that it is no longer being accessed otherwise your app will crash. Testing on OS 2.2.1
 and 3.1.2 has shown that this may occur if a buffer is being used by a source with state = AL_PLAYING
 when the buffer is deleted. If the data is freed too quickly after the source is stopped then
 a crash will occur. The implemented workaround is that when static buffers are used the unloadBuffer code will wait for
 any playing sources to finish playing before the associated buffer and data are deleted, however, this delay may negate any 
 performance gains that are achieved during loading.
 
 Performance tests on a 1st gen iPod running OS 2.2.1 loading the CocosDenshionDemo sounds were ~0.14 seconds without
 static buffers and ~0.12 seconds when using static buffers.

 */
//#define CD_USE_STATIC_BUFFERS 1


