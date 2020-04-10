////////////////////////////////////////////////////////////////////////////////
//
// File: WM_COMMAND_MessageHandler.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_WINDOWS_WM_COMMAND_MESSAGEHANDLER_H_
#define UI_PRIVATE_WINDOWS_WM_COMMAND_MESSAGEHANDLER_H_

#include <utility>

#include <windows.h>

#include <boost/unordered_map.hpp>

#include "ui/private/windows/IMessageHandler.h"

class AbstractUiEventObserver;

class WM_COMMAND_MessageHandler : public IMessageHandler
{
  public:

    WM_COMMAND_MessageHandler();

    virtual ~WM_COMMAND_MessageHandler();

    virtual int getIdentifier() const;

    virtual LRESULT messageHandler(UiComponent * uiComponent,
                                   UINT message,
                                   WPARAM wParam,
                                   LPARAM lParam);

    // Template parameters from left to right
    //
    // int                     - win32 notification code
    //
    // boost::unordered_map    - map of registered events associated with the notification code
    //
    // int                     - id associated with the ui component that triggered the notification
    //
    // std::pair               - event callback and ui component pair
    //
    // AbstractUiEventObserver - the handler for the ui component that triggered the notification
    //
    // UiComponent             - the ui component that triggered the notification
    boost::unordered_map<int, boost::unordered_map<int, std::pair<AbstractUiEventObserver *, UiComponent *> > > win32CommandCallbacks;

    // TODO: Add 2 more callback maps, one for menus and one for accelerators
};
#endif /* UI_PRIVATE_WINDOWS_WM_COMMAND_MESSAGEHANDLER_H_ */
