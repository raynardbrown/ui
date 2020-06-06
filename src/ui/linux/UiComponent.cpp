////////////////////////////////////////////////////////////////////////////////
//
// File: UiComponent.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include <gtk/gtk.h>

#include "graphics/Color.h"
#include "graphics/Font.h"
#include "graphics/FontFactory.h"
#include "graphics/Rectangle2D.h"
#include "graphics/Size2D.h"

#include "ui/TopLevelWindow.h"

#include "ui/layout/Margin.h"
#include "ui/layout/Padding.h"
#include "ui/layout/ILayout.h"

#include "ui/private/linux/UiComponentContext.h"
#include "ui/private/linux/UiComponentDrawableSurface.h"
#include "ui/private/DefaultFocusImpl.h"
#include "ui/private/IdManager.h"
#include "ui/private/UiComponentPrivate.h"

#include "ui/UiComponent.h"

UiComponentContext::UiComponentContext()
:widget(nullptr),
 fixedContainerWidget(nullptr)
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
    gtk_widget_set_sensitive(GTK_WIDGET(this->uiComponentContext->widget),
                             enabled);
  }
}

UiComponent::~UiComponent()
{

}

void UiComponent::setSize(int width, int height)
{
  dRoot->bounds->setSize(width, height);

  // TODO: set the window area drawable surface

  if(isInitialized())
  {
    gtk_widget_set_size_request(GTK_WIDGET(getUiComponentContext()->widget),
                                getWidth(),
                                getHeight());

    // Update your layout because your size changed
    doLayout();
  }
}

void UiComponent::setClientSize(int width, int height)
{

}

void UiComponent::setLocation(int x, int y)
{
  dRoot->bounds->setLocation(x, y);

  if(isInitialized())
  {
    gtk_fixed_put(GTK_FIXED(getUiComponentContext()->fixedContainerWidget),
                  GTK_WIDGET(getUiComponentContext()->widget),
                  getX(),
                  getY());
  }

}

void UiComponent::setBounds(int x, int y, int width, int height)
{
  dRoot->bounds->setBounds(x, y, width, height);

  if(isInitialized())
  {
    gtk_widget_set_size_request(GTK_WIDGET(getUiComponentContext()->widget),
                                getWidth(),
                                getHeight());

    gtk_fixed_put(GTK_FIXED(getUiComponentContext()->fixedContainerWidget),
                  GTK_WIDGET(getUiComponentContext()->widget),
                  getX(),
                  getY());

    // TODO: Update the client area accordingly

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

  }
}

void UiComponent::redrawUiComponentLater()
{
  // TODO: Implement
}

bool UiComponent::isParentValid() const
{
  return getParent() != nullptr &&
         getParent()->getUiComponentContext() != nullptr &&
         getParent()->getUiComponentContext()->widget != nullptr;
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
    // TODO: Set the new font
  }

  initializeChildren();

  // Perform the layout if a layout is registered.
  doLayout();
}

void UiComponent::initializeEventHandlers()
{

}

IDrawableSurface * UiComponent::getDrawableSurface() const
{
  return dRoot->drawableSurface;
}

void UiComponent::initialize()
{
  // Set up event handlers
  initializeEventHandlers();

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
      // TODO: I don't believe ids are used within the GTK framework, but keep this for now
      dRoot->idManager = boost::shared_ptr<IdManager>(new IdManager(0,
                                                                    65535));
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
      // TODO: Test typeface name change later
      dRoot->sharedFont = dRoot->fontfactory->createSharedFont("Sans", 9);
    }
  }
  
  // TODO: Adjust the widget client area

  if(!dRoot->enabled)
  {
    // TODO: Enable the widget
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
    return getUiComponentContext()->widget == uiComponent->getUiComponentContext()->widget &&
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

      invalidateLayout();
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
      childUiComponent->dRoot->sharedFont = parentUiComponent->dRoot->fontfactory->createSharedFont("Sans", 9);
    }

    childUiComponent->initialize();

    UiComponentContext * childUiComponentContext = childUiComponent->getUiComponentContext();

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
  if(isInitialized())
  {
    // TODO: Set the font
  }

  // we are now sharing the font
  dRoot->sharedFont = font;
}
