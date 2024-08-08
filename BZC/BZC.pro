QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(debug, debug|release){
    OBJECTS_DIR = ../../TmpD/$${TARGET}
    UI_DIR = ../../TmpD/$${TARGET}
    MOC_DIR = ../../TmpD/$${TARGET}
    RCC_DIR = ../../TmpD/$${TARGET}
    DESTDIR =../../BinD
}else{
    OBJECTS_DIR = ../../Tmp/$${TARGET}
    UI_DIR = ../../Tmp/$${TARGET}
    MOC_DIR = ../../Tmp/$${TARGET}
    RCC_DIR = ../../Tmp/$${TARGET}
    DESTDIR = ../../Bin
}

SOURCES += \
    CfgFile.cpp \
    Logger.cpp \
    NVRReplayWgt.cpp \
    WgtMain.cpp \
    WgtZhouShi.cpp \
    common/loadbmp.c \
    interfacechange.cpp \
    main.cpp \
    MainWindow.cpp \
    mousemoveoptimize.cpp \
    mousemovethread.cpp \
    player.cpp \
    qjzoomarea.cpp \
    sample_hifb.c \
    settimedialog.cpp \
    timersetter.cpp \
    tinyxml2.cpp \
    Comport.cpp \
    InfraredComport.cpp \
    JoyStickComport.cpp \
    Message.cpp \
    MyTcpSocket.cpp \
    MyUdpSocket.cpp \
    parse_json.cpp \
    SocketManage.cpp

HEADERS += \
    CfgFile.h \
    Logger.h \
    MainWindow.h \
    NVRReplayWgt.h \
    WgtMain.h \
    WgtZhouShi.h \
    common/loadbmp.h \
    common/sample_comm.h \
    interfacechange.h \
    mousemoveoptimize.h \
    mousemovethread.h \
    player.h \
    qjzoomarea.h \
    sample_hifb.h \
    settimedialog.h \
    timersetter.h \
    tinyxml2.h \
    Comport.h \
    InfraredComport.h \
    globalvar.h \
    JoyStickComport.h \
    Message.h \
    MyTcpSocket.h \
    MyUdpSocket.h \
    parse_json.h \
    SocketManage.h \
    cytglobaltype.h

FORMS += \
    MainWindow.ui \
    NVRReplayWgt.ui \
    WgtMain.ui \
    WgtZhouShi.ui \
    settimedialog.ui


contains(QMAKE_HOST.arch, x86_64){
    message("编译平台: x86")

}

contains(QMAKE_HOST.arch, aarch64){
    message("编译平台: arm64")
    INCLUDEPATH +=$$PWD/../../Inc/ffmpeg
    LIBS+=-L$$PWD/../../Lib3/FFmpeg/Linux/aarch64
}

#LIBS += -lavcodec \
#        -lavdevice \
#        -lavfilter \
#        -lavformat \
#        -lavutil \
#        -lpostproc \
#        -lswresample \
#        -lswscale

#INCLUDEPATH += $$PWD/../Player

CONFIG(debug, debug|release){
     LIBS += -L$$PWD/../../LibD
}else{
     LIBS += -L$$PWD/../../Lib
}

#LIBS += -lPlayer


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

INCLUDEPATH += $$PWD/common
INCLUDEPATH += $$PWD/include

LIBS += -L$$PWD/lib
LIBS += -Dhi3559av100 -DHICHIP=0x3559a100 -DHI_RELEASE -DHI_XXXX -DAI_DEV=2 -DAO_DEV=0 -D_GNU_SOURCE \
        -ldl -Wall -fpermissive -lstdc++ -ffunction-sections -fdata-sections  \
        -fstack-protector -fPIC -fno-aggressive-loop-optimizations
LIBS +=  $$PWD/lib/libmpi.a \
        $$PWD/lib/libVoiceEngine.a \
        $$PWD/lib/lib_hiawb.a \
        $$PWD/lib/lib_hiae.a \
        $$PWD/lib/libisp.a \
        $$PWD/lib/lib_hidrc.a \
        $$PWD/lib/lib_hidehaze.a \
        $$PWD/lib/libdnvqe.a \
        $$PWD/lib/libsns_sdi024.a \
        $$PWD/lib/libupvqe.a \
        $$PWD/lib/libhdmi.a \
        $$PWD/lib/libmd.a  \
        $$PWD/lib/libsecurec.a \
        $$PWD/lib/lib_hildci.a \
        $$PWD/lib/libive.a \
        $$PWD/lib/libnnie.a \

DISTFILES += \
    common/loadbmp.o \
    common/sample_comm_audio.o \
    common/sample_comm_isp.o \
    common/sample_comm_sys.o \
    common/sample_comm_vdec.o \
    common/sample_comm_venc.o \
    common/sample_comm_vi.o \
    common/sample_comm_vo.o \
    common/sample_comm_vpss.o
