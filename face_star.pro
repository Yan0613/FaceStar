QT       += core gui
QT       += multimedia
QT       += multimediawidgets
QT       +=core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui
SOURCES += \
    detailed.cpp \
    info_entry.cpp \
    insert_message.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    detailed.h \
    info_entry.h \
    insert_message.h \
    login.h \
    mainwindow.h \
    libncnn/include/arm/layer_declaration.h \
    libncnn/include/arm/layer_registry.h \
    libncnn/include/arm/layer_shader_registry.h \
    libncnn/include/arm/layer_shader_spv_data.h \
    libncnn/include/arm/layer_type_enum.h \
    libncnn/include/mips/layer_declaration.h \
    libncnn/include/mips/layer_registry.h \
    libncnn/include/mips/layer_shader_registry.h \
    libncnn/include/mips/layer_shader_spv_data.h \
    libncnn/include/mips/layer_type_enum.h \
    libncnn/include/x86/layer_declaration.h \
    libncnn/include/x86/layer_registry.h \
    libncnn/include/x86/layer_shader_registry.h \
    libncnn/include/x86/layer_shader_spv_data.h \
    libncnn/include/x86/layer_type_enum.h \
    libncnn/include/allocator.h \
    libncnn/include/benchmark.h \
    libncnn/include/blob.h \
    libncnn/include/command.h \
    libncnn/include/cpu.h \
    libncnn/include/datareader.h \
    libncnn/include/gpu.h \
    libncnn/include/layer.h \
    libncnn/include/layer_type.h \
    libncnn/include/mat.h \
    libncnn/include/modelbin.h \
    libncnn/include/net.h \
    libncnn/include/opencv.h \
    libncnn/include/option.h \
    libncnn/include/paramdict.h \
    libncnn/include/pipeline.h \
    libncnn/include/platform.h


FORMS += \
    detailed.ui \
    info_entry.ui \
    insert_message.ui \
    login.ui \
    mainwindow.ui
RESOURCES += \
    image.qrc

#opencv
INCLUDEPATH += $$PWD/opencv86/include
LIBS += -L$$PWD/opencv86/lib -lopencv_videoio -latomic -lopencv_objdetect
DEPENDPATH += $$PWD/opencv86/lib


#ncnn

INCLUDEPATH += $$PWD/libncnn/include
LIBS += -L$$PWD/libncnn -lncnn



