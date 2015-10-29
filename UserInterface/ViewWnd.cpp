// ViewWnd.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "UserInterface.h"
#include "ViewWnd.h"


// ViewWnd

IMPLEMENT_DYNAMIC(ViewWnd, CWnd)

ViewWnd::ViewWnd()
{

}

ViewWnd::~ViewWnd()
{
}


BEGIN_MESSAGE_MAP(ViewWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// ViewWnd �޽��� ó�����Դϴ�.


int ViewWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return 0;
}


void ViewWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	GetClientRect(cclientRect);
}


BOOL ViewWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CWnd::OnEraseBkgnd(pDC);
}


void ViewWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	dc.FillSolidRect(cclientRect, RGB(255,0,0));
}


CString ViewWnd::testString()
{
	return (_T("success"));
}