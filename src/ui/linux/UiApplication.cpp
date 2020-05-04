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

UiApplication::UiApplication(int argc, char ** argv)
{
  // I'm passing nullptr as parameters because command line processing is not
  // required since it has been done by the CommandLine class.
  ::gtk_init(nullptr, nullptr);
}

UiApplication::UiApplication()
{
  ::gtk_init(nullptr, nullptr);
}

int UiApplication::run(Window * window)
{
  gtk_main();
  return 0;
}

/* static */ void UiApplication::quit()
{
  ::gtk_main_quit();
}
