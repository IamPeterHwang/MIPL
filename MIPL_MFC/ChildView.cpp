
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MIPL_MFC.h"
#include "ChildView.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	dibData		= NULL; // constructor, initialize pointer to NULL
	dstData		= NULL;
}

CChildView::~CChildView()
{
	if(dibData)
		delete[] dibData; // destructor, remove allocated memory if program ends
	if(dstData)
		delete[] dstData;
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
		ON_WM_PAINT()
	
	ON_COMMAND(ID_TEST_TEST,					OnTestTest)
	ON_COMMAND(ID_FILE_OPEN,					OnFileOpen)
	ON_COMMAND(ID_ARITHMETIC_ADD,				OnArithmeticAdd)
	ON_COMMAND(ID_ARITHMETIC_SUB,				OnArithmeticSub)
	ON_COMMAND(ID_ARITHMETIC_MULTIPLY,			OnArithmeticMultiply)
	ON_COMMAND(ID_ARITHMETIC_DIVIDE,			OnArithmeticDivide)
	ON_COMMAND(ID_ARITHMETIC_NEGATIVE,			OnArithmeticNegative)
	ON_COMMAND(ID_ARITHMETIC_GAMMA,				OnArithmeticGamma)
	ON_COMMAND(ID_GEOMETRIC_FLIPV,				OnGeometricFlipV)
	ON_COMMAND(ID_GEOMETRIC_FLIPH,				OnGeometricFlipH)
	ON_COMMAND(ID_GEOMETRIC_ROTATELEFT,			OnGeometricRotateLeft)
	ON_COMMAND(ID_GEOMETRIC_ROTATERIGHT,		OnGeometricRotateRight)

END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if(dibData == NULL)
		return; // if dibData == NULL, end

	::SetDIBitsToDevice(dc.m_hDC,
		0, 0, width, height,
		0, 0, 0, height,
		dstData, bitmapInfo, DIB_RGB_COLORS); // print bmp file on screen 

	/*
	// filling color on whole screen
	CRect rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(0,0,255));
	*/

	/*
	// create quadrangle, then filling color
	CRect rect = CRect(0,0,100,100);
	dc.FillSolidRect(rect, RGB(0,0,255));
	*/

	// Do not call CWnd::OnPaint() for painting messages
}

void CChildView::OnTestTest()
{
	// show message
	AfxMessageBox(L"Hello World");
}

void CChildView::OnFileOpen()
{
	// show File Dialog Box
	CString szFilter = _T( "bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*|");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, szFilter, this );
	if(dlg.DoModal() == IDCANCEL)
		return;

	// read file
	FILE * file;
	_wfopen_s(&file, dlg.GetPathName(), L"rb");

	/* 
	_wfopen_s(&file, L"lena.bmp", L"rb");
	*/

	// declare struct BITMAPFILEHEADER variable, then connect file
	BITMAPFILEHEADER bitmapFileHeader;
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, file);

	// determine DIB size
	int dibSize = bitmapFileHeader.bfSize - sizeof(BITMAPFILEHEADER);

	// is dibData really zero? is memory empty?
	if (dibData)
		delete[] dibData;
	dibData = new unsigned char[dibSize]; // allocate memory as DIB size 

	fread(dibData, dibSize, 1, file);

	// important value
	bitmapInfo		= (BITMAPINFO*) dibData; // transform type, why?
	samplePerPixel	= bitmapInfo->bmiHeader.biBitCount / 8;
	width			= bitmapInfo->bmiHeader.biWidth;
	height			= bitmapInfo->bmiHeader.biHeight;
	step			= GetRealWidth(width);
	// dibData indicate first starting point of DIB structure, finally srcData indicate starting point of actual data
	srcData			= dibData + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * bitmapInfo->bmiHeader.biClrUsed;

	// copy data ¼±¾ð.
	if(dstData)
		delete[] dstData;
	dstData = new unsigned char[step*height];

	// copy srcdata to dstdata
	memcpy(dstData, srcData, step * height); // memmove has same function

	fclose(file); // disconnect between file and stream, otherwise stay put, with memory allocated 

	Invalidate(FALSE); // don't erase background

}

