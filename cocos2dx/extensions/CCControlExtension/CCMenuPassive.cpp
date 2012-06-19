#include "CCMenuPassive.h"
#include "CCDirector.h"
#include "support/CCPointExtension.h"
#include "menu_nodes/CCMenuItem.h"
#include <vector>

using namespace std;

NS_CC_EXT_BEGIN

enum 
{
    kDefaultPadding =  5,
};

//
//CCMenu
//
CCMenuPassive* CCMenuPassive::node()
{
    return CCMenuPassive::create();
}

CCMenuPassive* CCMenuPassive::create()
{
    return create(NULL, NULL);
}

CCMenuPassive * CCMenuPassive::menuWithItems(CCNode* item, ...)
{
    va_list args;
    va_start(args,item);
    CCMenuPassive *pRet = new CCMenuPassive();
    if (pRet && pRet->initWithItems(item, args))
    {
        pRet->autorelease();
        va_end(args);
        return pRet;
    }
    va_end(args);
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCMenuPassive * CCMenuPassive::create(CCNode* item, ...)
{
    va_list args;
    va_start(args,item);
    CCMenuPassive *pRet = new CCMenuPassive();
    if (pRet && pRet->initWithItems(item, args))
    {
        pRet->autorelease();
        va_end(args);
        return pRet;
    }
    va_end(args);
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCMenuPassive* CCMenuPassive::menuWithItem(CCNode* item)
{
    return CCMenuPassive::createWithItem(item);
}

CCMenuPassive* CCMenuPassive::createWithItem(CCNode* item)
{
    return create(item, NULL);
}

bool CCMenuPassive::initWithItems(CCNode* item, va_list args)
{
    if (CCLayer::init())
    {
        //this->m_bIsTouchEnabled = false;

        // menu in the center of the screen
        CCSize s = CCDirector::sharedDirector()->getWinSize();

        // Set the default anchor point
        ignoreAnchorPointForPosition(true);
        setAnchorPoint(ccp(0.5f, 0.5f));
        this->setContentSize(s);

        setPosition(ccp(s.width/2, s.height/2));

        int z=0;

        if (item)
        {
            this->addChild(item, z);
            CCMenuItem *i = va_arg(args, CCMenuItem*);
            while (i)
            {
                z++;
                this->addChild(i, z);
                i = va_arg(args, CCMenuItem*);
            }
        }

        return true;
    }

    return false;
}


//Menu - Alignment
void CCMenuPassive::alignItemsVertically()
{
    this->alignItemsVerticallyWithPadding(kDefaultPadding);
}

void CCMenuPassive::alignItemsVerticallyWithPadding(float padding)
{
    float height = -padding;
    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCNode* pChild = dynamic_cast<CCNode*>(pObject);
            if (pChild)
            {
                height += pChild->getContentSize().height * pChild->getScaleY() + padding;
            }
        }
    }
    float width=0;
    float y = height / 2.0f;
    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCNode* pChild = dynamic_cast<CCNode*>(pObject);
            if (pChild)
            {
                width=max(width, pChild->getContentSize().width);
                pChild->setPosition(ccp(0, y - pChild->getContentSize().height * pChild->getScaleY() / 2.0f));
                y -= pChild->getContentSize().height * pChild->getScaleY() + padding;
            }
        }
    }
    setContentSize(CCSizeMake(width, height));
}

void CCMenuPassive::alignItemsHorizontally(void)
{
    this->alignItemsHorizontallyWithPadding(kDefaultPadding);
}

void CCMenuPassive::alignItemsHorizontallyWithPadding(float padding)
{

    float width = -padding;
    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCNode* pChild = dynamic_cast<CCNode*>(pObject);
            if (pChild)
            {
                width += pChild->getContentSize().width * pChild->getScaleX() + padding;
            }
        }
    }

    float height=0;
    float x = -width / 2.0f;
    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCNode* pChild = dynamic_cast<CCNode*>(pObject);
            if (pChild)
            {
                height=max(height, pChild->getContentSize().height);
                pChild->setPosition(ccp(x + pChild->getContentSize().width * pChild->getScaleX() / 2.0f, 0));
                 x += pChild->getContentSize().width * pChild->getScaleX() + padding;
            }
        }
    }        
    setContentSize(CCSizeMake(width, height));
}

void CCMenuPassive::alignItemsInColumns(unsigned int columns, ...)
{
    va_list args;
    va_start(args, columns);

    this->alignItemsInColumns(columns, args);

    va_end(args);
}

