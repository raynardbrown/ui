////////////////////////////////////////////////////////////////////////////////
//
// File: MenuBar.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_MENUBAR_H_
#define UI_MENUBAR_H_

#include "ui/UiComponent.h"

class Menu;
class MenuBarPrivate;

/**
 * A horizontal list of items displayed just below the caption of a Window.
 * Often referred to as the top-level menu.
 *
 * A MenuBar can have pop-up menu or command menu as its entries. A pop-up
 * menu is a vertically displayed menu that pops up below its menu bar item. A
 * command menu item is often found on pop-up menus, but can appear on MenuBars.
 * Command items represent a final selection.
 */
class MenuBar : public UiComponent
{
  public:

    MenuBar();

    virtual ~MenuBar();

    void addMenu(Menu * menu);

    Menu * getMenuAt(std::size_t index) const;

    std::size_t getMenuCount() const;

  protected:

    virtual void internalCreate();

    virtual void calculateInternalPreferredSize();

    MenuBar(MenuBarPrivate& d);

    // allow top level window to access the protected bits of menu bar
    friend class TopLevelWindow;

    friend class TopLevelWindowPrivate;

    friend class MenuBarPrivate;
};
#endif /* UI_MENUBAR_H_ */
