////////////////////////////////////////////////////////////////////////////////
//
// File: Button.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_BUTTON_H_
#define UI_BUTTON_H_

#include <string>

#include "ui/UiComponent.h"

class ButtonPrivate;

class Button : public UiComponent
{
  public:

    Button();

    virtual ~Button();

    /**
     * Create a new Button with the specified text.
     *
     * @param[in] text the text that this Button will display.
     */
    Button(const std::string& text);

    /**
     * The text that is displayed on this button.
     *
     * @return the text that is displayed on this Button.
     */
    std::string getText() const;

    /**
     * Set the text that this Button will display.
     *
     * @param[in] text the text that this button will display.
     */
    void setText(const std::string& text);

  protected:

    virtual void internalCreate();

    Button(ButtonPrivate& d);

    virtual void calculateInternalPreferredSize();
};
#endif /* UI_BUTTON_H_ */
