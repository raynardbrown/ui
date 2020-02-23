////////////////////////////////////////////////////////////////////////////////
//
// File: TopLevelWindowContext.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_WINDOWS_TOPLEVELWINDOWCONTEXT_H_
#define UI_PRIVATE_WINDOWS_TOPLEVELWINDOWCONTEXT_H_

#include <memory>

#include <windows.h>

#include <boost/unordered_map.hpp>

class IMessageHandler;

class TopLevelWindowContext
{
  public:

    TopLevelWindowContext();

    ~TopLevelWindowContext();

    IMessageHandler * initWin32MessageHandler(std::auto_ptr<IMessageHandler> messageHandler);
    IMessageHandler * findWin32MessageHandler(UINT messageId);

    // UINT            - Win32 message ID
    // IMessageHandler - Interface that handles the Win32 message specified by UINT
    boost::unordered_map<UINT, IMessageHandler *> win32MessageCallbacks;
};
#endif /* UI_PRIVATE_WINDOWS_TOPLEVELWINDOWCONTEXT_H_ */
