////////////////////////////////////////////////////////////////////////////////
//
// File: WM_CTLCOLORSTATIC_MessageHandler.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "graphics/private/windows/SystemGraphics.h"
#include "graphics/private/windows/GraphicsDeleter.h"

#include "graphics/Color.h"

#include "ui/uiComponent.h"

#include "ui/private/windows/UiComponentContext.h"

#include "ui/event/AbstractColorChangeObserver.h"

#include "ui/private/windows/WM_CTLCOLORSTATIC_MessageHandler.h"

WM_CTLCOLORSTATIC_MessageHandler::WM_CTLCOLORSTATIC_MessageHandler()
:brush(nullptr)
{
}

WM_CTLCOLORSTATIC_MessageHandler::~WM_CTLCOLORSTATIC_MessageHandler()
{
  if(brush)
  {
    ::DeleteObject(brush);
  }
}

int WM_CTLCOLORSTATIC_MessageHandler::getIdentifier() const
{
  return WM_CTLCOLORSTATIC;
}

LRESULT WM_CTLCOLORSTATIC_MessageHandler::messageHandler(UiComponent * uiComponent,
                                                         UINT message,
                                                         WPARAM wParam,
                                                         LPARAM lParam)
{
  HWND childHwnd = reinterpret_cast<HWND>(lParam);

  int childHwndId = ::GetWindowLongPtr(childHwnd, GWLP_ID);

  boost::unordered_map<int, std::pair<AbstractColorChangeObserver *, UiComponent *> >::iterator it;

  it = win32MessageCallbacks.find(childHwndId);

  if(it != win32MessageCallbacks.end())
  {
    HDC hdc = reinterpret_cast<HDC>(wParam);

    UiComponent * childUiComponent = it->second.second;

    boost::shared_ptr<SystemGraphics> graphics(new SystemGraphics(childUiComponent,
                                                                  hdc),
                                               GraphicsDeleter());

    graphics->initialize();

    AbstractColorChangeObserver * abstractColorChangeObserver = it->second.first;

    (*abstractColorChangeObserver)(childUiComponent, graphics);

    if(brush)
    {
      ::DeleteObject(brush);
    }

    brush = ::CreateSolidBrush(childUiComponent->getBackgroundColor()->getColorValue());

    return reinterpret_cast<LRESULT>(brush);

  }
  else
  {
    // let the system handle the message
    return DefWindowProc(uiComponent->getUiComponentContext()->hwnd, message, wParam, lParam);
  }
}
