////////////////////////////////////////////////////////////////////////////////
//
// File: Menu.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

#include "string/extras/CharacterEncoder.h"

#include "ui/MenuItem.h"
#include "ui/TopLevelWindow.h"

#include "ui/private/IdManager.h"

#include "ui/private/windows/UiComponentContext.h"
#include "ui/private/UiComponentPrivate.h"
#include "ui/private/windows/MenuPrivate.h"

#include "ui/Menu.h"

MenuPrivate::MenuPrivate(const std::string& text)
:UiComponentPrivate(),
 text(text)
{

}

MenuPrivate::~MenuPrivate()
{
  for(; !menuItems.empty();)
  {
    delete menuItems.back();

    menuItems.pop_back();
  }
}

void MenuPrivate::initializeMenuItem(Menu * menu, MenuItem * menuItem)
{
  menuItem->setParent(menu);
  menuItem->dRoot->topLevelWindow = menu->getTopLevelWindow();
  menuItem->dRoot->idManager = idManager;
  menuItem->dRoot->id = menuItem->dRoot->idManager->requestId();
  menuItem->initialize();
}

Menu::Menu(const std::string& text)
:UiComponent(*new MenuPrivate(text))
{
}

Menu::Menu(MenuPrivate& d)
:UiComponent(d)
{

}

Menu::~Menu()
{
}

void Menu::addMenuItem(MenuItem * menuItem)
{
  MenuPrivate * d = static_cast<MenuPrivate *>(dRoot.get());

  std::size_t position = d->menuItems.size();

  d->menuItems.push_back(menuItem);

  menuItem->setPosition(position);

  // initialize menu item
  if(isInitialized())
  {
    d->initializeMenuItem(this, menuItem);
  }
}

void Menu::addSeparator()
{
  MenuItem * menuItem = new MenuItem();

  addMenuItem(menuItem);
}

std::string Menu::getMenuName() const
{
  MenuPrivate * d = static_cast<MenuPrivate *>(dRoot.get());

  return d->text;
}

MenuItem * Menu::getMenuItemAt(std::size_t index) const
{
  MenuPrivate * d = static_cast<MenuPrivate *>(dRoot.get());

  return d->menuItems.at(index);
}

std::size_t Menu::getMenuItemCount() const
{
  MenuPrivate * d = static_cast<MenuPrivate *>(dRoot.get());

  return d->menuItems.size();
}

void Menu::internalCreate()
{
  MenuPrivate * d = static_cast<MenuPrivate *>(dRoot.get());

  //assert(isParentValid());

  /*
   * Create a pop up menu that is initially empty.
   */
  HMENU hMenu = ::CreatePopupMenu();

  d->uiComponentContext = std::auto_ptr<UiComponentContext>(new UiComponentContext());
  d->uiComponentContext->hwnd = reinterpret_cast<HWND>(hMenu);;

  setInitialized(true);

  if(getParent() && !d->text.empty())
  {
    // The menu has a name so it is a menu on a menu bar.
    ::AppendMenu(getParent() ?  reinterpret_cast<HMENU>(getParent()->getUiComponentContext()->hwnd) : nullptr,
                 MF_POPUP,
                 reinterpret_cast<UINT_PTR>(getUiComponentContext()->hwnd),
                 CharacterEncoder::utf8ToUtf16(getMenuName()).c_str());
  }

  for(std::size_t i = 0; i < d->menuItems.size(); ++i)
  {
    MenuItem * menuItem = d->menuItems[i];

    // initialize menu item
    d->initializeMenuItem(this, menuItem);
  }
}

void Menu::calculateInternalPreferredSize()
{

}
