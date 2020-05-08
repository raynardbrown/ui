////////////////////////////////////////////////////////////////////////////////
//
// File: UiComponentContext.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_LINUX_UICOMPONENTCONTEXT_H_
#define UI_PRIVATE_LINUX_UICOMPONENTCONTEXT_H_

#include <gtk/gtk.h>

class UiComponentContext
{
  public:

    UiComponentContext();

    ~UiComponentContext();

    GtkWidget * widget;
};
#endif /* UI_PRIVATE_LINUX_UICOMPONENTCONTEXT_H_ */
