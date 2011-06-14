#include "../effects/CCGrid.h"
#include "NdCxList.h"

namespace NdCxControl 
{
    #define FLOAT_EQUAL(x,y)    (fabs((x)-(y)) < 0.0001f)

    NdCxList::NdCxList(float row_height, ccColor4B bg_color, CCSize size) 
          : sel_item_(NULL)
          , row_height_(row_height)
          , old_y_(0.f)
          , min_y_(0.f)
          , max_y_(0.f)
          , touch_began_y_(0.f)
          , touch_ended_y_(0.f)
          , snap_flag_(false)
          , list_state_(LS_WAITING)
          , item_click_listener_(NULL)
    {
        if (size.width <= 0 || size.height <= 0)
        {
            size = CCDirector::sharedDirector()->getWinSize();
        }

        initWithColorWidthHeight(bg_color, size.width, size.height);

        inner_panel_ = CCLayer::node();
        inner_panel_->setPosition(CCPointZero);
        inner_panel_->setContentSize(size);
        CCLayerColor::addChild(inner_panel_);

        line_color_ = ccc3(0xBD, 0xBD, 0xBD);
        sel_item_end_color_ = ccc3(0, 0xFF, 0xFF);
        sel_item_start_color_ = ccc3(0xFF, 0xFF, 0);
    }

    NdCxList::~NdCxList(void) 
    {
        inner_panel_->removeAllChildrenWithCleanup(true);
    }

    int NdCxList::addChild(NdCxListItem *item, bool scroll_to_view)
    {
        inner_panel_->addChild(item);
        item->release();

        CCArray *children = inner_panel_->getChildren();
        int item_count = children->count();
        if (1 == item_count)
        {
            item->setDrawTopLine(true);
        }

        CCSize panel_size = inner_panel_->getContentSize();

        item->setLineColor(line_color_);
        item->setSelectedColor(sel_item_start_color_, sel_item_end_color_);
        item->initWithWidthHeight(panel_size.width, row_height_);
        item->requestLayout();

        // 计算位置，item的高度可能在调用requestLayout后有所变化
        float item_y_pos = 0.f;
        CCSize item_size = item->getContentSize();
        if (item_count > 1)
        {
            CCNode *last_child = (CCNode *)children->objectAtIndex(item_count - 2);
            item_y_pos = last_child->getPosition().y - item_size.height;
        }
        else
        {
            item_y_pos = panel_size.height - item_size.height;
        }

        item->setPosition(CCPointMake(0, item_y_pos));

        float total_height = 0.f;
        for (int i = 0; i < (int)children->count(); ++i)
        {
            total_height += ((CCNode *)children->objectAtIndex(i))->getContentSize().height;
        }

        if (total_height > panel_size.height)
        {
            max_y_ = total_height - panel_size.height;
        }
        else
        {
            max_y_ = 0;
        }

        int rst = children->count() - 1;
        if (scroll_to_view && (rst + 1) * row_height_ > panel_size.height)
        {
            doFitPos(max_y_);
        }

        return rst;
    }

    NdCxListItem *NdCxList::getChild(int row_index)
    {
        return (NdCxListItem *)inner_panel_->getChildren()->objectAtIndex(row_index);
    }

    void NdCxList::clear(void)
    {
        inner_panel_->removeAllChildrenWithCleanup(true);
        sel_item_ = NULL;
        old_y_ = 0.f;
        min_y_ = 0.f;
        max_y_ = 0.f;
        touch_began_y_ = 0.f;
        touch_ended_y_ = 0.f;
        snap_flag_ = false;
        list_state_ = LS_WAITING;
        inner_panel_->setPosition(CCPointZero);
    }
    
    void NdCxList::onEnter(void)
    {
        setIsTouchEnabled(true);
        CCLayerColor::onEnter();
    }

    void NdCxList::onExit(void)
    {
        setIsTouchEnabled(false);
        CCLayerColor::onExit();
    }

