/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "platform/CCFileUtils.h"
#include "2d/CCSprite.h"
#include "2d/CCLabel.h"
#include "ui/UILayout.h"
#include "UITabControl.h"

NS_CC_BEGIN

namespace ui 
{

    TabControl::TabControl()
        : _currItemIndex(-1)
        , _headerHeight(20)
        , _headerWidth(50)
        , _headerDockPlace(TabControl::TOP)
        , _containerPosition(Vec2::ZERO)
        , _containerSize(Size::ZERO)
        , _currentHeaderZoom(0.1f)
    {
        this->_anchorPoint = Vec2(0.f, 0.f);
        setContentSize(Size(200, 200));
    }

    TabControl::~TabControl()
    {
        _tabItems.clear();
    }

    void TabControl::insertTab(int index, TabHeader* headerCell, Layout* container)
    {
        auto cellSize = _tabItems.size();
        if (index > cellSize)
        {
            CCLOG("%s", "insert index error");
            return;
        }

        addProtectedChild(container, -3, -1);
        addProtectedChild(headerCell, -2, -1);

        _tabItems.insert(_tabItems.begin() + index, TabItem(headerCell, container));
        headerCell->_tabView = this;
        headerCell->_tabSelectedEvent = CC_CALLBACK_2(TabControl::dispatchSelectedTabChanged, this); // binding tab selected event

        initAfterInsert(index);
    }

    void TabControl::initAfterInsert(int index)
    {
        auto cellSize =_tabItems.size();
        auto tabItem = _tabItems.at(index);
        auto headerCell = tabItem.header;
        auto container = tabItem.container;

        if (cellSize == 1)
        {
            setSelectTab(0);
        }
        else if (index <= _currItemIndex)
        {
            _currItemIndex += 1;
        }
        else
        {
            headerCell->setSelected(false);
            container->setVisible(false);
        }

        headerCell->setContentSize(Size(_headerWidth, _headerHeight));
		headerCell->setAnchorPoint(getHeaderAnchorWithDock());

        initTabHeadersPos(index);
        if (_containerSize.equals(Size::ZERO))
            initContainers();
        else
        {
            container->setPosition(_containerPosition);
            container->setContentSize(_containerSize);
        }
    }

    void TabControl::removeTab(int index)
    {
        auto cellSize = _tabItems.size();
        if (cellSize == 0 || index >= cellSize)
        {
            CCLOG("%s", "no tab or remove index error");
            return;
        }

        auto& tabItem = _tabItems.at(index);
        auto cell = tabItem.header;
        if (cell != nullptr)
        {
            cell->_tabSelectedEvent = nullptr;
            cell->_tabView = nullptr;
            removeProtectedChild(tabItem.container);
            removeProtectedChild(cell);
        }
        _tabItems.erase(_tabItems.begin() + index);
		if (index == _currItemIndex)
		{
			setSelectTab(0);
		}
		else if (index < _currItemIndex)
			_currItemIndex--;

        initTabHeadersPos(index);
    }

    size_t TabControl::getTabCount() const
    {
        return _tabItems.size();
    }

    void TabControl::setHeaderWidth(float headerWith)
    {
        _headerWidth = headerWith;
        if (_headerDockPlace == Dock::TOP || _headerDockPlace == Dock::BOTTOM)
            initTabHeadersPos(0);
        if (_headerDockPlace == Dock::LEFT || _headerDockPlace == Dock::RIGHT)
            initContainers();
    }

    void TabControl::setHeaderHeight(float headerHeigt)
    {
        _headerHeight = headerHeigt;
        if (_headerDockPlace == Dock::LEFT || _headerDockPlace == Dock::RIGHT)
            initTabHeadersPos(0);
        if (_headerDockPlace == Dock::TOP || _headerDockPlace == Dock::BOTTOM)
            initContainers();
    }

