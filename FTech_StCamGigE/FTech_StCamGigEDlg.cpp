
// FTech_StCamGigEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FTech_StCamGigE.h"
#include "FTech_StCamGigEDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT DisplayThread(LPVOID param)
{
	CFTech_StCamGigEDlg* pMain = (CFTech_StCamGigEDlg*)param;

	DWORD dwResult=0;
	while(pMain->m_bThDspWork)
	{
		Sleep(0);

		dwResult = WaitForSingleObject(pMain->m_Camera.GetHandleGrabDone(),1000);
		if (dwResult == WAIT_OBJECT_0)
			pMain->OnDisplay();
	}

	return 0;
}

// CFTech_StCamGigEDlg dialog
CFTech_StCamGigEDlg::CFTech_StCamGigEDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFTech_StCamGigEDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pThDsp	  = NULL;
	m_pBitmapInfo = NULL;
	m_nWidth	= 0;
	m_nHeight	= 0; 
	m_nBpp		= 0;
	m_pBuffer   = NULL;
}

void CFTech_StCamGigEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFTech_StCamGigEDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CONNECTION, &CFTech_StCamGigEDlg::OnBnClickedBtnConnection)
	ON_BN_CLICKED(IDC_BTN_ACQ, &CFTech_StCamGigEDlg::OnBnClickedBtnAcq)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_SAVE, &CFTech_StCamGigEDlg::OnBnClickedBtnSave)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RBTN_CONT, &CFTech_StCamGigEDlg::OnBnClickedRbtnCont)
	ON_BN_CLICKED(IDC_RBTN_SOFT, &CFTech_StCamGigEDlg::OnBnClickedRbtnSoft)
	ON_BN_CLICKED(IDC_RBTN_HARD, &CFTech_StCamGigEDlg::OnBnClickedRbtnHard)
	ON_BN_CLICKED(IDC_BTN_EVENT, &CFTech_StCamGigEDlg::OnBnClickedBtnEvent)
END_MESSAGE_MAP()

// CFTech_StCamGigEDlg message handlers

