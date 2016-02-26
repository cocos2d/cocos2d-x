#include "platform/CCFileUtils.h"
#include "UITabControl.h"

NS_CC_BEGIN

namespace ui 
{

    TabControl::TabControl()
        : _headerFontSize(12.f)
        , _currItemIndex(-1)
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

    void TabControl::insertTab(int index, std::string textStr)
    {
        int cellSize = _tabItems.size();
        if (index > cellSize)
        {
            CCLOG("%s", "insert index error");
            return;
        }

        auto tab = TabHeader::create(textStr, _headerBackGround, _headerBackGroundSelected,
            _headerCross, _headerBackGroundDisabled, _headerFrontCrossDisabled);

        tab->setTitleFontName(_headerFontName);
        tab->setTitleFontSize(_headerFontSize);
        tab->setTitleText(textStr);

        auto container = Layout::create();
        container->setBackGroundImage(_containerBackGround);
        
        insertTab(index, tab, container);
    }

    void TabControl::insertTab(int index, TabHeader* headerCell, Layout* container)
    {
        int cellSize = _tabItems.size();
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

        formatAfterInsert(index);
    }

    void TabControl::formatAfterInsert(int index)
    {
        int cellSize =_tabItems.size();
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

        resetTabHeadersPos(index);
        if (_containerSize.equals(Size::ZERO))
            resetContainers();
        else
        {
            container->setPosition(_containerPosition);
            container->setContentSize(_containerSize);
        }
    }

    void TabControl::removeTab(int index)
    {
        int cellSize = _tabItems.size();
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
        resetTabHeadersPos(index);
    }

    int TabControl::getTabCount() const
    {
        return _tabItems.size();
    }

    void TabControl::setAutoAdjustHeaders(bool autoAdjust)
    {
        _autoAdjustHeaders = true;
        resetTabHeadersPos(0);
    }

    void TabControl::setHeaderWidth(float headerWith)
    {
        _headerWidth = headerWith;
        if (_headerDockPlace == Dock::TOP || _headerDockPlace == Dock::BOTTOM)
            resetTabHeadersPos(0);
        if (_headerDockPlace == Dock::LEFT || _headerDockPlace == Dock::RIGHT)
            resetContainers();
    }

    void TabControl::setHeaderHeight(float headerHeigt)
    {
        _headerHeight = headerHeigt;
        if (_headerDockPlace == Dock::LEFT || _headerDockPlace == Dock::RIGHT)
            resetTabHeadersPos(0);
        if (_headerDockPlace == Dock::TOP || _headerDockPlace == Dock::BOTTOM)
            resetContainers();
    }

    void TabControl::setHeaderDockPlace(TabControl::Dock dockPlace)
    {
        if (_headerDockPlace != dockPlace)
        {
            _headerDockPlace = dockPlace;
            auto zoom = _currentHeaderZoom;
            setHeaderSelectedZoom(0.f);
            resetTabHeadersPos(0);
            resetContainers();
            setHeaderSelectedZoom(zoom);
        }
    }

    void TabControl::setHeaderFontSize(float fontsize)
    {
        _headerFontSize = fontsize;
        for (auto& item : _tabItems)
        {
            item.header->setTitleFontSize(fontsize);
        }
    }

    void TabControl::setHeaderFontName(std::string fontName)
    {
        _headerFontName = fontName;
        for (auto& item : _tabItems)
        {
            item.header->setTitleFontName(fontName);
        }
    }

    void TabControl::onSizeChanged()
    {
        resetTabHeadersPos(0);
        resetContainers();
    }

