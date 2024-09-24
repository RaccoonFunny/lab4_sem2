
// lab4Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "lab4.h"
#include "lab4Dlg.h"
#include "afxdialogex.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// Clab4Dlg dialog



Clab4Dlg::Clab4Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LAB4_DIALOG, pParent)
	, method(0)
	, result(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clab4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, method);
	//DDX_Text(pDX, IDC_EDIT1, accuracy);
	DDX_Text(pDX, IDC_EDIT2, result);
}

BEGIN_MESSAGE_MAP(Clab4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &Clab4Dlg::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT2, &Clab4Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &Clab4Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Clab4Dlg message handlers

BOOL Clab4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	CComboBox* comboBox = (CComboBox*)GetDlgItem(IDC_COMBO1);

	comboBox->AddString(_T("Метод равномерного поиска"));
	comboBox->AddString(_T("Метод половинного деления"));
	comboBox->AddString(_T("Метод золотого сечения"));
	
	comboBox->SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Clab4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Clab4Dlg::OnPaint()
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
HCURSOR Clab4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Clab4Dlg::OnCbnSelchangeCombo1()
{
}


void Clab4Dlg::OnEnChangeEdit2()
{

}
//Метод равномерного поиска

double func(double x) {
	return cos(6 * x) / (5 * pow(x, 2));
}
double dFunc(double x) {
	return (-1) * (6 * x * sin(6 * x) + 2 * cos(6 * x)) / (5 * pow(x, 3));
}

double Method(int M, double LowLimit, double HighLimit) {
	int n = 256;
	double lowest = 10000;
	std::vector<double> low;
	double a = LowLimit;
	double b = HighLimit;
	double x1 = 0;
	double x2 = 1000;
	double znach = 0;
	double step = 0.01;
	double i = a + step;
	double R1 = 0, R2 = 0, R3 = 0;
	double Fi = 1.6180339887;

	switch (M) {
	case 0:
		for (int i = 1;i <= n;i++) {
			double xi = func(i * ((b - a) / n));
			if (xi < lowest) {
				lowest = xi;
				znach = i * ((b - a) / n);
			}
			else {
				low.push_back(lowest);

			}

		}

		/*return low[1];*/
		return znach;
	case 1:
		while (i < b) {
			R1 = dFunc(i - step);
			R2 = dFunc(i);
			R3 = dFunc(i + step);
			if ((R1 > 0) && (R3 < 0) && (R2 >= (-1) * step * 10) && (R2 <= step * 10) && (R1 > R2) && (R3 < R2)) {
				low.push_back(i);
			}
			i += step;
		}
		if (low.size() > 1) {
			b = low[0];
		}
		while ((b - a) > 0.15) {
			x1 = (a + b) / 2 - 0.02;
			x2 = (a + b) / 2 + 0.02;
			if (func(x1) >= func(x2)) {
				a = x1;
			}
			else {
				b = x2;
			}
		}
		return (b + a) / 2;
	case 2:
		while (abs(b - a) > 0.0001) {
			x1 = b - (b - a) / (Fi - 0.5);
			x2 = a + (b - a) / (Fi - 0.5);
			if (func(x1) >= func(x2)) {
				a = x1;
			}
			else {
				b = x2;
			}
		}
		return (a + b) / 2;
	}
}


void Clab4Dlg::OnBnClickedButton1()
{
	UpdateData(1);
	result.Format(L"%f", Method(method, 1, 5));
	UpdateData(0);
}
