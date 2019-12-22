FORMS += maindialog.ui \
    logindialog.ui \
    display.ui
RESOURCES += image.qrc
SOURCES += main.cpp \
    login.cpp \
    maindialog.cpp \
    display.cpp \
    src/http.cpp \
    src/led_ctl.cpp
HEADERS += login.h \
    maindialog.h \
    display.h \
    include/http.h \
    include/led_ctl.h
