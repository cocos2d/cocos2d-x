
#include "NdCxListItem.h"

namespace NdCxControl 
{
    NdCxListItem::NdCxListItem(void) 
              : selected_(false)
              , draw_top_line_(false)
              , draw_bottom_line_(true)
              , horizontal_margin_(10.f)
              , vertical_margin_(10.f)
    {
    }
    
    NdCxListItem::~NdCxListItem(void) 
    {
    }
    
    void NdCxListItem::updateColor(void)
    {
        const unsigned int l = sizeof(m_pSquareColors) / sizeof(m_pSquareColors[0]);

        if (selected_)
        {
            ccColor3B color = sel_item_start_color_;
            const unsigned int half = l / 2;
            for (unsigned int i=0; i < l; ++i)
            {
                if (i >= half)
                {
                    color = sel_item_end_color_;
                }

                if (i % 4 == 0)
                    m_pSquareColors[i] = color.r;
                else if (i % 4 == 1)
                    m_pSquareColors[i] = color.g;
                else if (i % 4 ==2)
                    m_pSquareColors[i] = color.b;
                else
                    m_pSquareColors[i] = m_cOpacity;
            }
        }
        else
        {
            for( unsigned int i=0; i < 4; i++ )
            {
                m_pSquareColors[i * 4]     = m_tColor.r;
                m_pSquareColors[i * 4 + 1] = m_tColor.g;
                m_pSquareColors[i * 4 + 2] = m_tColor.b;
                m_pSquareColors[i * 4 + 3] = m_cOpacity;
            }
        }
    }

    void NdCxListItem::draw(void)
    {
        updateColor();

        CCSize size = getContentSize();
        if (selected_)
        {
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glDisable(GL_TEXTURE_2D);
            glShadeModel(GL_SMOOTH);

            glVertexPointer(2, GL_FLOAT, 0, m_pSquareVertices);
            glColorPointer(4, GL_UNSIGNED_BYTE, 0, m_pSquareColors);

            bool newBlend = false;
            if( m_tBlendFunc.src != CC_BLEND_SRC || m_tBlendFunc.dst != CC_BLEND_DST ) {
                newBlend = true;
                glBlendFunc(m_tBlendFunc.src, m_tBlendFunc.dst);
            }
            else if( m_cOpacity != 255 ) {
                newBlend = true;
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }

            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            if( newBlend )
                glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);

            // restore default GL state
            glShadeModel(GL_FLAT);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glEnable(GL_TEXTURE_2D);
        }
        else
        {
            CCLayerColor::draw();
        }
        
        glDisable(GL_LINE_SMOOTH);

        if (draw_top_line_)
        {
            glLineWidth(1.0f);
            glColor4ub(line_color_.r, line_color_.g, line_color_.b, 0xFF);
            ccDrawLine(CCPointMake(0, size.height-0.5f), CCPointMake(size.width, size.height-0.5f));
        }

