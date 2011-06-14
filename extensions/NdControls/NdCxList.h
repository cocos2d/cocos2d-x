#ifndef __NDCX_LIST_H__
#define __NDCX_LIST_H__

#include <time.h>
#include "../platform/platform.h"
#include "NdCxListItem.h"
#include <vector>
using namespace cocos2d;
namespace NdCxControl 
{
	class NdCxListItem;
    typedef enum  
    {
        LS_WAITING,
        LS_TRACKINGTOUCH,
    } LIST_STATE;

    struct NdCxListItemClickListener
    {
		virtual void onClick(int index, NdCxListItem *item) = 0;
    };

    class NdCxList : public CCLayerColor
    {
    public:
        NdCxList(float row_height, 
                 ccColor4B bg_color, 
                 CCSize size);
        virtual ~NdCxList(void);

    public:
        int addChild(NdCxListItem *item, bool scroll_to_view);
        NdCxListItem *getChild(int row_index);
        void clear(void);
        
        void selectChild(int row_index);

        NdCxListItem *getSelectedChild(void);

        void setLineColor(ccColor3B &color);
        void setSelectedItemColor(ccColor3B &start_color, ccColor3B &end_color);
        int getChildCount(void);
        
        // 必须在添加item之前调用
        void setRowHeight(float height);
        float getRowHeight(void);
        
    public:
        virtual void onEnter(void);
        virtual void onExit(void);
        virtual void registerWithTouchDispatcher(void);
        virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
        virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
        virtual void ccTouchCancelled(CCTouch *touch, CCEvent* event);
        virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
        virtual void destroy(void);
        virtual void keep(void);

        virtual void registerItemClickListener(NdCxListItemClickListener *listener);
        virtual void unregisterItemClickListener(void);
#ifdef  ENABLE_LUA
		virtual void registerItemClickListener(const char* szSeletor);
#endif

    protected:
        virtual void onItemClick(int index, NdCxListItem *item) {}
        virtual void visit(void);

    private:
        NdCxListItem *itemForTouch(CCTouch * touch);
        void doLayout(void);
        void doFitPos(float y_pos);
        
        CCRect rect(void)
        {
            CCSize s = getContentSize();
            return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
        }

        bool containsTouchLocation(CCTouch* touch)
        {
            return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
        }

    private:
        NdCxListItem *sel_item_;
        float row_height_;
        LIST_STATE list_state_;
        CCLayer *inner_panel_;
        float touch_began_y_;
        float touch_ended_y_;
        float old_y_;
        float min_y_;
        float max_y_;
        bool snap_flag_;
        //cc_timeval touch_began_time_;
        clock_t touch_began_time_;
        ccColor3B line_color_;
        ccColor3B sel_item_start_color_;
        ccColor3B sel_item_end_color_;

        NdCxListItemClickListener *item_click_listener_;
#ifdef  ENABLE_LUA
		std::string m_scriptSeletor;
#endif
    };
}

#endif