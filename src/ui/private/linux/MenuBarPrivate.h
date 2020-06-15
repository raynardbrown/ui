////////////////////////////////////////////////////////////////////////////////
//
// File: MenuBarPrivate.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_LINUX_MENUBARPRIVATE_H_
#define UI_PRIVATE_LINUX_MENUBARPRIVATE_H_

#include <vector>

#include "ui/private/UiComponentPrivate.h"

class Menu;
class MenuBar;

class MenuBarPrivate : public UiComponentPrivate
{
  public:

    MenuBarPrivate();

    virtual ~MenuBarPrivate();

    void initializeMenu(MenuBar * menuBar, Menu * menu);

    std::vector<Menu *> menus;
};
#endif /* UI_PRIVATE_LINUX_MENUBARPRIVATE_H_ */
