////////////////////////////////////////////////////////////////////////////////
//
// File: UiApplication.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include <gtk/gtk.h>

#include "ui/UiApplication.h"

int UiApplication::run(Window * window)
{
  gtk_main();
  return 0;
}

/* static */ void UiApplication::quit()
{
  ::gtk_main_quit();
}
