////////////////////////////////////////////////////////////////////////////////
//
// File: WM_CTLCOLORSTATIC_MessageHandler.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_WINDOWS_WM_CTLCOLORSTATIC_MESSAGEHANDLER_H_
#define UI_PRIVATE_WINDOWS_WM_CTLCOLORSTATIC_MESSAGEHANDLER_H_

#include <utility>

#include <windows.h>

#include <boost/unordered_map.hpp>

#include "ui/private/windows/IMessageHandler.h"

class AbstractColorChangeObserver;

class WM_CTLCOLORSTATIC_MessageHandler : public IMessageHandler
{
  public:

    WM_CTLCOLORSTATIC_MessageHandler();

    virtual ~WM_CTLCOLORSTATIC_MessageHandler();

    virtual int getIdentifier() const;

    virtual LRESULT messageHandler(UiComponent * uiComponent,
                                   UINT message,
                                   WPARAM wParam,
                                   LPARAM lParam);

    boost::unordered_map<int, std::pair<AbstractColorChangeObserver *, UiComponent *> > win32MessageCallbacks;

  private:

    HBRUSH brush;
};
#endif /* UI_PRIVATE_WINDOWS_WM_CTLCOLORSTATIC_MESSAGEHANDLER_H_ */
