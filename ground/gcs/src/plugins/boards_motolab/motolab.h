/**
 ******************************************************************************
 * @file       motolab.h
 * @author     AJ Christensen, <aj@junglistheavy.industries>, Copyright (C) 2015
 *
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup Boards_MotolabPlugin Motolab boards support Plugin
 * @{
 * @brief Plugin to support Motolab boards
 *****************************************************************************/
#ifndef MOTOLAB_H
#define MOTOLAB_H

#include <coreplugin/iboardtype.h>

class IBoardType;

class Motolab : public Core::IBoardType
{
public:
    Motolab();
    virtual ~Motolab();

    virtual QString shortName();
    virtual QString boardDescription();
    virtual bool queryCapabilities(BoardCapabilities capability);
    virtual QStringList getSupportedProtocols();
    virtual QPixmap getBoardPicture();
    virtual QString getHwUAVO();

    //! Determine if this board supports configuring the receiver
    virtual bool isInputConfigurationSupported();

    /**
     * Configure the board to use an receiver input type on a port number
     * @param type the type of receiver to use
     * @param port_num which input port to configure (board specific numbering)
     */
    virtual bool setInputOnPort(enum InputType type, int port_num = 0);

    /**
     * @brief getInputOnPort get the current input type
     * @param port_num which input port to query (board specific numbering)
     * @return the currently selected input type
     */
    virtual enum InputType getInputOnPort(int port_num = 0);

    /**
     * @brief getConnectionDiagram get the connection diagram for this board
     * @return a string with the name of the resource for this board diagram
     */
    virtual QString getConnectionDiagram() { return ":/motolab/images/motolab-connection-diagram.svg"; }

    virtual int queryMaxGyroRate();

};

#endif // MOTOLAB_H
