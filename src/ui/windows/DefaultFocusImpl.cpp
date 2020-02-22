////////////////////////////////////////////////////////////////////////////////
//
// File: DefaultFocusImpl.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

#include "ui/private/windows/UiComponentContext.h"

#include "ui/private/DefaultFocusImpl.h"

#include "ui/UiComponent.h"

DefaultFocusImpl::DefaultFocusImpl(UiComponent * childUiComponent)
:IFocusImpl(),
 childUiComponent(childUiComponent)
{

}

DefaultFocusImpl::~DefaultFocusImpl()
{

}

void DefaultFocusImpl::setFocus()
{
  ::SetFocus(childUiComponent->getUiComponentContext()->hwnd);
}
