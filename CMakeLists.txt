cmake_minimum_required(VERSION 3.5)

project(SimpleOCR LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets LinguistTools Network REQUIRED)

# set windows icon
set(app_WINRC app_win32.rc)
set_property(SOURCE app_win32.rc APPEND PROPERTY
    OBJECT_DEPENDS ${PROJECT_SOURCE_DIR}/assets/icon/simple_ocr.ico)

# set qrc files
set(QRC_FILE assets.qrc)
qt5_add_resources(QRC ${QRC})

#INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
#AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR} DIR_SRCS)

if(ANDROID)
  add_library(SimpleOCR SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    settingform.cpp
    settingform.h
    settingform.ui
    qswitchbutton.cpp
    qswitchbutton.h
    networkapi.cpp
    networkapi.h
    clipboardthread.cpp
    clipboardthread.h
    appsettings.cpp
    appsettings.h
    utils.cpp
    utils.h
    ${QRC_FILE}
  )
else()
  add_executable(SimpleOCR WIN32
      main.cpp
      mainwindow.cpp
      mainwindow.h
      mainwindow.ui
      settingform.cpp
      settingform.h
      settingform.ui
      qswitchbutton.cpp
      qswitchbutton.h
      networkapi.cpp
      networkapi.h
      clipboardthread.cpp
      clipboardthread.h
      appsettings.cpp
      appsettings.h
      utils.cpp
      utils.h
      ${QRC_FILE}
      ${app_WINRC}
  )
endif()

target_link_libraries(SimpleOCR PRIVATE Qt5::Widgets Qt5::Network)
