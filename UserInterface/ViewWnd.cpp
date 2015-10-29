// ViewWnd.cpp : 구현 파일입니다.
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



// ViewWnd 메시지 처리기입니다.


int ViewWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void ViewWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	GetClientRect(cclientRect);
}


BOOL ViewWnd::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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