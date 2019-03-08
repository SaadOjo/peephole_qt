#-------------------------------------------------
#
# Project created by QtCreator 2019-02-05T17:27:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = video_stream
TEMPLATE = app

LIBS +=     \
      -lv4l2 \
#    -lavutil \
    -lavcodec \
    -lavformat \
    -lswscale   \
#    -lvideoforqtv4lcapture \
    -lm \
    -lasound



SOURCES += main.cpp\
        mainwindow.cpp \
    videopane.cpp \
    capturethread.cpp \
  #  mic.cpp
    microphone.cpp \
    speaker.cpp \
    player_dialog.cpp \
    videoplayer_pane.cpp \
    video_decoder_thread.cpp \
    menu_dialog.cpp \
    gallery_dialog.cpp \
    settings_dialog.cpp \
    vp_speaker.cpp \
    audio_playback_thread.cpp

HEADERS  += mainwindow.h \
    videopane.h \
    capturethread.h \
  #  mic.h
    microphone.h \
    speaker.h \
    player_dialog.h \
    videoplayer_pane.h \
    video_decoder_thread.h \
    menu_dialog.h \
    gallery_dialog.h \
    settings_dialog.h \
    structures.h \
    vp_speaker.h \
    audio_playback_thread.h

FORMS    += mainwindow.ui \
    player_dialog.ui \
    menu_dialog.ui \
    gallery_dialog.ui \
    settings_dialog.ui

OTHER_FILES += \
    notes.txt
