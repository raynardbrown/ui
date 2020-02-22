////////////////////////////////////////////////////////////////////////////////
//
// File: IFocusImpl.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_IFOCUSIMPL_H_
#define UI_PRIVATE_IFOCUSIMPL_H_

class IFocusImpl
{
  protected:

    IFocusImpl()
    {

    }

  public:

    virtual ~IFocusImpl()
    {

    }

    virtual void setFocus() = 0;
};
#endif /* UI_PRIVATE_IFOCUSIMPL_H_ */
