
// ErFengMusicDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ErFengMusic.h"
#include "ErFengMusicDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CErFengMusicDlg 对话框



CErFengMusicDlg::CErFengMusicDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ERFENGMUSIC_DIALOG, pParent)
	, m_nVolumn(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_DeviceID = 0;
}

void CErFengMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Text(pDX, IDC_EDIT1, m_nVolumn);
}

BEGIN_MESSAGE_MAP(CErFengMusicDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CErFengMusicDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_PLAY, &CErFengMusicDlg::OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CErFengMusicDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_STOP, &CErFengMusicDlg::OnBnClickedBtnStop)
	ON_WM_DROPFILES()
	ON_WM_NCHITTEST()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CErFengMusicDlg::OnCustomdrawSlider1)
	ON_BN_CLICKED(IDC_MINI, &CErFengMusicDlg::OnBnClickedMini)
	ON_BN_CLICKED(IDC_ClOSE, &CErFengMusicDlg::OnBnClickedClose)
	
	ON_BN_CLICKED(IDC_BTNLIST, &CErFengMusicDlg::OnBnClickedBtnlist)
	
	
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CErFengMusicDlg 消息处理程序

BOOL CErFengMusicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//SetWindowPos(NULL, 0, 0, 345, 370, SWP_NOMOVE);
	SetWindowPos(NULL, 0, 0, 617, 370, SWP_NOMOVE);
	textFont.CreatePointFont(170, L"华文新魏");//控件1
	GetDlgItem(IDC_EDIT)->SetFont(&textFont);

	m_slider.SetRange(0, 100);
	m_slider.SetPos(100);
	m_nVolumn = 100;
	
	

	UpdateData(FALSE);//将变量里面的值设置到控件中显示出来，TRUE：控件里面的值设置的变量中

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CErFengMusicDlg::OnPaint()
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
		//获取客户端的宽度
		CRect rect;
		GetClientRect(&rect);

		//绘制标题栏
		CRect captionRect = rect;
		captionRect.bottom = 40;
		dc.FillSolidRect(&captionRect,RGB(225,212,170));

		//输出昵称
		CFont font;
		font.CreatePointFont(125,L"华文新魏");
		dc.SelectObject(&font);
		dc.SetTextColor(RGB(255,255,255));
		dc.TextOut(45,10,L"二峰音乐馆");

		DrawIconEx(dc.m_hDC, 0, 0, m_hIcon, 0, 0, 0, NULL, DI_IMAGE|DI_MASK);

		//加载一张图片
		CBitmap bmp;	
		bmp.LoadBitmapW(IDB_MAIN_BG);	

		//获取图片大小
		BITMAP logBmp;
		
		bmp.GetBitmap(&logBmp);
	
	
		//创建内存DC
		CDC memDC;
		
		memDC.CreateCompatibleDC(&dc);
		memDC.SelectObject(&bmp);
	
		
		//绘制到界面上面
		//dc.BitBlt(0, 0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY );
		dc.SetStretchBltMode(HALFTONE);
		dc.StretchBlt(0,40,rect.Width(),rect.Height(),&memDC,0,0,logBmp.bmWidth,logBmp.bmHeight,SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CErFengMusicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//打开
void CErFengMusicDlg::OnBnClickedButton1()
{
	//过滤音频文件
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|
		OFN_OVERWRITEPROMPT,
		L"MP3音频文件(*.mp3)|*.mp3|AVI种子文件(*.avi)|*.avi|WAV音频文件(*.wav)|*.wav|所有文件(*.*)|*.*||");
	
	//dlg.DoModal();
	//弹出对话框
	if (IDCANCEL==dlg.DoModal()) {
		return;
	}

	//获取音频文件路径
	CString strMusicFilePath = dlg.GetPathName();
	m_pathname = strMusicFilePath;

	//关闭当前正在播放的歌曲  --多媒体设备接口
	mciSendCommand(m_DeviceID,MCI_CLOSE,0,0);

	//打开音乐
	MCI_ANIM_OPEN_PARMS mciOpenParms;
	
	mciOpenParms.lpstrElementName = strMusicFilePath;

	GetDlgItem(IDC_EDIT)->SetWindowText(mciOpenParms.lpstrElementName);
	

	UpdateData(false);

	MCIERROR mciError= mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT,
		(DWORD)&mciOpenParms);

	if (mciError) {
		wchar_t szErrorMsg[256];
		mciGetErrorString(mciError, szErrorMsg, 256);
		AfxMessageBox(szErrorMsg);
		return;
	}

	m_DeviceID = mciOpenParms.wDeviceID;//当前歌曲的ID
}

