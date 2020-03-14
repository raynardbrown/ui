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

#include "graphics/Color.h"
#include "graphics/Font.h"
#include "graphics/FontFactory.h"
#include "graphics/Point2D.h"
#include "graphics/Size2D.h"
#include "graphics/Rectangle2D.h"

#include "ui/private/UiComponentPrivate.h"

#include "ui/private/DefaultFocusImpl.h"

#include "ui/layout/ILayout.h"
#include "ui/layout/Margin.h"
#include "ui/layout/Padding.h"

#include "ui/UiComponent.h"

void UiComponentPrivate::initChildFocusImpl(UiComponent * /*parentUiComponent*/,
                                            UiComponent * childUiComponent,
                                            UiComponentPrivate * childUiComponentImpl)
{
  // The default implementation doesn't care about the parent
  childUiComponentImpl->focusImpl = std::auto_ptr<DefaultFocusImpl>(new DefaultFocusImpl(childUiComponent));
}

void UiComponentPrivate::updateClientAreaDimensions(int width, int height)
{
  clientBounds->setSize(width, height);
}

UiComponent::UiComponent()
:dRoot(new UiComponentPrivate())
{
  dRoot->thisUiComponent = this;
}

UiComponent::UiComponent(UiComponentPrivate &dRoot)
:dRoot(&dRoot)
{
  this->dRoot->thisUiComponent = this;
}

int UiComponent::getWidth() const
{
  return dRoot->bounds->getWidth();
}

int UiComponent::getClientWidth() const
{
  return dRoot->clientBounds->getWidth();
}

int UiComponent::getHeight() const
{
  return dRoot->bounds->getHeight();
}

int UiComponent::getClientHeight() const
{
  return dRoot->clientBounds->getHeight();
}

const Size2D * UiComponent::getSize() const
{
  return dRoot->bounds->getSize();
}

const Size2D * UiComponent::getClientSize() const
{
  return dRoot->clientBounds->getSize();
}

void UiComponent::setSize(const Size2D * size2D)
{
  setSize(size2D->getWidth(), size2D->getHeight());
}

void UiComponent::setClientSize(const Size2D * size2D)
{
  setClientSize(size2D->getWidth(), size2D->getHeight());
}

int UiComponent::getX() const
{
  return dRoot->bounds->getX();
}

int UiComponent::getY() const
{
  return dRoot->bounds->getY();
}

const Point2D * UiComponent::getLocation() const
{
  return dRoot->bounds->getLocation();
}

void UiComponent::setLocation(const Point2D * location)
{
  setLocation(location->getX(), location->getY());
}

const Rectangle2D * UiComponent::getBounds() const
{
  return dRoot->bounds.get();
}

const Rectangle2D * UiComponent::getClientBounds() const
{
  return dRoot->clientBounds.get();
}

void UiComponent::setBounds(const Rectangle2D * rec)
{
  setBounds(rec->getX(), rec->getY(), rec->getWidth(), rec->getHeight());
}

int UiComponent::getPreferredWidth() const
{
  return getPreferredSize() ? getPreferredSize()->getWidth(): 0;
}

int UiComponent::getPreferredHeight() const
{
  return getPreferredSize() ? getPreferredSize()->getHeight() : 0;
}

const Size2D * UiComponent::getPreferredSize() const
{
  return dRoot->preferredSize.get() ? dRoot->preferredSize.get() : dRoot->internalPreferredSize.get();
}

void UiComponent::setPreferredSize(int preferredWidth, int preferredHeight)
{
  if(dRoot->preferredSize.get())
  {
    dRoot->preferredSize->setSize(preferredWidth, preferredHeight);
  }
  else
  {
    dRoot->preferredSize = std::auto_ptr<Size2D>(new Size2D(preferredWidth, preferredHeight));
  }
}

void UiComponent::setPreferredSize(const Size2D * preferredSize)
{
  if(preferredSize)
  {
    dRoot->preferredSize->setSize(preferredSize);
  }
  else
  {
    dRoot->preferredSize.reset(nullptr);
  }
}

