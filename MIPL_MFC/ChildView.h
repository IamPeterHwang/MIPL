
// ChildView.h : interface of the CChildView class
//


#pragma once


// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	// public -> anywhere access
	// struct BITMAPINFO : BITMAPINFOHEADER bmiHeader and RGBQUAD bmiColors[1]
	BITMAPINFO*			bitmapInfo;

	// dibData : BITMAPINFOHEADER + RGBQUAD + DATA
	unsigned char*		dibData;
	unsigned char*		srcData; // source data
	unsigned char*		dstData; // copy(destination) data

	int					samplePerPixel; // number of byte of using to express 1 pixel
	int					width; // pixel
	int					height; // pixel
	int					step; // size of one row, byte

	int					GetRealWidth(int width); // get step
	unsigned char		Clip(int value, int low, int high); // below low -> low, above high -> high 
	unsigned char		Clip_r(double value, double low, double high);

// Operations
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
};

