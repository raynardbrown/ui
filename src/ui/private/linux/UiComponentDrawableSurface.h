////////////////////////////////////////////////////////////////////////////////
//
// File: UiComponentDrawableSurface.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_LINUX_UICOMPONENTDRAWABLESURFACE_H_
#define UI_PRIVATE_LINUX_UICOMPONENTDRAWABLESURFACE_H_

#include "graphics/IDrawableSurface.h"

class UiComponentDrawableSurface : public IDrawableSurface
{
  public:

    UiComponentDrawableSurface();

  public:

    virtual ~UiComponentDrawableSurface();

    virtual int getWidth() const;
    virtual int getHeight() const;

    void setSize(int width, int height);

    virtual DrawableSurfaceContext * getDrawableSurfaceContext() const;

  private:

    int width;
    int height;
    DrawableSurfaceContext * drawableSurfaceContext;
};
#endif /* UI_PRIVATE_LINUX_UICOMPONENTDRAWABLESURFACE_H_ */
