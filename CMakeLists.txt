cmake_minimum_required(VERSION 3.15.5)

# Set the name of the project and store it in a variable PROJECT_NAME
project(ui)

# Require at least this version of boost
find_package(Boost 1.71.0)
if(NOT Boost_FOUND)
  message(FATAL_ERROR "boost not found")
endif()

set(Headers "")
list(APPEND Headers ${CMAKE_CURRENT_SOURCE_DIR}/inc)
list(APPEND Headers ${CMAKE_CURRENT_SOURCE_DIR}/src)
list(APPEND Headers ${Boost_INCLUDE_DIRS})

set(Sources src/ui/Button.cpp 
            src/ui/IdManager.cpp
            src/ui/UiApplication.cpp
            src/ui/UiComponent.cpp)

if (MSVC)
    add_compile_options(-Zi
                        -W4
                        -EHsc
                        -D_CRT_SECURE_NO_WARNINGS
                        -DSTRICT
                        -DUNICODE
                        -D_UNICODE
                        -DNOMINMAX)

    set(Sources_Windows src/ui/windows/Button.cpp
                        src/ui/windows/DefaultFocusImpl.cpp
                        src/ui/windows/Menu.cpp
                        src/ui/windows/MenuBar.cpp
                        src/ui/windows/MenuItem.cpp
                        src/ui/windows/TopLevelWindow.cpp
                        src/ui/windows/UiApplication.cpp
                        src/ui/windows/UiComponent.cpp
                        src/ui/windows/UiComponentDrawableSurface.cpp)
    
    list(APPEND Sources ${Sources_Windows})
else()
    # fail until we target more platforms
    message(FATAL_ERROR "compiler not supported")
endif()

find_path(STRING_EXTRAS_INCLUDE NAMES string/extras/CharacterEncoder.h PATH_SUFFIXES string_extras/inc)

if(NOT STRING_EXTRAS_INCLUDE)
  message(FATAL_ERROR "string extras headers not found")
endif()

list(APPEND Headers ${STRING_EXTRAS_INCLUDE})

find_path(GRAPHICS_INCLUDE NAMES graphics/Font.h PATH_SUFFIXES graphics/inc)

if(NOT GRAPHICS_INCLUDE)
  message(FATAL_ERROR "graphics headers not found")
endif()

list(APPEND Headers ${GRAPHICS_INCLUDE})

find_path(GRAPHICS_PRIVATE_INCLUDE NAMES graphics/private/windows/FontContext.h PATH_SUFFIXES graphics/src)

if(NOT GRAPHICS_PRIVATE_INCLUDE)
  message(FATAL_ERROR "graphics private headers not found")
endif()

list(APPEND Headers ${GRAPHICS_PRIVATE_INCLUDE})

find_path(UI_LAYOUT_INCLUDE NAMES ui/Layout/ILayout.h PATH_SUFFIXES ui_layout/inc)

if(NOT UI_LAYOUT_INCLUDE)
  message(FATAL_ERROR "ui layout headers not found")
endif()

list(APPEND Headers ${UI_LAYOUT_INCLUDE})

add_library(${PROJECT_NAME} ${Sources})

target_include_directories(${PROJECT_NAME} PRIVATE ${Headers})