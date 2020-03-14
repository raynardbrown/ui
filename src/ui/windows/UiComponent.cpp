////////////////////////////////////////////////////////////////////////////////
//
// File: UiComponent.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include <cstddef>

#include <windows.h>

#include "graphics/Color.h"
#include "graphics/Font.h"
#include "graphics/FontFactory.h"
#include "graphics/Rectangle2D.h"
#include "graphics/Size2D.h"

#include "graphics/private/windows/FontContext.h"

#include "ui/TopLevelWindow.h"

#include "ui/layout/Margin.h"
#include "ui/layout/Padding.h"
#include "ui/layout/ILayout.h"

#include "ui/private/windows/UiComponentContext.h"
#include "ui/private/windows/UiComponentDrawableSurface.h"
#include "ui/private/DefaultFocusImpl.h"
#include "ui/private/IdManager.h"
#include "ui/private/UiComponentPrivate.h"

#include "ui/UiComponent.h"

static const int WIN32_CONTROL_ID_MIN = 0;
static const int WIN32_CONTROL_ID_MAX = 65535;

UiComponentContext::UiComponentContext()
:hwnd(nullptr),
 hinstance(nullptr)
{

}

UiComponentContext::~UiComponentContext()
{

}

UiComponentPrivate::UiComponentPrivate()
:bounds(new Rectangle2D(0, 0, 0, 0)),
 preferredSize(nullptr),
 internalPreferredSize(nullptr),
 clientBounds(new Rectangle2D(0, 0, 0, 0)),
 margin(new Margin),
 padding(new Padding),
 backgroundColor(nullptr),
 foregroundColor(nullptr),
 parent(nullptr),
 drawableSurface(nullptr),
 sharedFont(nullptr),
 focusImpl(nullptr),
 id(-1),
 initialized(false),
 enabled(true),
 visible(true),
 uiComponentContext(nullptr),
 topLevelWindow(nullptr),
 idManager(nullptr),
 layout(nullptr),
 thisUiComponent(nullptr)
{
  margin->leftMargin = 0;
  margin->rightMargin = 0;
  margin->topMargin = 0;
  margin->bottomMargin = 0;

  padding->leftPadding = 0;
  padding->rightPadding = 0;
  padding->topPadding = 0;
  padding->bottomPadding = 0;
}

UiComponentPrivate::~UiComponentPrivate()
{

}

void UiComponentPrivate::updateWindowAreaDimensions(int width, int height)
{
  if(initialized)
  {
    DWORD controlStyles = ::GetWindowLongPtr(uiComponentContext->hwnd, GWL_STYLE);
    DWORD extendedControlStyles = ::GetWindowLongPtr(uiComponentContext->hwnd, GWL_EXSTYLE);

    BOOL menuSet = thisUiComponent->hasMenu() ? TRUE : FALSE;

    if(controlStyles != 0 && extendedControlStyles != 0)
    {
      RECT rect;
      rect.left = 0;
      rect.top = 0;
      rect.right = width;
      rect.bottom = height;

      // TODO: The AdjustWindowRectEx function does not add extra space when a menu bar wraps to two or more rows.
      // TODO: This must be handled
      // TODO: The AdjustWindowRectEx function does not take the WS_VSCROLL or WS_HSCROLL styles into account.
      //       To account for the scroll bars, call the GetSystemMetrics function with SM_CXVSCROLL or SM_CYHSCROLL.
      // TODO: This must be handled
      ::AdjustWindowRectEx(&rect, controlStyles, menuSet, extendedControlStyles);

      // Adjust the entire window accordingly
      width = rect.right - rect.left;
      height = rect.bottom - rect.top;
    }
  }
}

bool UiComponentPrivate::isEnabled() const
{
  return enabled;
}

void UiComponentPrivate::setEnabled(bool enabled)
{
  this->enabled = enabled;

  if(initialized)
  {
    ::EnableWindow(uiComponentContext->hwnd, (enabled ? TRUE : FALSE));
  }
}

UiComponent::~UiComponent()
{

}

