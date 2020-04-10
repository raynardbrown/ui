////////////////////////////////////////////////////////////////////////////////
//
// File: WM_COMMAND_MessageHandler.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "ui/UiComponent.h"

#include "ui/private/windows/UiComponentContext.h"

#include "ui/event/AbstractUiEventObserver.h"

#include "ui/private/windows/WM_COMMAND_MessageHandler.h"

WM_COMMAND_MessageHandler::WM_COMMAND_MessageHandler()
:IMessageHandler()
{
}

WM_COMMAND_MessageHandler::~WM_COMMAND_MessageHandler()
{

}

int WM_COMMAND_MessageHandler::getIdentifier() const
{
  return WM_COMMAND;
}

LRESULT WM_COMMAND_MessageHandler::messageHandler(UiComponent * uiComponent,
                                                  UINT message,
                                                  WPARAM wParam,
                                                  LPARAM lParam)
{
  int childHwndId = LOWORD(wParam);

  int notificationCode = HIWORD(wParam);

  boost::unordered_map<int, boost::unordered_map<int, std::pair<AbstractUiEventObserver *, UiComponent *> > >::iterator it;

  it = win32CommandCallbacks.find(notificationCode);

  if(it != win32CommandCallbacks.end())
  {
    // look up the child id
    boost::unordered_map<int, std::pair<AbstractUiEventObserver *, UiComponent *> >::iterator eventIt;

    eventIt = it->second.find(childHwndId);

    if(eventIt != it->second.end())
    {
      UiComponent * childUiComponent = eventIt->second.second;

      AbstractUiEventObserver * abstractUiEventObserver = eventIt->second.first;

      (*abstractUiEventObserver)(childUiComponent);

      return 0;
    }
  }

  // let the system handle the message
  return DefWindowProc(uiComponent->getUiComponentContext()->hwnd, message, wParam, lParam);
}
