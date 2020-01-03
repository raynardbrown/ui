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

#ifndef UIAPPLICATION_H_
#define UIAPPLICATION_H_

class Window;

class UiApplication
{
  public:

    UiApplication(int argc, char **argv);

    UiApplication();

    ~UiApplication();

    static int run(Window * window);
};
#endif /* UIAPPLICATION_H_ */
