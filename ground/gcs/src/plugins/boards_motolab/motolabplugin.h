/**
 ******************************************************************************
 *
 * @file       motolabplugin.h
 * @author     AJ Christensen, <aj@junglistheavy.industries>, Copyright (C) 2015
 *
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup Boards_MotolabPlugin Motolab boards support Plugin
 * @{
 * @brief Plugin to support Motolab boards
 *****************************************************************************/

#ifndef MOTOLABPLUGIN_H
#define MOTOLABPLUGIN_H

#include <extensionsystem/iplugin.h>

class MotolabPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TauLabs.plugins.Motolab" FILE "Motolab.json")

public:
   MotolabPlugin();
   ~MotolabPlugin();

   void extensionsInitialized();
   bool initialize(const QStringList & arguments, QString * errorString);
   void shutdown();
};

#endif // MOTOLABPLUGIN_H
