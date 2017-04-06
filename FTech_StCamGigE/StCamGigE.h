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
	/// \brief					Interface 개수 확인 함수.
	/// \param [out] nValue		Interface 개수 확인.
	/// \param bool				결과 반환.
	static bool GetNumberOfInterfaces(int &nValue);
	//******************************************************************************************************************
	/// \brief					특정 Interface의 IP Address 확인 함수.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [out] strvalue	IP Address 확인.
	/// \param bool				결과 반환.
	static bool GetInterfaceIPAddress(int nIfIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					특정 Interface의 Subnet Mask 확인 함수.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [out] strvalue	Subnet Mask 확인.
	/// \param bool				결과 반환.
	static bool GetInterfaceSubnetMask(int nIfIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					특정 Interface의 Device 개수 확인 함수.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [out] nValue		Device 개수 확인.
	/// \param bool				결과 반환.
	static bool GetNumberOfDevices(int nIfIdx, int &nValue);
	//******************************************************************************************************************
	/// \brief					특정 Device의 Model Name 확인 함수.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [in] nDvIdx		Device Index.
	/// \param [out] strValue	Device Model Name 확인.
	/// \param bool				결과 반환.
	static bool GetDeviceName(int nIfIdx, int nDvIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					특정 Device의 Serial Number 확인 함수.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [in] nDvIdx		Device Index.
	/// \param [out] strValue	Device Serial Number 확인.
	/// \param bool				결과 반환.
	static bool GetDeviceSerialNumber(int nIfIdx, int nDvIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					특정 Device의 IP Address 확인 함수.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [in] nDvIdx		Device Index.
	/// \param [out] strValue	Device IP Address 확인.
	/// \param bool				결과 반환.
	static bool GetDeviceIPAddress(int nIfIdx, int nDvIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					특정 Device의 MAC Address 확인 함수.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [in] nDvIdx		Device Index.
	/// \param [out] strValue	Device MAC Address 확인.
	/// \param bool				결과 반환.
	static bool GetDeviceMACAddress(int nIfIdx, int nDvIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					특정 Device의 Access Status 확인 함수.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [in] nDvIdx		Device Index.
	/// \param [out] strValue	Device Access Status 확인.
	/// \param bool				결과 반환.
	static bool GetDeviceAccessStatus(int nIfIdx, int nDvIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					특정 Device의 IP 구성이 올바른지 확인하는 함수.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [in] nDvIdx		Device Index.
	/// \param [out] bValid		유효 여부 확인.
	/// \param bool				결과 반환.
	static bool GetDeviceIPConfigurationValid(int nIfIdx, int nDvIdx, bool &bValid);
	//******************************************************************************************************************
	/// \brief					특정 Device의 IP Address 설정 함수.
	/// \param [in] nIfIdx		Interface Index.
	/// \param [in] nDvIdx		Device Index.
	/// \param [in] strValue	Device IP Address 설정 값 입력.
	/// \param bool				결과 반환.
	static bool SetDeviceIPAddress(int nIfIdx, int nDvIdx, CString strValue);

public :
	//******************************************************************************************************************
	/// \brief					Device Finder Window를 사용하여 카메라를 연결하는 함수.
	/// \param bool				결과 반환.
	bool OnConnect();
	//******************************************************************************************************************
	/// \brief					입력한 Device User ID와 동일한 카메라를 연결하는 함수.
	/// \param [in] strUserID	특정 Device User ID를 입력.
	/// \param bool				결과 반환.
	bool OnConnectID(CString strUserID);
	//******************************************************************************************************************
	/// \brief					입력한 IP Address와 동일한 카메라를 연결하는 함수.
	/// \param [in] nAddr1~4	특정 IP Address를 입력.
	/// \param bool				결과 반환.
	bool OnConnectIP(int nAddr1, int nAddr2, int nAddr3, int nAddr4);
	//******************************************************************************************************************
	/// \brief					입력한 IP Address와 동일한 카메라를 연결하는 함수.
	/// \param [in] strIPAddress특정 IP Address를 입력. ('.'를 포함해야 한다.)
	/// \param bool				결과 반환.
	bool OnConnectIP(CString strIPAddress);
	//******************************************************************************************************************
	/// \brief					카메라를 해제하는 함수.
	/// \param bool				결과 반환.
	void OnDisconnect();
	//******************************************************************************************************************
	/// \brief					영상 취득 시작 함수.
	/// \param bool				결과 반환.
	bool OnStartAcquisition();
	//******************************************************************************************************************
	/// \brief					영상 취득 종료 함수.
	/// \param bool				결과 반환.
	bool OnStopAcquisition();
	//******************************************************************************************************************
	/// \brief					Continuous Mode 설정 함수.
	/// \param bool				결과 반환.
	bool SetContinuousMode();
	//******************************************************************************************************************
	/// \brief					Software Trigger Mode 설정 함수.
	/// \param bool				결과 반환.
	bool SetSoftTriggerMode();
	//******************************************************************************************************************
	/// \brief					Hardware Trigger Mode 설정 함수.
	/// \param bool				결과 반환.
	bool SetHardTriggerMode();
	//******************************************************************************************************************
	/// \brief					Software Trigger Event 발생 함수.
	/// \param bool				결과 반환.
	bool OnTriggerEvent();
	//******************************************************************************************************************
	/// \brief					Acquisition Mode 설정 함수.
	/// \param [in] Mode		Continuous / Single Frame / Multi Frame 선택 가능.
	/// \param bool				결과 반환.
	bool SetAcquisitionMode(ACQMODE Mode);
	//******************************************************************************************************************
	/// \brief					Multi Frame Count 설정 함수.
	/// \param [in] nValue		Count 입력.
	/// \param bool				결과 반환.
	bool SetMultiFrameCount(int nValue);
	//******************************************************************************************************************
	/// \brief					이미지 저장 함수.
	/// \param [in] strPath		저장 경로 입력.
	/// \param bool				결과 반환.
	bool OnSaveImage(CString strPath);
	//******************************************************************************************************************
	/// \brief					User Set 저장 함수.
	/// \param bool				결과 반환.
	bool OnUserSetSave();
	//******************************************************************************************************************
	/// \brief					User Set 불러오기 함수.
	/// \param bool				결과 반환.
	bool OnUserSetLoad();
	//******************************************************************************************************************
	/// \brief					Auto White Balance 설정 함수.
	/// \param [in] Type		Off / Preset 1~3 / Continuous / Once 선택 가능.
	/// \param bool				결과 반환.
	bool OnAutoWhiteBalance(AWB Type);
	//******************************************************************************************************************
	/// \brief					AWB Once로 계산된 파라미터를 지정된 Preset 파라미터에 저장하는 함수.
	/// \param [in] nPresetNum	특정 Preset 번호 입력.
	/// \param bool				결과 반환.
	bool OnSaveAWBValueOnceToPreset(int nPresetNum);
public :
	//******************************************************************************************************************
	/// \brief					Device 연결 상태 확인 함수.
	/// \param bool				결과 반환.
	bool IsConnected() { return m_pvDevice.IsConnected(); }
	//******************************************************************************************************************
	/// \brief					영상 취득 상태 확인 함수.
	/// \param bool				결과 반환.
	bool IsActive() { return m_isAcquisition; };
	//******************************************************************************************************************
	/// \brief					Device User ID 확인 함수.
	/// \param [out] strValue	Device User ID 확인.
	/// \param bool				결과 반환.
	bool GetUserID(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Device Model Name 확인 함수.
	/// \param [out] strValue	Device Model Name 확인.
	/// \param bool				결과 반환.
	bool GetModelName(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Device Serial Number 확인 함수.
	/// \param [out] strValue	Device Serial Number 확인.
	/// \param bool				결과 반환.
	bool GetSerialNumber(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Offset X 확인 함수.
	/// \param [out] nValue		Offset X 확인.
	/// \param bool				결과 반환.
	bool GetOffsetX(int &nValue);
	//******************************************************************************************************************
	/// \brief					Offset Y 확인 함수.
	/// \param [out] nValue		Offset Y 확인.
	/// \param bool				결과 반환.
	bool GetOffsetY(int &nValue);
	//******************************************************************************************************************
	/// \brief					Acquisition Mode 확인 함수.
	/// \param [out] strValue	Acquisition Mode 확인.
	/// \param bool				결과 반환.
	bool GetAcquisitionMode(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Frame Rate 확인 함수.
	/// \param [out] dValue		Frame Rate 확인.
	/// \param bool				결과 반환.
	bool GetAcquisitionFrameRate(double &dValue);
	//******************************************************************************************************************
	/// \brief					Trigger Mode 확인 함수.
	/// \param [out] strValue	Trigger Mode 확인.
	/// \param bool				결과 반환.
	bool GetTriggerMode(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Trigger Source 확인 함수.
	/// \param [out] strValue	Trigger Source 확인.
	/// \param bool				결과 반환.
	bool GetTriggerSource(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Trigger Overlap 확인 함수.
	/// \param [out] strValue	Trigger Overlap 확인.
	/// \param bool				결과 반환.
	bool GetTriggerOverlap(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Exposure Mode 확인 함수.
	/// \param [out] strValue	Exposure Mode 확인.
	/// \param bool				결과 반환.
	bool GetExposureMode(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Exposure Time 확인 함수.
	/// \param [out] nValue		Exposure Time 확인.
	/// \param bool				결과 반환.
	bool GetExposureTimeRaw(int &nValue);
	//******************************************************************************************************************
	/// \brief					Pixel Format 확인 함수.
	/// \param [out] strValue	Pixel Format 확인.
	/// \param bool				결과 반환.
	bool GetPixelFormat(CString &strValue);
	//******************************************************************************************************************
	/// \brief					User Set Default Selector 확인 함수.
	/// \param [out] strValue	User Set Default Selector 확인.
	/// \param bool				결과 반환.
	bool GetUserSetDefaultSelector(CString &strValue);
	//******************************************************************************************************************
	/// \brief					IP Address 확인 함수.
	/// \param CString			결과 반환.
	CString GetIPAddress() { return m_strIP; }
	//******************************************************************************************************************
	/// \brief					MAC Address 확인 함수.
	/// \param CString			결과 반환.
	CString GetMACAddress() { return m_strMAC; }
	//******************************************************************************************************************
	/// \brief					Width 확인 함수.
	/// \param int				결과 반환.
	int  GetWidth()  { return m_nWidth;  }
	//******************************************************************************************************************
	/// \brief					Height 확인 함수.
	/// \param int				결과 반환.
	int  GetHeight() { return m_nHeight; }
	//******************************************************************************************************************
	/// \brief					BPP 확인 함수.
	/// \param int				결과 반환.
	int  GetBpp()	 { return m_nBpp;	 }
	//******************************************************************************************************************
	/// \brief					Grab Tact Time 확인 함수.
	/// \param double			결과 반환.
	double GetGrabTime() { return m_dTime; }
	//******************************************************************************************************************
	/// \brief					Image Buffer 확인 함수.
	/// \param BYTE*			Image Buffer Pointer 반환.
	BYTE* GetImageBuffer() { return m_pbyBuffer; }
	//******************************************************************************************************************
	/// \brief					마지막 에러 메시지 확인 함수.
	/// \param CString			마지막 에러 메시지 반환.
	CString GetLastErrorMessage() { return m_strErrorMsg; }
	//******************************************************************************************************************
	/// \brief					Grab Done Handle 반환 함수.
	/// \param HANDLE			결과 반환.
	HANDLE GetHandleGrabDone() { return m_hGrabDone; }
	//******************************************************************************************************************
	/// \brief					Device User ID 설정 함수.
	/// \param [in] strValue	Device User ID 입력.
	/// \param bool				결과 반환.
	bool SetDeviceUserID(CString strValue);
	//******************************************************************************************************************
	/// \brief					Offset X 설정 함수.
	/// \param [in] nValue		Offset X 입력.
	/// \param bool				결과 반환.
	bool SetOffsetX(int nValue);
	//******************************************************************************************************************
	/// \brief					Offset Y 설정 함수.
	/// \param [in] nValue		Offset Y 입력.
	/// \param bool				결과 반환.
	bool SetOffsetY(int nValue);
	//******************************************************************************************************************
	/// \brief					Frame Rate 설정 함수.
	/// \param [in] dValue		Frame Rate 입력.
	/// \param bool				결과 반환.
	bool SetAcquisitionFrameRate(double dValue);
	//******************************************************************************************************************
	/// \brief					Acquisition Mode 설정 함수.
	/// \param [in] strValue	Acquisition Mode 입력.
	/// \param bool				결과 반환.
	bool SetAcquisitionMode(CString strValue);
	//******************************************************************************************************************
	/// \brief					Trigger Mode 설정 함수.
	/// \param [in] Mode		On / Off 입력.
	/// \param bool				결과 반환.
	bool SetTriggerMode(TRGMODE Mode);
	//******************************************************************************************************************
	/// \brief					Trigger Source 설정 함수.
	/// \param [in] Src			Soft / Hard 입력.
	/// \param bool				결과 반환.
	bool SetTriggerSource(TRGSRC Src);
	//******************************************************************************************************************
	/// \brief					Trigger Overlap 설정 함수.
	/// \param [in] Ovl			Off=0 / ReadOut / Pre Frame 입력.
	/// \param bool				결과 반환.
	bool SetTriggerOverlap(TRGOVL Ovl);
	//******************************************************************************************************************
	/// \brief					Exposure Mode 설정 함수.
	/// \param [in] Mode		Timed / Trigger Width 입력.
	/// \param bool				결과 반환.
	bool SetExposureMode(EXPMODE Mode);
	//******************************************************************************************************************
	/// \brief					Exposure Time 설정 함수.
	/// \param [in] dValue		Exposure Time 입력.
	/// \param bool				결과 반환.
	bool SetExposureTime(double dValue);
	//******************************************************************************************************************
	/// \brief					User Selector 설정 함수.
	/// \param [in] Mode		Default / UserSet1 입력.
	/// \param bool				결과 반환.
	bool SetUserSetSelector(USER User);

protected:
	LARGE_INTEGER m_Start;
	LARGE_INTEGER m_Stop;
	LARGE_INTEGER m_Freq;
	double		  m_dTime;

private :
	HANDLE			m_hGrabDone;	// Grab Done 확인 Handle.
	HANDLE			m_hThTerminate;	// Buffer Thread 종료 확인 Handle.
	BYTE*			m_pbyBuffer;	// Image Buffer.
	BITMAPINFO*		m_pBitmapInfo;	// Image Bitmap Info.

	
	int	m_nWidth;			// Image Width Size.
	int	m_nHeight;			// Image Height Size.
	int	m_nBpp;				// Image Bit Per Pixel 크기.
	bool m_isAcquisition;	// Acquisition 상태 확인.
	CString m_strIP;		// IP Address.
	CString m_strMAC;		// MAC Address.
	CString m_strErrorMsg;	// 마지막 에러 메시지.

	// SENTECH 객체.
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
	/// \brief					Type별로 Get/Set 하는 함수.
	/// \param [in] pNodeName	파라미터의 Node Name 입력.
	/// \param [in]  Value		파라미터의 값 입력.
	/// \param [out] Value		파라미터의 값 확인.
	/// \param bool				결과 반환.
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