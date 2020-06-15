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

    /**
     * Create a new UiApplication, initializing it with the specified command
     * line.
     *
     * @param[in] argc the number of command line arguments in the specified
     * array.
     *
     * @param[in] argv array of command line arguments provided to this
     * UiApplication via the main function.
     */
    UiApplication(int argc, char **argv);

    /**
     * Create a new UiApplication without a command line.
     */
    UiApplication();

    ~UiApplication();

    int run(Window * window);

    static void quit();
};
#endif /* UI_UIAPPLICATION_H_ */
