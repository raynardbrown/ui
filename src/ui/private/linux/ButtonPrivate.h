////////////////////////////////////////////////////////////////////////////////
//
// File: ButtonPrivate.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_LINUX_BUTTONPRIVATE_H_
#define UI_PRIVATE_LINUX_BUTTONPRIVATE_H_

#include <string>

#include "ui/private/UiComponentPrivate.h"

class ButtonPrivate : public UiComponentPrivate
{
  public:

    ButtonPrivate(const std::string& text);

    virtual ~ButtonPrivate();

    std::string buttonText;
};
#endif /* UI_PRIVATE_LINUX_BUTTONPRIVATE_H_ */
