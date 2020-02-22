////////////////////////////////////////////////////////////////////////////////
//
// File: TopLevelWindow.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_TOPLEVELWINDOW_H_
#define UI_TOPLEVELWINDOW_H_

#include "ui/UiComponent.h"

class TopLevelWindowPrivate;
class TopLevelWindowContext;
class MenuBar;

class TopLevelWindow : public UiComponent
{
  public:

    virtual ~TopLevelWindow();

    MenuBar * getMenuBar() const;

    void setMenuBar(MenuBar * bar);

    virtual bool hasMenu() const;

    /**
     * Returns nullptr since top-level windows do not have parents.
     *
     * @return nullptr since top-level windows do not have parents.
     */
    virtual UiComponent * getParent() const;

    /**
     * Returns the owner of this TopLevelWindow or nullptr if this
     * TopLevelWindow does not have an owner.
     *
     * @return the owner of this TopLevelWindow or nullptr if this
     * TopLevelWindow does not have an owner.
     */
    virtual TopLevelWindow * getOwner() const;

    /**
     * Set the owner of this TopLevelWindow to the specified owner.
     *
     * @param[in] owner the new owner of this TopLevelWindow.
     */
    virtual void setOwner(TopLevelWindow * owner);

    TopLevelWindowContext * getTopLevelWindowContext() const;

  protected:

    TopLevelWindow();

    TopLevelWindow(TopLevelWindowPrivate& d);

    virtual void initializeMenu();
};
#endif /* UI_TOPLEVELWINDOW_H_ */
