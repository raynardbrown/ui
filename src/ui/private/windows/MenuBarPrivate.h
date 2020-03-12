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

#ifndef UI_PRIVATE_WINDOWS_MENUBARPRIVATE_H_
#define UI_PRIVATE_WINDOWS_MENUBARPRIVATE_H_

#include <vector>

#include <windows.h>

#include "ui/private/UiComponentPrivate.h"

class Menu;

class MenuBarPrivate : public UiComponentPrivate
{
  public:

    MenuBarPrivate();

    virtual ~MenuBarPrivate();

    std::vector<Menu *> menus;
};
#endif /* UI_PRIVATE_WINDOWS_MENUBARPRIVATE_H_ */
