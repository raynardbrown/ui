////////////////////////////////////////////////////////////////////////////////
//
// File: MenuItem.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "string/extras/CharacterEncoder.h"

#include "ui/Menu.h"

#include "ui/private/windows/UiComponentContext.h"
#include "ui/private/UiComponentPrivate.h"
#include "ui/private/windows/MenuItemPrivate.h"

#include "ui/MenuItem.h"

MenuItemPrivate::MenuItemPrivate(const std::string& text)
:UiComponentPrivate(),
 menuItemtext(text),
 checked(false),
 grayed(false),
 separator(false),
 position(0),
 subMenu(nullptr),
 thisMenuItem(nullptr)
{
  std::memset(&menuItemInfo, 0, sizeof(MENUITEMINFO));

  menuItemInfo.cbSize = sizeof(MENUITEMINFO);
  menuItemInfo.fMask = MIIM_FTYPE | MIIM_ID | MIIM_STATE | MIIM_STRING;
  menuItemInfo.fType = MFT_STRING;
  menuItemInfo.fState = MFS_ENABLED;
  menuItemInfo.hSubMenu = nullptr;
  menuItemInfo.hbmpChecked = nullptr;
  menuItemInfo.hbmpUnchecked = nullptr;
  menuItemInfo.dwItemData = 0;

  // the encoder truncate strings that are greater than the range of int
  std::wstring tempMenuItemString = CharacterEncoder::utf8ToUtf16(text);

  menuItemInfo.dwTypeData = new wchar_t[tempMenuItemString.length() + 1];
  std::wcscpy(menuItemInfo.dwTypeData, tempMenuItemString.c_str());

  menuItemInfo.cch = static_cast<UINT>(tempMenuItemString.length()); // length of the string in characters
  menuItemInfo.hbmpItem = 0;
}

MenuItemPrivate::MenuItemPrivate()
:UiComponentPrivate(),
 menuItemtext(""),
 checked(false),
 grayed(false),
 separator(true),
 position(0),
 subMenu(nullptr),
 thisMenuItem(nullptr)
{
  std::memset(&menuItemInfo, 0, sizeof(MENUITEMINFO));

  menuItemInfo.cbSize = sizeof(MENUITEMINFO);
  menuItemInfo.fMask = MIIM_FTYPE | MIIM_ID | MIIM_STATE;
  menuItemInfo.fType = MFT_SEPARATOR;
  menuItemInfo.fState = MFS_ENABLED;
  menuItemInfo.hSubMenu = nullptr;
  menuItemInfo.hbmpChecked = nullptr;
  menuItemInfo.hbmpUnchecked = nullptr;
  menuItemInfo.dwItemData = 0;
  menuItemInfo.dwTypeData = nullptr;
  menuItemInfo.cch = 0;
  menuItemInfo.hbmpItem = 0;
}

MenuItemPrivate::~MenuItemPrivate()
{
  delete subMenu;
  subMenu = nullptr;

  delete [] menuItemInfo.dwTypeData;
  menuItemInfo.dwTypeData = nullptr;
}

void MenuItemPrivate::initializeSubMenu(MenuItem * menuItem, Menu * subMenu)
{
  // add the popup menu
  menuItemInfo.fMask |= MIIM_SUBMENU;

  // Note: Since MenuItems don't have handles, they cannot set parent the handle
  //       of the sub menu (Menu) using their handler. MenuItems should just
  //       pass the parent handle of the MenuItem's parent to the MenuItem's
  //       submenu (Menu)
  if(!subMenu->isInitialized())
  {
    subMenu->setParent(menuItem->getParent());
    subMenu->dRoot->topLevelWindow = menuItem->getTopLevelWindow();
    subMenu->dRoot->idManager = menuItem->dRoot->idManager;
    subMenu->initialize();
  }

  menuItemInfo.hSubMenu = reinterpret_cast<HMENU>(subMenu->getUiComponentContext()->hwnd);

  ::SetMenuItemInfoW(reinterpret_cast<HMENU>(menuItem->getParent()->getUiComponentContext()->hwnd),
                     menuItem->getPosition(),
                     TRUE,
                     &menuItemInfo);
}

void MenuItemPrivate::setEnabled(bool enabled)
{
  if(enabled)
  {
    thisMenuItem->enableMenuItem();
  }
  else
  {
    thisMenuItem->disableMenuItem();
  }
}

MenuItem::MenuItem(const std::string& text)
:UiComponent(*new MenuItemPrivate(text))
{
  MenuItemPrivate * d = static_cast<MenuItemPrivate *>(dRoot.get());

  d->enabled = true;
  d->thisMenuItem = this;
}

MenuItem::MenuItem()
:UiComponent(*new MenuItemPrivate())
{
  MenuItemPrivate * d = static_cast<MenuItemPrivate *>(dRoot.get());

  d->enabled = true;
  d->thisMenuItem = this;
}

MenuItem::MenuItem(MenuItemPrivate& d)
:UiComponent(d)
{
  d.enabled = true;
  d.thisMenuItem = this;
}

MenuItem::~MenuItem()
{
}

std::string MenuItem::getText() const
{
  MenuItemPrivate * d = static_cast<MenuItemPrivate *>(dRoot.get());

  return d->menuItemtext;
}

