/**
 ******************************************************************************
 *
 * @file       motolabplugin.cpp
 * @author     AJ Christensen, <aj@junglistheavy.industries>, Copyright (C) 2015
 *
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup Boards_MotolabPlugin Motolab boards support Plugin
 * @{
 * @brief Plugin to support Motolab boards
 *****************************************************************************/

#include "motolabplugin.h"
#include "motolab.h"

#include <QtPlugin>

MotolabPlugin::MotolabPlugin() {}
MotolabPlugin::~MotolabPlugin() {}

bool MotolabPlugin::initialize(const QStringList& args, QString *errMsg)
{
   Q_UNUSED(args);
   Q_UNUSED(errMsg);
   return true;
}

void MotolabPlugin::extensionsInitialized()
{
    Motolab* motolab = new Motolab();
    addAutoReleasedObject(motolab);

}

void MotolabPlugin::shutdown()
{
}

