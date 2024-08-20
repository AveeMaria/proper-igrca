#include <windows.h>
#include <string>


class SerialPort {
public:
    SerialPort(const std::string& portName, int baudRate);
    ~SerialPort();
    std::string readLine(); // Reads a line from the serial port
private:
    HANDLE hSerial;
    DCB dcbSerialParams;
    COMMTIMEOUTS timeouts;
};