    void TabControl::setHeaderDockPlace(TabControl::Dock dockPlace)
    {
        if (_headerDockPlace != dockPlace)
        {
            _headerDockPlace = dockPlace;
            initTabHeadersPos(0);
            initContainers();
			
			auto anpoint = getHeaderAnchorWithDock();
			for (auto& item : _tabItems)
			{
				item.header->setAnchorPoint(anpoint);
			}
        }
    }


	cocos2d::Vec2 TabControl::getHeaderAnchorWithDock() const
	{
		Vec2 anpoint(.5f, .0f);
		switch (_headerDockPlace)
		{
		case TabControl::TOP:
			break;
		case TabControl::LEFT:
			anpoint.x = 1.f;
			anpoint.y = .5f;
			break;
		case TabControl::BOTTOM:
			anpoint.x = .5f;
			anpoint.y = 1.f;
			break;
		case TabControl::RIGHT:
			anpoint.x = 0.f;
			anpoint.y = .5f;
			break;
		default:
			break;
		}
		return anpoint;
	}

    void TabControl::onSizeChanged()
    {
        initTabHeadersPos(0);
        initContainers();
    }

    void TabControl::initTabHeadersPos(int startIndex)
    {
        auto cellSize = _tabItems.size();
        if (startIndex >= cellSize)
            return;

        float originX = _headerWidth * .5f;
        float originY = _contentSize.height - _headerHeight;
        Vec2 deltaPos(0.f, 0.f);
        switch (_headerDockPlace)
        {
        case TabControl::TOP:
            deltaPos.x = _headerWidth;
            break;
        case TabControl::LEFT:
			originX = _headerWidth;
			originY = _contentSize.height - _headerHeight * .5f;
            deltaPos.y = 0 - _headerHeight;
            break;
        case TabControl::BOTTOM:
            originY = _headerHeight;
            deltaPos.x = _headerWidth;
            break;
        case TabControl::RIGHT:
            originX = _contentSize.width - _headerWidth;
			originY = _contentSize.height - _headerHeight * .5f;
            deltaPos.y = 0 - _headerHeight;
            break;
        default:
            break;
        }

        for (int cellI = startIndex; cellI < cellSize; cellI++)
        {
            auto headerCell = _tabItems.at(cellI).header;
            headerCell->setPosition(Vec2(originX + cellI* deltaPos.x, originY + cellI * deltaPos.y));
        }
    }

    void TabControl::initContainers()
    {
        switch (_headerDockPlace)
        {
        case TabControl::TOP:
            _containerPosition = Vec2(0, 0);
            _containerSize = Size(_contentSize.width, _contentSize.height - _headerHeight);
            break;
        case TabControl::LEFT:
            _containerPosition = Vec2(_headerWidth, 0);
            _containerSize = Size(_contentSize.width - _headerWidth, _contentSize.height);
            break;
        case TabControl::BOTTOM:
            _containerPosition = Vec2(0, _headerHeight);
            _containerSize = Size(_contentSize.width, _contentSize.height - _headerHeight);
            break;
        case TabControl::RIGHT:
            _containerPosition = Vec2(0, 0);
            _containerSize = Size(_contentSize.width - _headerWidth, _contentSize.height);
            break;
        default:
            break;
        }

        for (auto& tabItem : _tabItems)
        {
            Layout* container = tabItem.container;
            container->setPosition(_containerPosition);
            container->setContentSize(_containerSize);
        }
    }

    TabHeader* TabControl::getTabHeader(int index) const
    {
        if (index >= getTabCount())
            return nullptr;

        return _tabItems.at(index).header;
    }

    Layout* TabControl::getTabContainer(int index) const
    {
        if (index >= getTabCount())
            return nullptr;
        return _tabItems.at(index).container;
    }

