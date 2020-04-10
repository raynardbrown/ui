////////////////////////////////////////////////////////////////////////////////
//
// File: UiEventObserver.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_EVENT_UIEVENTOBSERVER_H_
#define UI_EVENT_UIEVENTOBSERVER_H_

#include "ui/event/AbstractUiEventObserver.h"

template<typename T>
class UiEventObserver : public AbstractUiEventObserver
{
  public:

    UiEventObserver(T * thisPointer,
                    void (T::*pointerToMemberFunction)(UiComponent * uiComponent))
    :thisPointer(thisPointer),
     pointerToMemberFunction(pointerToMemberFunction)
    {

    }

    virtual ~UiEventObserver()
    {

    }

    virtual void operator()(UiComponent * uiComponent)
    {
      (thisPointer->*pointerToMemberFunction)(uiComponent);
    }

  private:

    T * thisPointer;
    void (T::*pointerToMemberFunction)(UiComponent * uiComponent);
};
#endif /* UI_EVENT_UIEVENTOBSERVER_H_ */
