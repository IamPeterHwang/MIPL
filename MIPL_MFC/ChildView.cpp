// ChildView.cpp : implementation of the CChildView class

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
	dibData		= NULL;		// constructor, initialize pointer to NULL
	dstData		= NULL;

	leftButtonDown = NULL;
	rightButtonDown = NULL;
}

CChildView::~CChildView()
{
	if(dibData)
		delete[] dibData;	// destructor, remove allocated memory if program ends
	if(dstData)
		delete[] dstData;
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
		ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	ON_COMMAND(ID_TEST_TEST,						OnTestTest)
	ON_COMMAND(ID_FILE_OPEN,						OnFileOpen)
	ON_COMMAND(ID_ARITHMETIC_ADD,					OnArithmeticAdd)
	ON_COMMAND(ID_ARITHMETIC_SUB,					OnArithmeticSub)
	ON_COMMAND(ID_ARITHMETIC_MULTIPLY,				OnArithmeticMultiply)
	ON_COMMAND(ID_ARITHMETIC_DIVIDE,				OnArithmeticDivide)
	ON_COMMAND(ID_ARITHMETIC_NEGATIVE,				OnArithmeticNegative)
	ON_COMMAND(ID_ARITHMETIC_GAMMA,					OnArithmeticGamma)
	ON_COMMAND(ID_GEOMETRIC_FLIPV,					OnGeometricFlipV)
	ON_COMMAND(ID_GEOMETRIC_FLIPH,					OnGeometricFlipH)
	ON_COMMAND(ID_GEOMETRIC_ROTATELEFT,				OnGeometricRotateLeft)
	ON_COMMAND(ID_GEOMETRIC_ROTATERIGHT,			OnGeometricRotateRight)
	ON_COMMAND(ID_LUT_ADD,							OnLutAdd)
	ON_COMMAND(ID_LUT_SUB,							OnLutSub)
	ON_COMMAND(ID_LUT_MULTIPLY,						OnLutMultiply)
	ON_COMMAND(ID_LUT_DIVIDE,						OnLutDivide)
	ON_COMMAND(ID_LUT_NEGATIVE,						OnLutNegative)
	ON_COMMAND(ID_LUT_GAMMA,						OnLutGamma)
	ON_COMMAND(ID_FILTER_BLUR,						OnBlur)
	ON_COMMAND(ID_FILTER_SHARPEN,					OnSharpen)
	ON_UPDATE_COMMAND_UI(ID_LUT_ADD,				OnUpdateLutAdd)
	ON_UPDATE_COMMAND_UI(ID_LUT_SUB,				OnUpdateLutSub)
	ON_UPDATE_COMMAND_UI(ID_LUT_MULTIPLY,			OnUpdateLutMultiply)
	ON_UPDATE_COMMAND_UI(ID_LUT_DIVIDE,				OnUpdateLutDivide)
	ON_UPDATE_COMMAND_UI(ID_LUT_NEGATIVE,			OnUpdateLutNegative)
	ON_UPDATE_COMMAND_UI(ID_LUT_GAMMA,				OnUpdateLutGamma)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
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

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	scrollBar.Create(SBS_HORZ | WS_VISIBLE | WS_CHILD, CRect(0, 520, 520, 540),
		this, 9999);						// SBS_HORZ: type of scrollbar, CRect(left, top, right, bottom), 9999: scrollbar id
	scrollBar.SetScrollRange(-100, 200);	// Scrollbar total range, far left = -100, far right = 200
	scrollBar.SetScrollPos(0);				// Scrollbox(thumb) starting position

	return 0;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this);						// device context for painting

	if(dibData == NULL)
		return;								// if dibData == NULL, end

	
	::SetDIBitsToDevice(dc.m_hDC,
		0, 0, width, height,					// Destination
		0, 0, 0, height,						// Source
		dstData, bitmapInfo, DIB_RGB_COLORS);	// print bmp file on screen, that is, draw image

	
	CString str;
	double GammaValue = 1 + scrollBar.GetScrollPos() / 100.;
	str.Format(_T("Gamma = %f"), GammaValue);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 0, 0));

	
	CFont font;
	CFont* pfont;
	font.CreateFont(20, 10, 0, 0, FW_BOLD, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));
	pfont = dc.SelectObject(&font);

	dc.TextOut(365, 450, str, 12);
	
	dc.SelectObject(pfont);
	font.DeleteObject();
	
	
	CPen	Pen;
	CPen*	poldPen;
	Pen.CreatePen(PS_SOLID, 3, RGB(0, 200, 255));
	poldPen = dc.SelectObject(&Pen);

	CBrush	Brush;
	CBrush*	poldBrush;
	Brush.CreateSolidBrush(RGB(0, 0, 255));
	poldBrush = dc.SelectObject(&Brush);

	{
		dc.MoveTo(520, 10);
		dc.LineTo(550, 50);

		dc.Rectangle(520, 60, 550, 100);
		dc.Ellipse(520, 110, 550, 150);
		dc.RoundRect(520, 160, 550, 200, 10, 20);
		dc.Pie(520, 210, 550, 250, 520, 210, 550, 230);
	}
	
	dc.SelectObject(poldBrush);
	Brush.DeleteObject();

	dc.SelectObject(poldPen);
	Pen.DeleteObject();

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
	AfxMessageBox(L"Test Word is Hello World");
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

	// declare dib data pointer variable
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

	// declare dst data pointer variable 
	if(dstData)
		delete[] dstData;
	dstData = new unsigned char[step*height];

	// copy srcdata to dstdata
	memcpy(dstData, srcData, step * height); // memmove has same function

	// disconnect between file and stream, otherwise stay put, with memory allocated 
	fclose(file);

	// As soon as file is opend, synchronize scrollbox, then operate gammacorrection
	switch (scrollBar.GetScrollPos())
	{
		case 0:
			break;

		default:
			double gamma = 1 + scrollBar.GetScrollPos() / (double)100;
			GammaCorrection( gamma );
			break;
	}
	
	Invalidate(FALSE); // don't erase background

}

