TEMPLATE = app
TARGET = test

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    clickable_widget.cpp \
    custom_text_field.cpp \
    document.cpp \
    editor.cpp \
    editor_button.cpp \
    main.cpp \
    node.cpp

HEADERS += \
    clickable_widget.hpp \
    custom_text_field.hpp \
    document.hpp \
    editor.hpp \
    editor_button.hpp \
    node.hpp \
    settings.hpp \
    utils.hpp
