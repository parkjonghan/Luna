/*
 * ccIoTDevice.h
 *
 *  Created on: 2016. 1. 26.
 *      Author: kmansoo
 */

#ifndef PRODUCTLIBRARY_CCIOTDEVICEAPI_CCIOTDEVICE_H_
#define PRODUCTLIBRARY_CCIOTDEVICEAPI_CCIOTDEVICE_H_

#include <memory>

#include "ccCore/ccSingleton.h"

#include "json/value.h"

#include "ccWebsocketClient/ccEasyWebsocketClient.h"

#include "ccIoTDeviceProtocol.h"
#include "ccIoTDeviceTransport.h"
#include "ccIoTDeviceTransportFactory.h"

#include "ccIoTDeviceInfo.h"

class ccIoTDevice {
public:
    ccIoTDevice(const std::string& strSpecFile = "MyDeviceInfo.json");
    virtual ~ccIoTDevice();

public:
    bool            attach_factory(std::shared_ptr<ccIoTDeviceTransportFactory> factory);
    virtual bool    start();
    virtual bool    stop();

    virtual bool    send(ccIoTDeviceProtocol& protocol);

public:
    bool    has_device(ccIoTDeviceSpecification::IoTDeviceType device_type);
    bool    has_device(const std::string& device_name);

public:
    virtual bool    on_recv_command(ccIoTDeviceProtocol& protocol);

protected:
    virtual bool    set_device_command(ccIoTDeviceProtocol& protocol);
    virtual bool    get_device_status_command(ccIoTDeviceProtocol& protocol);

protected:
    void    retry_connect();
    void    recv_data_from_websocket(Luna::ccWebsocket::ccWebSocketEvent ws_event, const std::string& message);

protected:
    bool                        is_connected_;
    bool                        is_stop_by_user_;

    ccIoTDeviceInfo             my_device_info_;
    std::string                 target_uri_;
    Luna::ccEasyWebsocketClient ws_client_;
    std::shared_ptr<ccIoTDeviceTransportFactory> factory_;

    std::map < std::string, std::function<bool(ccIoTDeviceProtocol& protocol)>> command_map_;
};

#endif /* PRODUCTLIBRARY_CCIOTDEVICEAPI_CCIOTDEVICE_H_ */