////////////////////////////////////////////////////////////////////////////////
//
// File: Label.h
//
// Author: Raynard Brown
//
// Copyright (c) 2020 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_LABEL_H_
#define UI_LABEL_H_

#include "ui/UiComponent.h"

class AbstractColorChangeObserver;

class LabelPrivate;

class Label : public UiComponent
{
  public:

    enum TextAlignment
    {
      RightAlignment,
      LeftAlignment,
      CenterAlignment
    };

    enum AcceleratorInterpretation
    {
      EnableAcceleratorInterpretation,
      DisableAcceleratorInterpretation,
    };

    Label(const std::string& text,
          TextAlignment alignment,
          AcceleratorInterpretation acceleratorInterpretation);

    virtual ~Label();

    std::string getText() const;

    void setText(const std::string& text);

    void setColorChangeObserver(AbstractColorChangeObserver * colorChangeObserver);

  protected:

    virtual void internalCreate();

    virtual void initializeEventHandlers();

    virtual void calculateInternalPreferredSize();

    Label(LabelPrivate& d);
};
#endif /* UI_LABEL_H_ */
