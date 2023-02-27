cmake_minimum_required(VERSION 3.5)

project(omega7_ctrl LANGUAGES CXX)

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

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES omega7_ctrl_zh_CN.ts)


set(eigen3_dir "E:/Softwares/Force Dimension/sdk-3.15.0/externals/Eigen")


include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/form
    ${eigen3_dir}
    )

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src)


#if(ANDROID)
#  add_library(omega7_ctrl SHARED
#    main.cpp
#    mainwindow.cpp
#    mainwindow.h
#    mainwindow.ui
#    ${TS_FILES}
#  )
#else()
#  add_executable(omega7_ctrl
#    main.cpp
#    mainwindow.cpp
#    mainwindow.h
#    mainwindow.ui
#    ${TS_FILES}
#  )
#endif()

target_link_libraries(omega7_ctrl PRIVATE Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
