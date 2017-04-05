#include "StdAfx.h"
#include "StCamGigE.h"

using namespace SENTECH_GIGE;


bool CStCamGigE::GetNumberOfInterfaces(int &nValue)
{
	PvUInt32 lInterfaceCount=0;
	PvSystem mlSystem;
	PvResult pvResult;

	mlSystem.SetDetectionTimeout(SEARCH_TIMEOUT);
	pvResult = mlSystem.Find();
	if (pvResult.IsOK() == false) return false;
	
	lInterfaceCount = mlSystem.GetInterfaceCount();

	nValue = lInterfaceCount;

	return true;
}

bool CStCamGigE::GetInterfaceIPAddress(int nIfIdx, CString &strValue)
{
	PvUInt32 lDeviceCount=0;
	PvSystem mlSystem;
	PvResult pvResult;

	mlSystem.SetDetectionTimeout(SEARCH_TIMEOUT);
	pvResult = mlSystem.Find();
	if (pvResult.IsOK() == false) return false;

	PvInterface *lInterface = NULL;
	lInterface = mlSystem.GetInterface(nIfIdx);
	if (lInterface == NULL) return false;

	strValue = lInterface->GetIPAddress().GetUnicode();

	return true;
}

bool CStCamGigE::GetInterfaceSubnetMask(int nIfIdx, CString &strValue)
{
	PvUInt32 lDeviceCount=0;
	PvSystem mlSystem;
	PvResult pvResult;

	mlSystem.SetDetectionTimeout(SEARCH_TIMEOUT);
	pvResult = mlSystem.Find();
	if (pvResult.IsOK() == false) return false;

	PvInterface *lInterface = NULL;
	lInterface = mlSystem.GetInterface(nIfIdx);
	if (lInterface == NULL) return false;

	strValue = lInterface->GetSubnetMask().GetUnicode();

	return true;
}

bool CStCamGigE::GetNumberOfDevices(int nIfIdx, int &nValue)
{
	PvUInt32 lDeviceCount=0;
	PvSystem mlSystem;
	PvResult pvResult;

	mlSystem.SetDetectionTimeout(SEARCH_TIMEOUT);
	pvResult = mlSystem.Find();
	if (pvResult.IsOK() == false) return false;

	PvInterface *lInterface = NULL;
	lInterface = mlSystem.GetInterface(nIfIdx);
	if (lInterface == NULL) return false;

	lDeviceCount = lInterface->GetDeviceCount();

	nValue = lDeviceCount;

	return true;
}

bool CStCamGigE::GetDeviceName(int nIfIdx, int nDvIdx, CString &strValue) 
{ 
	PvSystem mlSystem;
	PvResult pvResult;
	PvDeviceInfo *lDeviceInfo = NULL;

	mlSystem.SetDetectionTimeout(SEARCH_TIMEOUT);
	pvResult = mlSystem.Find();
	if (pvResult.IsOK() == false) return false;

	PvInterface *lInterface = NULL;
	lInterface = mlSystem.GetInterface(nIfIdx);
	if (lInterface == NULL) return false;

	lDeviceInfo = lInterface->GetDeviceInfo(nDvIdx);
	if (lDeviceInfo == NULL) return false;

	strValue = lDeviceInfo->GetModel().GetUnicode();

	return true;
}

bool CStCamGigE::GetDeviceSerialNumber(int nIfIdx, int nDvIdx, CString &strValue)
{ 
	PvSystem mlSystem;
	PvResult pvResult;
	PvDeviceInfo *lDeviceInfo = NULL;

	mlSystem.SetDetectionTimeout(SEARCH_TIMEOUT);
	pvResult = mlSystem.Find();
	if (pvResult.IsOK() == false) return false;

	PvInterface *lInterface = NULL;
	lInterface = mlSystem.GetInterface(nIfIdx);
	if (lInterface == NULL) return false;

	lDeviceInfo = lInterface->GetDeviceInfo(nDvIdx);
	if (lDeviceInfo == NULL) return false;

	strValue = lDeviceInfo->GetSerialNumber().GetUnicode();

	return true;
}

bool CStCamGigE::GetDeviceIPAddress(int nIfIdx, int nDvIdx, CString &strValue)
{ 
	PvSystem mlSystem;
	PvResult pvResult;
	PvDeviceInfo *lDeviceInfo = NULL;

	mlSystem.SetDetectionTimeout(SEARCH_TIMEOUT);
	pvResult = mlSystem.Find();
	if (pvResult.IsOK() == false) return false;

	PvInterface *lInterface = NULL;
	lInterface = mlSystem.GetInterface(nIfIdx);
	if (lInterface == NULL) return false;

	lDeviceInfo = lInterface->GetDeviceInfo(nDvIdx);
	if (lDeviceInfo == NULL) return false;

	strValue = lDeviceInfo->GetIPAddress().GetUnicode();

	return true;
}

bool CStCamGigE::GetDeviceMACAddress(int nIfIdx, int nDvIdx, CString &strValue)
{
	PvSystem mlSystem;
	PvResult pvResult;
	PvDeviceInfo *lDeviceInfo = NULL;

	mlSystem.SetDetectionTimeout(SEARCH_TIMEOUT);
	pvResult = mlSystem.Find();
	if (pvResult.IsOK() == false) return false;

	PvInterface *lInterface = NULL;
	lInterface = mlSystem.GetInterface(nIfIdx);
	if (lInterface == NULL) return false;

	lDeviceInfo = lInterface->GetDeviceInfo(nDvIdx);
	if (lDeviceInfo == NULL) return false;

	strValue = lDeviceInfo->GetMACAddress().GetUnicode();

	return true;
}

bool CStCamGigE::GetDeviceAccessStatus(int nIfIdx, int nDvIdx, CString &strValue)
{
	PvSystem mlSystem;
	PvResult pvResult;
	PvDeviceInfo *lDeviceInfo = NULL;

	mlSystem.SetDetectionTimeout(SEARCH_TIMEOUT);
	pvResult = mlSystem.Find();
	if (pvResult.IsOK() == false) return false;

	PvInterface *lInterface = NULL;
	lInterface = mlSystem.GetInterface(nIfIdx);
	if (lInterface == NULL) return false;

	lDeviceInfo = lInterface->GetDeviceInfo(nDvIdx);
	if (lDeviceInfo == NULL) return false;

	PvAccessType type = lDeviceInfo->GetAccessStatus();
	switch (type)
	{
	case PvAccessUnknown :
		strValue = _T("Unknown");
		break;
	case PvAccessOpen :
		strValue = _T("Open");
		break;
	case PvAccessControl :
		strValue = _T("Control");
		break;
	case PvAccessReadOnly :
		strValue = _T("ReadOnly");
		break;
	case PvAccessExclusive :
		strValue = _T("Exclusive");
		break;
	}
		
	return true;
}

