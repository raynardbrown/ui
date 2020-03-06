////////////////////////////////////////////////////////////////////////////////
//
// File: UiComponentPrivate.h
//
// Author: Raynard Brown
//
// Copyright (c) 2019 Raynard Brown
//
// All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef UI_PRIVATE_UICOMPONENTPRIVATE_H_
#define UI_PRIVATE_UICOMPONENTPRIVATE_H_

#include <memory>
#include <vector>

#include <boost/shared_ptr.hpp>

class UiComponent;
class UiComponentContext;
class IdManager;
class IFocusImpl;
class TopLevelWindow;
struct Margin;
struct Padding;
class ILayout;
class Rectangle2D;
class Size2D;
class Font;
class Color;
class FontFactory;
class UiComponentDrawableSurface;

class UiComponentPrivate
{
  public:

    UiComponentPrivate();

    virtual ~UiComponentPrivate();

    std::auto_ptr<Rectangle2D> bounds;

    std::auto_ptr<Size2D> preferredSize;

    std::auto_ptr<Size2D> internalPreferredSize;

    std::auto_ptr<Rectangle2D> clientBounds;

    std::auto_ptr<Margin> margin;

    std::auto_ptr<Padding> padding;

    std::auto_ptr<Color> backgroundColor;

    std::auto_ptr<Color> systemBackgroundColor;

    std::auto_ptr<Color> foregroundColor;

    std::auto_ptr<Color> systemForegroundColor;

    // un-owned
    UiComponent * parent;

    UiComponentDrawableSurface * drawableSurface;

    // parent font factory

    // Create the factory when the parent is initialized or when a child is
    // added.
    //
    // Give all your children the same font if and only if the client has not
    // already registered a font for a child.
    std::auto_ptr<FontFactory> fontfactory;

    boost::shared_ptr<Font> sharedFont;

    std::auto_ptr<IFocusImpl> focusImpl;

    int id;

    bool initialized;
    bool enabled;
    bool visible;

    std::auto_ptr<UiComponentContext> uiComponentContext;

    // un-owned
    TopLevelWindow * topLevelWindow;

    std::auto_ptr<IdManager> idManager;

    std::vector<UiComponent *> uiComponentChildren;

    std::auto_ptr<ILayout> layout;

    // un-owned
    UiComponent * thisUiComponent;

    virtual void initChildFocusImpl(UiComponent * parentUiComponent,
                                    UiComponent * childUiComponent,
                                    UiComponentPrivate * childUiComponentImpl);

    void updateClientAreaDimensions(int width, int height);

    void updateWindowAreaDimensions(int width, int height);

    void initializeBackgroundColorHelper(const wchar_t * className,
                                         void * reservedData);
};
#endif /* UI_PRIVATE_UICOMPONENTPRIVATE_H_ */
