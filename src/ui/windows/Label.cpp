////////////////////////////////////////////////////////////////////////////////
//
// File: Label.cpp
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <utility>

#include "string/extras/CharacterEncoder.h"

#include "graphics/Color.h"
#include "graphics/Graphics.h"
#include "graphics/Size2D.h"
#include "graphics/TextDimension.h"

#include "ui/TopLevelWindow.h"

#include "ui/event/ColorChangeObserver.h"
#include "ui/event/AbstractUiEventObserver.h"

#include "ui/layout/UiComponentSize.h"

#include "ui/private/windows/UiComponentContext.h"
#include "ui/private/windows/TopLevelWindowContext.h"

#include "ui/private/windows/LabelPrivate.h"

#include "ui/private/windows/IMessageHandler.h"
#include "ui/private/windows/WM_COMMAND_MessageHandler.h"
#include "ui/private/windows/WM_CTLCOLORSTATIC_MessageHandler.h"

#include "ui/Label.h"

LabelPrivate::LabelPrivate(const std::string& text,
                           Label::TextAlignment alignment,
                           Label::AcceleratorInterpretation acceleratorInterpretation)
:UiComponentPrivate(),
 text(text),
 styles(WS_CHILD | WS_VISIBLE | SS_NOTIFY),
 thisLabel(NULL),
 colorChangeObserver(nullptr),
 internalColorChangeObserver(nullptr),
 labelClickObserver(nullptr)
{
  if(acceleratorInterpretation == Label::DisableAcceleratorInterpretation)
  {
    styles |= SS_NOPREFIX;
  }

  switch(alignment)
  {
    case Label::RightAlignment:
    {
      styles |= SS_RIGHT;
      break;
    }

    case Label::CenterAlignment:
    {
      styles |= SS_CENTER;
      break;
    }

    case Label::LeftAlignment:
    {
      styles |= SS_LEFT;
      break;
    }
  }
}

LabelPrivate::~LabelPrivate()
{

}

void LabelPrivate::onInternalColorChange(UiComponent * uiComponent,
                                         boost::shared_ptr<Graphics> graphics)
{
  Color * textColor = uiComponent->getForegroundColor();
  Color * backgroundColor = uiComponent->getBackgroundColor();

  if(textColor)
  {
    graphics->setTextColor(textColor);
  }

  if(backgroundColor)
  {
    graphics->setBackgroundColor(backgroundColor);
  }
}

WM_COMMAND_MessageHandler * LabelPrivate::getWM_COMMAND_MessageHandler(Label * thisLabel)
{
  TopLevelWindow * topLevelWindow = thisLabel->getTopLevelWindow();

  std::auto_ptr<IMessageHandler> messageHandler(new WM_COMMAND_MessageHandler());

  IMessageHandler * registeredMessageHandler = topLevelWindow->getTopLevelWindowContext()->initWin32MessageHandler(messageHandler);

  // we know that the type of IMessageHandler is a WM_COMMAND_MessageHandler
  WM_COMMAND_MessageHandler * wm_command_messageHandler = static_cast<WM_COMMAND_MessageHandler *>(registeredMessageHandler);

  return wm_command_messageHandler;
}

WM_CTLCOLORSTATIC_MessageHandler * LabelPrivate::getWM_CTLCOLORSTATIC_MessageHandler(Label * thisLabel)
{
  TopLevelWindow * topLevelWindow = thisLabel->getTopLevelWindow();

  std::auto_ptr<IMessageHandler> messageHandler(new WM_CTLCOLORSTATIC_MessageHandler());

  IMessageHandler * registeredMessageHandler = topLevelWindow->getTopLevelWindowContext()->initWin32MessageHandler(messageHandler);

  // we know that the type of IMessageHandler is a WM_CTLCOLORSTATIC_MessageHandler
  WM_CTLCOLORSTATIC_MessageHandler * wm_ctlcolorstatic_messageHandler = static_cast<WM_CTLCOLORSTATIC_MessageHandler *>(registeredMessageHandler);

  return wm_ctlcolorstatic_messageHandler;
}

void LabelPrivate::setClickObserver(AbstractUiEventObserver * uiEventObserver)
{
  WM_COMMAND_MessageHandler * wm_command_messageHandler = getWM_COMMAND_MessageHandler(thisLabel);

  // look up the notification code to see if there is already a map registered, if a map is registered,
  // use it, if not create a new map for the notification code (STN_CLICKED)

  boost::unordered_map<int, boost::unordered_map<int, std::pair<AbstractUiEventObserver *, UiComponent *> > >::iterator it;

  const int Win32NotificationCode = STN_CLICKED;

  it = wm_command_messageHandler->win32CommandCallbacks.find(Win32NotificationCode);

  // check to see if a  map already exists and if not add it one
  if(it == wm_command_messageHandler->win32CommandCallbacks.end())
  {
    wm_command_messageHandler->win32CommandCallbacks[Win32NotificationCode][thisLabel->getId()] = std::pair<AbstractUiEventObserver *, UiComponent *>(uiEventObserver, thisLabel);
  }
  else
  {
    it->second[thisLabel->getId()] = std::pair<AbstractUiEventObserver *, UiComponent *>(uiEventObserver, thisLabel);
  }
}

Label::Label(const std::string& text,
             TextAlignment alignment,
             Label::AcceleratorInterpretation acceleratorInterpretation)