const Margin * UiComponent::getMargin() const
{
  return dRoot->margin.get();
}

int UiComponent::getLeftMargin() const
{
  return dRoot->margin->leftMargin;
}

int UiComponent::getRightMargin() const
{
  return dRoot->margin->rightMargin;
}

int UiComponent::getTopMargin() const
{
  return dRoot->margin->topMargin;
}

int UiComponent::getBottomMargin() const
{
  return dRoot->margin->bottomMargin;
}

const Padding * UiComponent::getPadding() const
{
  return dRoot->padding.get();
}

int UiComponent::getLeftPadding() const
{
  return dRoot->padding->leftPadding;
}

int UiComponent::getRightPadding() const
{
  return dRoot->padding->rightPadding;
}

int UiComponent::getTopPadding() const
{
  return dRoot->padding->topPadding;
}

int UiComponent::getBottomPadding() const
{
  return dRoot->padding->bottomPadding;
}

void UiComponent::setMargin(const Margin * margin)
{
  dRoot->margin->leftMargin = margin->leftMargin;
  dRoot->margin->rightMargin = margin->rightMargin;
  dRoot->margin->topMargin = margin->topMargin;
  dRoot->margin->bottomMargin = margin->bottomMargin;
}

void UiComponent::setMargin(int margin)
{
  dRoot->margin->leftMargin = margin;
  dRoot->margin->rightMargin = margin;
  dRoot->margin->topMargin = margin;
  dRoot->margin->bottomMargin = margin;
}

void UiComponent::setLeftMargin(int leftMargin)
{
  dRoot->margin->leftMargin = leftMargin;
}

void UiComponent::setRightMargin(int rightMargin)
{
  dRoot->margin->rightMargin = rightMargin;
}

void UiComponent::setTopMargin(int topMargin)
{
  dRoot->margin->topMargin = topMargin;
}

void UiComponent::setBottomMargin(int bottomMargin)
{
  dRoot->margin->bottomMargin = bottomMargin;
}

void UiComponent::setPadding(const Padding * padding)
{
  dRoot->padding->leftPadding = padding->leftPadding;
  dRoot->padding->rightPadding = padding->rightPadding;
  dRoot->padding->topPadding = padding->topPadding;
  dRoot->padding->bottomPadding = padding->bottomPadding;
}

void UiComponent::setPadding(int padding)
{
  dRoot->padding->leftPadding = padding;
  dRoot->padding->rightPadding = padding;
  dRoot->padding->topPadding = padding;
  dRoot->padding->bottomPadding = padding;
}

void UiComponent::setLeftPadding(int leftPadding)
{
  dRoot->padding->leftPadding = leftPadding;
}

void UiComponent::setRightPadding(int rightPadding)
{
  dRoot->padding->rightPadding = rightPadding;
}

void UiComponent::setTopPadding(int topPadding)
{
  dRoot->padding->topPadding = topPadding;
}

void UiComponent::setBottomPadding(int bottomPadding)
{
  dRoot->padding->bottomPadding = bottomPadding;
}

Color * UiComponent::getBackgroundColor() const
{
  return dRoot->backgroundColor.get();
}

void UiComponent::setBackgroundColor(Color * color)
{
  dRoot->backgroundColor.reset(color);
}

Color * UiComponent::getForegroundColor() const
{
  return dRoot->foregroundColor.get();
}

void UiComponent::setForegroundColor(Color * color)
{
  dRoot->foregroundColor.reset(color);
}

UiComponent * UiComponent::getParent() const
{
  return dRoot->parent;
}

void UiComponent::setParent(UiComponent * parent)
{
  dRoot->parent = parent;
}

bool UiComponent::isInitialized() const
{
  return dRoot->initialized;
}

void UiComponent::setInitialized(bool initialized)
{
  dRoot->initialized = initialized;
}

bool UiComponent::isEnabled() const
{
  return dRoot->isEnabled();
}

bool UiComponent::isVisible() const
{
  if(isInitialized())
  {
    return dRoot->visible;
  }
  else
  {
    return false;
  }
}

