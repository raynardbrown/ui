////////////////////////////////////////////////////////////////////////////////
//
// File: MenuPrivate.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_WINDOWS_MENUPRIVATE_H_
#define UI_PRIVATE_WINDOWS_MENUPRIVATE_H_

#include <string>

#include <vector>

#include "ui/private/UiComponentPrivate.h"

class Menu;
class MenuItem;

class MenuPrivate : public UiComponentPrivate
{
  public:

    MenuPrivate(const std::string& text);

    virtual ~MenuPrivate();

    void initializeMenuItem(Menu * menu, MenuItem * menuItem);

    // the menu text
    std::string text;

    std::vector<MenuItem *> menuItems;
};
#endif /* UI_PRIVATE_WINDOWS_MENUPRIVATE_H_ */
