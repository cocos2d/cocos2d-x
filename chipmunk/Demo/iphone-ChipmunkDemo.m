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
 
/*
	IMPORTANT - READ ME!
	
	This file sets up a simple interface that the individual demos can use to get
	a Chipmunk space running and draw what's in it. In order to keep the Chipmunk
	examples clean and simple, they contain no graphics code. All drawing is done
	by accessing the Chipmunk structures at a very low level. It is NOT
	recommended to write a game or application this way as it does not scale
	beyond simple shape drawing and is very dependent on implementation details
	about Chipmunk which may change with little to no warning.
*/
 
#import "cocos2d.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#ifdef __IPHONE_2_0
#endif

#include "chipmunk.h"
#include "drawSpace.h"
#include "cocos2dChipmunkDemo.h"

#define SLEEP_TICKS 16

//extern chipmunkDemo Test;
extern chipmunkDemo LogoSmash;
extern chipmunkDemo Simple;
extern chipmunkDemo PyramidStack;
extern chipmunkDemo Plink;
extern chipmunkDemo Tumble;
extern chipmunkDemo PyramidTopple;
extern chipmunkDemo Bounce;
extern chipmunkDemo Planet;
extern chipmunkDemo Springies;
extern chipmunkDemo Pump;
extern chipmunkDemo TheoJansen;
extern chipmunkDemo MagnetsElectric;
extern chipmunkDemo UnsafeOps;
extern chipmunkDemo Query;
extern chipmunkDemo OneWay;
extern chipmunkDemo Player;
extern chipmunkDemo Sensors;
extern chipmunkDemo Joints;

//extern chipmunkDemo Test;

static chipmunkDemo *demos[] = {
	&LogoSmash,
	&Simple,
	&PyramidStack,
	&Plink,
	&Tumble,
	&PyramidTopple,
	&Bounce,
	&Planet,
	&Springies,
	&Pump,
	&TheoJansen,
	&MagnetsElectric,
	&UnsafeOps,
//	&Query,
	&OneWay,
	&Player,
	&Sensors,
	&Joints,
};

static int maxDemos = sizeof(demos) / sizeof(demos[0]);

static const int demoCount = sizeof(demos)/sizeof(chipmunkDemo *);
static chipmunkDemo *currDemo = NULL;
static const int firstDemoIndex = 'a' - 'a';

static int ticks = 0;
static cpSpace *space;

cpVect mousePoint;
cpVect mousePoint_last;
cpBody *mouseBody = NULL;
cpConstraint *mouseJoint = NULL;

char messageString[1024] = {};

int key_up = 0;
int key_down = 0;
int key_left = 0;
int key_right = 0;

cpVect arrowDirection = {};

drawSpaceOptions options = {
	0,
	0,
	1,
	4.0f,
	0.0f,
	1.5f,
};

static void
drawString(int x, int y, char *str)
{
	// implement me
}

static void
drawInstructions()
{
	drawString(-300, 220,
		"Controls:\n"
		"A - * Switch demos. (return restarts)\n"
		"Use the mouse to grab objects.\n"
		"Arrow keys control some demos.\n"
		"\\ enables anti-aliasing.\n"
		"- toggles spatial hash visualization.\n"
		"= toggles bounding boxes."
	);
}

static int maxArbiters = 0;
static int maxPoints = 0;
static int maxConstraints = 0;

static void
drawInfo()
{
	int arbiters = space->arbiters->num;
	int points = 0;
	
	for(int i=0; i<arbiters; i++)
		points += ((cpArbiter *)(space->arbiters->arr[i]))->numContacts;
	
	int constraints = (space->constraints->num + points)*(space->iterations + space->elasticIterations);
	
	maxArbiters = arbiters > maxArbiters ? arbiters : maxArbiters;
	maxPoints = points > maxPoints ? points : maxPoints;
	maxConstraints = constraints > maxConstraints ? constraints : maxConstraints;
	
	char buffer[1000];
	char *format = 
		"Arbiters: %d (%d) - "
		"Contact Points: %d (%d)\n"
		"Other Constraints: %d, Iterations: %d\n"
		"Constraints x Iterations: %d (%d)";
	
	snprintf(buffer, 1000, format,
		arbiters, maxArbiters,
		points, maxPoints,
		space->constraints->num, space->iterations + space->elasticIterations,
		constraints, maxConstraints
	);
	
	drawString(0, 220, buffer);
}