bool CStCamGigE::GetDeviceIPConfigurationValid(int nIfIdx, int nDvIdx, bool &bValid)
{
	PvSystem mlSystem;
	PvResult pvResult;
	PvDeviceInfo *lDeviceInfo = NULL;

	mlSystem.SetDetectionTimeout(SEARCH_TIMEOUT);
	pvResult = mlSystem.Find();
	if (pvResult.IsOK() == false) return false;

	PvInterface *lInterface = NULL;
	lInterface = mlSystem.GetInterface(nIfIdx);
	if (lInterface == NULL) return false;

	lDeviceInfo = lInterface->GetDeviceInfo(nDvIdx);
	if (lDeviceInfo == NULL) return false;

	bValid = lDeviceInfo->IsIPConfigurationValid();

	return true;
}

bool CStCamGigE::SetDeviceIPAddress(int nIfIdx, int nDvIdx, CString strValue)
{
	PvSystem mlSystem;
	PvResult pvResult;
	PvDeviceInfo *lDeviceInfo = NULL;

	mlSystem.SetDetectionTimeout(SEARCH_TIMEOUT);
	pvResult = mlSystem.Find();
	if (pvResult.IsOK() == false) return false;

	PvInterface *lInterface = NULL;
	lInterface = mlSystem.GetInterface(nIfIdx);
	if (lInterface == NULL) return false;

	lDeviceInfo = lInterface->GetDeviceInfo(nDvIdx);
	if (lDeviceInfo == NULL) return false;

	PvString strIP = strValue;
	PvDevice lDevice; 
	pvResult = lDevice.SetIPConfiguration(lDeviceInfo->GetMACAddress(), strIP, lInterface->GetSubnetMask(), lInterface->GetDefaultGateway());
	if (pvResult.IsOK() == false) return false;

	return true;
}

CStCamGigE::CStCamGigE(void)
	: m_pvPipeline(&m_pvStream)
	, m_ppvAcqManager(NULL)
{
	m_pbyBuffer		= NULL;
	m_pBitmapInfo	= NULL;
	
	m_isAcquisition	= false;
	m_strErrorMsg	= L"";
	
	m_nWidth	= 0;
	m_nHeight	= 0;
	m_nBpp		= 0;
	m_dTime		= 0;
	m_strIP		= L"";
	m_strMAC	= L"";

	m_hGrabDone = CreateEvent(NULL,TRUE,FALSE,NULL);
	m_hThTerminate = CreateEvent(NULL,TRUE,FALSE,NULL);
}

CStCamGigE::~CStCamGigE(void)
{
	if (m_isAcquisition == true)
	{
		m_isAcquisition = false;
		WaitForSingleObject(m_hThTerminate,2000);
	}

	if (m_pbyBuffer != NULL)
	{
		delete []m_pbyBuffer;
		m_pbyBuffer = NULL;
	}

	if (m_pBitmapInfo != NULL)
	{
		delete m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}

	OnStopAcquisition();

	OnDisconnect();
}

bool CStCamGigE::OnConnect()
{
	PvResult StResult = PvResult::Code::NOT_CONNECTED;

	PvDeviceFinderWnd DeviceFinderWnd;
	if ( !DeviceFinderWnd.ShowModal().IsOK() )
		return false;
	
	PvDeviceInfo* ppvDeviceInfo = DeviceFinderWnd.GetSelected();
	if( ppvDeviceInfo == NULL )
		return false;
	
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	
	StResult = m_pvDevice.Connect( ppvDeviceInfo, PvAccessControl );
	if ( !StResult.IsOK() )
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		OnDisconnect();
		return false;
	}

#ifdef _DEBUG
	m_pvDevice.GetGenParameters()->SetIntegerValue( "GevHeartbeatTimeout", 60000 );
#endif
	StResult = m_pvDevice.NegotiatePacketSize( 0, 1440 );
	if ( !StResult.IsOK() )
	{
		::Sleep( 2500 );
	}

	for ( ;; )
	{
		StResult = m_pvStream.Open( ppvDeviceInfo->GetIPAddress() );
		if ( StResult.IsOK() )
			break;
		
		::Sleep( 1000 );
	}

	m_pvDevice.SetStreamDestination( m_pvStream.GetLocalIPAddress(), m_pvStream.GetLocalPort() );
	if ( !StResult.IsOK() )
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		OnDisconnect();
		return false;
	}

	ASSERT( m_ppvAcqManager == NULL );
	m_ppvAcqManager = new PvAcquisitionStateManager( &m_pvDevice, &m_pvStream );

	m_strIP = (CString)ppvDeviceInfo->GetIPAddress().GetUnicode();
	m_strMAC = (CString)ppvDeviceInfo->GetMACAddress().GetUnicode();

	PvInt64 Value=0;
	m_pvDevice.GetGenParameters()->GetInteger( "Width" )->GetValue(Value);
	m_nWidth = (int)Value;

	m_pvDevice.GetGenParameters()->GetInteger( "Height" )->GetValue(Value);
	m_nHeight = (int)Value;

	PvString Format;
	m_pvDevice.GetGenParameters()->GetEnumValue("PixelFormat",Format);
	CString FormatStr = Format.GetUnicode();
	if (FormatStr.Find(L"Mono",0) >= 0)
	{
		m_pvDevice.GetGenParameters()->SetEnumValue("PixelFormat", "Mono8");
		m_nBpp = 8;
		OnCreateBmpInfo(m_nWidth, m_nHeight, m_nBpp);
	}
	else if (FormatStr.Find(L"Bayer",0) >= 0)
	{
		FormatStr = FormatStr.Left(7);
		FormatStr += L"8";

		Format = (PvString)FormatStr;
		m_pvDevice.GetGenParameters()->SetEnumValue("PixelFormat", Format);
		m_nBpp = 24;
		OnCreateBmpInfo(m_nWidth, m_nHeight, m_nBpp);
	}

	m_pvDevice.GetGenParameters()->GetInteger( "PayloadSize" )->GetValue(Value);
	m_pbyBuffer = new BYTE[(int)Value*m_nBpp/8];
	memset(m_pbyBuffer, 0, (int)Value*m_nBpp/8);

	::SetCursor(NULL);

	return true;
}

