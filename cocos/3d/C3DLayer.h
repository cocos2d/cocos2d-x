#ifndef __C3DLayer_H__
#define __C3DLayer_H__

#include "cocos3d.h"
#include "cocos2d.h"

#include "CCNode.h"
//#include "touch_dispatcher/CCTouchDelegateProtocol.h"

//#include "EnumDef.h"
#include <string>

#include "C3DRenderState.h"

namespace cocos2d
{
class C3DSceneNode;
class Rectangle;
class C3DVector4;
class C3DScene;
class C3DRenderSystem;
class C3DViewport;
class C3DStateBlock;
class C3DStatRender;
class C3DSpriteManager;

/**
*Defines the 3DLayer.
*This class  is the 3D entry.One 3d layer have one scene.you can use 3d layer to interactive with 2d layer.
*/
class  C3DLayer :  public cocos2d::CCLayer
{  

public:
    C3DLayer();
    virtual ~C3DLayer();   
    virtual bool init();
 
    CREATE_FUNC(C3DLayer);  

    virtual void onEnter();

    virtual void onExit();

    // optional
	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event){};
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event){};
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event){};
	virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event){};


   // virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){};
  //  virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){};
  //  virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){};
  //  virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){};

    enum State //The game states.
    {
        UNINITIALIZED,
        RUNNING,
        PAUSED
    };

    enum MoveType
    {
        MoveType_2D = 0,
        MoveType_3D
    };


    State getState() const;     
   
    void pause();
    void resume();
    void exit();     
    
    virtual MoveType getMoveType(){ return MoveType_2D; }
    
    unsigned int getWidth() const;
    unsigned int getHeight() const;

    void setSize(unsigned int width, unsigned int height);

    /**
     * initialize callback that is called when the game on inits.
     */
    void initialize();
        
    void finalize();
      
    virtual void update(long elapsedTime);
    virtual void update(float delta);// overwrite CCLayer update
    virtual void draw(void);//render the 3d contents

    virtual void beginRender(); // prepare render states
    virtual void render(long elapsedTime);
    virtual void endRender();   // restore render states

    /**
     * Gets the game main scene.
     * 
     * @return The game main scene.
     */
    cocos2d::C3DScene* getScene3D() { return _scene; };

    void showBoundingBox(bool bShow);

    /**
     * Gets the total absolute running time (in milliseconds) since Game::run().
     * 
     * @return The total absolute running time (in milliseconds).
     */
    static long getAbsoluteTime();

    /**
     * Gets the total game time (in milliseconds). This is the total accumulated game time (unpaused).
     *
     * You would typically use things in your game that you want to stop when the game is paused.
     * This includes things such as game physics and animation.
     * 
     * @return The total game time (in milliseconds).
     */
    static long getGameTime();

    static C3DLayer* getMainLayer();

    void setAsMainLayer();

    const C3DViewport* getViewport() const;

private:    
    bool init3D();

protected:
    
    bool startup();   
    void shutdown();    

    bool _initialized;                          // If game has initialized yet.
     
    unsigned int _width;                        // The game's display width.
    unsigned int _height;                       // The game's display height.
  
    State _state;   
    C3DRenderSystem* _renderSystem;

    C3DScene* _scene;   //The Game main scene.
    
    C3DStateBlock* _2DState; // cocos2d opengl state backup
    
    // backup render states
    GLint _enablePos;
    GLint _enableColor;
    GLint _enableTex;
    GLint _texture;
    GLint _oldViewport[4];
    float _oldClearColor[4];
 
    C3DSpriteManager* _spriteManager;
};
}
#endif 
