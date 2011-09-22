/* Copyright (c) 2007 Scott Lembcke
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "chipmunk.h"
#include "drawSpace.h"
#include "../testBasic.h"

struct chipmunkDemo;

typedef cpSpace *(*demoInitFunc)(void);
typedef void (*demoUpdateFunc)(int ticks);
typedef void (*demoDestroyFunc)(void);

typedef struct chipmunkDemo {
	char *name;

	drawSpaceOptions *drawOptions;
	
	demoInitFunc initFunc;
	demoUpdateFunc updateFunc;
	demoDestroyFunc destroyFunc;
} chipmunkDemo;

static inline cpFloat
frand(void)
{
	return (cpFloat)rand()/(cpFloat)RAND_MAX;
}

extern cpVect arrowDirection;
extern char messageString[1024];

#define GRABABLE_MASK_BIT (1<<31)
#define NOT_GRABABLE_MASK (~GRABABLE_MASK_BIT)

// cocos2d-x test interface decalre
class ChipmunkTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

class ChipmunkTestLayer : public CCLayer
{
protected:
	std::string	m_strTitle;
    int demoIndex;
    CCLabelTTF *label;

public:
    void init();
	// virtual std::string title();
	virtual void onEnter();
    virtual void onExit();
    void update(ccTime dt);
    void draw();
    void ccTouchesEnded(CCSet* touches, CCEvent *event);
        
	// void restartCallback(CCObject* pSender);
	// void nextCallback(CCObject* pSender);
	// void backCallback(CCObject* pSender);
};