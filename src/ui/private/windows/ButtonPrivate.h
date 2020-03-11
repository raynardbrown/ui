////////////////////////////////////////////////////////////////////////////////
//
// File: ButtonPrivate.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_WINDOWS_BUTTONPRIVATE_H_
#define UI_PRIVATE_WINDOWS_BUTTONPRIVATE_H_

#include <windows.h>

#include <string>

#include "ui/private/UiComponentPrivate.h"

class ButtonPrivate : public UiComponentPrivate
{
  public:

    ButtonPrivate(const std::string& text);

    virtual ~ButtonPrivate();

    std::string buttonText;

    DWORD style;
};
#endif /* UI_PRIVATE_WINDOWS_BUTTONPRIVATE_H_ */
