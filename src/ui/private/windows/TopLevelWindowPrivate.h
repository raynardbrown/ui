////////////////////////////////////////////////////////////////////////////////
//
// File: TopLevelWindowPrivate.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_WINDOWS_TOPLEVELWINDOWPRIVATE_H_
#define UI_PRIVATE_WINDOWS_TOPLEVELWINDOWPRIVATE_H_

#include <memory>

#include "ui/private/UiComponentPrivate.h"

class MenuBar;
class TopLevelWindow;
class TopLevelWindowContext;

class TopLevelWindowPrivate : public UiComponentPrivate
{
  public:

    TopLevelWindowPrivate();

    virtual ~TopLevelWindowPrivate();

    bool updateMenuBar();

    /**
     * Helper function used to pass the this pointer of the TopLevelWindow to
     * its d-pointer.
     *
     * @param[in] window the this pointer of the TopLevelWindow that will be
     * passed to its d-pointer.
     */
    void setTopLevelWindow(TopLevelWindow * window);

    void initializeMenuBar(TopLevelWindow * topLevelWindow,
                           MenuBar * menubar);

    std::auto_ptr<MenuBar> menuBar;

    /**
     * The owner of this TopLevelWindow or nullptr if this TopLevelWindow does
     * not have an owner.
     */
    TopLevelWindow * owner;

    std::auto_ptr<TopLevelWindowContext> topLevelWindowContext;
};
#endif /* UI_PRIVATE_WINDOWS_TOPLEVELWINDOWPRIVATE_H_ */
