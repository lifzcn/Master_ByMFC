
// MasterDlg.h: 头文件
//

#pragma once
#include "mscomm.h"
#include "MyDLL.h"

// CMasterDlg 对话框
class CMasterDlg : public CDialogEx
{
// 构造
public:
	CMasterDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MASTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpencom();
	afx_msg void OnBnClickedClosecom();
	afx_msg void OnBnClickedSet();
	CComboBox m_PortNo;
	CMscomm m_myComm;
	int m_BaudRate;
	DECLARE_EVENTSINK_MAP()
	void OnOncommMscomm();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CString m_Velocity;
	int Velocity;
	CScrollBar m_VelocityValue;
	CPoint m_Point[200];
	int m_PointNum;
	afx_msg void OnBnClickedClear();
	CString m_Display;
};