void UiComponent::setSize(int width, int height)
{
  dRoot->bounds->setSize(width, height);

  if(isInitialized())
  {
    ::SetWindowPos(getUiComponentContext()->hwnd,
                   0,
                   0,
                   0,
                   getWidth(),
                   getHeight(),
                   SWP_NOZORDER | SWP_NOMOVE);

    // Update the client area accordingly

    RECT clientRect;
    ::GetClientRect(getUiComponentContext()->hwnd, &clientRect);

    dRoot->updateClientAreaDimensions(clientRect.right - clientRect.left,
                                      clientRect.bottom - clientRect.top);

    // Update your layout because your size changed
    doLayout();
  }
}

void UiComponent::setClientSize(int width, int height)
{
  dRoot->updateClientAreaDimensions(width, height);

  dRoot->updateWindowAreaDimensions(width, height);

  if(isInitialized())
  {
    ::SetWindowPos(getUiComponentContext()->hwnd,
                   0,
                   0,
                   0,
                   getWidth(),
                   getHeight(),
                   SWP_NOZORDER | SWP_NOMOVE);

    // Update your layout because your size changed
    doLayout();
  }
}

void UiComponent::setLocation(int x, int y)
{
  dRoot->bounds->setLocation(x, y);

  if(isInitialized())
  {
    ::SetWindowPos(getUiComponentContext()->hwnd,
                   0,
                   getX(),
                   getY(),
                   0,
                   0,
                   SWP_NOZORDER | SWP_NOSIZE);
  }

}

void UiComponent::setBounds(int x, int y, int width, int height)
{
  dRoot->bounds->setBounds(x, y, width, height);

  if(isInitialized())
  {
    ::SetWindowPos(getUiComponentContext()->hwnd,
                   0,
                   getX(),
                   getY(),
                   getWidth(),
                   getHeight(),
                   SWP_NOZORDER);

    // Update the client area accordingly

    RECT clientRect;
    ::GetClientRect(getUiComponentContext()->hwnd, &clientRect);

    dRoot->updateClientAreaDimensions(clientRect.right - clientRect.left,
                                      clientRect.bottom - clientRect.top);

    // Update your layout because your size changed
    doLayout();
  }
}

void UiComponent::setEnabled(bool enabled)
{
  dRoot->setEnabled(enabled);
}

void UiComponent::setVisible(bool visible)
{
  dRoot->visible = visible;

  if(isInitialized())
  {
    ::ShowWindow(getUiComponentContext()->hwnd, (visible ? SW_SHOW : SW_HIDE));
  }
}

bool UiComponent::isParentValid() const
{
  return getParent() != nullptr &&
         getParent()->getUiComponentContext() != nullptr &&
         getParent()->getUiComponentContext()->hwnd != nullptr;
}

void UiComponent::enableDrawing()
{

}

void UiComponent::disableDrawing()
{

}

void UiComponent::internalPostCreate()
{
  // Set the font
  if(dRoot->sharedFont.get())
  {
    ::SendMessage(getUiComponentContext()->hwnd,
                  WM_SETFONT,
                  reinterpret_cast<WPARAM>(dRoot->sharedFont->getContext()->handle),
                  TRUE);
  }

  initializeChildren();

  // Perform the layout if a layout is registered.
  doLayout();
}

IDrawableSurface * UiComponent::getDrawableSurface() const
{
  return dRoot->drawableSurface;
}

