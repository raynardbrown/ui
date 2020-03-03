////////////////////////////////////////////////////////////////////////////////
//
// File: Window.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_WINDOW_H_
#define UI_WINDOW_H_

#include <string>

#include "ui/TopLevelWindow.h"

class WindowPrivate;
class AbstractCloseObserver;

class Window : public TopLevelWindow
{
  public:

    Window(const std::string& title,
           int width, int height);

    virtual ~Window();

    void showWindow();

    void addCloseObserver(AbstractCloseObserver * closeObserver);

  protected:

    virtual void internalCreate();

    Window(WindowPrivate &d);

    virtual void calculateInternalPreferredSize();
};

#endif /* UI_WINDOW_H_ */