bool CStCamGigE::OnConnectID(CString strUserID)
{
	PvResult StResult = PvResult::Code::NOT_CONNECTED;

	SetCursor(LoadCursor(NULL, IDC_WAIT));

	PvString strID(strUserID);

	StResult = m_pvDevice.Connect(strID, PvAccessControl);
	if(!StResult.IsOK())
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

#ifdef _DEBUG
	m_pvDevice.GetGenParameters()->SetIntegerValue( "GevHeartbeatTimeout", 60000 );
#endif
	StResult = m_pvDevice.NegotiatePacketSize( 0, 1476 );
	if ( !StResult.IsOK() )
	{
		::Sleep( 2500 );
	}

	CString strIP=_T("");
	PvString pvstrIP="";
	PvGenInteger *pIntIP = m_pvDevice.GetGenParameters()->GetInteger("GevCurrentIPAddress");
	PvInt64 valueIP = 0;
	pIntIP->GetValue(valueIP);

	unsigned char bytesIP[4];
	bytesIP[0] = valueIP & 0xFF;
	bytesIP[1] = (valueIP >> 8) & 0xFF;
	bytesIP[2] = (valueIP >> 16) & 0xFF;
	bytesIP[3] = (valueIP >> 24) & 0xFF;   
	strIP.Format(_T("%d.%d.%d.%d"),bytesIP[3],bytesIP[2],bytesIP[1],bytesIP[0]);
	pvstrIP = (PvString)strIP;

	PvString strMac="";
	PvGenInteger *pIntMac = m_pvDevice.GetGenParameters()->GetInteger("GevMACAddress");
	strMac = pIntMac->ToString();
	m_strMAC = (CString)strMac.GetUnicode();

	StResult = m_pvStream.Open( pvstrIP );
	if ( !StResult.IsOK() )
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	m_pvDevice.SetStreamDestination( m_pvStream.GetLocalIPAddress(), m_pvStream.GetLocalPort() );

	m_pvStream.GetParameters()->SetIntegerValue("RequestTimeout", 1000 );

	ASSERT( m_ppvAcqManager == NULL );
	m_ppvAcqManager = new PvAcquisitionStateManager( &m_pvDevice, &m_pvStream );
	
	m_strIP = strIP;

	PvInt64 Value=0;
	m_pvDevice.GetGenParameters()->GetInteger( "Width" )->GetValue(Value);
	m_nWidth = (int)Value;

	m_pvDevice.GetGenParameters()->GetInteger( "Height" )->GetValue(Value);
	m_nHeight = (int)Value;

	PvString Format;
	m_pvDevice.GetGenParameters()->GetEnumValue("PixelFormat",Format);
	CString FormatStr = Format.GetUnicode();
	if (FormatStr.Find(L"Mono",0) >= 0)
	{
		m_pvDevice.GetGenParameters()->SetEnumValue("PixelFormat", "Mono8");
		m_nBpp = 8;
		OnCreateBmpInfo(m_nWidth, m_nHeight, m_nBpp);
	}
	else if (FormatStr.Find(L"Bayer",0) >= 0)
	{
		FormatStr = FormatStr.Left(7);
		FormatStr += L"8";

		Format = (PvString)FormatStr;
		m_pvDevice.GetGenParameters()->SetEnumValue("PixelFormat", Format);
		m_nBpp = 24;
		OnCreateBmpInfo(m_nWidth, m_nHeight, m_nBpp);
	}

	m_pvDevice.GetGenParameters()->GetInteger( "PayloadSize" )->GetValue(Value);
	m_pbyBuffer = new BYTE[(int)Value*m_nBpp/8];
	memset(m_pbyBuffer, 0, (int)Value*m_nBpp/8);

	SetCursor(NULL);

	return true;
}

bool CStCamGigE::OnConnectIP(int nAddr1, int nAddr2, int nAddr3, int nAddr4)
{
	SetCursor(LoadCursor(NULL, IDC_WAIT));

	CString IP=_T("");
	IP.Format(L"%d.%d.%d.%d", nAddr1,nAddr2,nAddr3,nAddr4);

	PvResult StResult = PvResult::Code::NOT_CONNECTED;
	

	PvString strIP(IP);
	
	StResult = m_pvDevice.Connect( strIP, PvAccessControl );
	if(!StResult.IsOK())
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

#ifdef _DEBUG
	m_pvDevice.GetGenParameters()->SetIntegerValue( "GevHeartbeatTimeout", 60000 );
#endif
	StResult = m_pvDevice.NegotiatePacketSize( 0, 1476 );
	if ( !StResult.IsOK() )
	{
		::Sleep( 2500 );
	}

	StResult = m_pvStream.Open( strIP );
	if ( !StResult.IsOK() )
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	m_pvDevice.SetStreamDestination( m_pvStream.GetLocalIPAddress(), m_pvStream.GetLocalPort() );

	m_pvStream.GetParameters()->SetIntegerValue("RequestTimeout", 1000 );

	ASSERT( m_ppvAcqManager == NULL );
	m_ppvAcqManager = new PvAcquisitionStateManager( &m_pvDevice, &m_pvStream );

	PvString strMac="";
	PvGenInteger *pIntMac = m_pvDevice.GetGenParameters()->GetInteger("GevMACAddress");
	strMac = pIntMac->ToString();
	m_strMAC = (CString)strMac.GetUnicode();
	m_strIP = IP;

	PvInt64 Value=0;
	m_pvDevice.GetGenParameters()->GetInteger( "Width" )->GetValue(Value);
	m_nWidth = (int)Value;

	m_pvDevice.GetGenParameters()->GetInteger( "Height" )->GetValue(Value);
	m_nHeight = (int)Value;

	PvString Format;
	m_pvDevice.GetGenParameters()->GetEnumValue("PixelFormat",Format);
	CString FormatStr = Format.GetUnicode();
	if (FormatStr.Find(L"Mono",0) >= 0)
	{
		m_pvDevice.GetGenParameters()->SetEnumValue("PixelFormat", "Mono8");
		m_nBpp = 8;
		OnCreateBmpInfo(m_nWidth, m_nHeight, m_nBpp);
	}
	else if (FormatStr.Find(L"Bayer",0) >= 0)
	{
		FormatStr = FormatStr.Left(7);
		FormatStr += L"8";

		Format = (PvString)FormatStr;
		m_pvDevice.GetGenParameters()->SetEnumValue("PixelFormat", Format);
		m_nBpp = 24;
		OnCreateBmpInfo(m_nWidth, m_nHeight, m_nBpp);
	}

	m_pvDevice.GetGenParameters()->GetInteger( "PayloadSize" )->GetValue(Value);
	m_pbyBuffer = new BYTE[(int)Value*m_nBpp/8];
	memset(m_pbyBuffer, 0, (int)Value*m_nBpp/8);

	SetCursor(NULL);

	return true;
}

