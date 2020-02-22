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

#ifndef UI_PRIVATE_WINDOWS_UICOMPONENTDRAWABLESURFACE_H_
#define UI_PRIVATE_WINDOWS_UICOMPONENTDRAWABLESURFACE_H_

#include <windows.h>

#include "graphics/IDrawableSurface.h"

class UiComponentDrawableSurface : public IDrawableSurface
{
  public:

    UiComponentDrawableSurface();

  public:

    virtual ~UiComponentDrawableSurface();

    virtual int getWidth() const;
    virtual int getHeight() const;

    void setHandle(HWND hwnd);
    void setSize(int width, int height);

    virtual DrawableSurfaceContext * getDrawableSurfaceContext() const;

  private:

    int width;
    int height;
    DrawableSurfaceContext * drawableSurfaceContext;
};
#endif /* SRC_UI_PRIVATE_WINDOWS_UICOMPONENTDRAWABLESURFACE_H_ */
