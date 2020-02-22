////////////////////////////////////////////////////////////////////////////////
//
// File: DefaultFocusImpl.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_DEFAULTFOCUSIMPL_H_
#define UI_PRIVATE_DEFAULTFOCUSIMPL_H_

#include "ui/private/IFocusImpl.h"

class UiComponent;

class DefaultFocusImpl : public IFocusImpl
{
  public:

    DefaultFocusImpl(UiComponent * childUiComponent);

    virtual ~DefaultFocusImpl();

    virtual void setFocus();

  private:

    UiComponent * childUiComponent;
};
#endif /* UI_PRIVATE_DEFAULTFOCUSIMPL_H_ */
