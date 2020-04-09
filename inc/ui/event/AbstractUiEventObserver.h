////////////////////////////////////////////////////////////////////////////////
//
// File: AbstractUiEventObserver.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_EVENT_ABSTRACTUIEVENTOBSERVER_H_
#define UI_EVENT_ABSTRACTUIEVENTOBSERVER_H_

class UiComponent;

class AbstractUiEventObserver
{
  protected:

    AbstractUiEventObserver()
    {

    }

  public:

    virtual ~AbstractUiEventObserver()
    {

    }

    virtual void operator()(UiComponent * uiComponent) = 0;
};
#endif /* UI_EVENT_ABSTRACTUIEVENTOBSERVER_H_ */
