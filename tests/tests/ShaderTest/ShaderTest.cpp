#include "ShaderTest.h"
#include "../testResource.h"

static int sceneIdx = -1; 

#define MAX_LAYER	6

static CCLayer* createShaderLayer(int nIndex)
{
	switch (sceneIdx)
	{
	case 0: return new ShaderMonjori();
	case 1: return new ShaderMandelbrot();
	case 2: return new ShaderJulia();
	case 3: return new ShaderHeart();
	case 4: return new ShaderFlower();
	case 5: return new ShaderPlasma();
	}

	return NULL;
}

static CCLayer* nextAction(void)
{
	sceneIdx++;
	sceneIdx = sceneIdx % MAX_LAYER;

	CCLayer* pLayer = createShaderLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

static CCLayer* backAction(void)
{
	sceneIdx--;
	int total = MAX_LAYER;
	if( sceneIdx < 0 )
		sceneIdx += total;	
	
	CCLayer* pLayer = createShaderLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}

static CCLayer* restartAction(void)
{
	CCLayer* pLayer = createShaderLayer(sceneIdx);
	pLayer->autorelease();

	return pLayer;
}


ShaderTestDemo::ShaderTestDemo()
{

}

bool ShaderTestDemo::init()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CCLabelTTF *label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 26);
	addChild(label, 1);
	label->setPosition(ccp(s.width/2, s.height-50));
	label->setColor(ccRED);

	std::string subtitle = this->subtitle();
	if (subtitle.length() > 0)
	{
		CCLabelTTF *l = CCLabelTTF::labelWithString(subtitle.c_str(), "Thonburi", 16);
		addChild(l, 1);
		l->setPosition(ccp(s.width/2, s.height-80));
	}

	CCMenuItemImage *item1 = CCMenuItemImage::itemWithNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(ShaderTestDemo::backCallback));
	CCMenuItemImage *item2 = CCMenuItemImage::itemWithNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(ShaderTestDemo::restartCallback));
	CCMenuItemImage *item3 = CCMenuItemImage::itemWithNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(ShaderTestDemo::nextCallback));

	CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

	menu->setPosition(ccp(0, 0));
	item1->setPosition(s.width/2-100, 30);
	item2->setPosition(s.width/2, 30);
	item3->setPosition(s.width/2 + 100, 30);
	addChild(menu, 1);

	return true;
}


