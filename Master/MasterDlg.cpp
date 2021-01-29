
// MasterDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "framework.h"
#include "Master.h"
#include "MasterDlg.h"
#include "afxdialogex.h"
#include "MyDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int Num = 0;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMasterDlg 对话框



CMasterDlg::CMasterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MASTER_DIALOG, pParent)
	, m_BaudRate(9600)
	, m_Velocity(_T(""))
	, m_Display(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_PointNum = 0;
	for (int k = 0; k < 200; k++)
	{
		m_Point[k].x = 20 + 3 * k;
	}
}

void CMasterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_DISPLAY, m_Display);
	DDX_Control(pDX, IDC_PORTNO, m_PortNo);
	DDX_Control(pDX, IDC_MSCOMM, m_myComm);
	DDX_Text(pDX, IDC_BAUDRATE, m_BaudRate);
	DDX_Text(pDX, IDC_VELOCITY, m_Velocity);
	DDX_Control(pDX, IDC_VELOCITYVALUE, m_VelocityValue);
	//  DDX_Text(pDX, IDC_DISPLAY, m_Display);
	DDX_Text(pDX, IDC_DISPLAY, m_Display);
}

BEGIN_MESSAGE_MAP(CMasterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENCOM, &CMasterDlg::OnBnClickedOpencom)
	ON_BN_CLICKED(IDC_CLOSECOM, &CMasterDlg::OnBnClickedClosecom)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_SET, &CMasterDlg::OnBnClickedSet)
	ON_BN_CLICKED(IDC_CLEAR, &CMasterDlg::OnBnClickedClear)
//	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMasterDlg 消息处理程序

BOOL CMasterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_PortNo.AddString(_T("COM1"));//组合框初始化
	m_PortNo.AddString(_T("COM2"));
	m_PortNo.AddString(_T("COM3"));
	m_PortNo.AddString(_T("COM4"));
	m_PortNo.AddString(_T("COM5"));
	m_PortNo.AddString(_T("COM6"));
	m_PortNo.AddString(_T("COM7"));
	m_PortNo.AddString(_T("COM8"));
	m_PortNo.SetCurSel(7);

	m_VelocityValue.SetScrollRange(0, 1000);
	m_VelocityValue.SetScrollPos(0);

	m_myComm.put__CommPort(1);//选择COM1
	m_myComm.put_InBufferSize(1024);//接收缓冲区
	m_myComm.put_OutBufferSize(1024);//发送缓冲区
	m_myComm.put_InputLen(0);//设置接收缓冲区数据长度为0，表示全部读取
	m_myComm.put_InputMode(1);//以二进制方式读写数据
	m_myComm.put_RThreshold(1);//接收缓冲区有1个以上字符时将引发接收数据的OnComm事件
	m_myComm.put_Settings(_T("9600,n,8,1"));//波特率9600，无校验，数据位8，停止位1

	SetWindowText(_T("永磁同步电机转速监控"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMasterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMasterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		dc.Rectangle(20, 20, 620, 320);

		for (int k = 0; k < 7; k++)
		{
			dc.MoveTo(20, 20 + 50 * k);
			dc.LineTo(620, 20 + 50 * k);
		}
		for (int k = 0; k < 13; k++)
		{
			dc.MoveTo(20 + 50 * k, 20);
			dc.LineTo(20 + 50 * k, 320);
		}

		CPen Pen;
		CPen* pOldPen = NULL;
		UpdateData(TRUE);
		Pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		pOldPen = dc.SelectObject(&Pen);
		dc.Polyline(m_Point, m_PointNum);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMasterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMasterDlg::OnBnClickedOpencom()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//打开串口
	int nPortNO = 0;

	//设置端口号
	nPortNO = m_PortNo.GetCurSel() + 1;
	m_myComm.put_CommPort(nPortNO);

	//设置波特率n:无校验 o:奇校验 e:偶校验
	CString szBaudRate;
	szBaudRate.Format(_T("%d, n, 8, 1"), m_BaudRate);
	m_myComm.put_Settings(szBaudRate);

	if (!m_myComm.get_PortOpen())//如果串口没有打开
	{
		m_myComm.put_PortOpen(TRUE);//打开串口
		AfxMessageBox(_T("串口打开成功！"));
	}
	Invalidate();
}


void CMasterDlg::OnBnClickedClosecom()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_myComm.get_PortOpen())
	{
		m_myComm.put_PortOpen(FALSE);
		AfxMessageBox(_T("串口关闭成功！"));
	}
	else
	{
		AfxMessageBox(_T("请打开串口！"));
	}
	Invalidate();
}
BEGIN_EVENTSINK_MAP(CMasterDlg, CDialogEx)
	ON_EVENT(CMasterDlg, IDC_MSCOMM, 1, CMasterDlg::OnOncommMscomm, VTS_NONE)