    void TabControl::dispatchSelectedTabChanged(int tabIndex, TabHeader::EventType eventType)
    {
        if (eventType == TabHeader::EventType::SELECTED)
        {
            if (tabIndex == _currItemIndex)
                return;

            bool selected = false;
            const auto n = _tabItems.size();
            for (int cellI = 0; cellI < n; cellI++)
            {
                auto& tabItem = _tabItems.at(cellI);
                auto container = tabItem.container;
                auto cellHeader = tabItem.header;
                if (tabIndex == cellI)
                {
                    activeHeader(cellI);
                    cellHeader->setSelected(true);
                    container->setVisible(true);
                    _currItemIndex = cellI;
                    selected = true;
                }
                else
                {
                    cellHeader->setSelected(false);
                    container->setVisible(false);
                }
            }
            if (!selected)
                _currItemIndex = -1;
        }
        else if (eventType == TabHeader::EventType::UNSELECTED)
        {
            auto& tabItem = _tabItems.at(tabIndex);
            auto container = tabItem.container;
            auto cellHeader = tabItem.header;
            cellHeader->setSelected(false);
            container->setVisible(false);
            if (tabIndex == _currItemIndex)
                _currItemIndex = -1;
        }

        if (_tabChangedCallback != nullptr)
        {
            _tabChangedCallback(tabIndex, EventType::SELECT_CHANGED);
        }
    }

    void TabControl::setTabChangedEventListener(const ccTabViewCallback& callBack)
    {
        _tabChangedCallback = callBack;
    }

    int TabControl::indexOfTabHeader(TabHeader* tabCell)
    {
        auto n = _tabItems.size();
        for (auto i = 0; i < n; i++)
        {
            if (tabCell == _tabItems.at(i).header)
            {
                return i;
            }
        }
        return -1;
    }

    TabControl* TabControl::create()
    {
        TabControl* tabview = new (std::nothrow) TabControl();
        if (tabview != nullptr && tabview->init())
        {
            tabview->autorelease();
            return tabview;
        }
        CC_SAFE_DELETE(tabview);
        return nullptr;
    }

    void TabControl::setSelectTab(int index)
    {
        auto cellSize = _tabItems.size();
        if (cellSize > 0 && index < cellSize)
        {
            dispatchSelectedTabChanged(index, TabHeader::EventType::SELECTED);
        }
    }

    void TabControl::setSelectTab(TabHeader* tabHeaderCell)
    {
        setSelectTab(indexOfTabHeader(tabHeaderCell));
    }

    void TabControl::setHeaderSelectedZoom(float zoom)
    {
        if (_currentHeaderZoom != zoom)
        {
            _currentHeaderZoom = zoom;
            if (_currItemIndex != -1)
            {
                auto currentHeader = _tabItems.at(_currItemIndex).header;
                currentHeader->setScale(1.0f + _currentHeaderZoom);
            }
        }
    }

    void TabControl::activeHeader(int tabIndex)
    {
        if (tabIndex == _currItemIndex)
            return;

        TabHeader* currentHeader = nullptr;
        if (_currItemIndex != -1)
        {
            currentHeader = _tabItems.at(_currItemIndex).header;
            currentHeader->setLocalZOrder(-2);
			currentHeader->setScale(1.0f);
        }
        TabHeader *activeHeader = nullptr;
        if (tabIndex != -1)
        {
            activeHeader = _tabItems.at(tabIndex).header;
            activeHeader->setLocalZOrder(-1);
			activeHeader->setScale(1.0f + _currentHeaderZoom);
        }
        _reorderProtectedChildDirty = true;
    }

	void TabControl::copySpecialProperties(Widget* model)
	{
		auto srcTab = dynamic_cast<TabControl*>(model);
		if (srcTab != nullptr)
		{
			Layout::copySpecialProperties(srcTab);
			_headerWidth = srcTab->_headerWidth;
			_headerHeight = srcTab->_headerHeight;
			_headerDockPlace = srcTab->_headerDockPlace;
			_currentHeaderZoom = srcTab->_currentHeaderZoom;
			_tabChangedCallback = srcTab->_tabChangedCallback;
		}
	}

    TabHeader::TabHeader()
        : _tabLabelRender(nullptr)
        , _tabLabelFontSize(12)
        , _tabView(nullptr)
        , _tabSelectedEvent(nullptr)
        , _fontType(FontType::SYSTEM)
    {
    }

