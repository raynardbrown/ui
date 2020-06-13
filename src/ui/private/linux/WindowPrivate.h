////////////////////////////////////////////////////////////////////////////////
//
// File: WindowPrivate.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_LINUX_WINDOWPRIVATE_H_
#define UI_PRIVATE_LINUX_WINDOWPRIVATE_H_

#include <string>

#include "ui/private/linux/TopLevelWindowPrivate.h"

class WindowPrivate : public TopLevelWindowPrivate
{
  public:

    WindowPrivate(const std::string& title);

    virtual ~WindowPrivate();

    std::string title;
};
#endif /* UI_PRIVATE_LINUX_WINDOWPRIVATE_H_ */
