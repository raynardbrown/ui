////////////////////////////////////////////////////////////////////////////////
//
// File: Button.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#include "ui/private/windows/ButtonPrivate.h"
#endif

#include "ui/Button.h"

Button::Button(const std::string& text)
:UiComponent(*new ButtonPrivate(text))
{
}

Button::~Button()
{

}

Button::Button(ButtonPrivate& d)
:UiComponent(d)
{

}

std::string Button::getText() const
{
  ButtonPrivate * d = static_cast<ButtonPrivate *>(dRoot.get());

  return d->buttonText;
}
