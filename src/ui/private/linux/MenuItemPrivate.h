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

#ifndef UI_PRIVATE_LINUX_MENUITEMPRIVATE_H_
#define UI_PRIVATE_LINUX_MENUITEMPRIVATE_H_

#include <string>

#include "ui/private/UiComponentPrivate.h"

class Menu;
class MenuItem;

class MenuItemPrivate : public UiComponentPrivate
{
  public:

    MenuItemPrivate(const std::string& text);

    MenuItemPrivate();

    virtual ~MenuItemPrivate();

    std::string menuItemtext;

    bool checked;

    bool grayed;

    bool separator;

    std::size_t position;

    MenuItem * thisMenuItem;
};
#endif /* UI_PRIVATE_LINUX_MENUITEMPRIVATE_H_ */
