
// ErFengMusicDlg.h: 头文件
//

#pragma once
#include <mmsystem.h>
#include <Digitalv.h>
#include<graphics.h>
#pragma comment(lib,"Winmm.lib")//在链接的时候


//int flag;
//CString m_pathname;
// CErFengMusicDlg 对话框
class CErFengMusicDlg : public CDialogEx
{
// 构造
public:
	CErFengMusicDlg(CWnd* pParent = nullptr);	// 标准构造函数

	int flag;//显示和隐藏
	CString m_pathname;//保存文件路径
	CFont textFont;//设置文本字体大小
	BOOL FLAG=TRUE;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ERFENGMUSIC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	MCIDEVICEID m_DeviceID;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slider;
	int m_nVolumn;
	

	afx_msg void OnBnClickedMini();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedClose2();
	
	afx_msg void OnStnClickedStaticMin();
	afx_msg void OnBnClickedBtnlist();
	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