bool CStCamGigE::OnConnectIP(CString strIPAddress)
{
	SetCursor(LoadCursor(NULL, IDC_WAIT));

	PvResult StResult = PvResult::Code::NOT_CONNECTED;
	
	PvString strIP(strIPAddress);
	
	StResult = m_pvDevice.Connect( strIP, PvAccessControl );
	if(!StResult.IsOK())
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

#ifdef _DEBUG
	m_pvDevice.GetGenParameters()->SetIntegerValue( "GevHeartbeatTimeout", 60000 );
#endif
	StResult = m_pvDevice.NegotiatePacketSize( 0, 1476 );
	if ( !StResult.IsOK() )
	{
		::Sleep( 2500 );
	}

	StResult = m_pvStream.Open( strIP );
	if ( !StResult.IsOK() )
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	m_pvDevice.SetStreamDestination( m_pvStream.GetLocalIPAddress(), m_pvStream.GetLocalPort() );

	m_pvStream.GetParameters()->SetIntegerValue("RequestTimeout", 1000 );

	ASSERT( m_ppvAcqManager == NULL );
	m_ppvAcqManager = new PvAcquisitionStateManager( &m_pvDevice, &m_pvStream );

	PvString strMac="";
	PvGenInteger *pIntMac = m_pvDevice.GetGenParameters()->GetInteger("GevMACAddress");
	strMac = pIntMac->ToString();
	m_strMAC = (CString)strMac.GetUnicode();
	m_strIP = strIPAddress;
	
	PvInt64 Value=0;
	m_pvDevice.GetGenParameters()->GetInteger( "Width" )->GetValue(Value);
	m_nWidth = (int)Value;

	m_pvDevice.GetGenParameters()->GetInteger( "Height" )->GetValue(Value);
	m_nHeight = (int)Value;

	PvString Format;
	m_pvDevice.GetGenParameters()->GetEnumValue("PixelFormat",Format);
	CString FormatStr = Format.GetUnicode();
	if (FormatStr.Find(L"Mono",0) >= 0)
	{
		m_pvDevice.GetGenParameters()->SetEnumValue("PixelFormat", "Mono8");
		m_nBpp = 8;
		OnCreateBmpInfo(m_nWidth, m_nHeight, m_nBpp);
	}
	else if (FormatStr.Find(L"Bayer",0) >= 0)
	{
		FormatStr = FormatStr.Left(7);
		FormatStr += L"8";

		Format = (PvString)FormatStr;
		m_pvDevice.GetGenParameters()->SetEnumValue("PixelFormat", Format);
		m_nBpp = 24;
		OnCreateBmpInfo(m_nWidth, m_nHeight, m_nBpp);
	}

	m_pvDevice.GetGenParameters()->GetInteger( "PayloadSize" )->GetValue(Value);
	m_pbyBuffer = new BYTE[(int)Value*m_nBpp/8];
	memset(m_pbyBuffer, 0, (int)Value*m_nBpp/8);

	SetCursor(NULL);

	return true;
}

void CStCamGigE::OnDisconnect()
{
	SetCursor(LoadCursor(NULL, IDC_WAIT));

	if (m_isAcquisition == true)
	{
		m_isAcquisition = false;
		WaitForSingleObject(m_hThTerminate,2000);
	}

	if(m_pvPipeline.IsStarted())
		m_pvPipeline.Stop();

	if(m_pvStream.IsOpen())
		m_pvStream.Close();

	if(m_pvDevice.IsConnected())
		m_pvDevice.Disconnect();

	if (m_pbyBuffer != NULL)
	{
		delete []m_pbyBuffer;
		m_pbyBuffer = NULL;
	}

	if (m_pBitmapInfo != NULL)
	{
		delete m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}

	if ( m_ppvAcqManager != NULL )
	{
		delete m_ppvAcqManager;
		m_ppvAcqManager = NULL;
	}

	SetCursor(NULL);
}

bool CStCamGigE::OnStartAcquisition()
{
	if (!m_pvDevice.IsConnected())
	{
		m_strErrorMsg = L"Device is not connected.";
		return false;
	}

	if (m_isAcquisition == true)
		OnStopAcquisition();
	
	PvResult StResult = PvResult::Code::NOT_CONNECTED;

	m_isAcquisition = true;

	AfxBeginThread(BufferThread, this);

	StResult = m_pvPipeline.Start();
	if (!StResult.IsOK())
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	PvGenInteger *lPayloadSize = m_pvDevice.GetGenParameters()->GetInteger( "PayloadSize" );

	PvInt64 lPayloadSizeValue = 0;
	if ( lPayloadSize != NULL )
		lPayloadSize->GetValue( lPayloadSizeValue );

	if ( lPayloadSizeValue > 0 )
	{
		m_pvPipeline.SetBufferSize( static_cast<PvUInt32>( lPayloadSizeValue ) );
	}

	StResult = m_pvPipeline.Reset();
	if (!StResult.IsOK())
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	StResult = m_pvStream.GetParameters()->ExecuteCommand( "Reset" );
	if (!StResult.IsOK())
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	ASSERT( m_ppvAcqManager != NULL );
	StResult = m_ppvAcqManager->Start();
	if (!StResult.IsOK())
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	return true;
}

bool CStCamGigE::OnStopAcquisition()
{
	if (!m_pvDevice.IsConnected())
	{
		m_strErrorMsg = L"Device is not connected.";
		return false;
	}

	PvResult StResult = PvResult::Code::NOT_CONNECTED;

	m_isAcquisition = false;

	if ( m_pvPipeline.IsStarted() )
	{
		StResult = m_pvPipeline.Stop();
		if (!StResult.IsOK())
		{
			m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
			return false;
		}
	}

	ASSERT( m_ppvAcqManager != NULL );
	StResult = m_ppvAcqManager->Stop();
	if (!StResult.IsOK())
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	return true;
}