        if (draw_bottom_line_)
        {
            glLineWidth(1.0f);
            glColor4ub(line_color_.r, line_color_.g, line_color_.b, 0xFF);
            ccDrawLine(CCPointMake(0, 0.5f), CCPointMake(size.width, 0.5f));
        }
    }

    CCRect NdCxListItem::rect(void)
    {
        return CCRectMake( m_tPosition.x - m_tContentSize.width * m_tAnchorPoint.x, 
            m_tPosition.y - m_tContentSize.height * m_tAnchorPoint.y,
            m_tContentSize.width, m_tContentSize.height);
    }
    
    void NdCxListItem::selected(void)
    {
        selected_ = true;
    }

    void NdCxListItem::unselected(void)
    {
        selected_ = false;
    }

    void NdCxListItem::setItemColor(const ccColor3B &color)
    {
        setColor(color);
    }

    void NdCxListItem::setMargin(CCSize margin)
    {
        horizontal_margin_ = margin.width;
        vertical_margin_ = margin.height;
    }

    CCSize NdCxListItem::getMargin(void)
    {
        return CCSizeMake(horizontal_margin_, vertical_margin_);
    }

    void NdCxListItem::addChild(NdCxListItemChild *child, const LayoutParam &layout)
    {
        addChild(child, layout, 0);
    }

    void NdCxListItem::addChild(NdCxListItemChild *child, const LayoutParam &layout, int tag)
    {
        layout_info_.insert(std::make_pair(child, layout));
        child->setIsRelativeAnchorPoint(false);
        CCLayerColor::addChild(child, 0, tag);
        child->release();
    }

    NdCxListItemChild *NdCxListItem::getChildByTag(int tag)
    {
        return (NdCxListItemChild *)CCLayerColor::getChildByTag(tag);
    }

    void NdCxListItem::requestLayout(void)
    {
        if (m_pChildren && m_pChildren->count() > 0)
        {
            CCPoint child_pos;
            CCSize size = getContentSize();
            CCPoint curr_pos;
            CCPoint prev_pos;
            float vertical_height = size.height;
            bool height_changed = false;

            for (int i = 0, l = m_pChildren->count(); i < l; ++i)
            {
                CCNode *it = (CCNode *)m_pChildren->objectAtIndex(i);
                if (!(it))
                {
                    break;
                }

                CCSize child_size = (*(it)).getContentSize();
                child_size.width *= (*(it)).getScaleX();
                child_size.height *= (*(it)).getScaleY();
                
                std::map<CCNode *, LayoutParam>::iterator pos = layout_info_.find(it);
                CCAssert(layout_info_.end() != pos, "!!");
                LayoutParam *lp = &pos->second;
                switch ((*lp).val_x.t)
                {
                case PARENT_CENTER:
                    child_pos.x = (size.width - child_size.width) / 2;
                    break;
                case HORIZONTAL_LEFT:
                    child_pos.x = horizontal_margin_;
                    break;
                case HORIZONTAL_RIGHT:
                    child_pos.x = size.width - child_size.width - horizontal_margin_;
                    break;
                case ABS_WITH_PIXEL:
                    child_pos.x = (float)(*lp).val_x.val.pixel_val;
                    break;
                case ABS_WITH_PERCENT:
                    child_pos.x = horizontal_margin_ + (*lp).val_x.val.percent_val * (size.width - 2*horizontal_margin_);
                    break;
                case REF_PREV_X_INC:
                    {
                        child_pos.x = prev_pos.x + (*lp).padding;
                        break;
                    }
                case REF_PREV_X_DEC:
                    {
                        child_pos.x = prev_pos.x - (*lp).padding;
                        break;
                    }
                case REL_FLOW:
                    child_pos.x = curr_pos.x + (*lp).padding;
                    break;
                }

                if (!(*lp).wrap)
                {
                    curr_pos.x = child_pos.x + child_size.width;
                }

                switch ((*lp).val_y.t)
                {
                case PARENT_CENTER:
                    {
                        if (child_size.height > vertical_height - 2*vertical_margin_)
                        {
                            vertical_height += child_size.height - (vertical_height - 2*vertical_margin_);
                            height_changed = true;
                        }

                        child_pos.y = (vertical_height - child_size.height)*0.5f;

                        break;
                    }
                case VERTICAL_TOP:
                    {
                        if (child_size.height > vertical_height - 2*vertical_margin_)
                        {
                            vertical_height += child_size.height - (vertical_height - 2*vertical_margin_);
                            height_changed = true;
                        }

                        child_pos.y = vertical_height - (child_size.height + vertical_margin_);

                        break;
                    }
                case VERTICAL_BOTTOM:
                    {
                        if (child_size.height > vertical_height - 2*vertical_margin_)
                        {
                            vertical_height += child_size.height - (vertical_height - 2*vertical_margin_);
                            height_changed = true;
                        }

                        child_pos.y = vertical_margin_;

                        break;
                    }
                case ABS_WITH_PIXEL:
                    {
                        child_pos.y = (float)(*lp).val_y.val.pixel_val;
                        if (child_pos.y + child_size.height > vertical_height - vertical_margin_)
                        {
                            vertical_height = child_pos.y + child_size.height + vertical_margin_;
                            height_changed = true;
                        }

                        break;
                    }
                case ABS_WITH_PERCENT:
                    {
                        child_pos.y = (*lp).val_y.val.percent_val * (vertical_height - 2*vertical_margin_);
                        if (child_pos.y + child_size.height > vertical_height - vertical_margin_)
                        {
                            vertical_height = child_pos.y + child_size.height + vertical_margin_;
                            height_changed = true;
                        }

                        break;
                    }
                case REF_PREV_Y_INC:
                    {
                        child_pos.y = prev_pos.y + (*lp).padding;
                        if (child_pos.y + child_size.height > + vertical_height - vertical_margin_)
                        {
                            vertical_height = child_pos.y + child_size.height + vertical_margin_;
                            height_changed = true;
                        }

                        break;
                    }
                case REF_PREV_Y_DEC:
                    {
                        child_pos.y = prev_pos.y - (child_size.height + (*lp).padding);
                        if (child_pos.y < vertical_margin_)
                        {
                            vertical_height += vertical_margin_-child_pos.y + vertical_margin_;
                            child_pos.y = vertical_margin_;
                            height_changed = true;
                        }
                        
                        break;
                    }                    
                case REL_FLOW:
                    {
                        child_pos.y = curr_pos.y + (*lp).padding;
                        if (child_pos.y + child_size.height > vertical_height - vertical_margin_)
                        {
                            vertical_height = curr_pos.y + child_size.height + vertical_margin_;
                            height_changed = true;
                        }

                        break;
                    }

                    curr_pos.y = child_pos.y + child_size.height;
                }
                
                prev_pos = child_pos;

                (*it).setPosition(child_pos);
            }

            setContentSize(CCSizeMake(size.width, vertical_height));

            if (height_changed)
            {
                requestLayout();
            }
        }
    }

    NdCxListItem *NdCxListItem::itemWithColor(const ccColor3B &color)
    {
        NdCxListItem *pRet = new NdCxListItem();
        pRet->setOpacity(255);
        pRet->setColor(color);
        return pRet;
    }

    bool NdCxListItem::initWithWidthHeight(GLfloat width, GLfloat height)
    {
        ccColor3B color = getColor();
        ccColor4B cl4b = { color.r, color.g, color.b, getOpacity() };
        return CCLayerColor::initWithColorWidthHeight(cl4b, width, height);
    }

    void NdCxListItem::setLineColor(const ccColor3B &color)
    {
        line_color_ = color;
    }

    void NdCxListItem::setSelectedColor(const ccColor3B &start_color, const ccColor3B &end_color)
    {
        sel_item_start_color_ = start_color;
        sel_item_end_color_ = end_color;
    }
}