    void NdCxList::registerWithTouchDispatcher()
    {
        CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, INT_MIN+9999, false);
    }

    bool NdCxList::ccTouchBegan(CCTouch* touch, CCEvent* event)
    {
        if (!containsTouchLocation(touch) || !getIsVisible())
        {
            return false;
        }

        CCArray *children = inner_panel_->getChildren();
        if (LS_WAITING != list_state_ || !m_bIsVisible || !children)
        {
            return false;
        }

        list_state_ = LS_TRACKINGTOUCH;
        CCPoint touchPoint = touch->locationInView(touch->view());
        old_y_ = inner_panel_->getPosition().y;
        touch_began_y_ = touch_ended_y_ = CCDirector::sharedDirector()->convertToGL(touchPoint).y;
        
        snap_flag_ = true;

        NdCxListItem *sel_item = itemForTouch(touch);
        if (sel_item && sel_item != sel_item_)
        {
            sel_item->selected();
            if (sel_item_)
            {
                sel_item_->unselected();
            }
        }
        
        sel_item_ = sel_item;

        //CCTime::gettimeofdayCocos2d(&touch_began_time_, NULL);
        touch_began_time_ = clock();

        return true;
    }

    void NdCxList::doFitPos(float y_pos)
    {
        inner_panel_->stopAllActions();

        CCMoveTo *move_to = new CCMoveTo();
        move_to->initWithDuration(0.66f, CCPointMake(0, y_pos));
        CCEaseExponentialOut *ease_action = new CCEaseExponentialOut();
        ease_action->initWithAction(move_to);
        move_to->release();
        inner_panel_->runAction(ease_action);
        ease_action->release();
    }

    void NdCxList::ccTouchEnded(CCTouch* touch, CCEvent* event)
    {
        if (LS_TRACKINGTOUCH != list_state_)
        {
            return;
        }

        if (sel_item_)
        {
            if (FLOAT_EQUAL(touch_began_y_, touch_ended_y_))
            {
                if (item_click_listener_)
                {
                    item_click_listener_->onClick(
                        inner_panel_->getChildren()->indexOfObject(sel_item_), sel_item_);
                }
#ifdef  ENABLE_LUA
				else if (m_scriptSeletor.size())
				{
					CCLuaScriptModule::sharedLuaScriptModule()->executeListItem(m_scriptSeletor,
						inner_panel_->getChildren()->indexOfObject(sel_item_), sel_item_);
				}
#endif

                onItemClick(inner_panel_->getChildren()->indexOfObject(sel_item_), sel_item_);
            }           
        }

        // 如果超出范围，则反弹回去。
        CCPoint pos = inner_panel_->getPosition();
        if (FLOAT_EQUAL(min_y_, max_y_))
        {
            if (!FLOAT_EQUAL(pos.y, 0.f))
            {
                doFitPos(0.f);
            }
        }
        else
        {
            if (pos.y < min_y_)
            {
                doFitPos(min_y_);
            }
            else if (pos.y > max_y_)
            {
                doFitPos(max_y_);
            }
            else
            {
                if (!FLOAT_EQUAL(touch_began_y_, touch_ended_y_))
                {
                    float acce_val = 0.f;
                    float fit_pos = inner_panel_->getPosition().y;
                    float abs_distance = fabs(touch_ended_y_ - touch_began_y_);

                    /*cc_timeval end_time, sub_time;
                    CCTime::gettimeofdayCocos2d(&end_time, NULL);
                    CCTime::timersubCocos2d(&sub_time, &touch_began_time_, &end_time);
                    int time_consume = sub_time.tv_sec * 1000 + sub_time.tv_usec/1000;*/
                    int time_consume = clock() - touch_began_time_;
                    if (time_consume < 400 && abs_distance > row_height_)
                    {
                        acce_val = (abs_distance / row_height_) * 3.f * row_height_;
                    }
                    else
                    {
                        acce_val = float((int)row_height_ / 3);
                    }                    

                    // 向下拖拽
                    if (touch_began_y_ > touch_ended_y_)
                    {
                        fit_pos -= acce_val;
                        if (fit_pos < min_y_)
                        {
                            fit_pos = min_y_;
                        }
                    }
                    else
                    {
                        fit_pos += acce_val;
                        if (fit_pos > max_y_)
                        {
                            fit_pos = max_y_;
                        }
                    }

                    doFitPos(fit_pos);
                }
            }
        }

        list_state_ = LS_WAITING;
    }

    void NdCxList::ccTouchCancelled(CCTouch *touch, CCEvent *event)
    {
        list_state_ = LS_WAITING;
    }

    void NdCxList::ccTouchMoved(CCTouch* touch, CCEvent* event)
    {
        if (LS_TRACKINGTOUCH != list_state_)
        {
            return;
        }

        CCPoint touchPoint = touch->locationInView(touch->view());
        touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);         
        touch_ended_y_ = touchPoint.y;

        if (snap_flag_ && fabs(touch_ended_y_ - touch_began_y_) < 15.f)
        {
            return;
        }

        snap_flag_ = false;
        
        inner_panel_->setPosition(CCPointMake(inner_panel_->getPosition().x, 
            old_y_ + (touch_ended_y_ - touch_began_y_)));
    }

    void NdCxList::destroy(void)
    {
        release();
    }

    void NdCxList::keep(void)
    {
        retain();
    }

    NdCxListItem* NdCxList::itemForTouch(CCTouch * touch)
    {
        CCArray *children = inner_panel_->getChildren();
        if (!children || !children->count())
        {
            return NULL;
        }

        CCPoint touch_loc = touch->locationInView(touch->view());
        touch_loc = CCDirector::sharedDirector()->convertToGL(touch_loc);
        CCPoint local_loc = inner_panel_->convertToNodeSpace(touch_loc);

        for (int i = 0, l = (int)children->count(); i != l; ++i)
        {
            CCNode *node = (CCNode *)children->objectAtIndex(i);
            if (CCRect::CCRectContainsPoint(node->boundingBox(), local_loc))
            {
                return (NdCxListItem*)node;
            }
        }
        
        return NULL;
    }

    void NdCxList::selectChild(int row_index)
    {
        CCArray *children = inner_panel_->getChildren();
        if (!children || !children->count() || row_index < 0 || row_index >= (int)children->count())
        {
            return;
        }

        NdCxListItem *sel_item = (NdCxListItem *)children->objectAtIndex(row_index);
        if (sel_item != sel_item_)
        {
            sel_item->selected();

            if (sel_item_)
            {
                sel_item_->unselected();
            }

            sel_item_ = sel_item;

            CCSize panel_size = inner_panel_->getContentSize();
            CCArray *children = inner_panel_->getChildren();
            float inc_height = 0.f;
            for (int i = 0; i <= row_index; ++i)
            {
                inc_height += ((CCNode *)children->objectAtIndex(i))->getContentSize().height;
            }

            if (inc_height > panel_size.height)
            {
                doFitPos(inc_height - panel_size.height);
            }
        }
    }

    NdCxListItem *NdCxList::getSelectedChild(void)
    {
        return sel_item_;
    }

    void NdCxList::setLineColor(ccColor3B &color)
    {
        line_color_ = color;
    }

    void NdCxList::setSelectedItemColor(ccColor3B &start_color, ccColor3B &end_color)
    {
        sel_item_start_color_ = start_color;
        sel_item_end_color_ = end_color;
    }

    int NdCxList::getChildCount(void)
    {
        CCArray *children = inner_panel_->getChildren();
        if (!children)
        {
            return 0;
        }
        else
        {
            return children->count();
        }
    }

    void NdCxList::setRowHeight(float height)
    {
        row_height_ = height;
    }

    float NdCxList::getRowHeight(void)
    {
        return row_height_;
    }

    void NdCxList::registerItemClickListener(NdCxListItemClickListener *listener)
    {
        item_click_listener_ = listener;
    }

    void NdCxList::unregisterItemClickListener(void)
    {
        item_click_listener_ = NULL;
		
#ifdef  ENABLE_LUA
		m_scriptSeletor.clear();
#endif
    }
