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
#include "ui/UILayout.h"

/**
* @addtogroup ui
* @{
*/
NS_CC_BEGIN

class Label;

namespace ui {
    
    class TabControl;
    /**
    * the header button in TabControl
    */
    class CC_GUI_DLL TabHeader : public AbstractCheckButton
    {
        friend class TabControl;

    public:

        enum EventType
        {
            SELECTED,
            UNSELECTED
        };


        /**
        * Create and return a empty TabHeaderCell instance pointer.
        */
        static TabHeader* create();

        /**
        * Another factory method to create a TabHeaderCell instance.
        * This method uses less resource to create a RadioButton.
        * @param backGround The background image name in `std::string`.
        * @param cross The cross image name in `std::string`.
        * @param texType  The texture's resource type in `Widget::TextureResType`.
        * @return A TabHeaderCell instance pointer
        */
        static TabHeader* create(const std::string& titleStr,
            const std::string& backGround,
            const std::string& cross,
            TextureResType texType = TextureResType::LOCAL);

        static TabHeader* create(const std::string& titleStr,
            const std::string& backGround,
            const std::string& backGroundSelected,
            const std::string& cross,
            const std::string& backGroundDisabled,
            const std::string& frontCrossDisabled,
            TextureResType texType = TextureResType::LOCAL);
        /**
        * Return the inner title renderer of Cell.
        * @return The Cell title.
        */
        Label* getTitleRenderer()const;

        /**
        * Change the content of Cell's title.
        *@param text The title in std::string.
        */
        void setTitleText(const std::string& text);

        /**
        * Query the Cell title content.
        *@return Get the Cell's title content.
        */
        const std::string getTitleText() const;

        /**
        * Change the color of Cell's title.
        *@param color The title color in Color3B.
        */
        void setTitleColor(const Color4B& color);

        /**
        * Query the Cell title color.
        *@return Color3B of button title.
        */
        Color3B getTitleColor() const;

        /**
        * Change the font size of Cell's title
        *@param size Title font size in float.
        */
        void setTitleFontSize(float size);

        /**
        * Query the font size of Cell title
        *@return font size in float.
        */
        float getTitleFontSize() const;

        /**
        * Change the font name of Cell's title
        *@param fontName a font name string.
        */
        void setTitleFontName(const std::string& fontName);

        /**
        * Query the font name of Cell's title
        *@return font name in std::string
        */
        const std::string getTitleFontName() const;

		/**
		* get the index this header in the TabControl
		* @return -1 means not in this TabControl
		*/
        int   getIndexInTabControl();


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

        //Color4B      _backgroundColor;
        enum FontType
        {
            SYSTEM,
            TTF,
            BMFONT
        };
        FontType  _fontType;

        /* CustomCommand _backgroundCmd;
        CustomCommand _beforeVisitCmdScissor;
        CustomCommand _afterVisitCmdScissor;*/
    };

	/**
	* TabControl, use header button switch container
	*/
    class CC_GUI_DLL TabControl : public Layout
    {
    public:
        enum Dock
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

        typedef std::function<void(int tabIndex, EventType)> ccTabViewCallback;

        static TabControl* create();

        /// @{
        /// @name behaviours

		/**
		* remove the tabItem
		*/
        void      removeTab(int index);

		/**
		* set tab selected
		*/
        void      setSelectTab(int index);

		/**
		* set tab selected
		*/
        void      setSelectTab(TabHeader* tabHeaderCell);

		/**
		* get TabHeader
		*/
        TabHeader* getTabHeader(int index) const;

		/**
		* get Container
		*/
        Layout*   getTabContainer(int index) const;

        /**
        * insert tab, and init the position of header and container
        * @param index, the index tab should be
        * @param headerCell, the header Button, will be a protected child in TabControl
        * @param the container, will be a protected child in TabControl
        */
        void      insertTab(int index, TabHeader* headerCell, Layout* container);

        // the tab count
        size_t    getTabCount() const;

        // get current selected tab's index
        inline int  getCurrentTabIndex() { return _currItemIndex; }

		// get the index of tabCell in TabView, return -1 if not exists in.
		int indexOfTabHeader(TabHeader* tabCell);

		// callback after selected changed
        void setTabChangedEventListener(const ccTabViewCallback& callBack);
        /// @} 

        /// @{ 
        /// @ properties
		// set header width, affect all tabitems
		void         setHeaderWidth(float headerWith);
		inline float getHeaderWidth() const { return _headerWidth; }

		// set header height, , affect all tabitems
		void         setHeaderHeight(float headerHeigt);
		inline int   getHeaderHeight() const { return _headerHeight; }

		// the delta Zoom after selected tab actived
		void         setHeaderSelectedZoom(float zoom);
		inline float getHeaderSelectedZoom() { return _currentHeaderZoom; }

		// set header dock place
		void         setHeaderDockPlace(TabControl::Dock dockPlace);
		inline TabControl::Dock getHeaderDockPlace() const { return _headerDockPlace; }

        /// @}
    protected:
        TabControl();
        ~TabControl();

        void onSizeChanged() override;
        void initTabHeadersPos(int startIndex);
        void initContainers();
		virtual void copySpecialProperties(Widget* model) override;

        ccTabViewCallback _tabChangedCallback;
        // dispatch selected changed
        void dispatchSelectedTabChanged(int tabIndex, TabHeader::EventType eventType);
    private:
        // format tabheader and container after insert
        void initAfterInsert(int index);
        void activeHeader(int tabindex);
		Vec2 getHeaderAnchorWithDock() const;

        int         _currItemIndex;

        int         _headerHeight;
        int         _headerWidth;
        Dock        _headerDockPlace;
        Vec2        _containerPosition;
        Size        _containerSize;
        float       _currentHeaderZoom;

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
        // for indexs the cells and containers
        std::vector<TabItem> _tabItems;
    };
}
// end group
/// @}
NS_CC_END

#endif // __UITABVIEW_H__