    TabHeader::~TabHeader()
    {
        _tabLabelRender = nullptr;
        _tabView = nullptr;
        _tabSelectedEvent = nullptr;
    }

    TabHeader * TabHeader::create()
    {
        TabHeader* tabcell = new (std::nothrow) TabHeader();
        if (tabcell != nullptr && tabcell->init())
        {
            tabcell->_frontCrossRenderer->setVisible(false); // _isSelected == fales
			tabcell->_anchorPoint = Vec2(.5f, 0);
            tabcell->autorelease();
            return tabcell;
        }
        CC_SAFE_DELETE(tabcell);
        return nullptr;
    }

    TabHeader * TabHeader::create(const std::string& titleStr, 
        const std::string & backGround,
        const std::string & cross, TextureResType texType)
    {
		TabHeader *tabcell = new (std::nothrow) TabHeader;
		if (tabcell && tabcell->init(backGround,
            "",
            cross,
            "",
            "",
            texType))
        {
			tabcell->_frontCrossRenderer->setVisible(false);
            tabcell->_tabLabelRender->setString(titleStr);
			tabcell->_anchorPoint = Vec2(.5f, 0);
			tabcell->autorelease();
			return tabcell;
        }
		CC_SAFE_DELETE(tabcell);
        return nullptr;
    }

    TabHeader* TabHeader::create(const std::string& titleStr,
        const std::string& backGround,
        const std::string& backGroundSelected,
        const std::string& cross,
        const std::string& backGroundDisabled,
        const std::string& frontCrossDisabled,
        TextureResType texType /*= TextureResType::LOCAL*/)
    {
		TabHeader *tabcell = new (std::nothrow) TabHeader;
		if (tabcell && tabcell->init(backGround,
            backGroundSelected,
            cross,
            backGroundDisabled,
            frontCrossDisabled,
            texType))
        {
			tabcell->_frontCrossRenderer->setVisible(false);
			tabcell->_tabLabelRender->setString(titleStr);
			tabcell->_anchorPoint = Vec2(.5f, 0);
			tabcell->autorelease();
			return tabcell;
        }
		CC_SAFE_DELETE(tabcell);
        return nullptr;
    }

    void TabHeader::initRenderer()
    {
        _backGroundBoxRenderer = Sprite::create();
        _backGroundSelectedBoxRenderer = Sprite::create();
        _frontCrossRenderer = Sprite::create();
        _backGroundBoxDisabledRenderer = Sprite::create();
        _frontCrossDisabledRenderer = Sprite::create();
        _tabLabelRender = Label::create();

        addProtectedChild(_backGroundBoxRenderer, -2, -1);
        addProtectedChild(_backGroundSelectedBoxRenderer, -2, -1);
        addProtectedChild(_frontCrossRenderer, -2, -1);
        addProtectedChild(_backGroundBoxDisabledRenderer, -2, -1);
        addProtectedChild(_frontCrossDisabledRenderer, -2, -1);
        addProtectedChild(_tabLabelRender, -1, -1);
    }

    void TabHeader::setTitleText(const std::string& text)
    {
        if (text == getTitleText())
        {
            return;
        }

        _tabLabelRender->setString(text);
        updateContentSize();
        _tabLabelRender->setPosition(_contentSize * 0.5f);
    }

    const std::string TabHeader::getTitleText() const
    {
        if (nullptr == _tabLabelRender)
        {
            return "";
        }
        return _tabLabelRender->getString();
    }

    void TabHeader::setTitleColor(const Color4B& color)
    {
        _tabLabelRender->setTextColor(color);
    }

    Color3B TabHeader::getTitleColor() const
    {
        if (nullptr == _tabLabelRender)
        {
            return Color3B::WHITE;
        }
        return Color3B(_tabLabelRender->getTextColor());
    }

