////////////////////////////////////////////////////////////////////////////////
//
// File: LabelPrivate.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_WINDOWS_LABELPRIVATE_H_
#define UI_PRIVATE_WINDOWS_LABELPRIVATE_H_

#include <windows.h>

#include <boost/shared_ptr.hpp>

#include "ui/Label.h"

#include "ui/private/UiComponentPrivate.h"

class Graphics;

class UiComponent;

class AbstractColorChangeObserver;
class AbstractUiEventObserver;

class WM_COMMAND_MessageHandler;
class WM_CTLCOLORSTATIC_MessageHandler;

class LabelPrivate : public UiComponentPrivate
{
  public:

    LabelPrivate(const std::string& text,
                 Label::TextAlignment alignment,
                 Label::AcceleratorInterpretation acceleratorInterpretation);

    virtual ~LabelPrivate();

    void onInternalColorChange(UiComponent * uiComponent,
                               boost::shared_ptr<Graphics> graphics);

    WM_COMMAND_MessageHandler * getWM_COMMAND_MessageHandler(Label * thisLabel);
    WM_CTLCOLORSTATIC_MessageHandler * getWM_CTLCOLORSTATIC_MessageHandler(Label * thisLabel);

    void setClickObserver(AbstractUiEventObserver * uiEventObserver);

    std::string text;
    DWORD styles;
    Label * thisLabel;

    AbstractColorChangeObserver * colorChangeObserver;
    AbstractColorChangeObserver * internalColorChangeObserver;
    AbstractUiEventObserver * labelClickObserver;
};
#endif /* UI_PRIVATE_WINDOWS_LABELPRIVATE_H_ */
