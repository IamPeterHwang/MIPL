// ChildView.cpp : implementation of the CChildView class

#include "stdafx.h"
#include "MIPL_MFC.h"
#include "ChildView.h"
#include "math.h"
#include "ippi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	dibData		= NULL;		// constructor, initialize pointer to NULL
	dibImage	= NULL;

	srcData		= NULL;
	dstData		= NULL;

	rightButtonDown = FALSE;
}

CChildView::~CChildView()
{
	if(dibData)
		delete[] dibData;	// destructor, remove allocated memory if program ends
	
	if(srcData)
		delete[] srcData;
	if(dstData)
		delete[] dstData;
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_CREATE()	
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
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
	ON_COMMAND(ID_FILTER_BLUR,						OnBlur)
	ON_COMMAND(ID_FILTER_SHARPEN,					OnSharpen)
	ON_COMMAND(ID_LUT_OPEN, &CChildView::OnLutOpen)
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
		dibImage, bitmapInfo, DIB_RGB_COLORS);	// print bmp file on screen, that is, draw image

	
	/*CString str;
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
	font.DeleteObject();*/
	
}

void CChildView::OnFileOpen()
{
	// show File Dialog Box
	CString szFilter = _T( "DICOM Files (*.dcm)|*.dcm|BITMAP Files (*.bmp)|*.bmp|All Files (*.*)|*.*|");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, szFilter, this );
	if(dlg.DoModal() == IDCANCEL)
		return;

	CString ext = dlg.GetFileExt();
	ext.MakeUpper();
	if(ext == _T("BMP"))
		OpenBMPFile(dlg.GetPathName());
	else if(ext == _T("DCM"))
		OpenDICOMFile(dlg.GetPathName());
}

void CChildView::OpenBMPFile(CString path)
{
	// read file
	FILE * file;
	_wfopen_s(&file, path, L"rb");

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
	srcStep			= GetRealWidth(width);
	// dibData indicate first starting point of DIB structure, finally srcData indicate starting point of actual data
	srcData			= dibData + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * bitmapInfo->bmiHeader.biClrUsed;

	// declare dst data pointer variable 
	if(dstData)
		delete[] dstData;
	dstData = new unsigned char[srcStep*height];

	// copy srcdata to dstdata
	memcpy(dstData, srcData, srcStep * height); // memmove has same function

	// disconnect between file and stream, otherwise stay put, with memory allocated 
	fclose(file);

	// As soon as file is opend, synchronize scrollbox, then operate gammacorrection
	/*switch (scrollBar.GetScrollPos())
	{
		case 0:
			break;

		default:
			double gamma = 1 + scrollBar.GetScrollPos() / (double)100;
			GammaCorrection( gamma );
			break;
	}*/
	
	Invalidate(FALSE); // don't erase background

}

void CChildView::OpenDICOMFile(CString path)
{
	KDicomDS * dicomDS = new KDicomDS;

	dicomDS -> LoadDS(path);

	samplePerPixel		= dicomDS -> m_nSamplePerPixel;
	photometric			= dicomDS -> m_nPhotometric;			
	width				= dicomDS -> m_nWidth;				
	height				= dicomDS -> m_nHeight;				
	bitsAllocated		= dicomDS -> m_nBitsAllocated;		
	bitsStored			= dicomDS -> m_nBitsStored;			
	pixelRepresentation	= dicomDS -> m_nRepresentation;	
	windowCenter		= dicomDS -> m_dWindowCenter;		
	windowWidth			= dicomDS -> m_dWindowWidth;			

	
	if(bitsAllocated == 8)
		srcStep = width * samplePerPixel;
	else
		srcStep = width * 2;

	if(srcData)
		delete[] srcData;
	srcData = new unsigned char[srcStep * height];
	dicomDS -> GetImageData(srcData);
	
	if(dstData)
		delete[] dstData;
	dstData = new unsigned char[srcStep * height];
	memcpy(dstData, srcData, srcStep * height);

	delete dicomDS;

	CreateDIB();
	
	if(samplePerPixel == 1)
		Convert16to8();
	
	else
	{
		int srcOffset;
		int dstOffset;
		
		for(int i=0; i < height ;i++)
		{
			
			dstOffset = (height - i - 1) * dibStep;
			srcOffset = i * srcStep;
			
			for(int j=0; j < width ;j++)
			{
				dibImage[dstOffset + j*3+2] = dstData[srcOffset + j*3];
				dibImage[dstOffset + j*3+1] = dstData[srcOffset + j*3+1];
				dibImage[dstOffset + j*3] = dstData[srcOffset + j*3+2];
			}
		}
	}  

	Invalidate(FALSE);
}

