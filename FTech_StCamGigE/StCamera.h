#pragma once

//----------------------------------------------------------
// Sentech GigE Camera Class
//----------------------------------------------------------
// Programmed by William Kim
//----------------------------------------------------------
// Last Update : 2016-11-10 16:37
// Modified by William Kim
//----------------------------------------------------------

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

//----- enum type -----//
enum AWB {AWB_Off=0, AWB_Preset1, AWB_Preset2, AWB_Preset3, AWB_Continuous, AWB_Once};
enum USER {USER_Default=0, USER_UserSet1};
enum TRGMODE {TRG_On=0, TRG_Off};
enum TRGSRC {SRC_SW=0, SRC_HW};
enum TRGOVL {OVL_Off=0, OVL_ReadOut, OVL_PreFrm};
enum EXPMODE {EXP_Timed=0, EXP_PWC};

class CStCamera
{
public:
	CStCamera(void);
	~CStCamera(void);

	//----- ���� �� ���� -----//
	bool OnConnect(); // Dialog ���� ����.
	bool OnConnect(CString strUserID); // User ID�� ����.
	bool OnConnect(int nAddr1, int nAddr2, int nAddr3, int nAddr4); // IP Address�� ����.
	void OnDisconnect(); // ���� ����.

	//----- ���� ��� ���� -----//
	bool OnStartAcquisition(); // ���� ��� ����.
	bool OnStopAcquisition();  // ���� ��� ����.

	//----- ���� ��� ��� ���� -----//
	bool SetContinuousMode();	// ������ ��� ����.
	bool SetSoftTriggerMode();	// ����Ʈ���� Ʈ���� ����.
	bool SetHardTriggerMode();  // �ϵ���� Ʈ���� ����.
	bool OnTriggerEvent();		// ����Ʈ���� Ʈ���� �̺�Ʈ.

	//----- ���� ����-----//
	bool OnSaveImage(CString strPath);	// �̹��� ����.

	//----- ���� ���� / �ҷ����� -----//
	bool OnUserSetSave();
	bool OnUserSetLoad();
	
	//----- Auto White Balance -----//
	bool OnAutoWhiteBalance(AWB Type);
	bool OnSaveAWBValueOnceToPreset(int nPresetNum);

	//----- Ȯ�� �� ��ȯ �Լ� -----//
	bool IsConnected() { return m_pvDevice.IsConnected(); }	// ���� ���� ��ȯ.
	bool IsActive() { return m_isAcquisition; };			// ���� ��� ���� ��ȯ.
	bool GetDeviceUserID(CString &strValue);				// Device User ID ��ȯ.
	bool GetDeviceModelName(CString &strValue);				// Device Model Name ��ȯ.
	bool GetSerialNumber(CString &strValue);				// Serial Number ��ȯ.
	bool GetOffsetX(int &nValue);							// Offset X ��ȯ.
	bool GetOffsetY(int &nValue);							// Offset Y ��ȯ.
	bool GetAcquisitionMode(CString &strValue);				// Acquisition Mode ��ȯ.
	bool GetAcquisitionFrameRate(double &dValue);			// Frame Rate ��ȯ.
	bool GetTriggerMode(CString &strValue);					// Trigger Mode ��ȯ.
	bool GetTriggerSource(CString &strValue);				// Trigger Source ��ȯ.
	bool GetTriggerOverlap(CString &strValue);				// Trigger Overlap ��ȯ.
	bool GetExposureMode(CString &strValue);				// Exposure Mode ��ȯ.
	bool GetExposureTimeRaw(int &nValue);					// Exposure Time ��ȯ.
	bool GetPixelFormat(CString &strValue);					// Pixel Format ��ȯ.
	bool GetUserSetDefaultSelector(CString &strValue);		// UserSet �⺻ �� ��ȯ.
	CString GetIPAddress() { return m_strIP; }				// IP Address ��ȯ.
	CString GetMACAddress() { return m_strMAC; }			// MAC Address ��ȯ.
	int  GetWidth()  { return m_nWidth ; }					// Image Width ��ȯ.
	int  GetHeight() { return m_nHeight; }					// Image Height ��ȯ.
	int  GetBPP()	 { return m_nBpp;	 }					// Image Bit per Pixel ��ȯ.
	double GetGrabTime() { return m_dTime; }				// Grab Tact Time ��ȯ.
	BYTE* GetImageBuffer() { return m_pbyBuffer; }			// Buffer ��ȯ.
	CString GetLastErrorMessage() { return m_strErrorMsg; }	// ������ ���� �޽��� ��ȯ.

	//----- ���� �Լ� -----//
	bool SetDeviceUserID(CString strValue);					// Device User ID ����.
	bool SetOffsetX(int nValue);							// Offset X ����.
	bool SetOffsetY(int nValue);							// Offset Y ����.
	bool SetAcquisitionFrameRate(double dValue);			// Frame Rate ����.
	bool SetAcquisitionMode(CString strValue);				// Acquistiion Mode ����.
	bool SetTriggerMode(TRGMODE Mode);						// Trigger Mode ����.
	bool SetTriggerSource(TRGSRC Src);						// Trigger Source ����.
	bool SetTriggerOverlap(TRGOVL Ovl);						// Trigger Overlap ����.
	bool SetExposureMode(EXPMODE Mode);						// Exposure Mode ����.
	bool SetExposureTime(double dValue);					// Exposure Time ����.
	bool SetUserSetSelector(USER User);						// UserSetSelector ����.
	
	HANDLE GetHandleGrabDone() { return m_hGrabDone; }

protected:
	LARGE_INTEGER m_Start;
	LARGE_INTEGER m_Stop;
	LARGE_INTEGER m_Freq;
	double		  m_dTime;

private :
	HANDLE m_hGrabDone;
	HANDLE m_hThTerminate;

	BYTE*			m_pbyBuffer;
	BITMAPINFO*		m_pBitmapInfo;
	PvAcquisitionStateManager *m_ppvAcqManager;
	PvSystem		m_pvSystem;
	PvStream		m_pvStream;
	PvPipeline		m_pvPipeline;
	PvDevice		m_pvDevice;

	CString m_strErrorMsg;
	bool m_isAcquisition;
	int	m_nWidth;
	int	m_nHeight;
	int	m_nBpp;
	CString m_strIP;
	CString m_strMAC;

	static UINT BufferThread(LPVOID param);
	void ShowErrorMessage(char* pcMessage, PvUInt32 nError);
	void OnCreateBmpInfo(int nWidth, int nHeight, int nBpp);

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

