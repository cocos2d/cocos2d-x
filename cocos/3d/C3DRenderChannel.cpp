#include "C3DRenderChannel.h"
#include "Base.h"
#include "C3DModel.h"
#include "C3DParticleRender.h"

namespace cocos3d
{

// -----------------------------------------------------------------------------
// Section: C3DRenderChannel
// -----------------------------------------------------------------------------

ChannelDrawItem::ChannelDrawItem()
{
	_sortInternal = false;
}

ChannelDrawItem::~ChannelDrawItem()
{
	
}


void ChannelDrawItem::init( float distance, C3DModel* model )
{
	_distance = distance;
	_model = model;
	
}

void ChannelDrawItem::fini()
{	
	_model = NULL;
}


/**
 *	This method draws the draw item.
 */
void ChannelDrawItem::draw()
{
	
	if (_sortInternal)
	{
		drawSorted();
	}
	else
	{
		drawUnsorted();
	}
}


/*
 *	This method sorts the draw item's triangles and then draws them
 */
void ChannelDrawItem::drawSorted()
{	
	
}

/*
 *	This method draws the draw item without sorting the triangles first,
 *	this is an optimisation for additive objects
 */
void ChannelDrawItem::drawUnsorted()
{
	_model->draw();
	
}

// Helper function for sorting two draw items
bool greater( const ChannelDrawItem* a, const ChannelDrawItem* b )
{
    return a->distance() > b->distance();
}
    
bool less(const ChannelDrawItem* a, const ChannelDrawItem* b)
{
    return a->distance() < b->distance();
}
    
    SortedChannel::SortedChannel(SortedChannel::SortType type )
{
    if (type == SortedChannel::Greater)
    {
        compare = greater;
    }
    else
        compare = less;
}

SortedChannel::~SortedChannel()
{	
	if(_drawItems.size() > 0)
	{
		for(std::vector<ChannelDrawItem*>::iterator iter=_drawItems.begin(); iter!=_drawItems.end(); ++iter)
		{
			SAFE_DELETE(*iter);
		}
		_drawItems.begin();
	}


}

	

/**
 *	This method creates a draw item and adds it to the sorted channel
 *
 */
void SortedChannel::addItem( float zDistance, C3DModel* model )
{	
	ChannelDrawItem* pDrawItem =  new ChannelDrawItem();
	pDrawItem->init( zDistance, model );
	
	_drawItems.push_back( pDrawItem );
}





bool s_alreadySorted = false;
/**
 *	This method renders the sorted channel, first it sorts the draw items back to front
 *	then it asks each one to draw itself.
 */
void SortedChannel::draw(bool clear /*=true*/)
{		
	if (!s_alreadySorted)
	{
		std::sort( _drawItems.rbegin() , _drawItems.rend(), compare );
		s_alreadySorted=!clear;
	}			

	std::vector< ChannelDrawItem* >::iterator it = _drawItems.begin();
	std::vector< ChannelDrawItem* >::iterator end = _drawItems.end();
	while (it != end)
	{
		if (clear)
		{
			(*it)->draw();
			(*it)->fini();
		}
		else
		{			
			(*it)->draw();			
		}
		it++;
	}
	if (clear)
	{		
		s_alreadySorted=false;
	}
	
}

/**
 *	This method clears the sorted channel.
 */
void SortedChannel::clear()
{
	std::vector< ChannelDrawItem* >::iterator it  = _drawItems.begin();
	std::vector< ChannelDrawItem* >::iterator end = _drawItems.end();

	while (it != end)
	{
		(*it)->fini();
		SAFE_DELETE(*it);
		++it;
	}

	_drawItems.clear();

	s_alreadySorted=false;
}
    
    
//////////////////////////////////////////////////////////////////
ParticleRenderChannel::ParticleRenderChannel():_sorted(false)
{
    
}

void ParticleRenderChannel::addItem( float zDistance, C3DParticleRender* render )
{
    static ParticleDrawItem item;
    item._render = render;
    item._distance = zDistance;
    
    _drawItems.push_back(item);
    _sorted = false;
}
/**
* clear items
*/
void ParticleRenderChannel::clear()
{
    _drawItems.clear();
}
    
  static bool particlelt( const ParticleRenderChannel::ParticleDrawItem& a, const ParticleRenderChannel::ParticleDrawItem& b )
    {
        return a._distance > b._distance;
    }
/**
* draw
*/
void ParticleRenderChannel::draw(bool clear)
{
    if (!_sorted)
    {
        std::sort(_drawItems.begin(), _drawItems.end(), particlelt);
        _sorted = true;
    }
    for (size_t i = 0; i < _drawItems.size(); ++i) {
        C3DParticleRender* render = _drawItems[i]._render;
        render->prepareDraw();
		render->draw();
        render->flush();
    }

}
///////////////////////////////////////////////////////////////////////////////////

RenderChannelManager::RenderChannelManager()
{
}

RenderChannelManager::~RenderChannelManager()
{
	finiChannels();
}

void RenderChannelManager::add( const std::string& name, C3DRenderChannel* pChannel )
{	
	if (pChannel != NULL)
	{
		_RenderChannels[name] = pChannel;
	}
}


void RenderChannelManager::remove( const std::string& name )
{
	std::map< std::string, C3DRenderChannel* >::iterator it = _RenderChannels.find( name );
	if (it != _RenderChannels.end())
	{		

		it->second = NULL;
		_RenderChannels.erase( it );
	}
}


C3DRenderChannel* RenderChannelManager::getRenderChannel( const std::string& name )
{
	std::map< std::string, C3DRenderChannel* >::iterator it = _RenderChannels.find( name );
	if (it != _RenderChannels.end())
		return it->second;
	return NULL;
}

void RenderChannelManager::initChannels()
{
    add("opacity", new SortedChannel(SortedChannel::Less));
	add( "sorted", new SortedChannel );
    add("particlechannel", new ParticleRenderChannel);
}

void RenderChannelManager::finiChannels()
{
	for(std::map< std::string, C3DRenderChannel* >::iterator it = _RenderChannels.begin();it != _RenderChannels.end();++it)
	{
		SAFE_DELETE(it->second);
	}
	_RenderChannels.clear();
}

void RenderChannelManager::clearChannelItems()
{
	std::map< std::string, C3DRenderChannel* >::iterator it = _RenderChannels.begin();
	while (it != _RenderChannels.end())
	{
		(it++)->second->clear();
	}
}

void RenderChannelManager::draw()
{
	std::map< std::string, C3DRenderChannel* >::iterator it = _RenderChannels.begin();
	while (it != _RenderChannels.end())
	{
		(it++)->second->draw();
	}
}

} 