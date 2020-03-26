////////////////////////////////////////////////////////////////////////////////
//
// File: TopLevelWindow.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "graphics/Rectangle2D.h"

#include "ui/MenuBar.h"

#include "ui/private/windows/IMessageHandler.h"
#include "ui/private/windows/UiComponentContext.h"

#include "ui/private/windows/TopLevelWindowPrivate.h"
#include "ui/private/windows/TopLevelWindowContext.h"

#include "ui/TopLevelWindow.h"

TopLevelWindowPrivate::TopLevelWindowPrivate()
:UiComponentPrivate(),
 menuBar(nullptr),
 owner(nullptr),
 topLevelWindowContext(new TopLevelWindowContext())
{

}

TopLevelWindowPrivate::~TopLevelWindowPrivate()
{

}

bool TopLevelWindowPrivate::updateMenuBar()
{
  if(menuBar.get())
  {
    int drawMenuCheck = ::DrawMenuBar(topLevelWindow->getUiComponentContext()->hwnd);
    if(drawMenuCheck == 0)
    {
      DWORD lastError = ::GetLastError();
      return false;
    }
    else
    {
      return true;
    }
  }
  return false;
}

void TopLevelWindowPrivate::setTopLevelWindow(TopLevelWindow * window)
{
  topLevelWindow = window;
}

void TopLevelWindowPrivate::initializeMenuBar(TopLevelWindow * topLevelWindow,
                                              MenuBar * menubar)
{
  menuBar->setParent(topLevelWindow);
  menuBar->dRoot->topLevelWindow = topLevelWindow;
  menuBar->dRoot->idManager = topLevelWindow->dRoot->idManager;

  menuBar->initialize();
}

TopLevelWindowContext::TopLevelWindowContext()
{

}

TopLevelWindowContext::~TopLevelWindowContext()
{
  boost::unordered_map<UINT, IMessageHandler *>::iterator it;

  for(it = win32MessageCallbacks.begin(); it != win32MessageCallbacks.end();)
  {
    delete it->second;
    it = win32MessageCallbacks.erase(it);
  }
}

IMessageHandler * TopLevelWindowContext::initWin32MessageHandler(std::auto_ptr<IMessageHandler> messageHandler)
{
  boost::unordered_map<UINT, IMessageHandler *>::iterator it;

  const int WM_Identifier = messageHandler->getIdentifier();

  it = win32MessageCallbacks.find(WM_Identifier);

  // check to see if a  handler already exists and if not add it one
  if(it == win32MessageCallbacks.end())
  {
    win32MessageCallbacks[WM_Identifier] = messageHandler.get();

    return messageHandler.release();
  }
  else
  {
    return it->second;
  }
}

IMessageHandler * TopLevelWindowContext::findWin32MessageHandler(UINT messageId)
{
  boost::unordered_map<UINT, IMessageHandler *>::iterator it;

  it = win32MessageCallbacks.find(messageId);

  if(it != win32MessageCallbacks.end())
  {
    return it->second;
  }

  return nullptr;
}

TopLevelWindow::TopLevelWindow()
:UiComponent(*new TopLevelWindowPrivate())
{
  TopLevelWindowPrivate * d = static_cast<TopLevelWindowPrivate *>(dRoot.get());
  d->setTopLevelWindow(this);
}

TopLevelWindow::TopLevelWindow(TopLevelWindowPrivate& d)
:UiComponent(d)
{
  d.setTopLevelWindow(this);
}

TopLevelWindow::~TopLevelWindow()
{
}

MenuBar * TopLevelWindow::getMenuBar() const
{
  TopLevelWindowPrivate * d = static_cast<TopLevelWindowPrivate *>(dRoot.get());
  return d->menuBar.get();
}

bool TopLevelWindow::hasMenu() const
{
  TopLevelWindowPrivate * d = static_cast<TopLevelWindowPrivate *>(dRoot.get());

  if(d->menuBar.get())
  {
    return true;
  }

  return false;
}

UiComponent * TopLevelWindow::getParent() const
{
  return nullptr;
}

TopLevelWindow * TopLevelWindow::getOwner() const
{
  TopLevelWindowPrivate * d = static_cast<TopLevelWindowPrivate *>(dRoot.get());

  return d->owner;
}

void TopLevelWindow::setOwner(TopLevelWindow * owner)
{
  TopLevelWindowPrivate * d = static_cast<TopLevelWindowPrivate *>(dRoot.get());

  d->owner = owner;
}

void TopLevelWindow::initializeMenu()
{
  TopLevelWindowPrivate * d = static_cast<TopLevelWindowPrivate *>(dRoot.get());

  if(d->menuBar.get())
  {
    if(!d->menuBar->isInitialized())
    {
      d->initializeMenuBar(this, d->menuBar.get());
    }
  }
}

void TopLevelWindow::setMenuBar(MenuBar * menuBar)
{
  TopLevelWindowPrivate * d = static_cast<TopLevelWindowPrivate *>(dRoot.get());
  d->menuBar.reset(menuBar);

  if(isInitialized())
  {
    d->initializeMenuBar(this, d->menuBar.get());

    if(d->updateMenuBar())
    {
      // Don't forget to update the client area now that a menubar has been set

      RECT rect;
      ::GetClientRect(getUiComponentContext()->hwnd, &rect);
      d->clientBounds->setBounds(rect.left, rect.top, rect.right, rect.bottom);
    }
  }
}

TopLevelWindowContext * TopLevelWindow::getTopLevelWindowContext() const
{
  TopLevelWindowPrivate * d = static_cast<TopLevelWindowPrivate *>(dRoot.get());

  return d->topLevelWindowContext.get();
}