void UiComponent::initialize()
{
  internalCreate();

  bool isTopLevelWindow = false;

  // Parent is valid at this point for uicomponents that have parents
  if(!getParent())
  {
    // No parent, do the default focus implementation
    dRoot->focusImpl = std::auto_ptr<DefaultFocusImpl>(new DefaultFocusImpl(this));

    isTopLevelWindow = true;

    // each top-level window has the one and only id manager that is shared with
    // its children
    if(!dRoot->idManager.get())
    {
      dRoot->idManager = boost::shared_ptr<IdManager>(new IdManager(WIN32_CONTROL_ID_MIN,
                                                                    WIN32_CONTROL_ID_MAX));
    }

    // also make sure that the font factory is initialized
    if(!dRoot->fontfactory.get())
    {
      dRoot->fontfactory = std::auto_ptr<FontFactory>(new FontFactory());
    }

    // if we do not have a font set by the client use the default font
    if(!dRoot->sharedFont.get())
    {
      // TODO: this is repeated code, hide the default font creation in a helper function
      dRoot->sharedFont = dRoot->fontfactory->createSharedFont("Segoe UI", 9);
    }
  }

  RECT rect;
  ::GetClientRect(getUiComponentContext()->hwnd, &rect);
  dRoot->clientBounds->setBounds(rect.left,
                               rect.top,
                               rect.right,
                               rect.bottom);

  if(!dRoot->enabled)
  {
    ::EnableWindow(getUiComponentContext()->hwnd, FALSE);
  }

  create();

  initializeMenu();

  internalPostCreate();

  postCreate();

  if(isTopLevelWindow)
  {
    updateChildren();
  }
}

UiComponentContext * UiComponent::getUiComponentContext() const
{
  return dRoot->uiComponentContext.get();
}

bool UiComponent::equals(UiComponent * uiComponent) const
{
  if(getUiComponentContext() && uiComponent->getUiComponentContext())
  {
    return getUiComponentContext()->hwnd == uiComponent->getUiComponentContext()->hwnd &&
           getId() == uiComponent->getId();
  }

  return false;
}

void UiComponent::addUiComponent(UiComponent * childUiComponent)
{
  // TODO: guard against adding yourself to yourself
  dRoot->uiComponentChildren.push_back(childUiComponent);

  // also make sure that the font factory is initialized
  // TODO: you must also ensure that the font factory is initialized for top
  //       level windows that do not have children
  if(!dRoot->fontfactory.get())
  {
    dRoot->fontfactory = std::auto_ptr<FontFactory>(new FontFactory());
  }

  if(isInitialized())
  {
    if(!childUiComponent->isInitialized())
    {
      initializeChild(childUiComponent);
    }
  }
}

void UiComponent::initializeChild(UiComponent * childUiComponent)
{
  UiComponent * parentUiComponent = this;

  if(!childUiComponent->isInitialized())
  {
    childUiComponent->setParent(parentUiComponent);

    // TODO: Make sure that this work for children with children, you may need
    //       to use getParent in a loop to get top level
    childUiComponent->dRoot->topLevelWindow = parentUiComponent->getTopLevelWindow();

    childUiComponent->dRoot->idManager = parentUiComponent->dRoot->idManager;

    childUiComponent->dRoot->id = childUiComponent->dRoot->idManager->requestId();

    // set your child's font if they do not already have one
    if(!childUiComponent->dRoot->sharedFont.get())
    {
      // use the default font
      // TODO: this is repeated code, hide the default font creation in a helper function
      childUiComponent->dRoot->sharedFont = parentUiComponent->dRoot->fontfactory->createSharedFont("Segoe UI", 9);
    }

    childUiComponent->initialize();

    UiComponentContext * childUiComponentContext = childUiComponent->getUiComponentContext();
    childUiComponentContext->hinstance = parentUiComponent->getUiComponentContext()->hinstance;

    dRoot->initChildFocusImpl(parentUiComponent,                // parent
                              childUiComponent,
                              childUiComponent->dRoot.get());   // child

    childUiComponent->setVisible(childUiComponent->isVisible()); // UiComponents are visible by default unless otherwise specified
  }
}

void UiComponent::updateChild(UiComponent * child)
{
  // Don't forget your children
  child->updateChildren();
}

void UiComponent::setFont(boost::shared_ptr<Font> font)
{
  // Set the new font - WM_SETFONT (If and only if we are initialized)
  if(isInitialized())
  {
    ::SendMessage(getUiComponentContext()->hwnd,
                  WM_SETFONT,
                  reinterpret_cast<WPARAM>(font->getContext()->handle),
                  TRUE);
  }

  // we are now sharing the font
  dRoot->sharedFont = font;
}
