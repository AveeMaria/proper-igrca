// SerialPort.cpp
#include "SerialPort.hpp"
#include <iostream>
#include <sstream>

SerialPort::SerialPort(const std::string& portName, int baudRate) {
    // Convert std::string to std::wstring (LPCWSTR)
    std::wstring wPortName = std::wstring(portName.begin(), portName.end());

    hSerial = CreateFile(wPortName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening serial port " << portName << "\n";
        return;
    }

    dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error getting serial port state\n";
        CloseHandle(hSerial);
        return;
    }

    dcbSerialParams.BaudRate = baudRate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error setting serial port parameters\n";
        CloseHandle(hSerial);
        return;
    }

    timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        std::cerr << "Error setting serial port timeouts\n";
        CloseHandle(hSerial);
    }
}

SerialPort::~SerialPort() {
    CloseHandle(hSerial);
}

std::string SerialPort::readLine() {
    std::string data;
    char c;
    DWORD bytesRead;
    while (ReadFile(hSerial, &c, 1, &bytesRead, NULL) && bytesRead == 1) {
        if (c == '\n') {
            break;
        }
        data += c;
    }
    return data;
}
