#-------------------------------------------------
#
# Project created by QtCreator 2019-03-25T08:54:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SZAKDOGA
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++1z
LIBS += -lfreeimage -lphysfs

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    Io/StdStream.cpp \
    Wrapper/BlurImage.cpp \
    Wrapper/MhImageWrapper.cpp \
    ImgClassifier/ProfileImage.cpp \
    ImgClassifier/ImageMetadataContainer.cpp \
    Io/PhysFsFileHandle.cpp \
    ImgClassifier/ImageCollection.cpp \
    Window/SharpenDialog.cpp \
    Window/ImageAdjuster.cpp
#    ImgClassifier/ImageClaster.cpp \
#    ImgClassifier/ClasterCollection.cpp

HEADERS += \
        MainWindow.hpp \
    Io/FIO.hpp \
    Io/FIOSys.hpp \
    Io/Global.hpp \
    Io/span.hpp \
    Io/StdStream.hpp \
    Wrapper/BlurImage.hpp \
    Wrapper/Clamp.hpp \
    Wrapper/MhImageWrapper.hpp \
    Wrapper/MhVector.hpp \
    Wrapper/Normalize.hpp \
    Wrapper/PixelWrapper.hpp \
    Wrapper/Matrix.hpp \
    ImgClassifier/ProfileImage.hpp \
    Wrapper/RgbType.hpp \
    ImgClassifier/ImageMetadataContainer.hpp \
    Io/PhysFsFileHandle.hpp \
    ImgClassifier/ImageCollection.hpp \
    Window/SharpenDialog.hpp \
    Window/ImageAdjuster.hpp
#    ImgClassifier/ImageClaster.hpp \
#    ImgClassifier/ClasterCollection.hpp \

FORMS += \
        MainWindow.ui \
    Window/SharpenDialog.ui \
    Window/ImageAdjuster.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    LICENSE
