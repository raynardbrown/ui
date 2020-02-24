////////////////////////////////////////////////////////////////////////////////
//
// File: AbstractCloseObserver.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_EVENT_ABSTRACTCLOSEOBSERVER_H_
#define UI_EVENT_ABSTRACTCLOSEOBSERVER_H_

class AbstractCloseObserver
{
  protected:

    AbstractCloseObserver()
    {

    }

  public:

    virtual ~AbstractCloseObserver()
    {

    }

    virtual void operator()() = 0;
};
#endif /* UI_EVENT_ABSTRACTCLOSEOBSERVER_H_ */