bool MenuItem::isChecked() const
{
  MenuItemPrivate * d = static_cast<MenuItemPrivate *>(dRoot.get());

  return d->checked;
}

bool MenuItem::isGrayed() const
{
  MenuItemPrivate * d = static_cast<MenuItemPrivate *>(dRoot.get());

  return d->grayed;
}

bool MenuItem::isSeparator() const
{
  MenuItemPrivate * d = static_cast<MenuItemPrivate *>(dRoot.get());

  return d->separator;
}

void MenuItem::setPosition(std::size_t index)
{
  MenuItemPrivate * d = static_cast<MenuItemPrivate *>(dRoot.get());

  // TODO: implement need to update parent
  d->position = index;
}

std::size_t MenuItem::getPosition() const
{
  MenuItemPrivate * d = static_cast<MenuItemPrivate *>(dRoot.get());

  // TODO: Needs to update based on peers being removed

  return d->position;
}

void MenuItem::internalCreate()
{
  MenuItemPrivate * d = static_cast<MenuItemPrivate *>(dRoot.get());

  assert(isParentValid());

  if(isChecked())
  {
    d->menuItemInfo.fState |= MFS_CHECKED;
  }
  else
  {
    d->menuItemInfo.fState |= MFS_UNCHECKED;
  }

  if(isEnabled())
  {
    d->menuItemInfo.fState |= MFS_ENABLED;
  }
  else
  {
    d->menuItemInfo.fState |= MFS_DISABLED;
  }

  if(isGrayed())
  {
    d->menuItemInfo.fState |= MFS_GRAYED;
  }

  // TODO: implement highlight

  d->menuItemInfo.wID = getId();

  ::InsertMenuItem(reinterpret_cast<HMENU>(getParent()->getUiComponentContext()->hwnd),
                   getPosition(),
                   TRUE,
                   &d->menuItemInfo);

  if(d->subMenu)
  {
    // add the popup menu
    d->initializeSubMenu(this, d->subMenu);
  }

  d->uiComponentContext = std::auto_ptr<UiComponentContext>(new UiComponentContext());
  d->uiComponentContext->hwnd = nullptr;

  setInitialized(true);

  calculateInternalPreferredSize();
}

void MenuItem::checkMenuItem()
{
  MenuItemPrivate * dd = static_cast<MenuItemPrivate *>(dRoot.get());

  if(getParent())
  {
    if(getParent()->isInitialized())
    {
      ::CheckMenuItem(reinterpret_cast<HMENU>(getParent()->getUiComponentContext()->hwnd),
                      getId(),
                      MF_BYCOMMAND | MF_CHECKED);

      dd->checked = true;
    }
  }
  else
  {
    dd->checked = true;
  }
}

void MenuItem::uncheckMenuItem()
{
  MenuItemPrivate * dd = static_cast<MenuItemPrivate *>(dRoot.get());

  if(getParent())
  {
    if(getParent()->isInitialized())
    {
      ::CheckMenuItem(reinterpret_cast<HMENU>(getParent()->getUiComponentContext()->hwnd),
                      getId(),
                      MF_BYCOMMAND | MF_UNCHECKED);

      dd->checked = false;
    }
  }
  else
  {
    dd->checked = false;
  }
}

void MenuItem::checkMenuRadioItem()
{
  // TODO: implement
}

void MenuItem::enableMenuItem()
{
  if(!isEnabled())
  {
    MenuItemPrivate * d = static_cast<MenuItemPrivate *>(dRoot.get());

    if(getParent())
    {
      if(getParent()->isInitialized())
      {
        ::EnableMenuItem(reinterpret_cast<HMENU>(getParent()->getUiComponentContext()->hwnd),
                         getId(),
                         MF_BYCOMMAND | MF_ENABLED);
      }
    }

    d->enabled = true;

    d->grayed = false;
  }
}

void MenuItem::disableMenuItem()
{
  if(isEnabled())
  {
    MenuItemPrivate * d = static_cast<MenuItemPrivate *>(dRoot.get());

    if(getParent())
    {
      if(getParent()->isInitialized())
      {
        ::EnableMenuItem(reinterpret_cast<HMENU>(getParent()->getUiComponentContext()->hwnd),
                         getId(),
                         MF_BYCOMMAND | MF_DISABLED);
      }
    }

    d->enabled = false;
  }
}

void MenuItem::grayMenuItem()
{
  if(!isGrayed())
  {
    MenuItemPrivate * d = static_cast<MenuItemPrivate *>(dRoot.get());
    if(getParent())
    {
      if(getParent()->isInitialized())
      {
        ::EnableMenuItem(reinterpret_cast<HMENU>(getParent()->getUiComponentContext()->hwnd),
                         getId(),
                         MF_BYCOMMAND | MF_GRAYED);
      }
    }

    d->grayed = true;
    d->enabled = false;
  }
}

void MenuItem::setSubMenu(Menu * subMenu)
{
  MenuItemPrivate * d = static_cast<MenuItemPrivate *>(dRoot.get());

  d->subMenu = subMenu;

  if(isInitialized())
  {
    // add the popup menu
    d->initializeSubMenu(this, d->subMenu);
  }
}

Menu * MenuItem::getSubMenu() const
{
  MenuItemPrivate * d = static_cast<MenuItemPrivate *>(dRoot.get());

  return d->subMenu;
}

void MenuItem::calculateInternalPreferredSize()
{

}