//播放
void CErFengMusicDlg::OnBnClickedBtnPlay()
{
	MCI_PLAY_PARMS mciPlayParms;
	mciPlayParms.dwCallback = NULL;
	mciPlayParms.dwFrom = 0;//从头开始播放
	//发送播放的命令
	mciSendCommand(m_DeviceID,MCI_PLAY,MCI_FROM | MCI_NOTIFY,(DWORD)
	&mciPlayParms);
}

//暂停，继续
void CErFengMusicDlg::OnBnClickedBtnPause()
{
	//获取按钮上面的文字
	CString str;
	GetDlgItemText(IDC_BTN_PAUSE,str);
	
	if (str == L"暂停") {
		//发送暂停的命令
		mciSendCommand(m_DeviceID, MCI_PAUSE, 0, 0);
		SetDlgItemText(IDC_BTN_PAUSE, L"继续");
	}
	else if (str == L"继续") {
		mciSendCommand(m_DeviceID, MCI_RESUME, 0, 0);
		SetDlgItemText(IDC_BTN_PAUSE, L"暂停");
	}
}

//停止
void CErFengMusicDlg::OnBnClickedBtnStop()
{
	mciSendCommand(m_DeviceID,MCI_STOP,0,0);
	mciSendCommand(m_DeviceID,MCI_CLOSE,0,0);
	
}


void CErFengMusicDlg::OnDropFiles(HDROP hDropInfo)
{
	//获取拖拽的文件的路径
	wchar_t szMusicPath[MAX_PATH];
	DragQueryFile(hDropInfo, 0,szMusicPath, MAX_PATH);

	//MessageBox(szMusicPath);
	//关闭当前正在播放的歌曲  --多媒体设备接口
	mciSendCommand(m_DeviceID, MCI_CLOSE, 0, 0);

	//打开音乐
	MCI_ANIM_OPEN_PARMS mciOpenParms;
	mciOpenParms.lpstrElementName = szMusicPath;
	
	GetDlgItem(IDC_EDIT)->SetWindowText(mciOpenParms.lpstrElementName);
	
	
	UpdateData(FALSE);

	MCIERROR mciError = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT,
		(DWORD)&mciOpenParms);

	if (mciError) {
		wchar_t szErrorMsg[256];
		mciGetErrorString(mciError, szErrorMsg, 256);
		AfxMessageBox(szErrorMsg);
		return;
	}

	m_DeviceID = mciOpenParms.wDeviceID;//当前歌曲的ID
	//播放
	OnBnClickedBtnPlay();

	CDialogEx::OnDropFiles(hDropInfo);
}


LRESULT CErFengMusicDlg::OnNcHitTest(CPoint point)
{
	UINT uHitTest = CDialogEx::OnNcHitTest(point);
	if (uHitTest == HTCLIENT) {
		uHitTest = HTCAPTION;
	}

	return  uHitTest;
}
/*
	MFC(图形窗口)，MCI(多媒体设备接口)，GDI(绘图技术)，MSDN(微软官方手册)
*/

void CErFengMusicDlg::OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	MCI_DGV_SETAUDIO_PARMS mciSetVolumn;
	mciSetVolumn.dwCallback = NULL;
	mciSetVolumn.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciSetVolumn.dwValue = m_slider.GetPos();//音量的大小

	mciSendCommand(m_DeviceID,MCI_SETAUDIO,MCI_DGV_SETAUDIO_VALUE|
		MCI_DGV_SETAUDIO_ITEM,(DWORD)&mciSetVolumn);

	m_nVolumn = m_slider.GetPos();
	UpdateData(FALSE);
	*pResult = 0;
}