void CStCamGigE::ShowErrorMessage(char* pcMessage, PvUInt32 nError)
{
	int Len = (int)strlen(pcMessage);
	char* Tmp = new char[128];
	strcpy_s(Tmp,Len+1,pcMessage);

	if		(nError == PvResult::Code::ABORTED				) strcat_s(Tmp,128," - The operation was aborted."); 
	else if (nError == PvResult::Code::AUTO_ABORTED			) strcat_s(Tmp,128," - Buffer reception failed."); 
	else if (nError == PvResult::Code::BAD_VERSION			) strcat_s(Tmp,128," - Some component versions are not compatible."); 
	else if (nError == PvResult::Code::BUFFER_TOO_SMALL 	) strcat_s(Tmp,128," - The buffer was not large enough to hold the payload of the block being received."); 
	else if (nError == PvResult::Code::CANCEL 				) strcat_s(Tmp,128," - The user closed a dialog and the operation was not performed."); 
	else if (nError == PvResult::Code::CANNOT_OPEN_FILE 	) strcat_s(Tmp,128," - The file doesn't exist or can't be opened."); 
	else if (nError == PvResult::Code::ERR_OVERFLOW 		) strcat_s(Tmp,128," - Overflow occurred."); 
	else if (nError == PvResult::Code::FILE_ERROR 			) strcat_s(Tmp,128," - A file operation error occured."); 
	else if (nError == PvResult::Code::GENERIC_ERROR 		) strcat_s(Tmp,128," - An undefined error occurred."); 
	else if (nError == PvResult::Code::GENICAM_XML_ERROR 	) strcat_s(Tmp,128," - The GenICam XML file could not be loaded into GenApi."); 
	else if (nError == PvResult::Code::IMAGE_ERROR 			) strcat_s(Tmp,128," - Error with an image."); 
	else if (nError == PvResult::Code::INVALID_DATA_FORMAT 	) strcat_s(Tmp,128," - The data format is not supported for the requested operation."); 
	else if (nError == PvResult::Code::INVALID_PARAMETER 	) strcat_s(Tmp,128," - A parameter passed to the method is invalid."); 
	else if (nError == PvResult::Code::MISSING_PACKETS 		) strcat_s(Tmp,128," - Some packets are missing in the buffer."); 
	else if (nError == PvResult::Code::NETWORK_ERROR 		) strcat_s(Tmp,128," - A network error occurred while performing the requested operation."); 
	else if (nError == PvResult::Code::NO_AVAILABLE_DATA 	) strcat_s(Tmp,128," - There is no available data to enumerate."); 
	else if (nError == PvResult::Code::NO_LICENSE 			) strcat_s(Tmp,128," - An eBUS SDK license is missing."); 
	else if (nError == PvResult::Code::NO_MORE_ENTRY 		) strcat_s(Tmp,128," - There are no more entries to retrieve/enumerate."); 
	else if (nError == PvResult::Code::NO_MORE_ITEM 		) strcat_s(Tmp,128," - No more of what was requested is currently available."); 
	else if (nError == PvResult::Code::NOT_CONNECTED 		) strcat_s(Tmp,128," - The object (PvDevice or PvStream object) isn't connected."); 
	else if (nError == PvResult::Code::NOT_ENOUGH_MEMORY 	) strcat_s(Tmp,128," - Not enough memory."); 
	else if (nError == PvResult::Code::NOT_FOUND 			) strcat_s(Tmp,128," - The expected item wasn't found."); 
	else if (nError == PvResult::Code::NOT_IMPLEMENTED 		) strcat_s(Tmp,128," - The requested feature or functionality is not implemented."); 
	else if (nError == PvResult::Code::NOT_INITIALIZED 		) strcat_s(Tmp,128," - An error code hasn't been set."); 
	else if (nError == PvResult::Code::NOT_SUPPORTED 		) strcat_s(Tmp,128," - The requested feature or functionality is not supported."); 
	else if (nError == PvResult::Code::RESENDS_FAILURE 		) strcat_s(Tmp,128," - Failure to receive all missing packets for a buffer through resend packets."); 
	else if (nError == PvResult::Code::STATE_ERROR 			) strcat_s(Tmp,128," - The method is (probably) legal, but the system's current state doesn't allow the action."); 
	else if (nError == PvResult::Code::THREAD_ERROR 		) strcat_s(Tmp,128," - An error occurred while attempting to perform an operation on a thread like starting, stopping or changing priority."); 
	else if (nError == PvResult::Code::TIMEOUT 				) strcat_s(Tmp,128," - The operation timed out."); 
	else if (nError == PvResult::Code::TOO_MANY_RESENDS 	) strcat_s(Tmp,128," - Too many resend packets were requested, buffer acquisition failure."); 
	else if (nError == PvResult::Code::TOO_MANY_CONSECUTIVE_RESENDS	) strcat_s(Tmp,128," - Buffer reception failed, consecutive missing buffers higher than allowed."); 

	MessageBoxA(NULL, Tmp, "Error", MB_OK | MB_ICONERROR);

	delete Tmp;
}


void CStCamGigE::OnCreateBmpInfo(int nWidth, int nHeight, int nBpp)
{
	if (nBpp == 8)
		m_pBitmapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO) + 255*sizeof(RGBQUAD)];
	else if (nBpp == 24)
		m_pBitmapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO)];

	m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo->bmiHeader.biPlanes = 1;
	m_pBitmapInfo->bmiHeader.biBitCount = nBpp;
	m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
	
	if (nBpp == 8)
		m_pBitmapInfo->bmiHeader.biSizeImage = 0;
	else if (nBpp == 24)
		m_pBitmapInfo->bmiHeader.biSizeImage = (((nWidth * 24 + 31) & ~31) >> 3) * nHeight;

	m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo->bmiHeader.biClrImportant = 0;

	if (nBpp == 8)
	{
		for (int i = 0 ; i < 256 ; i++)
		{
			m_pBitmapInfo->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbRed = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
	}
	
	m_pBitmapInfo->bmiHeader.biWidth = nWidth;
	m_pBitmapInfo->bmiHeader.biHeight = -nHeight;
}