    void TabHeader::setTitleFontSize(float size)
    {
        _tabLabelFontSize = size;
        if (_fontType == FontType::SYSTEM)
        {
            _tabLabelRender->setSystemFontSize(_tabLabelFontSize);
        }
        else if (_fontType == FontType::TTF)
        {
            TTFConfig config = _tabLabelRender->getTTFConfig();
            config.fontSize = _tabLabelFontSize;
            _tabLabelRender->setTTFConfig(config);
        }
        //we can't change font size of BMFont.
        if (FontType::BMFONT != _fontType)
        {
            updateContentSize();
        }
    }

    float TabHeader::getTitleFontSize() const
    {
        return _tabLabelFontSize;
    }

    void TabHeader::updateContentSize()
    {
        ProtectedNode::setContentSize(_customSize);
        onSizeChanged();
    }


    void TabHeader::setTitleFontName(const std::string& fontName)
    {
        if (FileUtils::getInstance()->isFileExist(fontName))
        {
            std::string lowerCasedFontName = fontName;
            std::transform(lowerCasedFontName.begin(), lowerCasedFontName.end(), lowerCasedFontName.begin(), ::tolower);
            if (lowerCasedFontName.find(".fnt") != std::string::npos)
            {
                _tabLabelRender->setBMFontFilePath(fontName);
                _fontType = FontType::BMFONT;
            }
            else
            {
                TTFConfig config = _tabLabelRender->getTTFConfig();
                config.fontFilePath = fontName;
                config.fontSize = _tabLabelFontSize;
                _tabLabelRender->setTTFConfig(config);
                _fontType = FontType::TTF;
            }
        }
        else
        {
            _tabLabelRender->setSystemFontName(fontName);
            if (_fontType == FontType::TTF)
            {
                _tabLabelRender->requestSystemFontRefresh();
            }
            _tabLabelRender->setSystemFontSize(_tabLabelFontSize);
            _fontType = FontType::SYSTEM;
        }
        this->updateContentSize();
    }

    Label* TabHeader::getTitleRenderer()const
    {
        return _tabLabelRender;
    }

    const std::string TabHeader::getTitleFontName() const
    {
        if (this->_fontType == FontType::SYSTEM)
        {
            return _tabLabelRender->getSystemFontName();
        }
        else if (this->_fontType == FontType::TTF)
        {
            return  _tabLabelRender->getTTFConfig().fontFilePath;
        }
        else
        {
            return _tabLabelRender->getBMFontFilePath();
        }
        return "";
    }

    void TabHeader::onSizeChanged()
    {
        AbstractCheckButton::onSizeChanged();
        _tabLabelRender->setPosition(_contentSize * 0.5f);
    }

    void TabHeader::releaseUpEvent()
    {
        Widget::releaseUpEvent();

        if (!_isSelected)
        {
            setSelected(true);
            dispatchSelectChangedEvent(true);
        }
    }

    void TabHeader::dispatchSelectChangedEvent(bool select)
    {
        if (_tabView == nullptr)
            return;

        EventType eventType = (select ? EventType::SELECTED : EventType::UNSELECTED);

        if (_tabSelectedEvent != nullptr)
        {
            int index = _tabView->indexOfTabHeader(this);
            if (index != -1)
                _tabSelectedEvent(index, eventType);
        }

        if (_ccEventCallback != nullptr)
        {
            _ccEventCallback(this, static_cast<int>(eventType));
        }
    }

    int TabHeader::getIndexInTabControl()
    {
        if (_tabView == nullptr)
            return -1;
        return _tabView->indexOfTabHeader(this);
    }

	void TabHeader::copySpecialProperties(Widget* model)
	{
		auto header = dynamic_cast<TabHeader*>(model);
		if (header != nullptr)
		{
			AbstractCheckButton::copySpecialProperties(model);
			_fontType = header->_fontType;
			_tabLabelFontSize = header->_tabLabelFontSize;
			_tabSelectedEvent = header->_tabSelectedEvent;
		}
	}

}
NS_CC_END