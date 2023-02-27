QT += core gui opengl
QT += serialport

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = omega7_commu
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


DESTDIR += ./bin


SOURCES += \
    main.cpp \
    catheter_kinemetic/kinemetic_widget.cpp \
    qplot3d/QPlot3D.cpp \
    src/mainwindow.cpp

HEADERS += \
    catheter_kinemetic/catheter_kinemetic.h \
    catheter_kinemetic/kinemetic_widget.h \
    header/mainwindow.h \
    header/sdk_utility.h \
    include/dhdc.h \
    include/drdc.h \
    qplot3d/QPlot3D.h \





FORMS += \
    form/mainwindow.ui

UI_DIR = ./form

TRANSLATIONS += \
    omega7_qcom_zh_CN.ts



#Eigen
INCLUDEPATH +=  E:/Softwares/Eigen


## GLFW
INCLUDEPATH += $$PWD/../../../../../Softwares/opengl/glfwx64/include
DEPENDPATH += $$PWD/../../../../../Softwares/opengl/glfwx64/include


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
#    lib/forceDimensionSDK/dhdms.lib \
    lib/forceDimensionSDK/dhdms64.lib \
#    lib/forceDimensionSDK/drdms.lib \
    lib/forceDimensionSDK/drdms64.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../Softwares/opengl/glfwx64/lib-mingw-w64/ -lglfw3dll -lOpengl32 -lglu32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../Softwares/opengl/glfwx64/lib-mingw-w64/ -lglfw3dll -lOpengl32 -lglu32


