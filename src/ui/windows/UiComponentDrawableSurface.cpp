////////////////////////////////////////////////////////////////////////////////
//
// File: UiComponentDrawableSurface.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "graphics/private/windows/DrawableSurfaceContext.h"

#include "ui/private/windows/UiComponentDrawableSurface.h"

UiComponentDrawableSurface::UiComponentDrawableSurface()
:IDrawableSurface(),
 width(0),
 height(0),
 drawableSurfaceContext(new DrawableSurfaceContext)
{

}

UiComponentDrawableSurface::~UiComponentDrawableSurface()
{

}

int UiComponentDrawableSurface::getWidth() const
{
  return width;
}

int UiComponentDrawableSurface::getHeight() const
{
  return height;
}

void UiComponentDrawableSurface::setHandle(HWND hwnd)
{
  drawableSurfaceContext->hwnd = hwnd;
}

void UiComponentDrawableSurface::setSize(int width, int height)
{
  this->width = width;
  this->height = height;
}

DrawableSurfaceContext * UiComponentDrawableSurface::getDrawableSurfaceContext() const
{
  return drawableSurfaceContext;
}
