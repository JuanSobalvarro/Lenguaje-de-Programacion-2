QT += widgets
requires(qtConfig(filedialog))

HEADERS       = \
    mainwindow.h \
    sudoku.h
SOURCES       = main.cpp \
    mainwindow.cpp \
    sudoku.cpp
RESOURCES     =

FORMS += \
    mainwindow.ui

