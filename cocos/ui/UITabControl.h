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


#ifndef __UITABVIEW_H__
#define __UITABVIEW_H__

#include "ui/UIAbstractCheckButton.h"
#include "ui/UIWidget.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

class Label;

namespace ui {
    
    class Layout;
    class TabControl;
    /**
     * the header button in TabControl
     */
    class CC_GUI_DLL TabHeader : public AbstractCheckButton
    {
        friend class TabControl;
        
    public:

        enum class EventType
        {
            SELECTED,
            UNSELECTED
        };
        
        
        /**
         * Create and return a empty TabHeader instance pointer.
         */
        static TabHeader* create();
        
        /**
         * factory method to create a TabHeader instance.
         * This method uses less resource to create a TabHeader.
         * @param titleStr The text on the TabHeader
         * @param backGround The background image name in `std::string`.
         * @param cross The cross image name in `std::string`.
         * @param texType  The texture's resource type in `Widget::TextureResType`.
         * @return A TabHeader instance pointer
         */
        static TabHeader* create(const std::string& titleStr,
                                 const std::string& backGround,
                                 const std::string& cross,
                                 TextureResType texType = TextureResType::LOCAL);
        
        /**
        * Create a TabHeader with various images.
        * @param titleStr The text on the TabHeader
        * @param backGround    backGround texture.
        * @param backGroundSelected    backGround selected state texture.
        * @param cross    cross texture.
        * @param backGroundDisabled    backGround disabled state texture.
        * @param frontCrossDisabled    cross dark state texture.
        * @param texType    @see `Widget::TextureResType`
        *
        * @return A TabHeader instance pointer.
        */
        static TabHeader* create(const std::string& titleStr,
                                 const std::string& backGround,
                                 const std::string& backGroundSelected,
                                 const std::string& cross,
                                 const std::string& backGroundDisabled,
                                 const std::string& frontCrossDisabled,
                                 TextureResType texType = TextureResType::LOCAL);
        /**
         * Return the inner Label renderer of TabHeader.
         * @return The TabHeader Label.
         */
        Label* getTitleRenderer()const;
        
        /**
         * Change the content of Header's text.
         *@param text The Header's text.
         */
        void setTitleText(const std::string& text);
        
        /**
         * get the TabHeader text
         *@return he TabHeader text
         */
        const std::string getTitleText() const;
        
        /**
         * Change the color of he TabHeader text
         *@param color The he TabHeader text's color in Color4B.
         */
        void setTitleColor(const Color4B& color);
        
        /**
         * get the TabHeader text color.
         *@return Color4B of TabHeader text.
         */
        const Color4B& getTitleColor() const;
        
        /**
         * Change the font size of TabHeader text
         *@param size TabHeader text's font size in float.
         */
        void setTitleFontSize(float size);
        
        /**
         * get the font size of TabHeader text
         *@return TabHeader text's font size in float.
         */
        float getTitleFontSize() const;
        
        /**
         * Change the font name of TabHeader text
         *@param fontName a font name string.
         */
        void setTitleFontName(const std::string& fontName);
        
        /**
         * get the font name of TabHeader text
         *@return font name in std::string
         */
        const std::string getTitleFontName() const;
        
        /**
         * get the index this header in the TabControl
         * @return -1 means not in any TabControl
         */
        int   getIndexInTabControl() const;
        
        
    protected:
        TabHeader();
        ~TabHeader();
        
        virtual void initRenderer() override;
        virtual void onSizeChanged() override;
        
        void updateContentSize();
        
        virtual void releaseUpEvent() override;
        void dispatchSelectChangedEvent(bool select) override;
        
        virtual void copySpecialProperties(Widget* model) override;
        
    private:
        Label*       _tabLabelRender;
        float        _tabLabelFontSize;
        TabControl*  _tabView;
        
        typedef std::function<void(int tabindex, TabHeader::EventType)> ccTabCallback;
        ccTabCallback  _tabSelectedEvent;

        enum class FontType
        {
            SYSTEM,
            TTF,
            BMFONT
        };
        FontType  _fontType;
    };

    /**
    * TabControl, use header button switch container
    */
    class CC_GUI_DLL TabControl : public Widget
    {
    public:
        enum class Dock
        {
            TOP,
            LEFT,
            BOTTOM,
            RIGHT
        };

        enum class EventType
        {
            SELECT_CHANGED,
        };
        
        typedef std::function<void(int tabIndex, EventType)> ccTabControlCallback;
        
        static TabControl* create();
        
        /// @{
        /// @name behaviours
        
