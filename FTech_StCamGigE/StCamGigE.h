//----------------------------------------------------------
// Sentech GigE Camera Class
//----------------------------------------------------------
// Programmed by William Kim
//----------------------------------------------------------
// Last Update : 2017-04-06 11:48
// Modified by William Kim
//----------------------------------------------------------
#pragma once

#include <PvDeviceFinderWnd.h>
#include <PvDevice.h>
#include <PvGenParameter.h>
#include <PvGenBrowserWnd.h>
#include <PvBuffer.h>
#include <PvStream.h>
#include <PvPipeline.h>
#include <PvDisplayWnd.h>
#include <PvBufferWriter.h>
#include <PvSystem.h>
#include <PvDeviceInfo.h>
#include <PvDevice.h>
#include <PvAcquisitionStateManager.h>

namespace SENTECH_GIGE {

#define SEARCH_TIMEOUT 100
//----- enum type -----//
enum AWB {AWB_Off=0, AWB_Preset1, AWB_Preset2, AWB_Preset3, AWB_Continuous, AWB_Once};
enum USER {USER_Default=0, USER_UserSet1};
enum TRGMODE {TRG_On=0, TRG_Off};
enum TRGSRC {SRC_SW=0, SRC_HW};
enum TRGOVL {OVL_Off=0, OVL_ReadOut, OVL_PreFrm};
enum EXPMODE {EXP_Timed=0, EXP_PWC};
enum ACQMODE {ACQ_CNT=0, ACQ_SINGLE, ACQ_MULTI};

class CStCamGigE
{
public:
	CStCamGigE(void);
	~CStCamGigE(void);
	
public :
	//******************************************************************************************************************
	/// \brief					Interface ���� Ȯ�� �Լ�.
	/// \param [out] nValue		Interface ���� Ȯ��.
	/// \param bool				��� ��ȯ.
	static bool GetNumberOfInterfaces(int &nValue);
	//******************************************************************************************************************
	/// \brief					Ư�� Interface�� IP Address Ȯ�� �Լ�.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [out] strvalue	IP Address Ȯ��.
	/// \param bool				��� ��ȯ.
	static bool GetInterfaceIPAddress(int nIfIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					Ư�� Interface�� Subnet Mask Ȯ�� �Լ�.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [out] strvalue	Subnet Mask Ȯ��.
	/// \param bool				��� ��ȯ.
	static bool GetInterfaceSubnetMask(int nIfIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					Ư�� Interface�� Device ���� Ȯ�� �Լ�.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [out] nValue		Device ���� Ȯ��.
	/// \param bool				��� ��ȯ.
	static bool GetNumberOfDevices(int nIfIdx, int &nValue);
	//******************************************************************************************************************
	/// \brief					Ư�� Device�� Model Name Ȯ�� �Լ�.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [in] nDvIdx		Device Index.
	/// \param [out] strValue	Device Model Name Ȯ��.
	/// \param bool				��� ��ȯ.
	static bool GetDeviceName(int nIfIdx, int nDvIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					Ư�� Device�� Serial Number Ȯ�� �Լ�.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [in] nDvIdx		Device Index.
	/// \param [out] strValue	Device Serial Number Ȯ��.
	/// \param bool				��� ��ȯ.
	static bool GetDeviceSerialNumber(int nIfIdx, int nDvIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					Ư�� Device�� IP Address Ȯ�� �Լ�.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [in] nDvIdx		Device Index.
	/// \param [out] strValue	Device IP Address Ȯ��.
	/// \param bool				��� ��ȯ.
	static bool GetDeviceIPAddress(int nIfIdx, int nDvIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					Ư�� Device�� MAC Address Ȯ�� �Լ�.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [in] nDvIdx		Device Index.
	/// \param [out] strValue	Device MAC Address Ȯ��.
	/// \param bool				��� ��ȯ.
	static bool GetDeviceMACAddress(int nIfIdx, int nDvIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					Ư�� Device�� Access Status Ȯ�� �Լ�.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [in] nDvIdx		Device Index.
	/// \param [out] strValue	Device Access Status Ȯ��.
	/// \param bool				��� ��ȯ.
	static bool GetDeviceAccessStatus(int nIfIdx, int nDvIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					Ư�� Device�� IP ������ �ùٸ��� Ȯ���ϴ� �Լ�.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [in] nDvIdx		Device Index.
	/// \param [out] bValid		��ȿ ���� Ȯ��.
	/// \param bool				��� ��ȯ.
	static bool GetDeviceIPConfigurationValid(int nIfIdx, int nDvIdx, bool &bValid);
	//******************************************************************************************************************
	/// \brief					Ư�� Device�� IP Address ���� �Լ�.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [in] nDvIdx		Device Index.
	/// \param [in] strValue	Device IP Address ���� �� �Է�.
	/// \param bool				��� ��ȯ.
	static bool SetDeviceIPAddress(int nIfIdx, int nDvIdx, CString strValue);

public :
	//******************************************************************************************************************
	/// \brief					Device Finder Window�� ����Ͽ� ī�޶� �����ϴ� �Լ�.
	/// \param bool				��� ��ȯ.
	bool OnConnect();
	//******************************************************************************************************************
	/// \brief					�Է��� Device User ID�� ������ ī�޶� �����ϴ� �Լ�.
	/// \param [in] strUserID	Ư�� Device User ID�� �Է�.
	/// \param bool				��� ��ȯ.
	bool OnConnectID(CString strUserID);
	//******************************************************************************************************************
	/// \brief					�Է��� IP Address�� ������ ī�޶� �����ϴ� �Լ�.
	/// \param [in] nAddr1~4	Ư�� IP Address�� �Է�.
	/// \param bool				��� ��ȯ.
	bool OnConnectIP(int nAddr1, int nAddr2, int nAddr3, int nAddr4);
	//******************************************************************************************************************
	/// \brief					�Է��� IP Address�� ������ ī�޶� �����ϴ� �Լ�.
	/// \param [in] strIPAddressƯ�� IP Address�� �Է�. ('.'�� �����ؾ� �Ѵ�.)
	/// \param bool				��� ��ȯ.
	bool OnConnectIP(CString strIPAddress);
	//******************************************************************************************************************
	/// \brief					ī�޶� �����ϴ� �Լ�.
	/// \param bool				��� ��ȯ.
	void OnDisconnect();
	//******************************************************************************************************************
	/// \brief					���� ��� ���� �Լ�.
	/// \param bool				��� ��ȯ.
	bool OnStartAcquisition();
	//******************************************************************************************************************
	/// \brief					���� ��� ���� �Լ�.
	/// \param bool				��� ��ȯ.
	bool OnStopAcquisition();
	//******************************************************************************************************************
	/// \brief					Continuous Mode ���� �Լ�.
	/// \param bool				��� ��ȯ.
	bool SetContinuousMode();
	//******************************************************************************************************************
	/// \brief					Software Trigger Mode ���� �Լ�.
	/// \param bool				��� ��ȯ.
	bool SetSoftTriggerMode();
	//******************************************************************************************************************
	/// \brief					Hardware Trigger Mode ���� �Լ�.
	/// \param bool				��� ��ȯ.
	bool SetHardTriggerMode();
	//******************************************************************************************************************
	/// \brief					Software Trigger Event �߻� �Լ�.
	/// \param bool				��� ��ȯ.
	bool OnTriggerEvent();
	//******************************************************************************************************************
	/// \brief					Acquisition Mode ���� �Լ�.
	/// \param [in] Mode		Continuous / Single Frame / Multi Frame ���� ����.
	/// \param bool				��� ��ȯ.
	bool SetAcquisitionMode(ACQMODE Mode);
	//******************************************************************************************************************
	/// \brief					Multi Frame Count ���� �Լ�.
	/// \param [in] nValue		Count �Է�.
	/// \param bool				��� ��ȯ.
	bool SetMultiFrameCount(int nValue);
	//******************************************************************************************************************
	/// \brief					�̹��� ���� �Լ�.
	/// \param [in] strPath		���� ��� �Է�.
	/// \param bool				��� ��ȯ.
	bool OnSaveImage(CString strPath);
	//******************************************************************************************************************
	/// \brief					User Set ���� �Լ�.
	/// \param bool				��� ��ȯ.
	bool OnUserSetSave();
	//******************************************************************************************************************
	/// \brief					User Set �ҷ����� �Լ�.
	/// \param bool				��� ��ȯ.
	bool OnUserSetLoad();
	//******************************************************************************************************************
	/// \brief					Auto White Balance ���� �Լ�.
	/// \param [in] Type		Off / Preset 1~3 / Continuous / Once ���� ����.
	/// \param bool				��� ��ȯ.
	bool OnAutoWhiteBalance(AWB Type);
	//******************************************************************************************************************
	/// \brief					AWB Once�� ���� �Ķ���͸� ������ Preset �Ķ���Ϳ� �����ϴ� �Լ�.
	/// \param [in] nPresetNum	Ư�� Preset ��ȣ �Է�.
	/// \param bool				��� ��ȯ.
	bool OnSaveAWBValueOnceToPreset(int nPresetNum);
public :
	//******************************************************************************************************************
	/// \brief					Device ���� ���� Ȯ�� �Լ�.
	/// \param bool				��� ��ȯ.
	bool IsConnected() { return m_pvDevice.IsConnected(); }
	//******************************************************************************************************************
	/// \brief					���� ��� ���� Ȯ�� �Լ�.
	/// \param bool				��� ��ȯ.
	bool IsActive() { return m_isAcquisition; };
	//******************************************************************************************************************
	/// \brief					Device User ID Ȯ�� �Լ�.
	/// \param [out] strValue	Device User ID Ȯ��.
	/// \param bool				��� ��ȯ.
	bool GetUserID(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Device Model Name Ȯ�� �Լ�.
	/// \param [out] strValue	Device Model Name Ȯ��.
	/// \param bool				��� ��ȯ.
	bool GetModelName(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Device Serial Number Ȯ�� �Լ�.
	/// \param [out] strValue	Device Serial Number Ȯ��.
	/// \param bool				��� ��ȯ.
	bool GetSerialNumber(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Offset X Ȯ�� �Լ�.
	/// \param [out] nValue		Offset X Ȯ��.
	/// \param bool				��� ��ȯ.
	bool GetOffsetX(int &nValue);
	//******************************************************************************************************************
	/// \brief					Offset Y Ȯ�� �Լ�.
	/// \param [out] nValue		Offset Y Ȯ��.
	/// \param bool				��� ��ȯ.
	bool GetOffsetY(int &nValue);
	//******************************************************************************************************************
	/// \brief					Acquisition Mode Ȯ�� �Լ�.
	/// \param [out] strValue	Acquisition Mode Ȯ��.
	/// \param bool				��� ��ȯ.
	bool GetAcquisitionMode(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Frame Rate Ȯ�� �Լ�.
	/// \param [out] dValue		Frame Rate Ȯ��.
	/// \param bool				��� ��ȯ.
	bool GetAcquisitionFrameRate(double &dValue);
	//******************************************************************************************************************
	/// \brief					Trigger Mode Ȯ�� �Լ�.
	/// \param [out] strValue	Trigger Mode Ȯ��.
	/// \param bool				��� ��ȯ.
	bool GetTriggerMode(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Trigger Source Ȯ�� �Լ�.
	/// \param [out] strValue	Trigger Source Ȯ��.
	/// \param bool				��� ��ȯ.
	bool GetTriggerSource(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Trigger Overlap Ȯ�� �Լ�.
	/// \param [out] strValue	Trigger Overlap Ȯ��.
	/// \param bool				��� ��ȯ.
	bool GetTriggerOverlap(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Exposure Mode Ȯ�� �Լ�.
	/// \param [out] strValue	Exposure Mode Ȯ��.
	/// \param bool				��� ��ȯ.
	bool GetExposureMode(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Exposure Time Ȯ�� �Լ�.
	/// \param [out] nValue		Exposure Time Ȯ��.
	/// \param bool				��� ��ȯ.
	bool GetExposureTimeRaw(int &nValue);
	//******************************************************************************************************************
	/// \brief					Pixel Format Ȯ�� �Լ�.
	/// \param [out] strValue	Pixel Format Ȯ��.
	/// \param bool				��� ��ȯ.
	bool GetPixelFormat(CString &strValue);
	//******************************************************************************************************************
	/// \brief					User Set Default Selector Ȯ�� �Լ�.
	/// \param [out] strValue	User Set Default Selector Ȯ��.
	/// \param bool				��� ��ȯ.
	bool GetUserSetDefaultSelector(CString &strValue);
	//******************************************************************************************************************
	/// \brief					IP Address Ȯ�� �Լ�.
	/// \param CString			��� ��ȯ.
	CString GetIPAddress() { return m_strIP; }
	//******************************************************************************************************************
	/// \brief					MAC Address Ȯ�� �Լ�.
	/// \param CString			��� ��ȯ.
	CString GetMACAddress() { return m_strMAC; }
	//******************************************************************************************************************
	/// \brief					Width Ȯ�� �Լ�.
	/// \param int				��� ��ȯ.
	int  GetWidth()  { return m_nWidth;  }
	//******************************************************************************************************************
	/// \brief					Height Ȯ�� �Լ�.
	/// \param int				��� ��ȯ.
	int  GetHeight() { return m_nHeight; }
	//******************************************************************************************************************
	/// \brief					BPP Ȯ�� �Լ�.
	/// \param int				��� ��ȯ.
	int  GetBpp()	 { return m_nBpp;	 }
	//******************************************************************************************************************
	/// \brief					Grab Tact Time Ȯ�� �Լ�.
	/// \param double			��� ��ȯ.
	double GetGrabTime() { return m_dTime; }
	//******************************************************************************************************************
	/// \brief					Image Buffer Ȯ�� �Լ�.
	/// \param BYTE*			Image Buffer Pointer ��ȯ.
	BYTE* GetImageBuffer() { return m_pbyBuffer; }
	//******************************************************************************************************************
	/// \brief					������ ���� �޽��� Ȯ�� �Լ�.
	/// \param CString			������ ���� �޽��� ��ȯ.
	CString GetLastErrorMessage() { return m_strErrorMsg; }
	//******************************************************************************************************************
	/// \brief					Grab Done Handle ��ȯ �Լ�.
	/// \param HANDLE			��� ��ȯ.
	HANDLE GetHandleGrabDone() { return m_hGrabDone; }
	//******************************************************************************************************************
	/// \brief					Device User ID ���� �Լ�.
	/// \param [in] strValue	Device User ID �Է�.
	/// \param bool				��� ��ȯ.
	bool SetDeviceUserID(CString strValue);
	//******************************************************************************************************************
	/// \brief					Offset X ���� �Լ�.
	/// \param [in] nValue		Offset X �Է�.
	/// \param bool				��� ��ȯ.
	bool SetOffsetX(int nValue);
	//******************************************************************************************************************
	/// \brief					Offset Y ���� �Լ�.
	/// \param [in] nValue		Offset Y �Է�.
	/// \param bool				��� ��ȯ.
	bool SetOffsetY(int nValue);
	//******************************************************************************************************************
	/// \brief					Frame Rate ���� �Լ�.
	/// \param [in] dValue		Frame Rate �Է�.
	/// \param bool				��� ��ȯ.
	bool SetAcquisitionFrameRate(double dValue);
	//******************************************************************************************************************
	/// \brief					Acquisition Mode ���� �Լ�.
	/// \param [in] strValue	Acquisition Mode �Է�.
	/// \param bool				��� ��ȯ.
	bool SetAcquisitionMode(CString strValue);
	//******************************************************************************************************************
	/// \brief					Trigger Mode ���� �Լ�.
	/// \param [in] Mode		On / Off �Է�.
	/// \param bool				��� ��ȯ.
	bool SetTriggerMode(TRGMODE Mode);
	//******************************************************************************************************************
	/// \brief					Trigger Source ���� �Լ�.
	/// \param [in] Src			Soft / Hard �Է�.
	/// \param bool				��� ��ȯ.
	bool SetTriggerSource(TRGSRC Src);
	//******************************************************************************************************************
	/// \brief					Trigger Overlap ���� �Լ�.
	/// \param [in] Ovl			Off=0 / ReadOut / Pre Frame �Է�.
	/// \param bool				��� ��ȯ.
	bool SetTriggerOverlap(TRGOVL Ovl);
	//******************************************************************************************************************
	/// \brief					Exposure Mode ���� �Լ�.
	/// \param [in] Mode		Timed / Trigger Width �Է�.
	/// \param bool				��� ��ȯ.
	bool SetExposureMode(EXPMODE Mode);
	//******************************************************************************************************************
	/// \brief					Exposure Time ���� �Լ�.
	/// \param [in] dValue		Exposure Time �Է�.
	/// \param bool				��� ��ȯ.
	bool SetExposureTime(double dValue);
	//******************************************************************************************************************
	/// \brief					User Selector ���� �Լ�.
	/// \param [in] Mode		Default / UserSet1 �Է�.
	/// \param bool				��� ��ȯ.
	bool SetUserSetSelector(USER User);

protected:
	LARGE_INTEGER m_Start;
	LARGE_INTEGER m_Stop;
	LARGE_INTEGER m_Freq;
	double		  m_dTime;

private :
	HANDLE			m_hGrabDone;	// Grab Done Ȯ�� Handle.
	HANDLE			m_hThTerminate;	// Buffer Thread ���� Ȯ�� Handle.
	BYTE*			m_pbyBuffer;	// Image Buffer.
	BITMAPINFO*		m_pBitmapInfo;	// Image Bitmap Info.

	
	int	m_nWidth;			// Image Width Size.
	int	m_nHeight;			// Image Height Size.
	int	m_nBpp;				// Image Bit Per Pixel ũ��.
	bool m_isAcquisition;	// Acquisition ���� Ȯ��.
	CString m_strIP;		// IP Address.
	CString m_strMAC;		// MAC Address.
	CString m_strErrorMsg;	// ������ ���� �޽���.

	// SENTECH ��ü.
	PvAcquisitionStateManager *m_ppvAcqManager;
	PvSystem		m_pvSystem;
	PvStream		m_pvStream;
	PvPipeline		m_pvPipeline;
	PvDevice		m_pvDevice;

private :
	static UINT BufferThread(LPVOID param);
	void ShowErrorMessage(char* pcMessage, PvUInt32 nError);
	void OnCreateBmpInfo(int nWidth, int nHeight, int nBpp);

private :
	//******************************************************************************************************************
	/// \brief					Type���� Get/Set �ϴ� �Լ�.
	/// \param [in] pNodeName	�Ķ������ Node Name �Է�.
	/// \param [in]  Value		�Ķ������ �� �Է�.
	/// \param [out] Value		�Ķ������ �� Ȯ��.
	/// \param bool				��� ��ȯ.
	bool GetValueString(char* pNodeName, CString &strValue);
	bool SetValueString(char* pNodeName, CString strValue);
	bool GetValueInt(char* pNodeName, int &nValue);
	bool SetValueInt(char* pNodeName, int nValue);
	bool GetValueDouble(char* pNodeName, double &dValue);
	bool SetValueDouble(char* pNodeName, double dValue);
	bool GetValueEnum(char* pNodeName, CString &strValue);
	bool SetValueEnum(char* pNodeName, CString strValue);
	bool OnExecuteCommand(char* pNodeName);
};

}