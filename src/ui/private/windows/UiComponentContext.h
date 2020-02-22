////////////////////////////////////////////////////////////////////////////////
//
// File: UiComponentContext.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_WINDOWS_UICOMPONENTCONTEXT_H_
#define UI_PRIVATE_WINDOWS_UICOMPONENTCONTEXT_H_

#include <windows.h>

class UiComponentContext
{
  public:

    UiComponentContext();

    ~UiComponentContext();

    HWND hwnd;

    HINSTANCE hinstance;
};
#endif /* UI_PRIVATE_WINDOWS_UICOMPONENTCONTEXT_H_ */
