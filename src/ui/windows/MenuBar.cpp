////////////////////////////////////////////////////////////////////////////////
//
// File: MenuBar.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include <cstddef>

#include <vector>

#include "ui/Menu.h"

#include "ui/private/UiComponentPrivate.h"
#include "ui/private/windows/UiComponentContext.h"

#include "ui/private/windows/MenuBarPrivate.h"

#include "ui/MenuBar.h"

MenuBarPrivate::MenuBarPrivate()
:UiComponentPrivate()
{

}

MenuBarPrivate::~MenuBarPrivate()
{
  for(; !menus.empty();)
  {
    delete menus.back();
    menus.pop_back();
  }
}

MenuBar::MenuBar()
:UiComponent(*new MenuBarPrivate())
{
}

MenuBar::MenuBar(MenuBarPrivate& d)
:UiComponent(d)
{

}

MenuBar::~MenuBar()
{

}

void MenuBar::addMenu(Menu * menu)
{
  MenuBarPrivate * d = static_cast<MenuBarPrivate *>(dRoot.get());

  d->menus.push_back(menu);

  if(isInitialized())
  {
    menu->setParent(this);
    menu->dRoot->topLevelWindow = getTopLevelWindow();
    menu->dRoot->idManager = dRoot->idManager;
    menu->initialize();
  }
}

Menu * MenuBar::getMenuAt(std::size_t index) const
{
  MenuBarPrivate * d = static_cast<MenuBarPrivate *>(dRoot.get());

  return d->menus.at(index);
}

std::size_t MenuBar::getMenuCount() const
{
  MenuBarPrivate * d = static_cast<MenuBarPrivate *>(dRoot.get());

  return d->menus.size();
}

void MenuBar::internalCreate()
{
  MenuBarPrivate * d = static_cast<MenuBarPrivate *>(dRoot.get());

  assert(isParentValid());

  /*
   * Create the top-level menu bar.
   */
  HMENU hMenu = ::CreateMenu();

  if(hMenu == nullptr)
  {
    /*
     * TODO: throw exception?
     */
    DWORD lastError = ::GetLastError();
  }

  d->uiComponentContext = std::auto_ptr<UiComponentContext>(new UiComponentContext());
  d->uiComponentContext->hwnd = reinterpret_cast<HWND>(hMenu);

  setInitialized(true);

  /*
   * This MenuBar is initialized. Now attach this MenuBar to the container.
   */
  ::SetMenu(getParent()->getUiComponentContext()->hwnd,
            reinterpret_cast<HMENU>(getUiComponentContext()->hwnd));

  // initialize all child menus
  for(std::size_t i = 0; i < d->menus.size(); ++i)
  {
    Menu * menu = d->menus[i];
    menu->setParent(this);
    menu->dRoot->topLevelWindow = getTopLevelWindow();
    menu->dRoot->idManager = dRoot->idManager;
    menu->initialize();
  }
}

void MenuBar::calculateInternalPreferredSize()
{

}
