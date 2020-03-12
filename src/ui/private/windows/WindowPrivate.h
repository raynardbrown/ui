////////////////////////////////////////////////////////////////////////////////
//
// File: WindowPrivate.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_WINDOWS_WINDOWPRIVATE_H_
#define UI_PRIVATE_WINDOWS_WINDOWPRIVATE_H_

#include <string>

#include <vector>

#include "ui/private/windows/TopLevelWindowPrivate.h"

class Window;

class AbstractCloseObserver;

class WindowPrivate : public TopLevelWindowPrivate
{
  public:

    WindowPrivate(const std::string& title);

    virtual ~WindowPrivate();

    void registerWindow(Window * window);

    std::string title;

    std::wstring windowClassName;

    std::vector<AbstractCloseObserver *> closeObservers;
};
#endif /* UI_PRIVATE_WINDOWS_WINDOWPRIVATE_H_ */