bool CStCamGigE::OnSaveImage(CString strPath)
{
	if (strPath.IsEmpty()) return false;

	if (m_pbyBuffer == NULL) return false;

	PvResult StResult = PvResult::Code::NOT_CONNECTED;

	BITMAPFILEHEADER dib_format_layout;
	ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
	dib_format_layout.bfType = 0x4D42;//*(WORD*)"BM";
	if (m_nBpp == 8)
		dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(m_pBitmapInfo->bmiColors) * 256;
	else
		dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	
	dib_format_layout.bfSize = dib_format_layout.bfOffBits + m_pBitmapInfo->bmiHeader.biSizeImage;

	wchar_t* wchar_str;     
	char*    char_str;      
	int      char_str_len;  
	wchar_str = strPath.GetBuffer(strPath.GetLength());

	char_str_len = WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, NULL, 0, NULL, NULL);
	char_str = new char[char_str_len];
	WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, char_str, char_str_len, 0,0);  

	FILE *p_file;
	fopen_s(&p_file,char_str, "wb");
	if(p_file != NULL)
	{
		fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);
		fwrite(m_pBitmapInfo, 1, sizeof(BITMAPINFOHEADER), p_file);
		if (m_nBpp == 8)
			fwrite(m_pBitmapInfo->bmiColors, sizeof(m_pBitmapInfo->bmiColors), 256, p_file);

		fwrite(m_pbyBuffer, 1, m_nWidth * m_nHeight * m_nBpp/8, p_file);
		fclose(p_file);
	}

	delete char_str;

	return true;
}

bool CStCamGigE::GetDeviceUserID(CString &strValue)
{
	CString value=_T("");
	bool ret = GetValueString("DeviceUserID",value);
	if (ret == false) return false;

	strValue = value;

	return true;
}

bool CStCamGigE::GetDeviceModelName(CString &strValue)
{
	CString value=_T("");
	bool ret = GetValueString("DeviceModelName",value);
	if (ret == false) return false;

	strValue = value;

	return true;
}

bool CStCamGigE::GetSerialNumber(CString &strValue)
{
	CString value=_T("");
	bool ret = GetValueString("DeviceID",value);
	if (ret == false) return false;

	strValue = value;

	return true;
}

bool CStCamGigE::GetOffsetX(int &nValue)
{
	int value=0;
	bool ret = GetValueInt("OffsetX",value);
	if (ret == false) return false;

	nValue = value;

	return true;
}

bool CStCamGigE::GetOffsetY(int &nValue)
{
	int value=0;
	bool ret = GetValueInt("OffsetY",value);
	if (ret == false) return false;

	nValue = value;

	return true;
}

bool CStCamGigE::GetAcquisitionMode(CString &strValue)
{
	CString value=_T("");
	bool ret = GetValueEnum("AcquisitionMode",value);
	if (ret == false) return false;

	strValue = value;

	return true;
}

bool CStCamGigE::GetAcquisitionFrameRate(double &dValue)
{
	double value=0;
	bool ret = GetValueDouble("AcquisitionFrameRate",value);
	if (ret == false) return false;

	dValue = value;

	return true;
}

bool CStCamGigE::GetTriggerMode(CString &strValue)
{
	CString value=_T("");
	bool ret = GetValueEnum("TriggerMode",value);
	if (ret == false) return false;

	strValue = value;

	return true;
}

bool CStCamGigE::GetTriggerSource(CString &strValue)
{
	CString value=_T("");
	bool ret = GetValueEnum("TriggerSource",value);
	if (ret == false) return false;

	strValue = value;

	return true;
}

bool CStCamGigE::GetTriggerOverlap(CString &strValue)
{
	CString value=_T("");
	bool ret = GetValueEnum("TriggerOverlap",value);
	if (ret == false) return false;

	strValue = value;

	return true;
}

bool CStCamGigE::GetExposureMode(CString &strValue)
{
	CString value=_T("");
	bool ret = GetValueEnum("ExposureMode",value);
	if (ret == false) return false;

	strValue = value;

	return true;
}

bool CStCamGigE::GetExposureTimeRaw(int &nValue)
{
	int value=0;
	bool ret = GetValueInt("ExposureTimeRaw",value);
	if (ret == false) return false;

	nValue = value;

	return true;
}

bool CStCamGigE::GetPixelFormat(CString &strValue)
{
	CString value=_T("");
	bool ret = GetValueEnum("PixelFormat",value);
	if (ret == false) return false;

	strValue = value;

	return true;
}

bool CStCamGigE::GetUserSetDefaultSelector(CString &strValue)
{
	CString value=_T("");
	bool ret = GetValueEnum("UserSetDefaultSelector",value);
	if (ret == false) return false;

	strValue = value;

	return true;
}

bool CStCamGigE::SetDeviceUserID(CString strValue)
{
	CString value=_T("");
	bool ret = SetValueString("DeviceUserID",strValue);
	if (ret == false) return false;

	return true;
}

bool CStCamGigE::SetOffsetX(int nValue)
{
	int value=0;
	bool ret = SetValueInt("OffsetX",value);
	if (ret == false) return false;

	nValue = value;

	return true;
}

bool CStCamGigE::SetOffsetY(int nValue)
{
	return SetValueInt("OffsetY",nValue);
}

bool CStCamGigE::SetAcquisitionFrameRate(double dValue)
{
	return SetValueDouble("AcquisitionFrameRate",dValue);
}

bool CStCamGigE::SetAcquisitionMode(CString strValue)
{
	return SetValueEnum("AcquisitionMode",strValue);
}

bool CStCamGigE::SetTriggerMode(TRGMODE Mode)
{
	CString value=_T("");
	switch (Mode)
	{
		case TRG_On	: value = "On"	; break;
		case TRG_Off: value = "Off" ; break;
	}

	bool ret = SetValueEnum("AcquisitionMode",value);
	if (ret == false) return false;

	return true;
}

bool CStCamGigE::SetTriggerSource(TRGSRC Src)
{
	CString value=_T("");
	switch (Src)
	{
		case SRC_SW : value = "Software"; break;
		case SRC_HW : value = "Hardware"; break;
	}

	bool ret = SetValueEnum("TriggerSource",value);
	if (ret == false) return false;

	return true;
}

bool CStCamGigE::SetTriggerOverlap(TRGOVL Ovl)
{
	CString value=_T("");
	switch (Ovl)
	{
		case OVL_Off	: value = "Off"			 ; break;
		case OVL_ReadOut: value = "ReadOut"		 ; break;
		case OVL_PreFrm	: value = "PreviousFrame"; break;
	}

	bool ret = SetValueEnum("TriggerOverlap",value);
	if (ret == false) return false;

	return true;
}

bool CStCamGigE::SetExposureMode(EXPMODE Mode)
{
	CString value=_T("");
	switch (Mode)
	{
		case EXP_Timed	: value = "Timed"		; break;
		case EXP_PWC	: value = "TriggerWidth"; break;
	}

	bool ret = SetValueEnum("ExposureMode",value);
	if (ret == false) return false;

	return true;
}

