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
#include "ui/private/DefaultFocusImpl.h"
#include "ui/private/IdManager.h"
#include "ui/private/UiComponentPrivate.h"

#include "ui/UiComponent.h"

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
