/****************************************************************************
Copyright (c) 2015 Neo Kim (neo.kim@neofect.com)

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

#ifndef __UIRADIOBUTTON_H__
#define __UIRADIOBUTTON_H__

#include "ui/UIAbstractCheckButton.h"
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_CC_BEGIN

namespace ui {

class RadioButtonGroup;

class CC_GUI_DLL RadioButton : public AbstractCheckButton
{

    DECLARE_CLASS_GUI_INFO
    
    friend class RadioButtonGroup;
    
public:
    /**
     * Radio button event types.
     */
    enum class EventType
    {
        SELECTED,
        UNSELECTED
    };
    
    /**
     * A callback which will be called after certain RadioButton event issue.
     * @see `RadioButton::EventType`
     */
    typedef std::function<void(RadioButton* radioButton, EventType)> ccRadioButtonCallback;
    
    /**
     * Default constructor.
     *
     * @lua new
     */
    RadioButton();
    
    /**
     * Default destructor.
     *
     * @lua NA
     */
    virtual ~RadioButton();
    
    /**
     * Create and return a empty RadioButton instance pointer.
     */
    static RadioButton* create();
    
    /**
     * Create a radio button with various images.
     *
     * @param backGround    backGround texture.
     * @param backGroundSelected    backGround selected state texture.
     * @param cross    cross texture.
     * @param backGroundDisabled    backGround disabled state texture.
     * @param frontCrossDisabled    cross dark state texture.
     * @param texType    @see `Widget::TextureResType`
     *
     * @return A RadioButton instance pointer.
     */
    static RadioButton* create(const std::string& backGround,
                            const std::string& backGroundSelected,
                            const std::string& cross,
                            const std::string& backGroundDisabled,
                            const std::string& frontCrossDisabled,
                            TextureResType texType = TextureResType::LOCAL);
    
    /**
     * Another factory method to create a RadioButton instance.
     * This method uses less resource to create a RadioButton.
     * @param backGround The background image name in `std::string`.
     * @param cross The cross image name in `std::string`.
     * @param texType  The texture's resource type in `Widget::TextureResType`.
     * @return A RadioButton instance pointer
     */
    static RadioButton* create(const std::string& backGround,
                            const std::string& cross,
                            TextureResType texType = TextureResType::LOCAL);
    
    /**
     * Add a callback function which would be called when radio button is selected or unselected.
     *@param callback A std::function with type @see `ccRadioButtonCallback`
     */
    void addEventListener(const ccRadioButtonCallback& callback);
    
    virtual std::string getDescription() const override;
    
protected:
    virtual void releaseUpEvent() override;

    virtual void dispatchSelectChangedEvent(bool selected) override;
    
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
protected:
    ccRadioButtonCallback _radioButtonEventCallback;
    RadioButtonGroup* _group;
    
};

class CC_GUI_DLL RadioButtonGroup : public Widget
{
    friend class RadioButton;
public:
    /**
     * Radio button group event types.
     */
    enum class EventType
    {
        SELECT_CHANGED,
    };
    
    /**
     * A callback which will be called after RadioButtonGroup event issue.
     * @see `RadioButtonGroup::EventType`
     */
    typedef std::function<void(RadioButton* radioButton, int index, EventType)> ccRadioButtonGroupCallback;
    
    /**
     * Default constructor.
     *
     * @lua new
     */
    RadioButtonGroup();
    
    /**
     * Default destructor.
     *
     * @lua NA
     */
    virtual ~RadioButtonGroup();
    
    /**
     * Create and return a empty RadioButtonGroup instance pointer.
     */
    static RadioButtonGroup* create();
    
    /**
     * Add a callback function which would be called when radio button is selected or unselected.
     *@param callback A std::function with type @see `ccRadioButtonGroupCallback`
     */
    void addEventListener(const ccRadioButtonGroupCallback& callback);
    
    virtual int getSelectedButtonIndex() const;
    
    virtual void setSelectedButton(int index);
    virtual void setSelectedButton(RadioButton* radioButton);
    
    virtual void addRadioButton(RadioButton* radioButton);
    virtual void removeRadioButton(RadioButton* radioButton);
	
	ssize_t getNumberOfRadioButtons() const;
	RadioButton* getRadioButtonByIndex(int index) const;
    
    void setAllowedNoSelection(bool allowedNoSelection);
    bool isAllowedNoSelection() const;
    
    virtual std::string getDescription() const override;
    
protected:
    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;
    
    void onChangedRadioButtonSelect(RadioButton* radioButton);
    void deselect();
	
	Vector<RadioButton*> _radioButtons;
    ccRadioButtonGroupCallback _radioButtonGroupEventCallback;
    RadioButton* _selectedRadioButton;
    bool _allowedNoSelection;
    
private:
    // Following methods are forbidden. Please use addRadioButton(), removeRadioButton() instead.
    using Widget::addChild;
    using Widget::addProtectedChild;
    using Widget::removeChild;
    using Widget::removeProtectedChild;
    
};
    
}

NS_CC_END
// end of ui group
/// @}

#endif /* defined(__UIRADIOBUTTON_H__) */