bool CStCamGigE::SetUserSetSelector(USER User)
{
	CString value=_T("");
	switch (User)
	{
		case USER_Default	: value = "Default" ; break;
		case USER_UserSet1	: value = "UserSet1"; break;
	}

	bool ret = SetValueEnum("UserSetSelector",value);
	if (ret == false) return false;

	return true;
}

bool CStCamGigE::SetExposureTime(double dValue)
{
	bool ret = SetValueDouble("ExposureTime",dValue);
	if (ret == false) return false;

	return true;
}

bool CStCamGigE::SetContinuousMode()
{
	bool ret=false;

	ret = SetValueEnum("TriggerMode", _T("Off"));
	if (ret == false) return false;
	
	ret = SetValueEnum("ExposureMode", _T("Timed"));
	if (ret == false) return false;

	return true;
}

bool CStCamGigE::SetAcquisitionMode(ACQMODE Mode)
{
	bool ret=false;

	switch (Mode)
	{
	case ACQ_CNT :
		ret = SetValueEnum("AcquisitionMode", _T("Continuous"));
		break;
	case ACQ_SINGLE :
		ret = SetValueEnum("AcquisitionMode", _T("SingleFrame"));
		break;
	case ACQ_MULTI :
		ret = SetValueEnum("AcquisitionMode", _T("MultiFrame"));
		break;
	}

	if (ret == false) return false;

	return true;
}

bool CStCamGigE::SetMultiFrameCount(int nValue)
{
	return SetValueInt("AcquisitionFrameCount", nValue);
}

bool CStCamGigE::SetSoftTriggerMode()
{
	bool ret=false;

	ret = SetValueEnum("TriggerMode", _T("On"));
	if (ret == false) return false;

	ret = SetValueEnum("TriggerSource", _T("Software"));
	if (ret == false) return false;

	ret = SetValueEnum("TriggerOverlap", _T("ReadOut"));
	if (ret == false) return false;

	ret = SetValueEnum("TriggerSoftwareSource", _T("Command"));
	if (ret == false) return false;

	return true;
}

bool CStCamGigE::SetHardTriggerMode()
{
	bool ret=false;

	ret = SetValueEnum("TriggerMode", _T("On"));
	if (ret == false) return false;

	ret = SetValueEnum("TriggerSource", _T("Hardware"));
	if (ret == false) return false;

	ret = SetValueEnum("TriggerOverlap", _T("ReadOut"));
	if (ret == false) return false;

	return true;
}

bool CStCamGigE::OnTriggerEvent()
{
	return OnExecuteCommand("TriggerSoftware");
}

bool CStCamGigE::OnUserSetLoad()
{
	return OnExecuteCommand("UserSetLoad");
}

bool CStCamGigE::OnAutoWhiteBalance(AWB Type)
{
	bool ret=false;

	CString Name=_T("");
	switch (Type)
	{
	case AWB_Off :
		ret = SetValueEnum("BalanceWhiteAuto", _T("Off"));
		break;
	case AWB_Preset1 :
		ret = SetValueEnum("BalanceWhiteAuto", _T("Preset1"));
		break;
	case AWB_Preset2 :
		ret = SetValueEnum("BalanceWhiteAuto", _T("Preset2"));
		break;
	case AWB_Preset3 :
		ret = SetValueEnum("BalanceWhiteAuto", _T("Preset3"));
		break;
	case AWB_Continuous :
		ret = SetValueEnum("BalanceWhiteAuto", _T("Continuous"));
		break;
	case AWB_Once :
		ret = SetValueEnum("BalanceWhiteAuto", _T("Once"));
		break;
	}

	if (ret == false) return false;

	return true;
}
bool CStCamGigE::OnSaveAWBValueOnceToPreset(int nPresetNum)
{
	if (!m_pvDevice.IsConnected())
	{
		m_strErrorMsg = L"Device is not connected.";
		return false;
	}

	if (nPresetNum < 1 || nPresetNum > 3)
	{
		m_strErrorMsg = L"Out of range of AWB Preset number.";
		return false;
	}

	PvResult StResult = PvResult::Code::NOT_CONNECTED;
	CString strPreset=L"";
	strPreset.Format(L"Preset%d",nPresetNum);

	CString Parameter=L"";
	PvString Name="";
	PvInt64 value=0;

	for (int i=0; i<4; i++)
	{
		switch (i)
		{
			case 0 : Parameter = L"BalanceRatio_R_"; break;
			case 1 : Parameter = L"BalanceRatio_Gr_"; break;
			case 2 : Parameter = L"BalanceRatio_B_"; break;
			case 3 : Parameter = L"BalanceRatio_Gb_"; break;
		}
		
		Name = PvString(Parameter+L"Once");
		CString Debug = Name.GetUnicode();
		StResult = m_pvDevice.GetGenParameters()->GetIntegerValue(Name, value);
		if (!StResult.IsOK())
		{
			m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
			return false;
		}
		Name = PvString(Parameter+strPreset);
		Debug = Name.GetUnicode();
		StResult = m_pvDevice.GetGenParameters()->SetIntegerValue(Name, value);
		if (!StResult.IsOK())
		{
			m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
			return false;
		}
	}
	
	return true;
}

bool CStCamGigE::OnUserSetSave()
{
	return OnExecuteCommand("UserSetSave");
}

