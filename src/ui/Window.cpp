////////////////////////////////////////////////////////////////////////////////
//
// File: Window.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32

// Title   - C++: auto_ptr + forward declaration?
//
// Link    - https://stackoverflow.com/questions/1951933/c-auto-ptr-forward-declaration
//
// Summary - You must include the header for the forward declaration in the
// source file that contains the destructor of the class that contains the
// auto_ptr that holds the forward declaration or you get the following error.
//
// warning C4150: deletion of pointer to incomplete type 'WindowPrivate'; no destructor called
//
#include "ui/private/windows/WindowPrivate.h"
#endif

#include "ui/Window.h"

Window::~Window()
{

}

