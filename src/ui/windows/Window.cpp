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

#include <memory>

#include <windows.h>

#include "string/extras/CharacterEncoder.h"

#include "ui/private/windows/UiComponentContext.h"
#include "ui/private/windows/WindowPrivate.h"
#include "ui/private/windows/TopLevelWindowContext.h"

#include "ui/private/windows/IMessageHandler.h"
#include "ui/private/windows/WM_CLOSE_MessageHandler.h"
#include "ui/event/AbstractCloseObserver.h"

#include "ui/Window.h"

WindowPrivate::WindowPrivate(const std::string& title)
:TopLevelWindowPrivate(),
 title(title),
 windowClassName(L"DEFAULT_WINDOW_CLASS")
{

}

WindowPrivate::~WindowPrivate()
{

}

Window::Window(const std::string& title,
               int width,
               int height)
:TopLevelWindow(*new WindowPrivate(title))
{
  this->setSize(width, height);
}

Window::Window(WindowPrivate &d)
:TopLevelWindow(d)
{

}

void Window::showWindow()
{
  WindowPrivate * d = static_cast<WindowPrivate *>(dRoot.get());

  if(!isInitialized())
  {
    initialize();
  }

  ::ShowWindow(d->uiComponentContext->hwnd, SW_NORMAL);
}

static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  Window * window = nullptr;

  window = reinterpret_cast<Window *>(::GetWindowLongPtr(hwnd, GWLP_USERDATA));

  if(window)
  {
    IMessageHandler * registeredMessageHandler = window->getTopLevelWindowContext()->findWin32MessageHandler(message);

    if(registeredMessageHandler)
    {
      return registeredMessageHandler->messageHandler(window, message, wParam, lParam);
    }
  }

  // We can't handle the message let the system handle it
  return ::DefWindowProc(hwnd, message, wParam, lParam);
}

void WindowPrivate::registerWindow(Window * window)
{
  WNDCLASSEX wcx;
  wcx.cbSize = sizeof(WNDCLASSEX);

  // Title   - What does the CS_OWNDC class style do?
  //
  // Link    - http://blogs.msdn.com/b/oldnewthing/archive/2006/06/01/612970.aspx
  //
  // Summary - CS_OWNDC tells the Window Manager to never purge the DC from the
  //           the Window Manager's cache of DCs. This is bad because DCs are a
  //           limited system resource and your application is reserving one for
  //           the lifetime of the application. In short "DCs should not be
  //           allocated carelessly".

  wcx.style = CS_VREDRAW |
              CS_HREDRAW;

  wcx.lpfnWndProc = &::WindowProcedure;
  wcx.cbClsExtra = 0;
  wcx.cbWndExtra = 0;
  wcx.hInstance = nullptr; // TODO: Use: GetModuleHandleEx

  wcx.hIcon = reinterpret_cast<HICON>(0); // TODO: Provide icon API

  wcx.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);

  // A one must be added to the chosen background color per
  // https://msdn.microsoft.com/en-us/library/windows/desktop/ms633576(v=vs.85).aspx
  // COLOR_BTNFACE --> Color of dialog box backgrounds.
  wcx.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
  wcx.lpszMenuName = 0;

  wcx.lpszClassName = static_cast<LPCTSTR>(windowClassName.c_str());

  wcx.hIconSm = reinterpret_cast<HICON>(0); // TODO: Provide icon API

  ATOM theAtom = ::RegisterClassExW(&wcx);

  if(theAtom == 0)
  {
    DWORD lastError = ::GetLastError();

    if(lastError != ERROR_CLASS_ALREADY_EXISTS)
    {
      // TODO: Failed to register window class, handle error
    }
  }
}

void Window::internalCreate()
{
  WindowPrivate * d = static_cast<WindowPrivate *>(dRoot.get());

  d->registerWindow(this);

  DWORD windowExtendedStyle = 0;
  DWORD windowStyle = WS_OVERLAPPEDWINDOW;

  // clip your child windows so that they do not flicker
  windowStyle |= WS_CLIPCHILDREN;

  HWND hwnd = ::CreateWindowExW(windowExtendedStyle,
                                reinterpret_cast<LPCTSTR>(d->windowClassName.c_str()),
                                CharacterEncoder::utf8ToUtf16(d->title).c_str(),
                                windowStyle,
                                getX(),
                                getY(),
                                getWidth(),
                                getHeight(),
                                reinterpret_cast<HWND>(nullptr), // TODO: support owned/owner
                                reinterpret_cast<HMENU>(0),
                                nullptr, // TODO: Use the HINSTANCE from the class registration
                                this);

  setInitialized(true);

  // TODO: check return value
  d->uiComponentContext = std::auto_ptr<UiComponentContext>(new UiComponentContext());
  d->uiComponentContext->hwnd = hwnd;

  /*
   * Set this Window in the user data section so that the window procedure can
   * access methods of this class
   */
  ::SetWindowLongPtr(getUiComponentContext()->hwnd,
                     GWLP_USERDATA,
                     reinterpret_cast<LONG_PTR>(this));
}

void Window::addCloseObserver(AbstractCloseObserver * closeObserver)
{
  WindowPrivate * d = static_cast<WindowPrivate *>(dRoot.get());

  d->closeObservers.push_back(closeObserver);

  std::auto_ptr<IMessageHandler> messageHandler(new WM_CLOSE_MessageHandler());

  IMessageHandler * registeredMessageHandler = getTopLevelWindowContext()->initWin32MessageHandler(messageHandler);

  // we know that the type of IMessageHandler is a WM_CLOSE_MessageHandler
  WM_CLOSE_MessageHandler * wm_close_messageHandler = static_cast<WM_CLOSE_MessageHandler *>(registeredMessageHandler);
  wm_close_messageHandler->observers.push_back(closeObserver);
}

void Window::calculateInternalPreferredSize()
{

}
