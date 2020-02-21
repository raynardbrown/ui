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

#ifndef IFOCUSIMPL_H_
#define IFOCUSIMPL_H_

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
#endif /* IFOCUSIMPL_H_ */
