######################################################################
# Automatically generated by qmake (2.01a) ?? ??? 1 23:56:42 2019
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . include src
INCLUDEPATH += . include

# Input
HEADERS += login.h \
           maindialog.h \
           include/adc.h \
           include/dcm_motor.h \
           include/led_ctl.h \
           include/s3c2410-adc.h
FORMS += logindialog.ui maindialog.ui
SOURCES += login.cpp \
           main.cpp \
           maindialog.cpp
RESOURCES += image.qrc
LIBS += -Llib -lmyctl