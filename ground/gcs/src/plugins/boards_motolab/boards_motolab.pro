TEMPLATE = lib
TARGET = Motolab
include(../../taulabsgcsplugin.pri)
include(../../plugins/uavobjects/uavobjects.pri)
include(../../plugins/coreplugin/coreplugin.pri)

OTHER_FILES += Motolab.pluginspec

HEADERS += \
    motolabplugin.h \
    motolab.h

SOURCES += \
    motolabplugin.cpp \
    motolab.cpp

RESOURCES += \
    motolab.qrc
