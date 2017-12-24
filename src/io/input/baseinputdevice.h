#ifndef IO_INPUT_BASEINPUTDEVICE_H_
#define IO_INPUT_BASEINPUTDEVICE_H_

#include <stdint.h>
#include <string>
#include <vector>
#include "../../common/consts.h"
#include "../../common/types.h"

using namespace std;

class BaseInputDevice
{
protected:
	static vector<string> eventNames;
	static vector<string> ledNames;


public:
	static string getDeviceName(int fd);
	static uint32_t getDeviceEventBits(int fd);
	static uint16_t getDeviceLEDs(int fd);

	static string getInputDeviceName(int deviceIndex);
	static VIDPID getInputDeviceVIDPID(int deviceIndex);

	static string readDeviceStringValue(const string& deviceName);
	static uint16_t readDeviceHexValue(const string& deviceName);

	static string printDeviceInfo(int fd);
	static bool getDeviceState(int fd, uint8_t type, unsigned long *array, size_t size);

protected:
	static const string getDeviceNameQuery();
	static const string getDeviceBusTypeQuery();
	static const string getDeviceVendorQuery();
	static const string getDeviceProductQuery();
};

#endif /* IO_INPUT_BASEINPUTDEVICE_H_ */