END_EVENTSINK_MAP()


void CMasterDlg::OnOncommMscomm()
{
	// TODO: 在此处添加消息处理程序代码
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	long len, k;
	BYTE rxdata[1024];//设置BYTE数组
	CString strtemp;
	double SampDate = 0.00;//原始数据
	int DisplayData = 0;//用于显示数据

	if (m_myComm.get_CommEvent() == 2) //值为2表示接收缓冲区内有字符
	{
		variant_inp = m_myComm.get_Input();//读取缓冲区
		safearray_inp = variant_inp;//变量转换
		len = safearray_inp.GetOneDimSize();//得到有效的数据长度
		for (k = 0; k < len; k++)
		{
			safearray_inp.GetElement(&k, rxdata + k);
		}	
		double Dou = 0.00;
		BYTE* p = (BYTE*)&Dou;//将数据转换为double,恢复采样时数据格式

		for (int k = 0; k < sizeof(double); k++)
		{
			*p++ = rxdata[k + 2];
		}

		SampDate = Dou;
		DisplayData = 170 - 50 * SampDate;

		if (m_PointNum < 200)
		{
			m_Point[m_PointNum].y = DisplayData;
			m_PointNum++;
			Num = -1 * (DisplayData / 50) + 3;
		}
		else
		{
			for (int k = 0; k < 199; k++)
			{
				m_Point[k].y = m_Point[k + 1].y;
			}
			m_Point[199].y = DisplayData;
			Num = -1 * (DisplayData / 50) + 3;
		}
		InvalidateRect(CRect(20, 20, 620, 320));
		for (k = 0; k < len; k++)//将数组转换为Cstring型变量    
		{
			BYTE bt = *(char*)(rxdata + k);//字符型      
			strtemp.Format(_T("%c"), bt); //将字符送入临时变量strtemp存放   
			m_Display += strtemp; //加入接收编辑框对应字符串    
			UpdateData(FALSE);
			m_Display = "";
		}
	}
}


void CMasterDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nSBCode)
	{
	case SB_THUMBTRACK:
		pScrollBar->SetScrollPos(nPos);
		break;
	case SB_LINELEFT:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() - 1);
		break;
	case SB_LINERIGHT:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() + 1);
		break;
	case SB_PAGELEFT:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() - 10);
		break;
	case SB_PAGERIGHT:
		pScrollBar->SetScrollPos(pScrollBar->GetScrollPos() + 10);
		break;
	}
	UpdateData(TRUE);
	CString Str_Velocity;
	Velocity = m_VelocityValue.GetScrollPos();
	Str_Velocity.Format(L"%d",Velocity);
	m_Velocity = Str_Velocity;
	UpdateData(FALSE);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);

}


void CMasterDlg::OnBnClickedSet()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_myComm.put_Output(COleVariant(m_Velocity));
}


void CMasterDlg::OnBnClickedClear()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_PointNum; i++)//删除所有数据
	{
		m_Point[i].y = 0;
	}
	m_PointNum = 0;//清空数据计数变量
	CRect rect(20, 20, 620, 320);
	InvalidateRect(&rect, TRUE);//强制刷新，需要重新输出,发送刷新消息
}