BOOL CFTech_StCamGigEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CheckDlgButton(IDC_RBTN_CONT, 1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFTech_StCamGigEDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFTech_StCamGigEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFTech_StCamGigEDlg::OnBnClickedBtnConnection()
{
	CString caption=L"";
	GetDlgItemText(IDC_BTN_CONNECTION,caption);

	if (caption == L"Connect")
	{
		if (m_Camera.IsConnected() == true) return;
		bool ret = m_Camera.OnConnect();
		if (ret == true)
		{
			m_nWidth  = m_Camera.GetWidth();
			m_nHeight = m_Camera.GetHeight();
			m_nBpp	  = m_Camera.GetBPP();

			m_pBuffer = new BYTE[m_nWidth*m_nHeight*m_nBpp/8];
			memset(m_pBuffer, 0, m_nWidth*m_nHeight*m_nBpp/8);

			CreateBmpInfo(m_nWidth, m_nHeight ,m_nBpp);
			CString model=L"";
			m_Camera.GetDeviceModelName(model);
			SetDlgItemText(IDC_LB_MODEL,model);
			GetDlgItem(IDC_BTN_ACQ)->EnableWindow(TRUE);
			SetDlgItemText(IDC_BTN_ACQ, L"Start");
			SetDlgItemText(IDC_BTN_CONNECTION, L"Disconnect");
		}
	}
	else
	{
		if (m_Camera.IsConnected() == false) return;

		if (m_pThDsp != NULL)
		{
			m_bThDspWork = false;
			DWORD dwResult = WaitForSingleObject(m_pThDsp->m_hThread, INFINITE);
			if (dwResult == WAIT_OBJECT_0)
				OutputDebugString(_T("Display thread is terminated.\n"));
		}

		m_Camera.OnDisconnect();

		SetDlgItemText(IDC_LB_MODEL,L"Disconnected");
		GetDlgItem(IDC_BTN_ACQ)->EnableWindow(FALSE);
		SetDlgItemText(IDC_BTN_CONNECTION, L"Connect");

		if (m_pBuffer != NULL)
		{
			delete []m_pBuffer;
			m_pBuffer = NULL;
		}
	}
}

void CFTech_StCamGigEDlg::OnBnClickedBtnAcq()
{
	CString caption=L"";
	GetDlgItemText(IDC_BTN_ACQ,caption);

	if (caption == L"Start")
	{
		SetTimer(100,30,NULL);
		
		m_Camera.OnStartAcquisition();
		GetDlgItem(IDC_BTN_SAVE)->EnableWindow(TRUE);
		SetDlgItemText(IDC_BTN_ACQ, L"Stop");

		m_bThDspWork = true;
		m_pThDsp = AfxBeginThread(DisplayThread, this);

		GetDlgItem(IDC_RBTN_CONT)->EnableWindow(FALSE);
		GetDlgItem(IDC_RBTN_SOFT)->EnableWindow(FALSE);
		GetDlgItem(IDC_RBTN_HARD)->EnableWindow(FALSE);
	}
	else
	{
		KillTimer(100);

		m_bThDspWork = false;
		DWORD dwResult=0;
		dwResult = WaitForSingleObject(m_pThDsp->m_hThread, INFINITE);
		if (dwResult == WAIT_OBJECT_0)
			OutputDebugString(_T("Display thread is terminated.\n"));
		
		m_Camera.OnStopAcquisition();

		SetDlgItemText(IDC_BTN_ACQ, L"Start");

		GetDlgItem(IDC_RBTN_CONT)->EnableWindow(TRUE);
		GetDlgItem(IDC_RBTN_SOFT)->EnableWindow(TRUE);
		GetDlgItem(IDC_RBTN_HARD)->EnableWindow(TRUE);
	}
}

void CFTech_StCamGigEDlg::CreateBmpInfo(int nWidth, int nHeight, int nBpp)
{
	if (m_pBitmapInfo != NULL) 
	{
		delete []m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}

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

void CFTech_StCamGigEDlg::OnDisplay()
{
	CClientDC dc(GetDlgItem(IDC_PC_CAMERA));
	CRect rect;
	GetDlgItem(IDC_PC_CAMERA)->GetClientRect(&rect);

	dc.SetStretchBltMode(COLORONCOLOR); 

	BYTE *pBuffer = m_Camera.GetImageBuffer();
	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, m_nWidth, m_nHeight, pBuffer, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

void CFTech_StCamGigEDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(100);

	if (m_pThDsp != NULL)
	{
		m_bThDspWork = false;

		DWORD dwResult=0;
		dwResult = WaitForSingleObject(m_pThDsp->m_hThread, INFINITE);
		if (dwResult == WAIT_OBJECT_0)
			OutputDebugString(_T("Display thread is terminated.\n"));
	}

	if (m_Camera.IsConnected() == true)
	{
		if (m_Camera.IsActive() == true)
			m_Camera.OnStopAcquisition();

		m_Camera.OnDisconnect();
	}

	if (m_pBuffer != NULL)
	{
		delete []m_pBuffer;
		m_pBuffer = NULL;
	}

	if (m_pBitmapInfo != NULL)
	{
		delete []m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}
}


void CFTech_StCamGigEDlg::OnBnClickedBtnSave()
{
	if (m_Camera.IsConnected() == false) return;
	CString	strFilter = _T("All Files (*.*)|*.*||");

	CFileDialog FileDlg(FALSE, _T(".bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter);

	if( FileDlg.DoModal() == IDOK )
	{
		m_Camera.OnSaveImage(FileDlg.GetPathName());
	}
}

void CFTech_StCamGigEDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 100)
	{
		double t = m_Camera.GetGrabTime();
		CString tmp;
		tmp.Format(L"%.2f ms", t);
		SetDlgItemText(IDC_LB_TIME, tmp);
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CFTech_StCamGigEDlg::OnBnClickedRbtnCont()
{
	if (m_Camera.IsConnected() == false) return;

	m_Camera.SetContinuousMode();

	GetDlgItem(IDC_BTN_EVENT)->EnableWindow(FALSE);
}


void CFTech_StCamGigEDlg::OnBnClickedRbtnSoft()
{
	if (m_Camera.IsConnected() == false) return;

	m_Camera.SetSoftTriggerMode();

	GetDlgItem(IDC_BTN_EVENT)->EnableWindow(TRUE);
}


void CFTech_StCamGigEDlg::OnBnClickedRbtnHard()
{
	if (m_Camera.IsConnected() == false) return;

	m_Camera.SetHardTriggerMode();

	GetDlgItem(IDC_BTN_EVENT)->EnableWindow(FALSE);
}


void CFTech_StCamGigEDlg::OnBnClickedBtnEvent()
{
	if (m_Camera.IsConnected() == false) return;

	m_Camera.OnTriggerEvent();
}
