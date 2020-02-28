////////////////////////////////////////////////////////////////////////////////
//
// File: ColorChangeObserver.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_EVENT_COLORCHANGEOBSERVER_H_
#define UI_EVENT_COLORCHANGEOBSERVER_H_

#include "ui/event/AbstractColorChangeObserver.h"

template<typename T>
class ColorChangeObserver : public AbstractColorChangeObserver
{
  public:

    ColorChangeObserver(T * thisPointer,
                        void (T::*pointerToMemberFunction)(UiComponent * uiComponent,
                                                           boost::shared_ptr<Graphics>))
    :thisPointer(thisPointer),
     pointerToMemberFunction(pointerToMemberFunction)
    {

    }

    virtual ~ColorChangeObserver()
    {

    }

    virtual void operator()(UiComponent * uiComponent,
                            boost::shared_ptr<Graphics> graphics)
    {
      (thisPointer->*pointerToMemberFunction)(uiComponent, graphics);
    }

  private:

    T * thisPointer;
    void (T::*pointerToMemberFunction)(UiComponent * uiComponent,
                                       boost::shared_ptr<Graphics>);
};
#endif /* UI_EVENT_COLORCHANGEOBSERVER_H_ */
