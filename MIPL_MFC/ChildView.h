
// ChildView.h : interface of the CChildView class

#pragma once


// CChildView window

class CChildView : public CWnd
{
// Construction : constructor or initailizing function
public:
	CChildView();

// Attributes : member variable or Get/Set function
public:									// public -> anywhere access
	BITMAPINFO*			bitmapInfo;		// struct BITMAPINFO : BITMAPINFOHEADER bmiHeader and RGBQUAD bmiColors[1]

	unsigned char*		dibData;		// dibData : BITMAPINFOHEADER + RGBQUAD + DATA
	unsigned char*		dibImage;

	unsigned char*		srcData;		// source data
	unsigned char*		dstData;		// copy(destination) data

	int					samplePerPixel; // number of byte of using to express 1 pixel
	int					width;			// pixel
	int					height;			// pixel
	int					srcStep;		// size of one row, byte
	int					dibStep;
	int					bitsAllocated, bitsStored, pixelRepresentation;
	double				windowCenter, windowWidth, windowCenterTemp, windowWidthTemp;
	KD_PHOTOMETRIC		photometric;


	int					GetRealWidth(int width);				// function : get step
	unsigned char		Clip(int value, int low, int high);		// function : below low -> low, above high -> high 

	void				SpatialFilter3x3(double* mask);

	BOOL				rightButtonDown;
	CPoint				rightButtonPoint;

	void				OpenBMPFile(CString path);
	void				OpenDICOMFile(CString path);

	BOOL				CreateDIB();	

	void				Convert16to8();

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
		DECLARE_MESSAGE_MAP()

public:
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

	afx_msg void OnBlur();
	afx_msg void OnSharpen();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

};

