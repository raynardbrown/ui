////////////////////////////////////////////////////////////////////////////////
//
// File: IMessageHandler.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_WINDOWS_IMESSAGEHANDLER_H_
#define UI_PRIVATE_WINDOWS_IMESSAGEHANDLER_H_

#include <windows.h>

class UiComponent;

class IMessageHandler
{
  protected:

    IMessageHandler()
    {

    }

  public:

    virtual ~IMessageHandler()
    {

    }

    virtual int getIdentifier() const = 0;

    virtual LRESULT messageHandler(UiComponent * uiComponent,
                                   UINT message,
                                   WPARAM wParam,
                                   LPARAM lParam) = 0;
};
#endif /* UI_PRIVATE_WINDOWS_IMESSAGEHANDLER_H_ */
