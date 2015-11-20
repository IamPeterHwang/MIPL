#pragma once

class Caption3D;
// ViewWnd

class ViewWnd : public CWnd
{
	DECLARE_DYNAMIC(ViewWnd)

public:
	ViewWnd();
	virtual ~ViewWnd();

public:
	CRect		cclientRect;
	CString		testString();
	Caption3D *	caption3d;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
};


