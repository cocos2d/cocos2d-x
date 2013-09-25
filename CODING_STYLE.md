# cocos2d-x C++ coding sytle


## Detailed information

Please, refer to this document for a detailed version of the cocos2d-x C++ coding sytle:

* [cocos2d-x c++ coding style](http://www.cocos2d-x.org/wiki/Cocos2d_c++_coding_style)


## Quick Sample

Use this sample as a quick reference. But DO READ the detailed doc for more info.

Header file:

```c++
/** 
 * We use Doxygen strings for documentation.
 * All public classes, methods, structs should be documented using Doxygen Strings
 */
class CC_DLL Sprite : public NodeRGBA, public TextureProtocol
{         /* class braces start in a new line */

/* no indentation here  for public, protected or private */
/* First add all the "public" stuff, then all the "protected" stuff, and finally all the "private" stuff
public:   

    /* we don't use tabs, we use spaces, and we use a 4 space identation */
    /* 1st add all static const */
    static const int INDEX_NOT_INITIALIZED = -1; 

    /* then add all the creators and other relevant static methods */    
    static Sprite* create();    
    static Sprite* create(const char *filename);    
    static Sprite* create(const char *filename, const Rect& rect);

    /* if applicable, then add the consturctors / destructors */        
    Sprite();    
    virtual ~Sprite(void);

	/* then add all the initialization methods */    
    /* notice that they are in the same order as the creators */
    virtual bool init(void);    
    virtual bool initWithTexture(Texture2D *texture);    
    virtual bool initWithTexture(Texture2D *texture, const Rect& rect);
    
    

    /* then add the regular instace methods */
    virtual void updateTransform(void);    
    virtual SpriteBatchNode* getBatchNode(void);
    virtual void setBatchNode(SpriteBatchNode *spriteBatchNode);
     

    /* then add all the overriden methods */
    /* notice that all overriden methods must use the 'override' keyword */
    /* overriden methods are not forced to have doxygen strings UNLESS they change the behavior in a non obvios way */
    virtual void setPosition(const Point& pos) override;
    virtual void setRotation(float rotation) override;
    virtual void setRotationX(float rotationX) override;

    
	/* once you finish with the 'public' methods, start with the 'protected' ones */
protected:

    /* protected methods are not forced to have Doxygen strings, but if they have it, better */
    void updateColor(void);
    virtual void setTextureCoords(Rect rect);

    /* After adding all the methods, add the ivars */
    /* all ivars must start with _ */
    /* Do not use Hungarian notation */
    TextureAtlas*       _textureAtlas;
    int                 _atlasIndex;
    SpriteBatchNode*    _batchNode;
};

```

Implementation file:

```c++
/* Do not use doxygen comments on the implementation file */

/* The methos MUST be in the same order as where declared in the header file */

Sprite* Sprite::create(const char *filename)
{
	/* Don't use tabs. Use spaces. Use 4-space indentation */
    Sprite *sprite = new Sprite();

	/* put curly braces in the same line as in the 'if'*/
	/* leave a space between the 'if' and the '(' */
	/* don't leave spaces between '()' */
    if (sprite && sprite->initWithFile(filename)) {   
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

/* Initialization list can be indented to 0 spaces, or to 4 spaces. If in doubt, be consistent with the indentation already used in the file */
/* Only use the Initialization lists for types that can't fail when initialized */
Sprite::Sprite()
: _shouldBeHidden(false)
, _texture(nullptr)
, _physicsBody(nullptr)
{
}

/* use the 'initXXX' methods to initialize types that might fail */
bool Sprite::initWithTexture(Texture2D *texture, const Rect& rect, bool rotated)
{
    /* it ok not use use curly braces */
    if (something)
    	do_something();
    else
    	something_else();

    /* but if you use curly branches in one branch, all the branches should use curly branches */
    if (something) {
    	do_something1();
    	do_something2();
    } else {
    	so_something_else();
    }
}

```
