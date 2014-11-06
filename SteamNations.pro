######################################################################
# Automatically generated by qmake (3.0) ?r. lis 5 21:29:43 2014
######################################################################

QT += core gui widgets

TEMPLATE = app
TARGET = SteamNations
CONFIG += c++11

SOURCES += src/SNCore/Board.cpp \
           src/SNCore/GameManager.cpp \
           src/SNCore/Object.cpp \
           src/SNCore/Player.cpp \
           src/SNCore/Prototype.cpp \
           src/SNCore/Settler.cpp \
           src/SNCore/SettlerPrototype.cpp \
           src/SNCore/Tile.cpp \
           src/SNCore/Town.cpp \
           src/SNCore/Unit.cpp \
           src/SNGame/GameView.cpp \
           src/SNGame/GraphicInterface.cpp \
           src/SNGame/main.cpp \
           src/SNGame/MenuController.cpp \
           src/SNGame/Menus.cpp \
           src/SNGame/NextTurnButton.cpp \
           src/SNGame/SNScene.cpp \
           src/SNGame/SteamNations.cpp \
           src/SNGame/TileGraphics.cpp \
           src/SNGame/TownGraphics.cpp \
           src/SNGame/UnitGraphics.cpp

HEADERS += src/SNCore/Board.hpp \
           src/SNCore/GameManager.hpp \
           src/SNCore/Object.hpp \
           src/SNCore/Player.hpp \
           src/SNCore/Prototype.hpp \
           src/SNCore/Settler.hpp \
           src/SNCore/SettlerPrototype.hpp \
           src/SNCore/SNCommon.hpp \
           src/SNCore/Tile.hpp \
           src/SNCore/Town.hpp \
           src/SNCore/Unit.hpp \
           src/SNGame/GameView.hpp \
           src/SNGame/GraphicInterface.h \
           src/SNGame/MenuController.hpp \
           src/SNGame/Menus.hpp \
           src/SNGame/NextTurnButton.hpp \
           src/SNGame/SNHelpers.hpp \
           src/SNGame/SNScene.hpp \
           src/SNGame/SteamNations.hpp \
           src/SNGame/TileGraphics.hpp \
           src/SNGame/TownGraphics.hpp \
           src/SNGame/UnitGraphics.hpp


CONFIG += mobility           

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml