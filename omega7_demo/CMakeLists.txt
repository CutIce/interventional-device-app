cmake_minimum_required(VERSION 3.24)
project(omega7_demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "E:/Softwares/qt/qt_5_14/5.14.2/mingw73_64")

find_package(Qt5 COMPONENTS
        Core
        Widgets
        Gui
        REQUIRED)

set(Eigen3_dir "E:/Softwares/Force Dimension/sdk-3.15.0/externals/Eigen")
#set(GLFW_dir "E:/Softwares/Force Dimension/sdk-3.15.0/externals/GLFW")

# 添加头文件目录
include_directories( ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/form
        ${Eigen3_dir}
        ${GLFW_dir}
        )

# 添加源文件目录
aux_source_directory(./src proj_src)
#aux_source_directory(./src/SDK_examples sdk_examples_src)


# 添加库文件
link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)

#
find_library(dhdlib dhdms64.lib ${CMAKE_CURRENT_LIST_DIR}/lib)
find_library(drdlib drdms64.lib ${CMAKE_CURRENT_LIST_DIR}/lib)

# 设置构建目标
add_executable(omega7_demo main.cpp ${proj_src})


target_link_libraries(omega7_demo
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        ${dhdlib}
        ${drdlib}
        )

if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
