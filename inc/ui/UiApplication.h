////////////////////////////////////////////////////////////////////////////////
//
// File: UiApplication.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_UIAPPLICATION_H_
#define UI_UIAPPLICATION_H_

class Window;

class UiApplication
{
  public:

    UiApplication(int argc, char **argv);

    UiApplication();

    ~UiApplication();

    static int run(Window * window);

    static void quit();
};
#endif /* UI_UIAPPLICATION_H_ */
