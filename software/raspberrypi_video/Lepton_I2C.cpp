#include <iostream>
#include "Lepton_I2C.h"

#include "leptonSDKEmb32PUB/LEPTON_SDK.h"
#include "leptonSDKEmb32PUB/LEPTON_SYS.h"
#include "leptonSDKEmb32PUB/LEPTON_OEM.h"
#include "leptonSDKEmb32PUB/LEPTON_Types.h"

bool _connected;

LEP_CAMERA_PORT_DESC_T _port;
LEP_SYS_TELEMETRY_ENABLE_STATE_E  state;


int lepton_connect() {
	LEP_OpenPort(1, LEP_CCI_TWI, 400, &_port);
	_connected = true;
	return 0;
}

void lepton_perform_ffc() {
	if(!_connected) {
		lepton_connect();
	}
	LEP_RESULT r =  LEP_GetSysTelemetryEnableState(&_port, &state);
	std::cout << "LEP_GetSysTelemetryEnableState result: " << r <<std::endl;
	std::cout << "LEP_GetSysTelemetryEnableState state: " << state <<std::endl;
	LEP_RunSysFFCNormalization(&_port);
}

//presumably more commands could go here if desired

void lepton_reboot() {
	if(!_connected) {
		lepton_connect();
	}
	LEP_RunOemReboot(&_port);
}