BOOL CChildView::CreateDIB()
{
	int colorNum;
	if(samplePerPixel == 1)
		colorNum = 256;
	else
		colorNum = 0;

	dibStep = GetRealWidth(width*samplePerPixel);

	int dibSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * colorNum + dibStep * height;

	if(dibData)
		delete[] dibData;
	dibData = new unsigned char[dibSize];

	bitmapInfo = (BITMAPINFO*) dibData;

	bitmapInfo -> bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo -> bmiHeader.biWidth = width;
	bitmapInfo -> bmiHeader.biHeight = height;
	bitmapInfo -> bmiHeader.biPlanes = 1;
	bitmapInfo -> bmiHeader.biBitCount = WORD(samplePerPixel*8);
	bitmapInfo -> bmiHeader.biCompression = 0;
	bitmapInfo -> bmiHeader.biSizeImage = dibStep * height;
	bitmapInfo -> bmiHeader.biXPelsPerMeter = 0;
	bitmapInfo -> bmiHeader.biYPelsPerMeter = 0;
	bitmapInfo -> bmiHeader.biClrUsed = colorNum;
	bitmapInfo -> bmiHeader.biClrImportant = 0;

	dibImage = dibData + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * colorNum;

	if(photometric == MONOCHROME1)
	{
		for(int i=0; i < colorNum; i++)
		{
			bitmapInfo -> bmiColors[i].rgbRed = 255-i;
			bitmapInfo -> bmiColors[i].rgbGreen = 255-i+30;
			bitmapInfo -> bmiColors[i].rgbBlue = 255-i+60;
			bitmapInfo -> bmiColors[i].rgbReserved = 0;
		}
	} else if(photometric == MONOCHROME2)
	{
		for(int i=0; i < colorNum; i++)
		{
			bitmapInfo -> bmiColors[i].rgbRed = i;
			bitmapInfo -> bmiColors[i].rgbGreen = i+30;
			bitmapInfo -> bmiColors[i].rgbBlue = i+60;
			bitmapInfo -> bmiColors[i].rgbReserved = 0;
		}
	}

	return TRUE;

}


void CChildView::Convert16to8()
{
	if(bitsAllocated == 8)
		return;

	short * src = (short*) dstData;
	int windowLow = windowCenter - windowWidth / 2;
	int windowHigh = windowCenter + windowWidth / 2;
	double ratio = 255 / windowWidth;
	short value;
	for(int i=0; i < height; i++)
	{
		for(int j=0; j < width; j++)
		{
			value = src[i*width + j];
			if(value < windowLow)
				dibImage[(height-1-i)*width + j] = 0;
			else if(value > windowHigh)
				dibImage[(height-1-i)*width + j] = 255;
			else
				dibImage[(height-1-i)*width + j] = (value - windowLow) * ratio;
		}
	}
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


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	rightButtonDown = TRUE;
	rightButtonPoint = point;

	windowCenterTemp = windowCenter;
	windowWidthTemp = windowWidth;

	CWnd::OnRButtonDown(nFlags, point);
}

void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	rightButtonDown = FALSE;

	CWnd::OnRButtonUp(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if(rightButtonDown)
	{
		if(bitsAllocated == 16)
		{
			int dx = (point.x - rightButtonPoint.x)*10;
			int dy = (point.y - rightButtonPoint.y)*10;
			
			windowWidth = windowWidthTemp + dx;
			windowCenter = windowCenterTemp + dy;
			
			Convert16to8();
			
			Invalidate(FALSE);
		}
	}
	
	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnLutOpen()
{
	// open file
	CString szFilter = _T ("LUT Files (*.lut)|*.lut|All Files (*.*)|*.*|");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, szFilter, this);
	if(dlg.DoModal() == IDCANCEL)
		return;
	
	FILE * file;
	if((file = _tfopen(dlg.GetPathName(), _T("r"))) == NULL)
	{
		AfxMessageBox(_T("Cannot Open LUT file"));
		return;
	}
	
	// read

	char szLine[1024];
	char seps[] = "\n\\\r\\\t\\ "; 
	char * token;
	CString	str, type;
	unsigned short r,g, b, index ;
	
	while(fgets(szLine , 1024, file) != NULL)
	{
		token = strtok(szLine, seps);    
		str = token ;        
		
		if(str == "*")
			continue;
		
		type = token ;
		type.MakeUpper();

		if(type == "S")
		{
			token = strtok(NULL, seps);
			
			if(token == NULL)
				continue;
			
			index = atoi (token);
			
			token = strtok (NULL, seps);
			
			if(token == NULL)
				continue;
			
			r = atoi (token);
			
			token = strtok (NULL, seps);
			
			if(token == NULL)
				continue;
			
			g = atoi (token);
			
			token = strtok (NULL, seps);
			
			if(token == NULL)
				continue;
			
			b = atoi (token);


			bitmapInfo->bmiColors [index]. rgbRed    = Clip (r, 0, 255);
			bitmapInfo->bmiColors [index]. rgbGreen  = Clip (g, 0, 255);
			bitmapInfo->bmiColors [index]. rgbBlue   = Clip (b, 0, 255);

		}
	}

	fclose( file);
	
	Invalidate( FALSE);

}