int CChildView::GetRealWidth(int width)  // get step 
{
	int real_width;
	div_t r;
	r = div(width,4);
	if(r.rem != 0) {
		real_width = ((r.quot + 1) * 4); // make multiple of 4, ex) in case to need 13 bytes, dump remainder, then quotient plus one and multiply 4, it is 4 multiple of 4 more than 13
		return real_width;
	}
	else
		return width;
}

unsigned char CChildView::Clip(int value, int low, int high) // clipping, below low -> low, above high -> high
{
	if(value < low)
		return (unsigned char) low;
	else if(value > high)
		return (unsigned char) high;
	else
		return (unsigned char) value;
}

void CChildView::OnArithmeticAdd() // pixel value + 100
{
	if( dibData == NULL )
		return;

	for( int i=0; i < width * height; i++) {
		dstData[i] = Clip(srcData[i] + 100, 0, 255);
	}

	Invalidate(FALSE);
}

void CChildView::OnArithmeticSub() // pixel value - 100
{
	if( dibData == NULL )
		return;

	for( int i=0; i < width * height; i++) {
		dstData[i] = Clip(srcData[i] - 100, 0, 255);
	}

	Invalidate(FALSE);

}

void CChildView::OnArithmeticMultiply() // pixel value * 5
{
	if( dibData == NULL )
		return;

	for( int i=0; i < width * height; i++){
		dstData[i] = Clip(srcData[i] * 5, 0, 255);
	}

	Invalidate(FALSE);

}

void CChildView::OnArithmeticDivide() // pixel value / 4
{
	if( dibData == NULL )
		return;

	for( int i=0; i < width * height; i++){
		dstData[i] = Clip(srcData[i] / 4, 0, 255);
	}

	Invalidate(FALSE);

}

void CChildView::OnArithmeticNegative() // reversal, 0 -> 255, 255 -> 0
{
	if( dibData == NULL )
		return;

	for( int i=0; i < width * height; i++){
		dstData[i] = 255 - srcData[i];
	}

	Invalidate(FALSE);

}

unsigned char CChildView::Clip_r(double value, double low, double high) // parameter is real
{
	if(value < low)
		return (unsigned char) low;
	else if(value > high)
		return (unsigned char) high;
	else
		return (unsigned char) value;
}

void CChildView::OnArithmeticGamma() // Gamma correction, because of hardware problem and etc, it appears convex, then must make 1st linear function  
{
	if( dibData == NULL )
		return;

	for( int i=0; i < width * height; i++) {
		dstData[i] = Clip_r(255*pow(srcData[i]/255.0,1.0/2.2), 0.0, 255.0);
	}

	Invalidate(FALSE);
}

void CChildView::OnGeometricFlipV() // flip vertically
{
	memset(dstData, 0, step * height);
	for(int i = 0 ; i < height ; i++)
	{
		memcpy(dstData + i*step, srcData + (height-1-i)*step, step);
	}

	Invalidate(FALSE);
}

void CChildView::OnGeometricFlipH() // flip horizontally
{
	memset(dstData, 0, step * height);
	for(int i = 0 ; i < height ;i++)
	{
		for(int j = 0 ; j < width ;j++)
		{
			dstData[(i*step) + j] = srcData[(i*step) + (width - 1 - j)];
			// *(dstData(i*step) + j) = *(srcData((i*step) + (width - 1 - j));
		}
	}

	Invalidate(FALSE);
}

void CChildView::OnGeometricRotateLeft() // Rotate Left
{
	memset(dstData, 0, step * height);
	for(int i = 0 ; i < height ; i++)
	{
		for(int j = 0 ; j < width ; j++)
		{
			dstData[(j*step) + (height - 1 - i)] = srcData[(i*step) + j];
		}
	}

	Invalidate(FALSE);
}

void CChildView::OnGeometricRotateRight() // Rotate Right
{
	memset(dstData, 0, step * height);
	for(int i = 0 ; i < height ; i++)
	{
		for(int j = 0 ; j < width ; j++)
		{
			dstData[(i*step) + j] = srcData[j*step + height - 1 - i];
		}
	}

	Invalidate(FALSE);
}