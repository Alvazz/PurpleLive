#pragma once

#include "common.h"
#include <string>

enum eGPU_Vender
{
	// (����) ���� �׷��� ī���� �Ʒ� vendor id�� ������ 
	// ��Ʈ�ϰ� ���� ���κ��忡 ����� �׷���ī���� ��� vendor id�� ���� ��
	INTEL_VENDOR_ID = 0x8086,
	MICROSOFT_VENDOR_ID = 0x1414,
	NVIDIA_VENDOR_ID = 0x10de,
	AMD_VENDOR_ID = 0x1002
};

struct VideoAdapterInfo {
	unsigned int	vendorID;
	std::wstring		disc;
};

// This class is exported from the dll
class HardwareEncoderDetector {
public:
	HardwareEncoderDetector(void);
	
	static int detect();
	static bool is_supported_nvidea();
	static bool is_supported_amf();
	static bool is_supported_qsv();
};