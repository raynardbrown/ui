////////////////////////////////////////////////////////////////////////////////
//
// File: Menu.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_MENU_H_
#define UI_MENU_H_

#include "ui/UiComponent.h"

class MenuItem;
class MenuPrivate;

class Menu : public UiComponent
{
  public:

    /**
     * Creates a new Menu with the specified name.
     *
     * @param[in] menuName the name that this Menu will display. If menuName is
     * the empty string then this Menu will not display any text.
     */
    Menu(const std::string& menuName);

    /**
     * Destructor
     */
    virtual ~Menu();

    /**
     * Adds the specified MenuItem by appending it to the end of this Menu.
     *
     * @param[in] menuItem the MenuItem that will be appended to this Menu.
     */
    void addMenuItem(MenuItem * menuItem);

    void addSeparator();

    /**
     * Returns the name of this Menu.
     *
     * @return the name of this Menu.
     */
    std::string getMenuName() const;

    MenuItem * getMenuItemAt(std::size_t index) const;

    std::size_t getMenuItemCount() const;

  protected:

    virtual void internalCreate();

    virtual void calculateInternalPreferredSize();

    Menu(MenuPrivate& d);

    // allow menu bar to access menu protected bits
    friend class MenuBar;
    friend class MenuBarPrivate;

    // allow menu item to access menu protected bits
    friend class MenuItem;
    friend class MenuItemPrivate;
};
#endif /* UI_MENU_H_ */
