// ToolWnd.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "UserInterface.h"
#include "ToolWnd.h"
#include "MainFrm.h"
#include "ViewWnd.h"


#define	ID_TOOLWND_TEST	ID_TOOLWND + 1

// ToolWnd

IMPLEMENT_DYNAMIC(ToolWnd, CWnd)

ToolWnd::ToolWnd()
{

}

ToolWnd::~ToolWnd()
{
}


BEGIN_MESSAGE_MAP(ToolWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_TOOLWND_TEST, OnButtonTest)
END_MESSAGE_MAP()



// ToolWnd �޽��� ó�����Դϴ�.




int ToolWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	testButton.Create(_T("Test"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(10, 10, 100, 40),
		this, ID_TOOLWND_TEST);
	

	return 0;
}


void ToolWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	GetClientRect(ccclientRect);
}


BOOL ToolWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CWnd::OnEraseBkgnd(pDC);
}


void ToolWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	dc.FillSolidRect(ccclientRect, RGB(0,255,0));
}


void ToolWnd::OnButtonTest()
{
	CMainFrame * pFrame = (CMainFrame *) AfxGetApp()->m_pMainWnd;
	AfxMessageBox( pFrame -> viewWnd -> testString() );
}