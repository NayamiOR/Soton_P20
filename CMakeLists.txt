cmake_minimum_required(VERSION 3.5)

project(P20_Code VERSION 0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#这个错误是因为你在使用Ninja生成器时，CMake试图修改一个从构建树中的RPATH，但是这在非ELF或XCOFF平台上是不支持的。你可以通过设置CMAKE_BUILD_WITH_INSTALL_RPATH变量来避免这个重新链接步骤。
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
#这将使得在构建时就设置好安装RPATH，从而避免在安装时进行重新链接。这样做的一个可能的副作用是，如果你的安装RPATH依赖于目标在构建树中的位置，那么这可能会导致问题，因为构建RPATH将不再包含这些位置。然而，对于许多项目来说，这可能并不是问题。
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        Canvas.cpp
        Canvas.h
        colors.cpp
        colors.h
        Canvas.cpp
        ReceiveCanvas.cpp
        ReceiveCanvas.h
        DrawingCommand.cpp
        DrawingCommand.h
        Receiver.cpp
        Receiver.h
        SafeQueue.cpp
        SafeQueue.h
        threads.cpp
        threads.h
        SendThread.cpp
        SendThread.h
        ReceivedThread.cpp
        ReceivedThread.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(P20_Code
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET P20_Code APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(P20_Code SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(P20_Code
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(P20_Code PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.P20_Code)
endif()
set_target_properties(P20_Code PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS P20_Code
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(P20_Code)
endif()