static void
display(void)
{
//	glClear(GL_COLOR_BUFFER_BIT);
//	
//	drawSpace(space, currDemo->drawOptions ? currDemo->drawOptions : &options);
//	drawInstructions();
//	drawInfo();
//	drawString(-300, -210, messageString);
//		
//	glutSwapBuffers();
	ticks++;
	
	cpVect newPoint = cpvlerp(mousePoint_last, mousePoint, 0.25f);
	mouseBody->p = newPoint;
	mouseBody->v = cpvmult(cpvsub(newPoint, mousePoint_last), 60.0f);
	mousePoint_last = newPoint;
	currDemo->updateFunc(ticks);
}

static char *
demoTitle(chipmunkDemo *demo)
{
	static char title[1024];
	sprintf(title, "Demo: %s", demo->name);
	
	return title;
}

static void
runDemo(chipmunkDemo *demo)
{
	if(currDemo)
		currDemo->destroyFunc();
		
	currDemo = demo;
	ticks = 0;
	mouseJoint = NULL;
	messageString[0] = '\0';
	maxArbiters = 0;
	maxPoints = 0;
	maxConstraints = 0;
	space = currDemo->initFunc();

//	glutSetWindowTitle(demoTitle(currDemo));
}

static void
keyboard(unsigned char key, int x, int y)
{
	int index = key - 'a';
	
	if(0 <= index && index < demoCount){
		runDemo(demos[index]);
	} else if(key == '\r'){
		runDemo(currDemo);
	} else if(key == '-'){
		options.drawHash = !options.drawHash;
	} else if(key == '='){
		options.drawBBs = !options.drawBBs;
	} else if(key == '\\'){
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
		glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
	}
}

static cpVect
mouseToSpace(int x, int y)
{
//	GLdouble model[16];
//	glGetDoublev(GL_MODELVIEW_MATRIX, model);
//	
//	GLdouble proj[16];
//	glGetDoublev(GL_PROJECTION_MATRIX, proj);
//	
//	GLint view[4];
//	glGetIntegerv(GL_VIEWPORT, view);
//	
//	GLdouble mx, my, mz;
//	gluUnProject(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 0.0f, model, proj, view, &mx, &my, &mz);
	
//	return cpv(mx, my);
	return cpv(x,y);
}

static void
mouse(int x, int y)
{
	mousePoint = mouseToSpace(x, y);
}

static void
click(int button, int state, int x, int y)
{
//	if(button == GLUT_LEFT_BUTTON){
//		if(state == GLUT_DOWN){
//			cpVect point = mouseToSpace(x, y);
//		
//			cpShape *shape = cpSpacePointQueryFirst(space, point, GRABABLE_MASK_BIT, 0);
//			if(shape){
//				cpBody *body = shape->body;
//				mouseJoint = cpPivotJointNew2(mouseBody, body, cpvzero, cpBodyWorld2Local(body, point));
//				mouseJoint->maxForce = 50000.0f;
//				mouseJoint->biasCoef = 0.15f;
//				cpSpaceAddConstraint(space, mouseJoint);
//			}
//		} else if(mouseJoint){
//			cpSpaceRemoveConstraint(space, mouseJoint);
//			cpConstraintFree(mouseJoint);
//			mouseJoint = NULL;
//		}
//	}
}

static void
timercall(int value)
{
//	glutTimerFunc(SLEEP_TICKS, timercall, 0);
//		
//	glutPostRedisplay();
}

static void
set_arrowDirection()
{
	int x = 0, y = 0;
	
	if(key_up) y += 1;
	if(key_down) y -= 1;
	if(key_right) x += 1;
	if(key_left) x -= 1;
	
	arrowDirection = cpv(x, y);
}

static void
arrowKeyDownFunc(int key, int x, int y)
{
//	if(key == GLUT_KEY_UP) key_up = 1;
//	else if(key == GLUT_KEY_DOWN) key_down = 1;
//	else if(key == GLUT_KEY_LEFT) key_left = 1;
//	else if(key == GLUT_KEY_RIGHT) key_right = 1;

	set_arrowDirection();
}

static void
arrowKeyUpFunc(int key, int x, int y)
{
//	if(key == GLUT_KEY_UP) key_up = 0;
//	else if(key == GLUT_KEY_DOWN) key_down = 0;
//	else if(key == GLUT_KEY_LEFT) key_left = 0;
//	else if(key == GLUT_KEY_RIGHT) key_right = 0;

	set_arrowDirection();
}

static void
idle(void)
{
//	glutPostRedisplay();
}

static void
initGL(void)
{
//	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-320.0f, 320.0f, -240.0f, 240.0f, -1.0f, 1.0f);
//	glTranslatef(0.5f, 0.5f, 0.0f);
//	
//	glEnableClientState(GL_VERTEX_ARRAY);
}

