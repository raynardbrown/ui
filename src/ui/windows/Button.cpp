////////////////////////////////////////////////////////////////////////////////
//
// File: Button.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <algorithm>

#include <windows.h>
#include <commctrl.h>

#include "string/extras/CharacterEncoder.h"

#include "graphics/Size2D.h"
#include "graphics/TextDimension.h"

#include "ui/layout/UiComponentSize.h"

#include "ui/private/windows/UiComponentContext.h"
#include "ui/private/windows/ButtonPrivate.h"

#include "ui/Button.h"

ButtonPrivate::ButtonPrivate(const std::string& text)
:UiComponentPrivate(),
 buttonText(text),
 style(WS_CHILD | WS_VISIBLE)
{

}

ButtonPrivate::~ButtonPrivate()
{
}

void Button::setText(const std::string& text)
{
  ButtonPrivate * d = static_cast<ButtonPrivate *>(dRoot.get());

  d->buttonText = text;

  if(d->initialized)
  {
    ::SendMessageW(d->uiComponentContext->hwnd,
                   WM_SETTEXT,
                   static_cast<WPARAM>(0),
                   reinterpret_cast<LPARAM>(CharacterEncoder::utf8ToUtf16(d->buttonText).c_str()));
  }
}

void Button::internalCreate()
{
  ButtonPrivate * d = static_cast<ButtonPrivate *>(dRoot.get());

  // TODO: Verify parent is valid

  // http://msdn.microsoft.com/en-us/library/windows/desktop/bb761822(v=vs.85).aspx
  //
  // +---------------------------+---------------------+----------------------+
  // | BS_ICON or BS_BITMAP Set? | BM_SETIMAGE Called? | Result               |
  // +---------------------------+---------------------+----------------------+
  // | Yes                       | Yes                 | Show icon only       |
  // +---------------------------+---------------------+----------------------+
  // | No                        | Yes                 | Show icon and text   |
  // +---------------------------+---------------------+----------------------+
  // | Yes                       | No                  | Show text only       |
  // +---------------------------+---------------------+----------------------+
  // | No                        | No                  | Show text only       |
  // +---------------------------+---------------------+----------------------+

  HWND hwnd = ::CreateWindowEx(0,
                               L"BUTTON",
                               CharacterEncoder::utf8ToUtf16(getText()).c_str(),
                               d->style,
                               getX(),
                               getY(),
                               getWidth(),
                               getHeight(),
                               getParent()->getUiComponentContext()->hwnd,
                               reinterpret_cast<HMENU>(getId()),
                               reinterpret_cast<HINSTANCE>(getParent()->getUiComponentContext()->hinstance),
                               reinterpret_cast<LPVOID>(0));

  if(hwnd == nullptr)
  {
    DWORD lastError = ::GetLastError();

    // TODO: Throw exception?
  }

  setInitialized(true);

  d->uiComponentContext = std::auto_ptr<UiComponentContext>(new UiComponentContext());
  d->uiComponentContext->hwnd = hwnd;

  // Initialize the internal preferred size.
  calculateInternalPreferredSize();
}

void Button::calculateInternalPreferredSize()
{
  ButtonPrivate * d = static_cast<ButtonPrivate *>(dRoot.get());

  // Get the platform preferred size for buttons.

  // If the platform preferred size for buttons is greater than the calculated
  // size of this button, then use the platform size otherwise use the
  // calculated size.

  std::auto_ptr<Size2D> calculatedSize(TextDimension::getTextSize(getFont(),
                                                                  d->buttonText));

  // Ensure you get the platform internal margins too since they are required
  // for a correct calculation.
  RECT rect;
  std::memset(&rect, 0, sizeof(RECT));
  ::SendMessageW(getUiComponentContext()->hwnd,
                 BCM_GETTEXTMARGIN,
                 0,                                // not used must be 0.
                 reinterpret_cast<LPARAM>(&rect));

  if(calculatedSize.get())
  {
    int calculatedWidth = calculatedSize->getWidth();

    int calculatedHeight = calculatedSize->getHeight();

    // Apply the platform internal margins if any. Remember the first
    // calculation (TextDimension::getTextSize) only calculates the size of the
    // text.

    int tempTextWidthMargin = static_cast<int>(static_cast<double>(calculatedWidth) * 0.30);
    calculatedWidth += tempTextWidthMargin;

    calculatedWidth += (rect.left + rect.right);

    calculatedHeight += (rect.top + rect.bottom);

    // Add the border too.
    int xBorder = ::GetSystemMetrics(SM_CXBORDER);
    int yBorder = ::GetSystemMetrics(SM_CYBORDER);

    calculatedWidth += (xBorder * 2);
    calculatedHeight += (yBorder * 2);

    calculatedWidth = std::max(UiComponentSize::getButtonWidth(),
                               calculatedWidth);

    calculatedHeight = std::max(UiComponentSize::getButtonHeight(),
                                calculatedHeight);

    setInternalPreferredSize(calculatedWidth,
                             calculatedHeight);
  }
  else
  {
    // Could not get the text size just use the platform button size.
    setInternalPreferredSize(UiComponentSize::getButtonWidth(),
                             UiComponentSize::getButtonHeight());
  }
}
