
#ifndef __UITABVIEW_H__
#define __UITABVIEW_H__

#include "2d/CCSprite.h"
#include "2d/CCLabel.h"
#include "ui/UIAbstractCheckButton.h"
#include "ui/UILayout.h"

/**
* @addtogroup ui
* @{
*/
NS_CC_BEGIN

class Label;

namespace ui {

    /**
    *
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
        void setTitleColor(const Color3B& color);

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

        int   getIndexInTabControl();

    protected:
        TabHeader();
        ~TabHeader();

        virtual void initRenderer() override;
        virtual void onSizeChanged() override;

        void updateContentSize();

        virtual void releaseUpEvent() override;
        void dispatchSelectChangedEvent(bool select) override;

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

        static TabControl* create(const std::string& headerBackGround,
            const std::string& headerCross,
            const std::string& containerBackGround);

        static TabControl* TabControl::create(const std::string& headerBackGround,
            const std::string& headerBackGroundSelected,
            const std::string& headerCross,
            const std::string& headerBackGroundDisabled,
            const std::string& headerFrontCrossDisabled,
            const std::string& containerBackGround);
        /// @{
        /// @name behaviours

        // tab options
        void      insertTab(int index, std::string textStr);
        void      removeTab(int index);

        void      setSelectTab(int index);
        void      setSelectTab(TabHeader* tabHeaderCell);

        TabHeader* getTabHeader(int index) const;
        Layout*   getTabContainer(int index) const;

        /**
        * insert a custom tab, and format the header and container
        * @param index the index tab should be
        * @param headerBtn, the header Button, will be a protected child in tabcontrol
        * @param the container, will be a protected child in tabcontrol
        */
        void      insertTab(int index, TabHeader* headerCell, Layout* container);

        // the tab count
        int         getTabCount() const;
        // get current selected tab's index
        inline int  getCurrentTabIndex() { return _currItemIndex; }

        // auto adjust header width
        void        setAutoAdjustHeaders(bool autoAdjust);
        inline bool isAutoAdjsutHeaders() const { return _autoAdjustHeaders; }
        // set header width, no affect when auto adjust headers
        void         setHeaderWidth(float headerWith);
        inline float getHeaderWidth() const { return _headerWidth; }

        // set header height, no affect when auto adjust headers
        void         setHeaderHeight(float headerHeigt);
        inline int   getHeaderHeight() const { return _headerHeight; }

        void         setHeaderSelectedZoom(float zoom);
        inline float getHeaderSelectedZoom() { return _currentHeaderZoom; }

        // set header dock place
        void         setHeaderDockPlace(TabControl::Dock dockPlace);
        inline TabControl::Dock getHeaderDockPlace() const { return _headerDockPlace; }

        void setTabChangedEventListener(const ccTabViewCallback& callBack);
        /// @} 

        /// @{ 
        /// @ properties

        /**
        * set fontsize and all existed header cell
        * @param fontsize the font size of header cell 's label
        */
        void setHeaderFontSize(float fontsize);

        /**
        * set fontsize and all existed header cell
        * @param set the font name of header cell 's label
        */
        void setHeaderFontName(std::string fontName);

        // get the index of tabCell in TabView, return -1 if not exists in.
        int indexOfTabHeader(TabHeader* tabCell);

        /// @}
    protected:
        TabControl();
        ~TabControl();

        void onSizeChanged() override;
        void resetTabHeadersPos(int startIndex);
        void resetContainers();

        ccTabViewCallback _tabChangedCallback;
        // dispatch selected changed
        void dispatchSelectedTabChanged(int tabIndex, TabHeader::EventType eventType);
    private:
        // format tabheader and container after insert
        void formatAfterInsert(int index);
        void activeHeader(int tabindex);
        int         _currItemIndex;
        bool        _crossTextureLoaded;

        float       _headerFontSize;
        std::string _headerFontName;

        bool        _autoAdjustHeaders;
        int         _headerHeight;
        int         _headerWidth;
        Dock        _headerDockPlace;
        Vec2        _containerPosition;
        Size        _containerSize;
        float       _currentHeaderZoom;

        // normal textures
        std::string _headerBackGround;
        std::string _headerBackGroundSelected;
        std::string _headerCross;
        std::string _headerBackGroundDisabled;
        std::string _headerFrontCrossDisabled;
        std::string _headerContainerBackground;
        std::string _containerBackGround;


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