        /**
         * remove the tab from this TabControl
         * @param index: the index of tab
         */
        void      removeTab(int index);
        
        /**
         * set tab selected, switch the current selected tab and visible container
         * @param index: the index of tab
         */
        void      setSelectTab(int index);
        
        /**
         * set tab selected, switch the current selected tab and visible container
         * @param tabHeader, the tab instance
         */
        void      setSelectTab(TabHeader* tabHeader);
        
        /**
         * get TabHeader
         * @param index, the index of tab
         */
        TabHeader* getTabHeader(int index) const;
        
        /**
         * get Container
         * @param index, the index of tab
         */
        Layout*   getTabContainer(int index) const;
        
        /**
         * insert tab, and init the position of header and container
         * @param index, the index tab should be
         * @param header, the header Button, will be a protected child in TabControl
         * @param the container, will be a protected child in TabControl
         */
        void      insertTab(int index, TabHeader* header, Layout* container);
        
        /**
        * get the count of tabs in this TabControl
        * @return the count of tabs
        */
        size_t    getTabCount() const;
        
        /**
        * get current selected tab's index
        * @return the current selected tab index
        */
        int getSelectedTabIndex() const;

        /**
        * get the index of tabCell in TabView, return -1 if not exists in.
        / @return the index of tabCell in TabView,  `-1` means not exists in.
        */
        int indexOfTabHeader(const TabHeader* tabCell) const;

        /**
        * Add a callback function which would be called when selected tab changed
        *@param callback A std::function with type @see `ccTabControlCallback`
        */
        void setTabChangedEventListener(const ccTabControlCallback& callBack);
        /// @}

        /// @{
        /// @ properties

        /**
        * set header width, affect all tab
        * @param headerWith: each tab header's width
        */
        void  setHeaderWidth(float headerWith);

        /**
        * get tab header's width
        * @return header's width
        */
        float getHeaderWidth() const { return _headerWidth; }

        /**
        * set header height, affect all tab
        * @param headerHeigt: each tab header's height
        */
        void  setHeaderHeight(float headerHeigt);

        /**
        * get tab header's height
        * @return header's height
        */
        int   getHeaderHeight() const { return _headerHeight; }

        /**
        * ignore the textures' size in header, scale them with _headerWidth and _headerHeight
        * @param ignore is `true`, the header's texture scale with _headerWidth and _headerHeight
        *        ignore is `false`, use the texture's size, do not scale them
        */
        void  ignoreHeadersTextureSize(bool ignore);

        /**
        * get whether ignore the textures' size in header, scale them with _headerWidth and _headerHeight
        * @return whether ignore the textures' size in header
        */
        bool  isIgnoreHeadersTextureSize() const { return _ignoreHeaderTextureSize; };

        /**
        * set the delta zoom of selected tab
        * @param zoom, the delta zoom
        */
        void  setHeaderSelectedZoom(float zoom);

        /**
        * get the delta zoom of selected tab
        * @return zoom, the delta zoom
        */
        float getHeaderSelectedZoom() const { return _currentHeaderZoom; }

        /**
        * the header dock place of header in TabControl
        * @param: dockPlace, the strip place
        */
        void         setHeaderDockPlace(TabControl::Dock dockPlace);
        TabControl::Dock getHeaderDockPlace() const { return _headerDockPlace; }

        /// @}
    protected:
        TabControl();
        ~TabControl();

        void onSizeChanged() override;
        void initTabHeadersPos(int startIndex);
        void initContainers();
        virtual void copySpecialProperties(Widget* model) override;

        ccTabControlCallback _tabChangedCallback;
        // dispatch selected changed
        void dispatchSelectedTabChanged(int tabIndex, TabHeader::EventType eventType);
    private:

        typedef struct CellContainer
        {
            TabHeader* header;
            Layout*        container;

            CellContainer(TabHeader* headerCell, Layout* layout)
            {
                header = headerCell;
                container = layout;
            }
        } TabItem;

        // format tab header and container after insert
        void initAfterInsert(int index);
        void activeTabItem(TabItem* item);
        void deactiveTabItem(TabItem* item);
        Vec2 getHeaderAnchorWithDock() const;

        TabItem*    _selectedItem;

        int         _headerHeight;
        int         _headerWidth;
        Dock        _headerDockPlace;
        Vec2        _containerPosition;
        Size        _containerSize;
        float       _currentHeaderZoom;
        bool        _ignoreHeaderTextureSize;

        // for index the cells and containers
        std::vector<TabItem*> _tabItems;
    };
}
// end group
/// @}
NS_CC_END

#endif // __UITABVIEW_H__

