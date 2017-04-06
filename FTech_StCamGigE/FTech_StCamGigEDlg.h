
// FTech_StCamGigEDlg.h : header file
//

#pragma once
#include "StCamGigE.h"

using namespace SENTECH_GIGE;
// CFTech_StCamGigEDlg dialog
class CFTech_StCamGigEDlg : public CDialogEx
{
// Construction
public:
	CFTech_StCamGigEDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FTech_StCamGigE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
public :
	CStCamGigE m_Camera;
	CWinThread* m_pThDsp;
	bool m_bThDspWork;
	int m_nWidth;
	int m_nHeight;
	int m_nBpp;
	BITMAPINFO*	m_pBitmapInfo;
	BYTE* m_pBuffer;
	void OnDisplay();
	void CreateBmpInfo(int nWidth, int nHeight, int nBpp);
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnConnection();
	afx_msg void OnBnClickedBtnAcq();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRbtnCont();
	afx_msg void OnBnClickedRbtnSoft();
	afx_msg void OnBnClickedRbtnHard();
	afx_msg void OnBnClickedBtnEvent();
	afx_msg void OnBnClickedRBtnConnection(UINT ID);
	int m_nRBtnConnection;
};
