#include "MySerialPort.h"
#include <qdebug.h>

MySerialPort::MySerialPort()
{
	port_ = INVALID_HANDLE_VALUE;
	InitializeCriticalSection(&critical_section_);
}
MySerialPort::~MySerialPort()
{
	DeleteCriticalSection(&critical_section_);
}

void MySerialPort::SearchCom()
{
	sComInfo_t cominfo_tmp;

	cominfo_buf_.clear();
	HDEVINFO hdevinfo = SetupDiGetClassDevs((LPGUID)&GUID_DEVCLASS_PORTS, 0, 0, DIGCF_PRESENT);
	if (hdevinfo == INVALID_HANDLE_VALUE)
	{
		DWORD t_error = GetLastError();
		return;
	}
	SP_DEVINFO_DATA spdevinfodata;
	spdevinfodata.cbSize = sizeof(SP_DEVINFO_DATA);
	for (DWORD i = 0; SetupDiEnumDeviceInfo(hdevinfo, i, &spdevinfodata); i++)
	{
		DWORD datatype = 0;
		char buffer[256] = { 0 };
		DWORD buffersize = sizeof(buffer);
		while (!SetupDiGetDeviceRegistryProperty(hdevinfo, &spdevinfodata, SPDRP_FRIENDLYNAME, &datatype, (PBYTE)buffer, buffersize, &buffersize))
		{
			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {}
			else { break; }
		}
		std::string t_port_name;
		for (int i = 0; i < buffersize; i = i + 2)
		{
			t_port_name = t_port_name + buffer[i];
		}
		int positionelse = t_port_name.find("(COM");
		if (positionelse != std::string::npos)
		{
			std::string _com_No = t_port_name.substr(positionelse + 4, t_port_name.size() - (positionelse + 4) - 2);
			cominfo_tmp.ComName = t_port_name.c_str();
			cominfo_tmp.comId = std::stoi(_com_No);
			cominfo_buf_.push_back(cominfo_tmp);
		}
		memset(buffer, 0, buffersize);
	}
	if (GetLastError() != NO_ERROR && GetLastError() != ERROR_NO_MORE_ITEMS) { return; }
	SetupDiDestroyDeviceInfoList(hdevinfo);
}

int MySerialPort::SearchComNo(std::string comName)
{
	SearchCom();
	for (int i = 0; i < cominfo_buf_.size(); ++i)
	{
		if (cominfo_buf_[i].ComName.find(comName) == 0)
		{
			return cominfo_buf_[i].comId;
		}
	}
	return 0;
}

bool MySerialPort::OpenPort(int comNo)
{
	std::stringstream ss;
	ss << comNo;
	std::string str = ss.str();
	std::string t_comNo;
	if (comNo <= 0) { return false; }
	else if (comNo > 0 && comNo < 10) { t_comNo = "COM" + str; }
	else { t_comNo = "\\\\.\\COM" + str; }
	EnterCriticalSection(&critical_section_);
	std::wstring t_wcomNo(t_comNo.begin(), t_comNo.end());
	port_ = CreateFile(t_wcomNo.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
	if (port_ == INVALID_HANDLE_VALUE)
	{
		LeaveCriticalSection(&critical_section_);
		return false;
	}
	LeaveCriticalSection(&critical_section_);
	DCB dcb;
	SecureZeroMemory(&dcb, sizeof(DCB));
	dcb.BaudRate = 921600;
	dcb.ByteSize = 8;
	dcb.Parity = PARITY_NONE;
	dcb.StopBits = ONESTOPBIT;
	EnterCriticalSection(&critical_section_);
	if (!SetCommState(port_, &dcb))
	{
		port_ = INVALID_HANDLE_VALUE;
		LeaveCriticalSection(&critical_section_);
		return false;
	}
	PurgeComm(port_, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	LeaveCriticalSection(&critical_section_);
	return true;
}

bool MySerialPort::ClosePort()
{
	if (port_ != INVALID_HANDLE_VALUE)
	{
		CloseHandle(port_);
		port_ = INVALID_HANDLE_VALUE;
	}
	return true;
}

bool MySerialPort::SendCmd(uint8_t *data_buf, int len)
{
	DWORD bytes_to_send = 0;

	if (port_ == INVALID_HANDLE_VALUE) { return false; }
	EnterCriticalSection(&critical_section_);
	bool result = WriteFile(port_, data_buf, len, &bytes_to_send, NULL); // write data to sensor buffer
	if (!result)
	{
		DWORD error = GetLastError();
		PurgeComm(port_, PURGE_RXCLEAR | PURGE_RXABORT);
		LeaveCriticalSection(&critical_section_);
		return false;
	}
	LeaveCriticalSection(&critical_section_);
	return true;
}

UINT MySerialPort::BytesToRead()
{
	DWORD error = 0;
	COMSTAT comstat;
	memset(&comstat, 0, sizeof(COMSTAT));
	UINT bytes_in_queue = 0;
	if (ClearCommError(port_, &error, &comstat))
	{
		bytes_in_queue = comstat.cbInQue;
	}
	return bytes_in_queue;
}

bool MySerialPort::ReadChar(char &portData)
{
	bool is_get_char = true;
	DWORD bytes_read = 0;
	if (port_ == INVALID_HANDLE_VALUE) { return false; }
	EnterCriticalSection(&critical_section_);
	is_get_char = ReadFile(port_, &portData, 1, &bytes_read, NULL);
	if (!is_get_char)
	{
		DWORD error = GetLastError();
		PurgeComm(port_, PURGE_RXCLEAR | PURGE_RXABORT);
		LeaveCriticalSection(&critical_section_);
		return false;
	}
	LeaveCriticalSection(&critical_section_);
	return (bytes_read == 1);
}