#cmake_minimum_required(VERSION 3.24)
cmake_minimum_required(VERSION 3.16)

project(omega7_com)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "E:/Softwares/qt/qt_5_14/5.14.2/mingw73_64")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        OpenGL
        REQUIRED)
find_package(OpenGL REQUIRED)

set(eigen3_dir "E:/Softwares/Force Dimension/sdk-3.15.0/externals/Eigen")
set(freeglut_dir "E:/Softwares/opengl/freeglut-MinGW-3.0.0-1.mp/freeglut")
set(glfw_dir "E:/Softwares/opengl/glfwx64")
set(glad_dir "E:/Softwares/opengl/glad/glad")
set(glew_dir "E:/Softwares/opengl/glew-2.1.0-win32/glew-2.1.0")

add_definitions(-DGLEW_STATIC)

# 添加头文件目录
include_directories( ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/header
        ${CMAKE_CURRENT_LIST_DIR}/form
        ${eigen3_dir}
        ${freeglut_dir}/include
        ${glfw_dir}/include
        ${glad_dir}/include
        ${glew_dir}/include
        ${OpenGL_INCLUDE_DIRS}
        )

# 添加源文件目录
aux_source_directory(./src proj_src)
#aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/forceDimension sdk_src)
aux_source_directory(${glad_dir}/src glad_src)

#aux_source_directory(./src/SDK_examples sdk_examples_src)


# 添加库文件
link_directories(
        ${CMAKE_CURRENT_LIST_DIR}/lib
        ${glfw_dir}/lib-mingw-w64
        ${freeglut_dir}/lib/x64
        ${glew_dir}/lib/Release/x64

)

#
#find_library(dhdlib dhdms64.lib ${CMAKE_CURRENT_LIST_DIR}/lib)
#find_library(drdlib drdms64.lib ${CMAKE_CURRENT_LIST_DIR}/lib)
#find_library(libfreeglut libfreeglut.a ${freeglut_dir}/lib)
#find_library(libfreeglut_static libfreeglut_static.a ${freeglut_dir}/lib)
#find_library(libglfw3 libglfw3.a ${glfw_dir}/lib-mingw)
#find_library(libglfw3dll libglfw3dll.a ${glfw_dir}/lib-mingw)


# 设置构建目标
add_executable(${PROJECT_NAME} main.cpp ${proj_src} ${glad_src})


target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        Qt5::OpenGL
        dhdms64.lib
        drdms64.lib
        libfreeglut.a
        libfreeglut_static.a
        libglfw3.a
        libglfw3dll.a
        libglfw3.dll
        glu32.dll
        libglew32.lib
        libglew32s.lib
        ${OpenGL_LIBRARIES}
        OpenGL::GL
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
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
