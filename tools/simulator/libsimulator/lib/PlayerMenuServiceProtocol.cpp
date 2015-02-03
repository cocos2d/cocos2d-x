
#include "PlayerMenuServiceProtocol.h"

PLAYER_NS_BEGIN

PlayerMenuItem::PlayerMenuItem()
: _order(0)
, _isGroup(false)
, _isEnabled(true)
, _isChecked(false)
{
}

PlayerMenuItem::~PlayerMenuItem()
{
}

std::string PlayerMenuItem::getMenuId() const
{
    return _menuId;
}

std::string PlayerMenuItem::getTitle() const
{
    return _title;
}

int PlayerMenuItem::getOrder() const
{
    return _order;
}

bool PlayerMenuItem::isGroup() const
{
    return _isGroup;
}

bool PlayerMenuItem::isEnabled() const
{
    return _isEnabled;
}

bool PlayerMenuItem::isChecked() const
{
    return _isChecked;
}

std::string PlayerMenuItem::getShortcut() const
{
    return _shortcut;
}

PLAYER_NS_END