void UiComponent::setFocus()
{
  if(isInitialized())
  {
    dRoot->focusImpl->setFocus();
  }
}

int UiComponent::getId() const
{
  return dRoot->id;
}

bool UiComponent::hasMenu() const
{
  return false;
}

MenuBar * UiComponent::getMenuBar() const
{
  // By default UiComponents don't have menus only TopLevelWindows can have menus
  return nullptr;
}

Font * UiComponent::getFont() const
{
  return dRoot->sharedFont.get();
}

void UiComponent::removeUiComponent(UiComponent * uiComponent)
{
  std::vector<UiComponent *>::iterator iterator = dRoot->uiComponentChildren.begin();

  for(; iterator != dRoot->uiComponentChildren.begin(); ++iterator)
  {
    // Get a UiComponent, check for equality
    UiComponent * check = *iterator;
    if(check->equals(uiComponent))
    {
      // Found the UiComponent remove it
      dRoot->uiComponentChildren.erase(iterator);

      // exit the loop
      break;
    }
  }

  invalidateLayout();
}

UiComponent * UiComponent::getUiComponentAt(std::size_t index) const
{
  return dRoot->uiComponentChildren.at(index);
}

void UiComponent::removeUiComponentAt(std::size_t index)
{
  dRoot->uiComponentChildren.erase(dRoot->uiComponentChildren.begin() + index);
}

std::size_t UiComponent::getUiComponentCount() const
{
  return dRoot->uiComponentChildren.size();
}

ILayout * UiComponent::getLayout() const
{
  return dRoot->layout.get();
}

void UiComponent::setLayout(ILayout * layout)
{
  dRoot->layout.reset(layout);
}

void UiComponent::invalidateLayout()
{
  UiComponent * parent = getParent();

  if(parent)
  {
    parent->invalidateLayout();
  }
  else
  {
    // We are the top level window, so just perform the layout.
    doLayout();

    // Update the tooltip here since the tooltip's parent client area may not have
    // been valid prior to the parent being laid out.
    updateChildren();
  }
}

void UiComponent::doLayout()
{
  if(dRoot->layout.get())
  {
    dRoot->layout->executeLayout(this);
  }
}

TopLevelWindow * UiComponent::getTopLevelWindow() const
{
  return dRoot->topLevelWindow;
}

void UiComponent::internalCreate()
{

}


void UiComponent::create()
{

}

void UiComponent::initializeMenu()
{

}

void UiComponent::postCreate()
{

}

void UiComponent::initializeChildren()
{
  for(std::size_t i = 0; i < dRoot->uiComponentChildren.size(); ++i)
  {
    UiComponent * uiComponentChild = dRoot->uiComponentChildren.at(i);
    initializeChild(uiComponentChild);
  }
}

void UiComponent::updateChildren()
{
  for(std::size_t i = 0; i < dRoot->uiComponentChildren.size(); ++i)
  {
    UiComponent * uiComponentChild = dRoot->uiComponentChildren.at(i);
    updateChild(uiComponentChild);
  }
}

int UiComponent::getInternalPreferredWidth() const
{
  return getInternalPreferredSize() ? getInternalPreferredSize()->getWidth(): 0;
}

int UiComponent::getInternalPreferredHeight() const
{
  return getInternalPreferredSize() ? getInternalPreferredSize()->getHeight(): 0;
}

const Size2D * UiComponent::getInternalPreferredSize() const
{
  return dRoot->internalPreferredSize.get();
}

void UiComponent::setInternalPreferredSize(int preferredWidth, int preferredHeight)
{
  if(dRoot->internalPreferredSize.get())
  {
    dRoot->internalPreferredSize->setSize(preferredWidth, preferredHeight);
  }
  else
  {
    dRoot->internalPreferredSize = std::auto_ptr<Size2D>(new Size2D(preferredWidth, preferredHeight));
  }
}

void UiComponent::setInternalPreferredSize(const Size2D * preferredSize)
{
  if(preferredSize)
  {
    dRoot->internalPreferredSize->setSize(preferredSize);
  }
  else
  {
    dRoot->internalPreferredSize.reset(nullptr);
  }
}