#ifdef  ENABLE_LUA
	void NdCxList::registerItemClickListener(const char* szSeletor)
	{
		if (szSeletor)
		{
			m_scriptSeletor = szSeletor;
		}
		else
		{
			CCLog("registerItemClickListener Error szSelector == null");
		}
	}
#endif

    void NdCxList::visit(void)
    {
        // quick return if not visible
        if (!m_bIsVisible)
        {
            return;
        }
        glPushMatrix();

        /*if (m_pGrid && m_pGrid->isActive())
        {
            m_pGrid->beforeDraw();
            this->transformAncestors();
        }*/

        this->transform();

        CCNode* pNode = NULL;
        unsigned int i = 0;

        if(m_pChildren && m_pChildren->count() > 0)
        {
            // draw children zOrder < 0
            ccArray *arrayData = m_pChildren->data;
            for( ; i < arrayData->num; i++ )
            {
                pNode = (CCNode*) arrayData->arr[i];

                if ( pNode && pNode->getZOrder() < 0 ) 
                {
                    pNode->visit();
                }
                else
                {
                    break;
                }
            }
        }

        // self draw
        this->draw();

        // 左下角世界坐标
        CCPoint world_pt = convertToWorldSpace(CCPointZero);
        CCPoint ui_pt = CCDirector::sharedDirector()->convertToUI(world_pt);
        CCPoint gl_pt = CCDirector::sharedDirector()->convertToGL(ui_pt);

        glEnable(GL_SCISSOR_TEST);
        glScissor((GLsizei)gl_pt.x, (GLsizei)gl_pt.y, (GLsizei)m_tContentSize.width, (GLsizei)m_tContentSize.height);

        // draw children zOrder >= 0
        if (m_pChildren && m_pChildren->count() > 0)
        {
            ccArray *arrayData = m_pChildren->data;
            for( ; i < arrayData->num; i++ )
            {
                pNode = (CCNode*) arrayData->arr[i];
                if (pNode)
                {
                    pNode->visit();
                }
            }		
        }

        glDisable(GL_SCISSOR_TEST);

        glPopMatrix();
    }
}

