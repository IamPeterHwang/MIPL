
// ChildView.h : interface of the CChildView class

#pragma once


// CChildView window

class CChildView : public CWnd
{
// Construction, constructor or initailizing function
public:
	CChildView();

// Attributes, member variable or Get/Set function
public:									// public -> anywhere access
	BITMAPINFO*			bitmapInfo;		// struct BITMAPINFO : BITMAPINFOHEADER bmiHeader and RGBQUAD bmiColors[1]

	unsigned char*		dibData;		// dibData : BITMAPINFOHEADER + RGBQUAD + DATA
	unsigned char*		srcData;		// source data
	unsigned char*		dstData;		// copy(destination) data

	int					samplePerPixel; // number of byte of using to express 1 pixel
	int					width;			// pixel
	int					height;			// pixel
	int					step;			// size of one row, byte

	int					GetRealWidth(int width);				// function : get step
	unsigned char		Clip(int value, int low, int high);		// function : below low -> low, above high -> high 

	void				GammaCorrection(double gamma);			// function : gamma correction

	CScrollBar			scrollBar;								// class CScrollBar : pertaining to scrollbar

	void				SpatialFilter3x3(double* mask);

	BOOL				leftButtonDown;
	CPoint				leftButtonPoint;

	BOOL				rightButtonDown;
	CPoint				rightButtonPoint;

	void				OpenBMPFile(CString path);
	void				OpenDICOMFile(CString path);

	BOOL				CreateDIB();

	CString				photometric;
	double				windowCenter, windowWidth;
	int					bitsAllocated, bitsStored, pixelRepresentation;

	void				Convert16to8(double windowCenter, double windowWidth);

// Operations, member function occuring activity
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

// Generated message map functions
protected:
		afx_msg void OnPaint();
	afx_msg int	OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
		DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTestTest();

	afx_msg void OnFileOpen();

	afx_msg void OnArithmeticAdd();
	afx_msg void OnArithmeticSub();
	afx_msg void OnArithmeticMultiply();
	afx_msg void OnArithmeticDivide();
	afx_msg void OnArithmeticNegative();
	afx_msg void OnArithmeticGamma();

	afx_msg void OnGeometricFlipV();
	afx_msg void OnGeometricFlipH();
	afx_msg void OnGeometricRotateLeft();
	afx_msg void OnGeometricRotateRight();

	afx_msg void OnLutAdd();
	afx_msg void OnLutSub();
	afx_msg void OnLutMultiply();
	afx_msg void OnLutDivide();
	afx_msg void OnLutNegative();
	afx_msg void OnLutGamma();
	afx_msg void OnUpdateLutAdd(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLutSub(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLutMultiply(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLutDivide(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLutNegative(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLutGamma(CCmdUI *pCmdUI);

	afx_msg void OnBlur();
	afx_msg void OnSharpen();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

