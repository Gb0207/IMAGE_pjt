﻿
// IMAGE_pjtDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "IMAGE_pjt.h"
#include "IMAGE_pjtDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CIMAGEpjtDlg 대화 상자



CIMAGEpjtDlg::CIMAGEpjtDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGE_PJT_DIALOG, pParent)
	, m_iX1(0)
	, m_iY1(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIMAGEpjtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ED_X, m_iX1);
	DDX_Text(pDX, IDC_ED_Y, m_iY1);
}

BEGIN_MESSAGE_MAP(CIMAGEpjtDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMAGE, &CIMAGEpjtDlg::OnBnClickedBtnImage)
	ON_BN_CLICKED(IDC_BTN_CREATE, &CIMAGEpjtDlg::OnBnClickedBtnCreate)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CIMAGEpjtDlg::OnBnClickedBtnLoad)
END_MESSAGE_MAP()


// CIMAGEpjtDlg 메시지 처리기

BOOL CIMAGEpjtDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CIMAGEpjtDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CIMAGEpjtDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CIMAGEpjtDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*함수이름: OnBnClickedBtnImage()
기능: 윈도우에서 image 선택 시 윈도우에 이미지를 생성하고 출력하는 이벤트함수
반환값: 없음*/
void CIMAGEpjtDlg::OnBnClickedBtnImage()
{
	int nWidth = 1200;
	int nHeight = 800;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}
	UpdataDisplay();
}



/*함수이름: OnBnClickedBtnCreate()
기능: 윈도우에서 create 선택 시 moveRect() 지정한 만큼 호출하는 이벤트 함수
반환값: 없음*/
void CIMAGEpjtDlg::OnBnClickedBtnCreate()
{
	int nConut = 101;
	for (int i = 0; i < nConut; i++) {
		moveRect();
		Save(i);
	}
}
/*함수이름: Save(int conut) 
기능: OnBnClickedBtnCreate()에서 호출하며, 해당하는 숫자에 해당 경로로 이미지 저장하는 함수
반환값: 없음*/
void CIMAGEpjtDlg::Save(int i) 
{
	switch (i)
	{
	case 10:
		m_image.Save(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save1.bmp"));
		break;
	case 20:
		m_image.Save(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save2.bmp"));
		break;
	case 30:
		m_image.Save(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save3.bmp"));
		break;
	case 40:
		m_image.Save(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save4.bmp"));
		break;
	case 50:
		m_image.Save(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save5.bmp"));
		break;
	case 60:
		m_image.Save(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save6.bmp"));
		break;
	case 70:
		m_image.Save(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save7.bmp"));
		break;
	case 80:
		m_image.Save(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save8.bmp"));
		break;
	case 90:
		m_image.Save(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save9.bmp"));
		break;
	case 100:
		m_image.Save(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save10.bmp"));
		break;
	default:
		break;
	}
}
/*함수이름: moveRect()
기능: 윈도우에 출력할 도형의 좌표 함수
반환값: 없음*/
void CIMAGEpjtDlg::moveRect()
{
	UpdateData(TRUE);
	static int nSttX = m_iX1;
	static int nSttY = m_iY1;

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0x00, nWidth*nHeight);

	for (int i = nSttX; i < nSttX+48; i++) {
		for (int j = nSttY; j < nSttY+64; j++) {
			Create(fm, nSttX, nSttY);
		}
	}
	nSttX++;
	nSttY++;
	UpdataDisplay();
}
/*함수이름: Create(unsigned char* fm, int x, int y)
기능: moveRect() 함수에서 호출되며 지정한 좌표의 반지름을 더해 도형을 만드는 함수
반환값: bool bRet*/
void CIMAGEpjtDlg::Create(unsigned char* fm, int x, int y)
{
	int nWhite = 255;
	int nRadius = 50;
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();

	for (int j = x;j < x + nRadius * 2; j++) {
		for (int i = y; i < y+ nRadius * 2; i++) {
			if (Circle(i, j, nCenterX, nCenterY, nRadius))
				fm[j*nPitch + i] = nWhite;
		}
	}
}
/*함수이름: Circle(int x, int y, int nCenterX, int nCenterY, int nRadius)
기능: Create() 함수에서 호출되며 사각형 도형에서 원형이 되도록 알려주는 함수 
반환값: bool bRet*/
bool CIMAGEpjtDlg::Circle(int x, int y, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = x - nCenterX;
	double dY = y - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius*nRadius) {
		bRet = true;
	}

	return bRet;
}



/*함수이름: OnBnClickedBtnLoad()
기능: 윈도우에서 load 선택 시 호출되는 이벤트 함수로 저장된 사진을 가져와 윈도우에 출력하고 원을 찾아 좌표를 콘솔에 출력하는 함수
반환값: 없음*/
void CIMAGEpjtDlg::OnBnClickedBtnLoad()
{
	if (m_image != NULL) {
		m_image.Destroy();
	}

	int nRandom = Random();
	Load(nRandom);

	UpdataDisplay();

	GetPoint();
}
/*함수이름: Random()
기능: OnBnClickedBtnLoad()에서 호출된 함수로 랜덤 숫자를 반환하는 함수
반환값: int nRandom*/
int CIMAGEpjtDlg::Random()
{
	srand((unsigned int)(time(NULL)));
	int nStart_num = 1, nEnd_num = 10;
	int nRandom_num = (rand() % (nEnd_num - nStart_num + 1)) + nStart_num;

	return nRandom_num;
}
/*함수이름: Load()
기능: OnBnClickedBtnLoad()에서 호출된 함수로 숫자를 받아 해당하는 숫자의 이미지 파일을 불러오는 함수
반환값: 없음*/
void CIMAGEpjtDlg::Load(int nRandom)
{
	switch (nRandom)
	{
	case 1:
		m_image.Load(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save1.bmp"));
		break;
	case 2:
		m_image.Load(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save2.bmp"));
		break;
	case 3:
		m_image.Load(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save3.bmp"));
		break;
	case 4:
		m_image.Load(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save4.bmp"));
		break;
	case 5:
		m_image.Load(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save5.bmp"));
		break;
	case 6:
		m_image.Load(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save6.bmp"));
		break;
	case 7:
		m_image.Load(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save7.bmp"));
		break;
	case 8:
		m_image.Load(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save8.bmp"));
		break;
	case 9:
		m_image.Load(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save9.bmp"));
		break;
	case 10:
		m_image.Load(_T("C:/Users/lms/Documents/test/IMAGE_pjt/Save_image/save10.bmp"));
		break;
	default:
		break;
	}
}
/*함수이름: GetPoint()
기능: OnBnClickedBtnLoad()에서 호출된 함수로 원의 좌표를 찾아 콘솔 창에 출력하는 함수
반환값: 없음*/
void CIMAGEpjtDlg::GetPoint()
{
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();

	int nLumiere = 10;
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	CRect rect(0, 0, nWidth, nHeight);
	for (int i = rect.top; i < rect.bottom; i++) {
		for (int j = rect.left; j < rect.right; j++) {
			if (fm[i*nPitch + j] > nLumiere) {
				nSumX += j;
				nSumY += i;
				nCount++;
			}
		}
	}
	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;

	std::cout << "불러온 원의 X : " << dCenterX << std::endl;
	std::cout << "불러온 원의 Y : " << dCenterY << std::endl;
}



/*함수이름: UpdataDisplay()
기능: 윈도우 이미지에 출력하는 함수
반환값: 없음*/
void CIMAGEpjtDlg::UpdataDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}