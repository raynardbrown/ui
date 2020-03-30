////////////////////////////////////////////////////////////////////////////////
//
// File: WM_CLOSE_MessageHandler.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "ui/event/AbstractCloseObserver.h"

#include "ui/private/windows/WM_CLOSE_MessageHandler.h"

WM_CLOSE_MessageHandler::WM_CLOSE_MessageHandler()
:IMessageHandler()
{
}

WM_CLOSE_MessageHandler::~WM_CLOSE_MessageHandler()
{
}

int WM_CLOSE_MessageHandler::getIdentifier() const
{
  return WM_CLOSE;
}

LRESULT WM_CLOSE_MessageHandler::messageHandler(UiComponent * uiComponent,
                                                UINT message,
                                                WPARAM wParam,
                                                LPARAM lParam)
{
  for(std::size_t i = 0; i < observers.size(); ++i)
  {
    AbstractCloseObserver * abstractCloseObserver = observers.at(i);
    (*abstractCloseObserver)();
  }
  return 0;
}
