////////////////////////////////////////////////////////////////////////////////
//
// File: MenuItem.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_MENUITEM_H_
#define UI_MENUITEM_H_

#include <string>

#include "ui/UiComponent.h"

class Menu;
class MenuItemPrivate;

class MenuItem : public UiComponent
{
  public:

    /**
     * Create a new MenuItem with the specified text.
     *
     * @param[in] text the text of this MenuItem.
     */
    MenuItem(const std::string& text);

    /**
     * Create a new Menu separator
     */
    MenuItem();

    /**
     * Destructor
     */
    virtual ~MenuItem();

    /**
     * Returns the text registered to this MenuItem.
     *
     * @return the text of this MenuItem.
     */
    std::string getText() const;

    void setPosition(std::size_t index);

    std::size_t getPosition() const;

    /**
     * Sets the checkmark on this MenuItem.
     */
    void checkMenuItem();

    /**
     * Unsets the checkmark on this MenuItem.
     */
    void uncheckMenuItem();
    void checkMenuRadioItem();

    /**
     * Enables this MenuItem and restores it from a grayed state.
     */
    void enableMenuItem();

    /**
     * Disables this MenuItem without graying it.
     */
    void disableMenuItem();

    /**
     * Grays this MenuItem disabling it so that it cannot be selected.
     */
    void grayMenuItem();

    /**
     * Checks whether this MenuItem is checked.
     *
     * @return true if and only if this MenuItem is checked.
     */
    bool isChecked() const;

    /**
     * Checks whether this MenuItem is grayed.
     *
     * @return true if and only if this MenuItem is grayed.
     */
    bool isGrayed() const;

    bool isSeparator() const;

    void setSubMenu(Menu * subMenu);

    Menu * getSubMenu() const;

  protected:

    virtual void internalCreate();

    virtual void calculateInternalPreferredSize();

    MenuItem(MenuItemPrivate& d);

    // let menu access the protected bits in menu item
    friend class Menu;

    friend class MenuPrivate;
};
#endif /* UI_MENUITEM_H_ */