static void
glutStuff(int argc, const char *argv[])
{
//	glutInit(&argc, (char**)argv);
//	
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//	
//	glutInitWindowSize(640, 480);
//	glutCreateWindow(demoTitle(demos[firstDemoIndex]));
//	
//	initGL();
//	
//	glutDisplayFunc(display);
////	glutIdleFunc(idle);
//	glutTimerFunc(SLEEP_TICKS, timercall, 0);
//
//	glutIgnoreKeyRepeat(1);
//	glutKeyboardFunc(keyboard);
//	
//	glutSpecialFunc(arrowKeyDownFunc);
//	glutSpecialUpFunc(arrowKeyUpFunc);
//
//	glutMotionFunc(mouse);
//	glutPassiveMotionFunc(mouse);
//	glutMouseFunc(click);
}

//#include <sys/time.h>
//void time_trial(char index, int count)
//{
//	currDemo = demos[index];
//	space = currDemo->initFunc();
//	
//	struct timeval start_time, end_time;
//	gettimeofday(&start_time, NULL);
//	
//	for(int i=0; i<count; i++)
//		currDemo->updateFunc(i);
//	
//	gettimeofday(&end_time, NULL);
//	long millisecs = (end_time.tv_sec - start_time.tv_sec)*1000;
//	millisecs += (end_time.tv_usec - start_time.tv_usec)/1000;
//	
//	currDemo->destroyFunc();
//	
//	printf("Time(%c) = %ldms\n", index + 'a', millisecs);
//}

#pragma mark -
#pragma mark MainLayer

@implementation MainLayer
-(id) init
{
	if( (self=[super init]) ) {
		self.isTouchEnabled = YES;
		cpInitChipmunk();	
		mouseBody = cpBodyNew(INFINITY, INFINITY);

		runDemo(demos[firstDemoIndex]);
		
		label = [CCLabel labelWithString:[NSString stringWithUTF8String:demos[firstDemoIndex]->name ] fontName:@"Marker Felt" fontSize:32];
		label.position = ccp(0,-300);
		label.color = ccBLACK;
		[self addChild:label];
		
		[self schedule: @selector(step:)];
	}
	
	return self;
}

-(void) onEnter
{
	[super onEnter];
	
	glClearColor(1,1,1,1);
	float factor = 1.0f;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(-320/factor, 320/factor, -480/factor, 480/factor, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glPointSize(3.0f);
    glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
    glLineWidth(1.5f);
}

-(void) step: (ccTime) dt
{
	display();
}

-(void) draw
{
	drawSpace(space, currDemo->drawOptions ? currDemo->drawOptions : &options);
}

- (void)ccTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	
	demoIndex++;
	if( demoIndex >= maxDemos )
		demoIndex = 0;
	
	runDemo(demos[demoIndex]);
	
	[label setString: [NSString stringWithUTF8String:demos[demoIndex]->name ] ];	
}
@end

#pragma mark -
#pragma mark AppController

@implementation AppController
- (void) applicationDidFinishLaunching:(UIApplication*)application
{
	// CC_DIRECTOR_INIT()
	//
	// 1. Initializes an EAGLView with 0-bit depth format, and RGB565 render buffer
	// 2. Attaches to the main window
	// 3. Creates Display Link Director
	// 3a. If it fails, it will use an NSTimer director
	// 4. It will try to run at 60 FPS
	// 4. Display FPS: NO
	// 5. Device orientation: Portrait
	// 6. Connect the director to the EAGLView
	//
	CC_DIRECTOR_INIT();
	
	// Obtain the shared director in order to...
	CCDirector *director = [CCDirector sharedDirector];
	
	// Turn on display FPS
	[director setDisplayFPS:YES];
	
	CCScene *scene = [CCScene node];
	
	MainLayer * mainLayer =[MainLayer node];
	
	[scene addChild: mainLayer];
		
	[director runWithScene: scene];
}

// getting a call, pause the game
-(void) applicationWillResignActive:(UIApplication *)application
{
	[[CCDirector sharedDirector] pause];
}

// call got rejected
-(void) applicationDidBecomeActive:(UIApplication *)application
{
	[[CCDirector sharedDirector] resume];
}

// next delta time will be zero
-(void) applicationSignificantTimeChange:(UIApplication *)application
{
	[[CCDirector sharedDirector] setNextDeltaTimeZero:YES];
}

- (void) dealloc
{
	[window release];
	[super dealloc];
}


@end


int main(int argc, char *argv[]) {
	
	NSAutoreleasePool *pool = [NSAutoreleasePool new];
	UIApplicationMain(argc, argv, nil, @"AppController");
	[pool release];
	return 0;
}
