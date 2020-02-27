////////////////////////////////////////////////////////////////////////////////
//
// File: CloseObserver.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_EVENT_CLOSEOBSERVER_H_
#define UI_EVENT_CLOSEOBSERVER_H_

#include "ui/event/AbstractCloseObserver.h"

template<typename T>
class CloseObserver : public AbstractCloseObserver
{
  public:

    CloseObserver(T * thisPointer, void (T::*pointerToMemberFunction)())
    :AbstractCloseObserver(),
     thisPointer(thisPointer),
     pointerToMemberFunction(pointerToMemberFunction)
    {

    }

    virtual ~CloseObserver()
    {

    }

    virtual void operator()()
    {
      (thisPointer->*pointerToMemberFunction)();
    }

  private:

    T * thisPointer;
    void (T::*pointerToMemberFunction)();
};
#endif /* UI_EVENT_CLOSEOBSERVER_H_ */