UINT CStCamGigE::BufferThread(LPVOID param)
{
	CStCamGigE* pThis = reinterpret_cast<CStCamGigE*>(param);

	PvResult StResult;

	while(pThis->m_isAcquisition)
	{
		PvBuffer *lBuffer = NULL;
		PvResult  OperationResult;
		ResetEvent(pThis->m_hGrabDone);

		QueryPerformanceFrequency(&pThis->m_Freq);
		QueryPerformanceCounter(&pThis->m_Start);
		StResult = pThis->m_pvPipeline.RetrieveNextBuffer( & lBuffer, 0xFFFFFFFF, &OperationResult );
		if ( StResult.IsOK() )
		{ 
			if (OperationResult.IsOK())
			{
				if (pThis->m_nBpp == 8)
				{
					int size = lBuffer->GetImage()->GetImageSize();
					memcpy(pThis->m_pbyBuffer,(BYTE*)lBuffer->GetImage()->GetDataPointer(), lBuffer->GetImage()->GetImageSize());
					SetEvent(pThis->m_hGrabDone);
					QueryPerformanceCounter(&pThis->m_Stop);
					
					pThis->m_dTime = (double)(pThis->m_Stop.QuadPart - pThis->m_Start.QuadPart)/pThis->m_Freq.QuadPart*1000; 
				}
				else
				{
					PvPixelType lPixelTypeID = lBuffer->GetImage()->GetPixelType();
					PvBuffer outBuffer;
					PvPixelType aDestination = PvPixelWinRGB24;
					PvBufferConverter lBufferConverter;
					lBufferConverter.SetBayerFilter( PvBayerFilter3X3 );
					bool bConversionSupported = lBufferConverter.IsConversionSupported(lPixelTypeID,aDestination);
					if( bConversionSupported )
					{
						BYTE* pbyteBuffer = new BYTE[pThis->m_nWidth * pThis->m_nHeight * pThis->m_nBpp/8];
						outBuffer.GetImage()->Attach( pbyteBuffer, pThis->m_nWidth, pThis->m_nHeight, aDestination );
						PvResult lResult = lBufferConverter.Convert( lBuffer, &outBuffer, FALSE );
						if( lResult.IsOK() )
						{
							memcpy(pThis->m_pbyBuffer,(BYTE*)outBuffer.GetImage()->GetDataPointer(), outBuffer.GetImage()->GetImageSize());
							
							SetEvent(pThis->m_hGrabDone);
							QueryPerformanceCounter(&pThis->m_Stop);

							pThis->m_dTime = (double)(pThis->m_Stop.QuadPart - pThis->m_Start.QuadPart)/pThis->m_Freq.QuadPart*1000; 
						}
						outBuffer.GetImage()->Detach();
						delete [] pbyteBuffer;
						pbyteBuffer = NULL;
					}
				}
			}
			pThis->m_pvPipeline.ReleaseBuffer( lBuffer );
		}
	}

	SetEvent(pThis->m_hThTerminate);
	return 0;
}

bool CStCamGigE::GetValueString(char* pNodeName, CString &strValue)
{
	if (m_pvDevice.IsConnected() == false)
	{
		m_strErrorMsg = _T("Device is not connected.");
		return false;
	}

	PvResult StResult = PvResult::Code::NOT_CONNECTED;

	PvString NodeName(pNodeName);
	PvString value="";
	StResult = m_pvDevice.GetGenParameters()->GetString(NodeName, value);
	if (StResult.IsOK() == false)
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	strValue = (CString)value.GetUnicode();

	return true;
}
bool CStCamGigE::SetValueString(char* pNodeName, CString strValue)
{
	if (m_pvDevice.IsConnected() == false)
	{
		m_strErrorMsg = _T("Device is not connected.");
		return false;
	}

	PvResult StResult = PvResult::Code::NOT_CONNECTED;

	PvString NodeName(pNodeName);
	PvString value=strValue;
	
	StResult = m_pvDevice.GetGenParameters()->SetString(NodeName, value);
	if (StResult.IsOK() == false)
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	return true;
}
bool CStCamGigE::GetValueInt(char* pNodeName, int &nValue)
{
	if (m_pvDevice.IsConnected() == false)
	{
		m_strErrorMsg = _T("Device is not connected.");
		return false;
	}

	PvResult StResult = PvResult::Code::NOT_CONNECTED;

	PvString NodeName(pNodeName);
	PvInt64 value=0;
	StResult = m_pvDevice.GetGenParameters()->GetIntegerValue(NodeName, value);
	if (StResult.IsOK() == false)
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	nValue = (int)value;

	return true;
}
bool CStCamGigE::SetValueInt(char* pNodeName, int nValue)
{
	if (m_pvDevice.IsConnected() == false)
	{
		m_strErrorMsg = _T("Device is not connected.");
		return false;
	}

	PvResult StResult = PvResult::Code::NOT_CONNECTED;

	PvString NodeName(pNodeName);
	StResult = m_pvDevice.GetGenParameters()->SetIntegerValue(NodeName, nValue);
	if (StResult.IsOK() == false)
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	return true;
}
bool CStCamGigE::GetValueDouble(char* pNodeName, double &dValue)
{
	if (m_pvDevice.IsConnected() == false)
	{
		m_strErrorMsg = _T("Device is not connected.");
		return false;
	}

	PvResult StResult = PvResult::Code::NOT_CONNECTED;

	PvString NodeName(pNodeName);
	double value=0;
	StResult = m_pvDevice.GetGenParameters()->GetFloatValue(NodeName, value);
	if (StResult.IsOK() == false)
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	dValue = value;

	return true;
}
bool CStCamGigE::SetValueDouble(char* pNodeName, double dValue)
{
	if (m_pvDevice.IsConnected() == false)
	{
		m_strErrorMsg = _T("Device is not connected.");
		return false;
	}

	PvResult StResult = PvResult::Code::NOT_CONNECTED;

	PvString NodeName(pNodeName);
	StResult = m_pvDevice.GetGenParameters()->SetFloatValue(NodeName, dValue);
	if (StResult.IsOK() == false)
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	return true;
}
bool CStCamGigE::GetValueEnum(char* pNodeName, CString &strValue)
{
	if (m_pvDevice.IsConnected() == false)
	{
		m_strErrorMsg = _T("Device is not connected.");
		return false;
	}

	PvResult StResult = PvResult::Code::NOT_CONNECTED;

	PvString NodeName(pNodeName);
	PvString value="";
	StResult = m_pvDevice.GetGenParameters()->GetEnumValue("NodeName", value);
	if (StResult.IsOK() == false)
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	strValue = (CString)value.GetUnicode();

	return true;
}
bool CStCamGigE::SetValueEnum(char* pNodeName, CString strValue)
{
	if (m_pvDevice.IsConnected() == false)
	{
		m_strErrorMsg = _T("Device is not connected.");
		return false;
	}

	PvResult StResult = PvResult::Code::NOT_CONNECTED;

	PvString NodeName(pNodeName);
	PvString value=strValue;

	StResult = m_pvDevice.GetGenParameters()->SetEnumValue(NodeName, value);
	if (StResult.IsOK() == false)
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	return true;
}
bool CStCamGigE::OnExecuteCommand(char* pNodeName)
{
	if (m_pvDevice.IsConnected() == false)
	{
		m_strErrorMsg = _T("Device is not connected.");
		return false;
	}

	PvResult StResult = PvResult::Code::NOT_CONNECTED;

	PvString NodeName(pNodeName);
	StResult = m_pvDevice.GetGenParameters()->ExecuteCommand(NodeName);
	if (StResult.IsOK() == false)
	{
		m_strErrorMsg = (CString)StResult.GetCodeString().GetUnicode();
		return false;
	}

	return true;
}