void CCMenuPassive::alignItemsInColumns(unsigned int columns, va_list args)
{
    vector<unsigned int> rows;
    while (columns)
    {
        rows.push_back(columns);
        columns = va_arg(args, unsigned int);
    }

    int height = -5;
    unsigned int row = 0;
    unsigned int rowHeight = 0;
    unsigned int columnsOccupied = 0;
    unsigned int rowColumns;

    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCNode* pChild = dynamic_cast<CCNode*>(pObject);
            if (pChild)
            {
                CCAssert(row < rows.size(), "");

                rowColumns = rows[row];
                // can not have zero columns on a row
                CCAssert(rowColumns, "");

                float tmp = pChild->getContentSize().height;
                rowHeight = (unsigned int)((rowHeight >= tmp || isnan(tmp)) ? rowHeight : tmp);

                ++columnsOccupied;
                if (columnsOccupied >= rowColumns)
                {
                    height += rowHeight + 5;

                    columnsOccupied = 0;
                    rowHeight = 0;
                    ++row;
                }
            }
        }
    }    

    // check if too many rows/columns for available menu items
    CCAssert(! columnsOccupied, "");

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    row = 0;
    rowHeight = 0;
    rowColumns = 0;
    float w = 0.0;
    float x = 0.0;
    float y = (float)(height / 2);

    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCNode* pChild = dynamic_cast<CCNode*>(pObject);
            if (pChild)
            {
                if (rowColumns == 0)
                {
                    rowColumns = rows[row];
                    w = winSize.width / (1 + rowColumns);
                    x = w;
                }

                float tmp = pChild->getContentSize().height;
                rowHeight = (unsigned int)((rowHeight >= tmp || isnan(tmp)) ? rowHeight : tmp);

                pChild->setPosition(ccp(x - winSize.width / 2,
                                       y - pChild->getContentSize().height / 2));

                x += w;
                ++columnsOccupied;

                if (columnsOccupied >= rowColumns)
                {
                    y -= rowHeight + 5;

                    columnsOccupied = 0;
                    rowColumns = 0;
                    rowHeight = 0;
                    ++row;
                }
            }
        }
    }    
}

void CCMenuPassive::alignItemsInRows(unsigned int rows, ...)
{
    va_list args;
    va_start(args, rows);

    this->alignItemsInRows(rows, args);

    va_end(args);
}

void CCMenuPassive::alignItemsInRows(unsigned int rows, va_list args)
{
    vector<unsigned int> columns;
    while (rows)
    {
        columns.push_back(rows);
        rows = va_arg(args, unsigned int);
    }

    vector<unsigned int> columnWidths;
    vector<unsigned int> columnHeights;

    int width = -10;
    int columnHeight = -5;
    unsigned int column = 0;
    unsigned int columnWidth = 0;
    unsigned int rowsOccupied = 0;
    unsigned int columnRows;

    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCNode* pChild = dynamic_cast<CCNode*>(pObject);
            if (pChild)
            {
                // check if too many menu items for the amount of rows/columns
                CCAssert(column < columns.size(), "");

                columnRows = columns[column];
                // can't have zero rows on a column
                CCAssert(columnRows, "");

                // columnWidth = fmaxf(columnWidth, [item contentSize].width);
                float tmp = pChild->getContentSize().width;
                columnWidth = (unsigned int)((columnWidth >= tmp || isnan(tmp)) ? columnWidth : tmp);

                columnHeight += (int)(pChild->getContentSize().height + 5);
                ++rowsOccupied;

                if (rowsOccupied >= columnRows)
                {
                    columnWidths.push_back(columnWidth);
                    columnHeights.push_back(columnHeight);
                    width += columnWidth + 10;

                    rowsOccupied = 0;
                    columnWidth = 0;
                    columnHeight = -5;
                    ++column;
                }
            }
        }
    }

    // check if too many rows/columns for available menu items.
    CCAssert(! rowsOccupied, "");

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    column = 0;
    columnWidth = 0;
    columnRows = 0;
    float x = (float)(-width / 2);
    float y = 0.0;

    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCNode* pChild = dynamic_cast<CCNode*>(pObject);
            if (pChild)
            {
                if (columnRows == 0)
                {
                    columnRows = columns[column];
                    y = (float) columnHeights[column];
                }

                // columnWidth = fmaxf(columnWidth, [item contentSize].width);
                float tmp = pChild->getContentSize().width;
                columnWidth = (unsigned int)((columnWidth >= tmp || isnan(tmp)) ? columnWidth : tmp);

                pChild->setPosition(ccp(x + columnWidths[column] / 2,
                                       y - winSize.height / 2));

                y -= pChild->getContentSize().height + 10;
                ++rowsOccupied;

                if (rowsOccupied >= columnRows)
                {
                    x += columnWidth + 5;
                    rowsOccupied = 0;
                    columnRows = 0;
                    columnWidth = 0;
                    ++column;
                }
            }
        }
    }
}

// Opacity Protocol

/** Override synthesized setOpacity to recurse items */
void CCMenuPassive::setOpacity(GLubyte var)
{
    m_cOpacity = var;

    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCNode* pChild = dynamic_cast<CCNode*>(pObject);
            if (pChild)
            {
                CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pChild);
                if (pRGBAProtocol)
                {
                    pRGBAProtocol->setOpacity(m_cOpacity);
                }
            }
        }
    }
}

GLubyte CCMenuPassive::getOpacity(void)
{
    return m_cOpacity;
}

void CCMenuPassive::setColor(const ccColor3B& var)
{
    m_tColor = var;

    if (m_pChildren && m_pChildren->count() > 0)
    {
        CCObject* pObject = NULL;
        CCARRAY_FOREACH(m_pChildren, pObject)
        {
            CCNode* pChild = dynamic_cast<CCNode*>(pObject);
            if (pChild)
            {
                CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pChild);
                if (pRGBAProtocol)
                {
                    pRGBAProtocol->setColor(m_tColor);
                }
            }
        }
    }
}

const ccColor3B& CCMenuPassive::getColor(void)
{
    return m_tColor;
}

NS_CC_EXT_END