void CErFengMusicDlg::OnBnClickedMini()
{
	// TODO: 在此添加控件通知处理程序代码
	PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
}


void CErFengMusicDlg::OnBnClickedClose()
{
	// TODO: 在此添加控件通知处理程序代码
	PostMessage(WM_CLOSE);
}




void CErFengMusicDlg::OnBnClickedBtnlist()
{
	// TODO: 在此添加控件通知处理程序代码

	flag = !flag;
	if (flag) {
		SetWindowPos(NULL, 0, 0, 345, 370, SWP_NOMOVE);
		SetDlgItemText(IDC_BTNLIST, L"隐藏<-");
	}
	else {
		//617,370
		SetWindowPos(NULL, 0, 0, 617, 370, SWP_NOMOVE);
		SetDlgItemText(IDC_BTNLIST, L"显示->");
	}
}









void CErFengMusicDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC buttonDC;
	CBitmap bitmapTrans;
	BITMAP bmp;
	CDC mem;
	CRect rc;
	buttonDC.Attach(lpDrawItemStruct->hDC);//得到用于绘制按钮的DC
	mem.CreateCompatibleDC(&buttonDC);//准备向按钮区域传输图形    

	if (lpDrawItemStruct->CtlID == IDC_ClOSE) {
		rc = lpDrawItemStruct->rcItem;//获取按钮所占的矩形大小
		UINT state = lpDrawItemStruct->itemState;//获取按钮当前的状态，不同状态绘制不同的按钮    
		if (state & ODS_FOCUS)//如果按钮已经取得焦点，绘制选中状态下的按钮
		{
			bitmapTrans.LoadBitmap(IDB_BITMAP7);
			bitmapTrans.GetBitmap(&bmp);
			CBitmap * old = mem.SelectObject(&bitmapTrans);
			//向按钮传输位图，使用stretcnblt可以使图片随按钮大小而改变
			buttonDC.StretchBlt(rc.left, rc.top, rc.right, rc.bottom, &mem, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
			mem.SelectObject(old);
			bitmapTrans.DeleteObject();
		}
		else {
			bitmapTrans.LoadBitmap(IDB_BITMAP4);
			CBitmap *old2 = mem.SelectObject(&bitmapTrans);
			bitmapTrans.GetBitmap(&bmp);
			CBitmap *old = mem.SelectObject(&bitmapTrans);
			buttonDC.StretchBlt(rc.left, rc.top, rc.right, rc.bottom, &mem, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
			mem.SelectObject(old2);
			bitmapTrans.DeleteObject();
		}
	}



	if (lpDrawItemStruct->CtlID == IDC_MINI) {
		rc = lpDrawItemStruct->rcItem;//获取按钮所占的矩形大小
		UINT state = lpDrawItemStruct->itemState;//获取按钮当前的状态，不同状态绘制不同的按钮    
		if (state & ODS_FOCUS)//如果按钮已经取得焦点，绘制选中状态下的按钮
		{
			bitmapTrans.LoadBitmap(IDB_BITMAP1);
			bitmapTrans.GetBitmap(&bmp);
			CBitmap * old = mem.SelectObject(&bitmapTrans);
			//向按钮传输位图，使用stretcnblt可以使图片随按钮大小而改变
			buttonDC.StretchBlt(rc.left, rc.top, rc.right, rc.bottom, &mem, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
			mem.SelectObject(old);
			bitmapTrans.DeleteObject();
		}
		else {
			bitmapTrans.LoadBitmap(IDB_BITMAP3);
			CBitmap *old2 = mem.SelectObject(&bitmapTrans);
			bitmapTrans.GetBitmap(&bmp);
			CBitmap *old = mem.SelectObject(&bitmapTrans);
			buttonDC.StretchBlt(rc.left, rc.top, rc.right, rc.bottom, &mem, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
			mem.SelectObject(old2);
			bitmapTrans.DeleteObject();
		}
	}

	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