void ShaderTestDemo::backCallback(CCObject* pSender)
{
	CCScene* s = new ShaderTestScene();
	s->addChild( backAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void ShaderTestDemo::nextCallback(CCObject* pSender)
{
	CCScene* s = new ShaderTestScene();//CCScene::node();
	s->addChild( nextAction() );
	CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

std::string ShaderTestDemo::title()
{
	return "No title";
}

std::string ShaderTestDemo::subtitle()
{
	return "";
}

void ShaderTestDemo::restartCallback(CCObject* pSender)
{
	CCScene* s = new ShaderTestScene();
	s->addChild(restartAction()); 

	CCDirector::sharedDirector()->replaceScene(s);
    s->release();	
}

///---------------------------------------
// 
// ShaderNode
// 
///---------------------------------------
enum 
{
	SIZE_X = 256,
	SIZE_Y = 256,
};

ShaderNode::ShaderNode()
:m_center(vertex2(0.0f, 0.0f))
,m_resolution(vertex2(0.0f, 0.0f))
,m_time(0.0f)
,m_uniformCenter(0)
,m_uniformResolution(0)
,m_uniformTime(0)
{
}

ShaderNode* ShaderNode::shaderNodeWithVertex(const char *vert, const char *frag)
{
	ShaderNode *node = new ShaderNode();
	node->initWithVertex(vert, frag);
	node->autorelease();

	return node;
}

bool ShaderNode::initWithVertex(const char *vert, const char *frag)
{

	loadShaderVertex(vert, frag);

    m_time = 0;
	m_resolution = vertex2(SIZE_X, SIZE_Y);

	scheduleUpdate();

	setContentSize(CCSizeMake(SIZE_X, SIZE_Y));
	setAnchorPoint(ccp(0.5f, 0.5f));

	return true;
}

void ShaderNode::loadShaderVertex(const char *vert, const char *frag)
{
	CCGLProgram *shader = new CCGLProgram();
	shader->initWithVertexShaderFilename(vert, frag);

	shader->addAttribute("aVertex", kCCVertexAttrib_Position);
	shader->link();

	shader->updateUniforms();

	m_uniformCenter = glGetUniformLocation(shader->getProgram(), "center");
	m_uniformResolution = glGetUniformLocation(shader->getProgram(), "resolution");
	m_uniformTime = glGetUniformLocation(shader->getProgram(), "time");

	this->setShaderProgram(shader);

    shader->release();
}

void ShaderNode::update(ccTime dt)
{
	m_time += dt;
}

void ShaderNode::setPosition(CCPoint &newPosition)
{
	CCNode::setPosition(newPosition);
	CCPoint position = getPosition();
	m_center = vertex2(position.x * CC_CONTENT_SCALE_FACTOR(), position.y * CC_CONTENT_SCALE_FACTOR());
}

void ShaderNode::draw()
{
	CC_NODE_DRAW_SETUP();

	float w = SIZE_X, h = SIZE_Y;
	GLfloat vertices[12] = {0,0, w,0, w,h, 0,0, 0,h, w,h};

    //
	// Uniforms
	//
	getShaderProgram()->setUniformLocationWith2f(m_uniformCenter, m_center.x, m_center.y);
	getShaderProgram()->setUniformLocationWith2f(m_uniformResolution, m_resolution.x, m_resolution.y);

    // time changes all the time, so it is Ok to call OpenGL directly, and not the "cached" version
	glUniform1f(m_uniformTime, m_time);

	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	CC_INCREMENT_GL_DRAWS(1);
}


/// ShaderMonjori

ShaderMonjori::ShaderMonjori()
{
	init();
}

bool ShaderMonjori::init()
{
	if (ShaderTestDemo::init())
	{
		ShaderNode *sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Monjori.vsh", "Shaders/example_Monjori.fsh");

	    CCSize s = CCDirector::sharedDirector()->getWinSize();
	    sn->setPosition(ccp(s.width/2, s.height/2));

	    addChild(sn);

		return true;
	}

	return false;
}

std::string ShaderMonjori::title()
{
	return "Shader: Frag shader";
}

std::string ShaderMonjori::subtitle()
{
	return "Monjori plane deformations";
}


/// ShaderMandelbrot
ShaderMandelbrot::ShaderMandelbrot()
{
	init();
}

bool ShaderMandelbrot::init()
{
	if (ShaderTestDemo::init())
	{
		ShaderNode *sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Mandelbrot.vsh", "Shaders/example_Mandelbrot.fsh");

	    CCSize s = CCDirector::sharedDirector()->getWinSize();
	    sn->setPosition(ccp(s.width/2, s.height/2));

	    addChild(sn);

		return true;
	}
	
	return false;
}

std::string ShaderMandelbrot::title()
{
	return "Shader: Frag shader";
}

std::string ShaderMandelbrot::subtitle()
{
	return "Mandelbrot shader with Zoom";
}

/// ShaderJulia
ShaderJulia::ShaderJulia()
{
	init();
}

bool ShaderJulia::init()
{
	if (ShaderTestDemo::init())
	{
		ShaderNode *sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Julia.vsh", "Shaders/example_Julia.fsh");

		CCSize s = CCDirector::sharedDirector()->getWinSize();
		sn->setPosition(ccp(s.width/2, s.height/2));

		addChild(sn);

		return true;
	}

	return false;
}

std::string ShaderJulia::title()
{
	return "Shader: Frag shader";
}

std::string ShaderJulia::subtitle()
{
	return "Julia shader";
}


/// ShaderHeart
ShaderHeart::ShaderHeart()
{
	init();
}

bool ShaderHeart::init()
{
	if (ShaderTestDemo::init())
	{
		ShaderNode *sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Heart.vsh", "Shaders/example_Heart.fsh");

		CCSize s = CCDirector::sharedDirector()->getWinSize();
		sn->setPosition(ccp(s.width/2, s.height/2));

		addChild(sn);

		return true;
	}

	return false;
}

std::string ShaderHeart::title()
{
	return "Shader: Frag shader";
}

std::string ShaderHeart::subtitle()
{
	return "Heart";
}

/// ShaderFlower
ShaderFlower::ShaderFlower()
{
	init();
}

bool ShaderFlower::init()
{
	if (ShaderTestDemo::init())
	{
		ShaderNode *sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Flower.vsh", "Shaders/example_Flower.fsh");

		CCSize s = CCDirector::sharedDirector()->getWinSize();
		sn->setPosition(ccp(s.width/2, s.height/2));

		addChild(sn);

		return true;
	}

	return false;
}

std::string ShaderFlower::title()
{
	return "Shader: Frag shader";
}

std::string ShaderFlower::subtitle()
{
	return "Flower";
}

/// ShaderPlasma
ShaderPlasma::ShaderPlasma()
{
	init();
}

bool ShaderPlasma::init()
{
	if (ShaderTestDemo::init())
	{
		ShaderNode *sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Plasma.vsh", "Shaders/example_Plasma.fsh");

		CCSize s = CCDirector::sharedDirector()->getWinSize();
		sn->setPosition(ccp(s.width/2, s.height/2));

		addChild(sn);

		return true;
	}

	return false;
}

std::string ShaderPlasma::title()
{
	return "Shader: Frag shader";
}

std::string ShaderPlasma::subtitle()
{
	return "Plasma";
}

///---------------------------------------
// 
// ShaderTestScene
// 
///---------------------------------------
void ShaderTestScene::runThisTest()
{
	sceneIdx = -1;
    addChild(nextAction());

    CCDirector::sharedDirector()->replaceScene(this);
}
