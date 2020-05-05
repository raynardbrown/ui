////////////////////////////////////////////////////////////////////////////////
//
// File: UiApplication.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

#include "ui/UiApplication.h"

UiApplication::UiApplication(int argc, char ** argv)
{

}

UiApplication::UiApplication()
{

}

int UiApplication::run(Window * window)
{
  MSG msg;

  BOOL getMessageReturn;

  while((getMessageReturn = ::GetMessageW(&msg, NULL, 0, 0)) != 0)
  {
    if(getMessageReturn == -1)
    {
      /*
       * TODO: Handle error and possibly exit. Think about giving the user
       * an option to exit on errors by changing the Application::run
       * signature.
       */
    }
    else
    {
      ::TranslateMessage(&msg);
      ::DispatchMessageW(&msg);
    }
  }

  return static_cast<int>(msg.wParam);
}

/* static */ void UiApplication::quit()
{
  ::PostQuitMessage(0);
}
