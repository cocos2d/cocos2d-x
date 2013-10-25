#ifndef VISUAL_CHANNELS_H_
#define VISUAL_CHANNELS_H_

#include <string>
#include <map>
#include <vector>

namespace cocos3d
{

class C3DModel;
class C3DParticleRender;
    

/**
 * This is the base class for the primitives drawn by the visual channels.
 */
class ChannelDrawItem
{
public:
	/**
	 * Constructor & Destructor
	 */
	ChannelDrawItem();
	virtual ~ChannelDrawItem();

	/**
	 * draw this item
	 */
	void draw();

	/**
	 * init & fini item
	 */
	void init( float distance, C3DModel* model );
	void fini();

	/**
	 * get item distance
	 */
	float distance() const { return _distance; }

private:

	void drawSorted();
	void drawUnsorted();	

	// properties
	bool	_sortInternal;	// always true currently
	float	_distance;//distance to camera  
	C3DModel*  _model;      // model to draw
	
};
    




/**
 * This class is the base class and the manager for the visual channels. A 
 * channel is essentially a bucket of objects with similar rendering rules.
 * The channels are traversed fixed global order, and within each channel items
 * are drawn, possibly in a sorted order. 
 */
class C3DRenderChannel
{
public:
	/**
	 * Constructor & Destructor
	 */
	C3DRenderChannel(){};
	virtual ~C3DRenderChannel(){};

	/**
	 * add draw item
	 */
	virtual void addItem( float zDistance, C3DModel* model ){};
	/**
	 * clear
	 */
	virtual void clear(){};	
	/**
	 * draw routine
	 */
	virtual void draw(bool clear=false){};

	/**
	 * get channel name
	 */
    virtual const char* getName() { return ""; }

};

/**
 * This class implements the sorted channel, sorted objects are rendered after 
 * the main scene and the shimmer.
 */
class SortedChannel : public C3DRenderChannel
{
public:
    enum SortType
    {
        Greater,
        Less,
    };
	/**
	 * Constructor & Destructor
	 */
	SortedChannel(SortType type = Greater);
	virtual ~SortedChannel();

	/**
	 * add draw item
	 */
	void addItem( float zDistance, C3DModel* model );
	/**
	 * clear items
	 */
	void clear();
	/**
	 * draw
	 */
	void draw(bool clear=false);
	/**
	 * channe name
	 */
    virtual const char* getName() { return "sorted"; }

private:	
	std::vector< ChannelDrawItem* >		_drawItems;
    
    SortType _type;

    bool (*compare)( const ChannelDrawItem* a, const ChannelDrawItem* b );
};
   

class ParticleRenderChannel : public C3DRenderChannel
{
public:
    ParticleRenderChannel();
    virtual ~ParticleRenderChannel()
    {
        
    }
    
    /**
     * item drawn by particle channel
     */
    struct ParticleDrawItem
    {
        C3DParticleRender* _render;
        float _distance;
    };
    /**
	 * add draw item
	 */
	void addItem( float zDistance, C3DParticleRender* render );
	/**
	 * clear items
	 */
	void clear();
	/**
	 * draw
	 */
	void draw(bool clear=false);
	/**
	 * channe name
	 */
    virtual const char* getName() { return "particlechannel"; }
private:
	std::vector< ParticleDrawItem>		_drawItems;
    bool                                _sorted;
    
};

/**
 * This class manage all the render channel.
 */
class RenderChannelManager
{
public:
	/**
	 * Constructor & Destructor
	 */
	RenderChannelManager();
	virtual ~RenderChannelManager();	

	/**
	 * get channel by name
	 */
	C3DRenderChannel* getRenderChannel( const std::string& name );

	/**
	 * init & fini channels
	 */
	void initChannels();
	void finiChannels();
	/**
	 * clear channel items
	 */
	void clearChannelItems();

	/**
	 * draw routine
	 */
	void draw();
private:
	/**
	 * add & remove channel
	 */
	void add( const std::string& name, C3DRenderChannel* pChannel );
	void remove( const std::string& name );

	
private:
	std::map< std::string, C3DRenderChannel* > _RenderChannels;	

};


 



}
#endif // VISUAL_CHANNELS_H
