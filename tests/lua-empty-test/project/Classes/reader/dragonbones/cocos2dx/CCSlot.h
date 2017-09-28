#ifndef DRAGONBONES_CC_SLOT_H
#define DRAGONBONES_CC_SLOT_H

#include "dragonbones/DragonBonesHeaders.h"
#include "cocos2d.h"

DRAGONBONES_NAMESPACE_BEGIN
class CCSlot : public Slot
{
    BIND_CLASS_TYPE(CCSlot);

private:
    cocos2d::Node* _renderDisplay;

public:
    CCSlot();
    ~CCSlot();

    virtual void _onClear() override;

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(CCSlot);

protected:
    virtual void _initDisplay(void* value) override;
    virtual void _disposeDisplay(void* value) override;
    virtual void _onUpdateDisplay() override;
    virtual void _addDisplay() override;
    virtual void _replaceDisplay(void* value, bool isArmatureDisplayContainer) override;
    virtual void _removeDisplay() override;
    virtual void _updateColor() override;
    virtual void _updateFilters() override;
    virtual void _updateFrame() override;
    virtual void _updateMesh() override;
    virtual void _updateTransform() override;

public:
    virtual void _updateVisible() override;
    virtual void _updateBlendMode() override;
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_CC_SLOT_H
