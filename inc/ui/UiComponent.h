////////////////////////////////////////////////////////////////////////////////
//
// File: UiComponent.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_UICOMPONENT_H_
#define UI_UICOMPONENT_H_

#include <memory>

#include <boost/shared_ptr.hpp>

#include "graphics/IDrawable.h"

class UiComponentPrivate;
class UiComponentContext;
class TopLevelWindow;
class ILayout;
class MenuBar;
class Size2D;
class Point2D;
class Rectangle2D;
struct Margin;
struct Padding;
class Font;
class Color;

class UiComponent : public IDrawable
{
  protected:

    UiComponent();

  public:

    virtual ~UiComponent();

    int getWidth() const;

    int getClientWidth() const;

    int getHeight() const;

    int getClientHeight() const;

    const Size2D * getSize() const;

    const Size2D * getClientSize() const;

    void setSize(int width, int height);

    void setClientSize(int width, int height);

    void setSize(const Size2D * size2D);

    void setClientSize(const Size2D * size2D);

    int getX() const;

    int getY() const;

    const Point2D * getLocation() const;

    void setLocation(int x, int y);
    void setLocation(const Point2D * location);

    const Rectangle2D * getBounds() const;

    const Rectangle2D * getClientBounds() const;

    void setBounds(int x, int y, int width, int height);

    void setBounds(const Rectangle2D * rec);

    int getPreferredWidth() const;
    int getPreferredHeight() const;
    const Size2D * getPreferredSize() const;

    void setPreferredSize(int preferredWidth, int preferredHeight);
    void setPreferredSize(const Size2D * preferredSize);

    const Margin * getMargin() const;
    int getLeftMargin() const;
    int getRightMargin() const;
    int getTopMargin() const;
    int getBottomMargin() const;

    const Padding * getPadding() const;
    int getLeftPadding() const;
    int getRightPadding() const;
    int getTopPadding() const;
    int getBottomPadding() const;

    void setMargin(const Margin * margin);
    void setMargin(int margin);
    void setLeftMargin(int leftMargin);
    void setRightMargin(int rightMargin);
    void setTopMargin(int topMargin);
    void setBottomMargin(int bottomMargin);

    void setPadding(const Padding * padding);
    void setPadding(int padding);
    void setLeftPadding(int leftPadding);
    void setRightPadding(int rightPadding);
    void setTopPadding(int topPadding);
    void setBottomPadding(int bottomPadding);

    Color * getBackgroundColor() const;

    void setBackgroundColor(Color * color);

    Color * getForegroundColor() const;

    void setForegroundColor(Color * color);

    void setEnabled(bool enabled);

    bool isEnabled() const;

    bool isVisible() const;

    void setVisible(bool visible);

    /**
     * Tell this UiComponent to grab the input focus.
     */
    void setFocus();

    virtual UiComponent * getParent() const;

    void setParent(UiComponent * parent);

    /**
     * Checks whether this UiComponent is initialized. A UiComponent is
     * initialized when it has a valid parent and a call to initialize() is made.
     *
     * return true if this UiComponent is initialized.
     */
    bool isInitialized() const;


    // -1 if the UiComponent has not yet been initialized
    int getId() const;

    UiComponentContext * getUiComponentContext() const;

    /**
     * Adds the specified UiComponent to this UiComponent. The specified
     * UiComponent becomes a child of this UiComponent and resides within the
     * client area of this UiComponent.
     *
     * @param[in] uiComponent the UiComponent that shall become a child of this
     * UiComponent.
     */
    void addUiComponent(UiComponent * uiComponent);

    /**
     * Removes the specified UiComponent from this UiComponent.
     *
     * @param[in] uiComponent the UiComponent that will be removed from this
     * UiComponent.
     */
    void removeUiComponent(UiComponent * uiComponent);

    /**
     * Returns the UiComponent at the specified index in this UiComponent.
     *
     * @param[in] index the index of the UiComponent to return.
     *
     * @return the UiComponent at the index specified.
     */
    UiComponent * getUiComponentAt(std::size_t index) const;

    /**
     * Removes the UiComponent from this UiComponent at the specified index.
     *
     * @param[in] index the index of the UiComponent to remove.
     */
    void removeUiComponentAt(std::size_t index);

    /**
     * Returns the number of UiComponents in this UiComponent.
     *
     * @return the current number of UiComponents.
     */
    std::size_t getUiComponentCount() const;

    virtual void enableDrawing();

    virtual void disableDrawing();

    virtual bool equals(UiComponent * UiComponent) const;

    ILayout * getLayout() const;

    void setLayout(ILayout * layout);

    void invalidateLayout();

    void doLayout();

    virtual IDrawableSurface * getDrawableSurface() const;

    /**
     * Check whether this UiComponent has a menu attached.
     *
     * @return true if this UiComponent has a menu attached.
     */
    virtual bool hasMenu() const;

    virtual MenuBar * getMenuBar() const;

    /**
     * Returns the font associated with this UiComponent.
     *
     * The client does not own the font returned by this function and must not
     * free the font.
     *
     * @return the font associated with this UiComponent.
     */
    Font * getFont() const;

    void setFont(boost::shared_ptr<Font> font);

    /**
     * Return the TopLevelWindow that owns this UiComponent or itself if this
     * UiComponent is in fact a TopLevelWindow.
     *
     * @return the TopLevelWindow that owns this UiComponent or this UiComponent
     * if this UiComponent is a TopLevelWindow.
     */
    TopLevelWindow * getTopLevelWindow() const;

  protected:

    UiComponent(UiComponentPrivate &d);

    void initialize();

    void setInitialized(bool initialized);

    virtual void internalCreate();

    virtual void create();

    virtual void initializeMenu();

    virtual void internalPostCreate();

    virtual void postCreate();

    virtual bool isParentValid() const;

    void initializeChildren();
    void initializeChild(UiComponent * uiComponentChild);

    void updateChildren();
    void updateChild(UiComponent * uiComponentChild);

    /**
     * Callback that is invoked when this UiComponent should recalculate its
     * preferred dimensions.
     */
    virtual void calculateInternalPreferredSize() = 0;

    int getInternalPreferredWidth() const;
    int getInternalPreferredHeight() const;
    const Size2D * getInternalPreferredSize() const;
    void setInternalPreferredSize(int preferredWidth, int preferredHeight);
    void setInternalPreferredSize(const Size2D * preferredSize);

    std::auto_ptr<UiComponentPrivate> dRoot;
};
#endif /* UI_UICOMPONENT_H_ */