:UiComponent(*new LabelPrivate(text, alignment, acceleratorInterpretation))
{
  LabelPrivate * d = static_cast<LabelPrivate *>(dRoot.get());

  d->thisLabel = this;
}

Label::Label(LabelPrivate& d)
:UiComponent(d)
{

}

Label::~Label()
{
}

void Label::internalCreate()
{
  LabelPrivate * d = static_cast<LabelPrivate *>(dRoot.get());

  assert(isParentValid());

  HWND hwnd = ::CreateWindowEx(0,
                               L"STATIC" ,
                               nullptr,
                               d->styles,
                               this->getX(),
                               this->getY(),
                               this->getWidth(),
                               this->getHeight(),
                               this->getParent()->getUiComponentContext()->hwnd,
                               reinterpret_cast<HMENU>(getId()),
                               reinterpret_cast<HINSTANCE>(0),
                               NULL);

  if(hwnd == nullptr)
  {
    // TODO: Handle error
    DWORD lastError = ::GetLastError();
  }

  d->uiComponentContext = std::auto_ptr<UiComponentContext>(new UiComponentContext());
  d->uiComponentContext->hwnd = hwnd;

  setInitialized(true);

  ::SetWindowText(getUiComponentContext()->hwnd,
                  CharacterEncoder::utf8ToUtf16(d->text).c_str());

  // Initialize the internal preferred size.
  calculateInternalPreferredSize();
}

std::string Label::getText() const
{
  LabelPrivate * d = static_cast<LabelPrivate *>(dRoot.get());

  return d->text;
}

void Label::setText(const std::string& text)
{
  LabelPrivate * d = static_cast<LabelPrivate *>(dRoot.get());

  d->text = text;

  if(isInitialized())
  {
    ::SetWindowText(getUiComponentContext()->hwnd,
                    CharacterEncoder::utf8ToUtf16(d->text).c_str());
  }
}

void Label::setColorChangeObserver(AbstractColorChangeObserver * colorChangeObserver)
{
  LabelPrivate * d = static_cast<LabelPrivate *>(dRoot.get());

  delete d->colorChangeObserver;

  d->colorChangeObserver = colorChangeObserver;

  if(isInitialized())
  {
    WM_CTLCOLORSTATIC_MessageHandler * wm_ctlcolorstatic_messageHandler = d->getWM_CTLCOLORSTATIC_MessageHandler(this);

    wm_ctlcolorstatic_messageHandler->win32MessageCallbacks[getId()] = std::pair<AbstractColorChangeObserver *, UiComponent *>(d->colorChangeObserver, this);
  }

  if(d->internalColorChangeObserver)
  {
    delete d->internalColorChangeObserver;

    d->internalColorChangeObserver = nullptr;
  }
}

void Label::setClickObserver(AbstractUiEventObserver * uiEventObserver)
{
  LabelPrivate * d = static_cast<LabelPrivate *>(dRoot.get());

  delete d->labelClickObserver;

  d->labelClickObserver = uiEventObserver;

  if(isInitialized())
  {
    d->setClickObserver(uiEventObserver);
  }
}

void Label::initializeEventHandlers()
{
  LabelPrivate * d = static_cast<LabelPrivate *>(dRoot.get());

  WM_CTLCOLORSTATIC_MessageHandler * wm_ctlcolorstatic_messageHandler = d->getWM_CTLCOLORSTATIC_MessageHandler(this);

  if(!d->colorChangeObserver &&
      (d->backgroundColor.get() || d->foregroundColor.get()))
  {
    // register the internal call back
    d->internalColorChangeObserver = new ColorChangeObserver<LabelPrivate>(d, &LabelPrivate::onInternalColorChange);

    wm_ctlcolorstatic_messageHandler->win32MessageCallbacks[getId()] = std::pair<AbstractColorChangeObserver *, UiComponent *>(d->internalColorChangeObserver, this);
  }
  else if(d->colorChangeObserver)
  {
    wm_ctlcolorstatic_messageHandler->win32MessageCallbacks[getId()] = std::pair<AbstractColorChangeObserver *, UiComponent *>(d->colorChangeObserver, this);
  }

  if(d->labelClickObserver)
  {
    d->setClickObserver(d->labelClickObserver);
  }
}

void Label::calculateInternalPreferredSize()
{
  LabelPrivate * d = static_cast<LabelPrivate *>(dRoot.get());

  std::auto_ptr<Size2D> calculatedSize(TextDimension::getTextSize(getFont(), d->text));

  if(calculatedSize.get())
  {
    int calculatedWidth = calculatedSize->getWidth();

    int calculatedHeight = calculatedSize->getHeight();

    // Add the border too.
    int xBorder = ::GetSystemMetrics(SM_CXBORDER);
    int yBorder = ::GetSystemMetrics(SM_CYBORDER);

    calculatedWidth += (xBorder * 2);
    calculatedHeight += (yBorder * 2);

    calculatedHeight = std::max(UiComponentSize::getLabelHeight(),
                                calculatedHeight);

    setInternalPreferredSize(calculatedWidth,
                             calculatedHeight);
  }
  else
  {
    // Could not get the text size just use the platform button width instead.
    setInternalPreferredSize(UiComponentSize::getButtonWidth(),
                             UiComponentSize::getLabelHeight());
  }
}
