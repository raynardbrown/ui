////////////////////////////////////////////////////////////////////////////////
//
// File: AbstractColorChangeObserver.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_EVENT_ABSTRACTCOLORCHANGEOBSERVER_H_
#define UI_EVENT_ABSTRACTCOLORCHANGEOBSERVER_H_

#include <boost/shared_ptr.hpp>

class Graphics;
class UiComponent;

class AbstractColorChangeObserver
{
  protected:

    AbstractColorChangeObserver()
    {
    }

  public:

    virtual ~AbstractColorChangeObserver()
    {

    }

    virtual void operator()(UiComponent * uiComponent,
                            boost::shared_ptr<Graphics> graphics) = 0;
};
#endif /* UI_EVENT_ABSTRACTCOLORCHANGEOBSERVER_H_ */