    void TabControl::resetTabHeadersPos(int startIndex)
    {
        int cellSize = _tabItems.size();
        if (startIndex >= cellSize)
            return;

        float originX = _headerWidth >> 1;
        float originY = _contentSize.height - (_headerHeight >> 1);
        Vec2 deltaPos(0.f, 0.f);
        switch (_headerDockPlace)
        {
        case TabControl::TOP:
            deltaPos.x = _headerWidth;
            break;
        case TabControl::LEFT:
            deltaPos.y = 0 - _headerHeight;
            break;
        case TabControl::BOTTOM:
            originY = _headerHeight >> 1;
            deltaPos.x = _headerWidth;
            break;
        case TabControl::RIGHT:
            originX = _contentSize.width - originX;
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

    void TabControl::resetContainers()
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
            const int n = _tabItems.size();
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
        int n = _tabItems.size();
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

    TabControl* TabControl::create(const std::string& headerBackGround,
        const std::string& headerBackGroundSelected,
        const std::string& headerCross,
        const std::string& headerBackGroundDisabled,
        const std::string& headerFrontCrossDisabled,
        const std::string& containerBackGround)
    {

        auto tabControl = TabControl::create();
        if (tabControl != nullptr)
        {
            tabControl->_headerBackGround = headerBackGround;
            tabControl->_headerBackGroundSelected = headerBackGroundSelected;
            tabControl->_headerCross = headerCross;
            tabControl->_headerBackGroundDisabled = headerBackGroundDisabled;
            tabControl->_headerFrontCrossDisabled = headerFrontCrossDisabled;
            tabControl->_containerBackGround = containerBackGround;
            return tabControl;
        }
        return nullptr;
    }

    TabControl* TabControl::create(const std::string& headerBackGround,
        const std::string& headerCross,
        const std::string& containerBackGround)
    {
        return TabControl::create(headerBackGround, "", headerCross, "", "", containerBackGround);
    }

    void TabControl::setSelectTab(int index)
    {
        int cellSize = _tabItems.size();
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
            auto deltaZoom = zoom - _currentHeaderZoom;
            _currentHeaderZoom = zoom;
            if (_currItemIndex != -1)
            {
                auto currentHeader = _tabItems.at(_currItemIndex).header;
                currentHeader->setScale(1.0f + _currentHeaderZoom);
                float deltay = (_headerHeight * 0.5f * deltaZoom);
                float deltax = (_headerWidth * 0.5f * deltaZoom);
                auto pos = currentHeader->getPosition();
                if (_headerDockPlace == Dock::TOP)
                    pos.y += deltay;
                else if (_headerDockPlace == Dock::LEFT)
                    pos.x -= deltax;
                else if (_headerDockPlace == Dock::BOTTOM)
                    pos.y -= deltay;
                else if (_headerDockPlace == Dock::RIGHT)
                    pos.x += deltax;
                currentHeader->setPosition(pos);
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
        }
        TabHeader *activeHeader = nullptr;
        if (tabIndex != -1)
        {
            activeHeader = _tabItems.at(tabIndex).header;
            activeHeader->setLocalZOrder(-1);
        }
        _reorderProtectedChildDirty = true;

        float deltay = (_headerHeight * 0.5f * _currentHeaderZoom);
        float deltax = (_headerWidth * 0.5f * _currentHeaderZoom);
        if (currentHeader != nullptr)
        {
            currentHeader->setScale(1.0f);
            auto pos = currentHeader->getPosition();
            if (_headerDockPlace == Dock::TOP)
                pos.y -= deltay;
            else if (_headerDockPlace == Dock::LEFT)
                pos.x += deltax;
            else if (_headerDockPlace == Dock::BOTTOM)
                pos.y += deltay;
            else if (_headerDockPlace == Dock::RIGHT)
                pos.x -= deltax;
            currentHeader->setPosition(pos);
        }

        if (activeHeader != nullptr)
        {
            activeHeader->setScale(1.0f + _currentHeaderZoom);
            auto pos = activeHeader->getPosition();
            if (_headerDockPlace == Dock::TOP)
                pos.y += deltay;
            else if (_headerDockPlace == Dock::LEFT)
                pos.x -= deltax;
            else if (_headerDockPlace == Dock::BOTTOM)
                pos.y -= deltay;
            else if (_headerDockPlace == Dock::RIGHT)
                pos.x += deltax;
            activeHeader->setPosition(pos);
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
        TabHeader *pWidget = new (std::nothrow) TabHeader;
        if (pWidget && pWidget->init(backGround,
            "",
            cross,
            "",
            "",
            texType))
        {
            pWidget->_frontCrossRenderer->setVisible(false); // _isSelected == false
            pWidget->_tabLabelRender->setString(titleStr);
            pWidget->autorelease();
            return pWidget;
        }
        CC_SAFE_DELETE(pWidget);
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
        TabHeader *pWidget = new (std::nothrow) TabHeader;
        if (pWidget && pWidget->init(backGround,
            backGroundSelected,
            cross,
            backGroundDisabled,
            frontCrossDisabled,
            texType))
        {
            pWidget->_frontCrossRenderer->setVisible(false); // _isSelected == false
            pWidget->_tabLabelRender->setString(titleStr);
            pWidget->autorelease();
            return pWidget;
        }
        CC_SAFE_DELETE(pWidget);
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
        //this->setTitleFontSize(_fontSize);
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

    void TabHeader::setTitleColor(const Color3B& color)
    {
        _tabLabelRender->setTextColor(Color4B(color));
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

}
NS_CC_END