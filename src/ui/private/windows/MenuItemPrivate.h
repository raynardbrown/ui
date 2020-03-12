////////////////////////////////////////////////////////////////////////////////
//
// File: MenuItemPrivate.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_WINDOWS_MENUITEMPRIVATE_H_
#define UI_PRIVATE_WINDOWS_MENUITEMPRIVATE_H_

#include <string>

#include <windows.h>

#include "ui/private/UiComponentPrivate.h"

class Menu;
class MenuItem;

class MenuItemPrivate : public UiComponentPrivate
{
  public:

    MenuItemPrivate(const std::string& text);

    MenuItemPrivate();

    virtual ~MenuItemPrivate();

    virtual void setEnabled(bool enabled);

    std::string menuItemtext;

    bool checked;

    bool grayed;

    bool separator;

    std::size_t position;

    MENUITEMINFO menuItemInfo;

    Menu * subMenu;

    MenuItem * thisMenuItem;
};
#endif /* UI_PRIVATE_WINDOWS_MENUITEMPRIVATE_H_ */
