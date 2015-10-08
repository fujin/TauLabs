/**
 ******************************************************************************
 * @file       motolab.cpp
 * @author		 AJ Christensen, <aj@junglistheavy.industries>, Copyright (C) 2015
 *
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup Boards_MotolabPlugin Motolabs boards support Plugin
 * @{
 * @brief Plugin to support Motolab boards
 *****************************************************************************/

#include "motolab.h"

#include <uavobjectmanager.h>
#include "uavobjectutil/uavobjectutilmanager.h"
#include <extensionsystem/pluginmanager.h>

#include "hwmotolab.h"

/**
 * @brief Motolab::Motolab
 *  This is the Motolab board definition
 */
Motolab::Motolab(void)
{
    // Initialize our USB Structure definition here:
    USBInfo board;
    board.vendorID = 0x0fda;
    board.productID = 0x9999;

    setUSBInfo(board);

    boardType = 0xB0;

    // PWM1 - PA4 - TIM3_CH2
    // PWM2 - PA6 - TIM3_CH1, TIM8_BKIN, TIM1_BKIN, TIM16_CH1
    // PWM3 - PB0 - TIM3_CH3, TIM1_CH2N, TIM8_CH2N
    // PWM4 - PB1 - TIM3_CH4, TIM1_CH3N, TIM8_CH3N
    // PWM5 - PA1 - TIM2_CH2, TIM15_CH1N
    // PWM6 - PA2 - TIM2_CH3, !TIM15CH1N
    // PWM7 - PA3 - TIM15_CH2, TIM2_CH4
    // PWM8 - PA8 - TIM1_CH1, TIM4_ETR

    // PPM - PA7 - TIM17_CH1, TIM1_CH1N, TIM8_CH1

    // Define the bank of channels that are connected to a given timer
    channelBanks.resize(6);
    channelBanks[0] = QVector<int> () << 1 << 2;      // TIM15
    channelBanks[1] = QVector<int> () << 3;           // TIM1
    channelBanks[2] = QVector<int> () << 4 << 7 << 9; // TIM3
    channelBanks[3] = QVector<int> () << 5;           // TIM16
    channelBanks[4] = QVector<int> () << 6 << 10;     // TIM2
    channelBanks[5] = QVector<int> () << 8;           // TIM17
}

Motolab::~Motolab() {}

QString Motolab::shortName()
{
    return QString("Motolab");
}

QString Motolab::boardDescription()
{
    return QString("Motolab Tornado F3");
}

//! Return which capabilities this board has
bool Motolab::queryCapabilities(BoardCapabilities capability)
{
    switch(capability) {
    case BOARD_CAPABILITIES_GYROS:
        return true;
    case BOARD_CAPABILITIES_ACCELS:
        return true;
    case BOARD_CAPABILITIES_MAGS:
        return false;
    case BOARD_CAPABILITIES_BAROS:
        return false;
    case BOARD_CAPABILITIES_RADIO:
        return false;
    }
    return false;
}


/**
 * @brief Motolab::getSupportedProtocols
  * @return
 */
QStringList Motolab::getSupportedProtocols()
{
    return QStringList("uavtalk");
}

QPixmap Motolab::getBoardPicture()
{
    return QPixmap(":/motolab/images/tornadof3.png");
}

QString Motolab::getHwUAVO()
{
    return "HwMotolab";
}

//! Determine if this board supports configuring the receiver
bool Motolab::isInputConfigurationSupported()
{
    return true;
}

/**
 * Configure the board to use a receiver input type on a port number
 * @param type the type of receiver to use
 * @param port_num which input port to configure (board specific numbering)
 * @return true if successfully configured or false otherwise
 */
bool Motolab::setInputOnPort(enum InputType type, int port_num)
{
    if (port_num != 0)
        return false;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    UAVObjectManager *uavoManager = pm->getObject<UAVObjectManager>();
    HwMotolab *hwMotolab = HwMotolab::GetInstance(uavoManager);
    Q_ASSERT(hwMotolab);
    if (!hwMotolab)
        return false;

    HwMotolab::DataFields settings = hwMotolab->getData();

    switch(type) {
    case INPUT_TYPE_PPM:
        settings.RcvrPort = HwMotolab::RCVRPORT_PPM;
        break;
    case INPUT_TYPE_SBUS:
        settings.RcvrPort = HwMotolab::RCVRPORT_SBUS;
        break;
    case INPUT_TYPE_DSM:
        settings.RcvrPort = HwMotolab::RCVRPORT_DSM;
        break;
    case INPUT_TYPE_HOTTSUMD:
        settings.RcvrPort = HwMotolab::RCVRPORT_HOTTSUMD;
        break;
    default:
        return false;
    }

    // Apply these changes
    hwMotolab->setData(settings);

    return true;
}

/**
 * @brief Motolab::getInputOnPort fetch the currently selected input type
 * @param port_num the port number to query (must be zero)
 * @return the selected input type
 */
enum Core::IBoardType::InputType Motolab::getInputOnPort(int port_num)
{
    if (port_num != 0)
        return INPUT_TYPE_UNKNOWN;

    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    UAVObjectManager *uavoManager = pm->getObject<UAVObjectManager>();
    HwMotolab *hwMotolab = HwMotolab::GetInstance(uavoManager);
    Q_ASSERT(hwMotolab);
    if (!hwMotolab)
        return INPUT_TYPE_UNKNOWN;

    HwMotolab::DataFields settings = hwMotolab->getData();

    switch(settings.RcvrPort) {
    case HwMotolab::RCVRPORT_PPM:
        return INPUT_TYPE_PPM;
    case HwMotolab::RCVRPORT_SBUS:
        return INPUT_TYPE_SBUS;
    case HwMotolab::RCVRPORT_DSM:
        return INPUT_TYPE_DSM;
    case HwMotolab::RCVRPORT_HOTTSUMD:
        return INPUT_TYPE_HOTTSUMD;
    default:
        return INPUT_TYPE_UNKNOWN;
    }
}

int Motolab::queryMaxGyroRate()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    UAVObjectManager *uavoManager = pm->getObject<UAVObjectManager>();
    HwMotolab *hwMotolab = HwMotolab::GetInstance(uavoManager);
    Q_ASSERT(hwMotolab);
    if (!hwMotolab)
        return 0;

    HwMotolab::DataFields settings = hwMotolab->getData();

    switch(settings.GyroRange) {
    case HwMotolab::GYRORANGE_250:
        return 250;
    case HwMotolab::GYRORANGE_500:
        return 500;
    case HwMotolab::GYRORANGE_1000:
        return 1000;
    case HwMotolab::GYRORANGE_2000:
        return 2000;
    default:
        return 500;
    }
}
