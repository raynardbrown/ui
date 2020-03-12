////////////////////////////////////////////////////////////////////////////////
//
// File: WM_CLOSE_MessageHandler.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_WINDOWS_WM_CLOSE_MESSAGEHANDLER_H_
#define UI_PRIVATE_WINDOWS_WM_CLOSE_MESSAGEHANDLER_H_

#include <vector>

#include "ui/private/windows/IMessageHandler.h"

class AbstractCloseObserver;

class WM_CLOSE_MessageHandler : public IMessageHandler
{
  public:

    WM_CLOSE_MessageHandler();

    virtual ~WM_CLOSE_MessageHandler();

    virtual int getIdentifier() const;

    virtual LRESULT messageHandler(UiComponent * uiComponent,
                                   UINT message,
                                   WPARAM wParam,
                                   LPARAM lParam);

    std::vector<AbstractCloseObserver *> observers;
};
#endif /* UI_PRIVATE_WINDOWS_WM_CLOSE_MESSAGEHANDLER_H_ */