int CChildView::GetRealWidth(int width)  // get step 
{
	int real_width;
	div_t r;
	r = div(width,4);
	if(r.rem != 0) 
	{
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

void CChildView::OnArithmeticAdd() // pixel value + 50
{
	if( dibData == NULL )
		return;

	for( int i=0; i < width * height; i++) 
	{
		dstData[i] = Clip(srcData[i] + 50, 0, 255);
	}

	Invalidate(FALSE);
}

void CChildView::OnArithmeticSub() // pixel value - 50
{
	if( dibData == NULL )
		return;

	for( int i=0; i < width * height; i++) 
	{
		dstData[i] = Clip(srcData[i] - 50, 0, 255);
	}

	Invalidate(FALSE);

}

void CChildView::OnArithmeticMultiply() // pixel value * 5
{
	if( dibData == NULL )
		return;

	for( int i=0; i < width * height; i++)
	{
		dstData[i] = Clip(srcData[i] * 5, 0, 255);
	}

	Invalidate(FALSE);

}

void CChildView::OnArithmeticDivide() // pixel value / 4
{
	if( dibData == NULL )
		return;

	for( int i=0; i < width * height; i++)
	{
		dstData[i] = Clip(srcData[i] / 4, 0, 255);
	}

	Invalidate(FALSE);

}

void CChildView::OnArithmeticNegative() // reversal, 0 -> 255, 255 -> 0
{
	if( dibData == NULL )
		return;

	for( int i=0; i < width * height; i++)
	{
		dstData[i] = 255 - srcData[i];
	}

	Invalidate(FALSE);

}

void CChildView::OnArithmeticGamma() // Gamma correction, because of hardware problem and etc, it appears convex, then must make 1st linear function  
{
	if( dibData == NULL )
		return;

	for( int i=0; i < width * height; i++) 
	{
		dstData[i] = Clip((int)(255 * pow(srcData[i] / (double)255, 1 / 2.2)), 0, 255);
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
			// *(dstData(j*step + (height - 1 - i)) = *(srcData(i*step + j);
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
			// *(dstData(i*step + j)) = *(srcData(j*step + (height - 1 - i)));
		}
	}

	Invalidate(FALSE);
}

void CChildView::OnLutAdd()				// create Add lut		
{
	unsigned char lut[256];				// declare lut array, size of array is 256, because of 8 bit
	
	for(int i = 0; i < 256; i++)
		lut[i] = Clip(i + 50, 0, 255);

	for(int i = 0; i < width * height; i++)
		dstData[i] = lut[ srcData[i] ];

	Invalidate(FALSE);
}


void CChildView::OnUpdateLutAdd(CCmdUI *pCmdUI)
{
	if( dibData == NULL)
		pCmdUI->Enable (FALSE);			// if file or image is not opened, "Add" button in "LUT" tab is enable 
}

void CChildView::OnLutSub()				// create Sub lut
{
	unsigned char lut[256];

	for(int i = 0; i < 256; i++)
		lut[i] = Clip(i - 50, 0, 255);	

	for(int i = 0; i < width * height; i++)
		dstData[i] = lut[ srcData[i] ];

	Invalidate(FALSE);
}


void CChildView::OnUpdateLutSub(CCmdUI *pCmdUI)
{
	if( dibData == NULL)
		pCmdUI->Enable (FALSE);
}


void CChildView::OnLutMultiply()		// create Multiply lut
{
	unsigned char lut[256];

	for(int i = 0; i < 256; i++)
		lut[i] = Clip(i * 5, 0, 255);	

	for(int i = 0; i < width * height; i++)
		dstData[i] = lut[ srcData[i] ];

	Invalidate(FALSE);
}


void CChildView::OnUpdateLutMultiply(CCmdUI *pCmdUI)
{
	if( dibData == NULL)
		pCmdUI->Enable (FALSE);
}


void CChildView::OnLutDivide()			// create Divide lut
{
	unsigned char lut[256];

	for(int i = 0; i < 256; i++)
		lut[i] = Clip(i / 5, 0, 255);	

	for(int i = 0; i < width * height; i++)
		dstData[i] = lut[ srcData[i] ];

	Invalidate(FALSE);
}


void CChildView::OnUpdateLutDivide(CCmdUI *pCmdUI)
{
	if( dibData == NULL)
		pCmdUI->Enable (FALSE);
}


void CChildView::OnLutNegative()		// create Negative lut
{
	unsigned char lut[256];

	for(int i = 0; i < 256; i++)
		lut[i] = 255 - i;	

	for(int i = 0; i < width * height; i++)
		dstData[i] = lut[ srcData[i] ];

	Invalidate(FALSE);
}


void CChildView::OnUpdateLutNegative(CCmdUI *pCmdUI)
{
	if( dibData == NULL)
		pCmdUI->Enable (FALSE);
}


void CChildView::OnLutGamma()			// create Gamma lut
{
	double gamma = 2.2;

	GammaCorrection( gamma );
}

void CChildView::GammaCorrection( double gamma )
{
	double			exp = 1 / gamma;
	unsigned char	lut[256];
	
	for(int i = 0; i < 256; i++)
		lut[i] = Clip((int)(255 * pow(i / (double)255, exp)), 0, 255);

	for(int i = 0; i < width * height; i++)
		dstData[i] = lut[ srcData[i] ];

	Invalidate(FALSE);
}

void CChildView::OnUpdateLutGamma(CCmdUI *pCmdUI)
{
	if( dibData == NULL)
		pCmdUI->Enable (FALSE);
}

void CChildView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// SCROLLINFO contains scroll bar parameter
	SCROLLINFO info;
	scrollBar.GetScrollInfo(&info, SIF_ALL);
	
	int minpos = info.nMin;
	int maxpos = info.nMax;
	int curpos = scrollBar.GetScrollPos();

   // Determine the new position of scroll box.
	switch (nSBCode)
	{
		case SB_LINELEFT:      // Scroll left
			if (curpos > minpos)
				curpos--;
			break;
		
		case SB_LINERIGHT:      // Scroll right
			if (curpos < maxpos)
				curpos++;
			break;

		case SB_PAGELEFT:      // Scroll page(Shaft, in addition to Thumb) left
			if (curpos > minpos)
				curpos = max(minpos, curpos - 10);
			break;

		case SB_PAGERIGHT:      // Scroll page(Shaft, in addition to Thumb) right
			if (curpos < maxpos)
				curpos = min(maxpos, curpos + 10);
			break;
		
		case SB_THUMBTRACK:   // Drag scroll box to specified position.
			curpos = nPos;    // nPos is the position that the scroll box has been dragged to.
			break;
	}
	
	scrollBar.SetScrollPos(curpos);	 // Set the new position of the thumb (scroll box).
	
	double gamma = 1 + curpos / (double)100;
	GammaCorrection( gamma );


	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CChildView::OnBlur()			// Filtering
{
	double mask[9] = { 1/9. , 1/9. , 1/9. ,
						1/9. , 1/9. , 1/9. ,
						1/9. , 1/9. , 1/9. };
	SpatialFilter3x3( mask );
}

void CChildView::OnSharpen()		// Filtering
{
	double mask[9] = { -1, -1, -1,
						-1, 9, -1,
						-1, -1, -1 };
	SpatialFilter3x3( mask );
}

void CChildView::SpatialFilter3x3( double* mask )
{
	for(int i = 1; i < height; i++)
	{
		for(int j = 1; j < width; j++)
		{
			double sum = 0;
			
			for(int k = 0; k < 3; k++)
			{
				for(int l = 0; l < 3; l++)
				{
					sum += srcData[(i - 1 + k)*step + (j - 1 + l)] * mask[k*3 + l];
				}
			}
			
			dstData[i*step + j] = Clip(int(sum), 0, 255);
		}
	}

	Invalidate(FALSE);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	leftButtonDown = TRUE;
	leftButtonPoint = point;

	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	leftButtonDown = FALSE;

	CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	rightButtonDown = TRUE;
	rightButtonPoint = point;

	CWnd::OnRButtonDown(nFlags, point);
}

void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	rightButtonDown = FALSE;

	CWnd::OnRButtonUp(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	int left_diff = point.y - leftButtonPoint.y;
	int right_diff = point.y - rightButtonPoint.y;

	unsigned char lut[256];

	if (leftButtonDown)
	{
		for(int i = 0; i < 256; i++)
			lut[i] = Clip(i + left_diff, 0, 255);
		
		for(int i = 0; i < width * height; i++)
			dstData[i] = lut[ srcData[i] ];
	} else if(rightButtonDown) {
		
		for(int i = 0; i < 256; i++)
			lut[i] = Clip(i - right_diff, 0, 255);
		
		for(int i = 0; i < width * height; i++)
			dstData[i] = lut[ srcData[i] ];
	}

	Invalidate(FALSE);
	
	CWnd::OnMouseMove(nFlags, point);
}