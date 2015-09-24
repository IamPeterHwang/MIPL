#include "stdafx.h"
#include "MIPL_MFC.h"
#include "ChildView.h"
#include "math.h"
#include "ippi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CChildView::OnArithmeticAdd() // pixel value + 50
{
	if( dibData == NULL )
		return;

	short * src = (short*) srcData;
	short * dst = (short*) dstData;

	IppiSize roiSize;
	roiSize.width = width;
	roiSize.height = height;
	
	ippiAddC_16s_C1RSfs(src, srcStep, 300, dst, srcStep, roiSize, 0);

	Convert16to8();

	Invalidate(FALSE);
}

void CChildView::OnArithmeticSub() // pixel value - 50
{
	if( dibData == NULL )
		return;

	short * src = (short*) srcData;
	short * dst = (short*) dstData;

	IppiSize roiSize;
	roiSize.width = width;
	roiSize.height = height;
	
	ippiSubC_16s_C1RSfs(src, srcStep, 200, dst, srcStep, roiSize, 0);

	Convert16to8();

	Invalidate(FALSE);

}

void CChildView::OnArithmeticMultiply() // pixel value * 5
{
	if( dibData == NULL )
		return;

	short * src = (short*) srcData;
	short * dst = (short*) dstData;

	IppiSize roiSize;
	roiSize.width = width;
	roiSize.height = height;
	
	ippiMulC_16s_C1RSfs(src, srcStep, 3, dst, srcStep, roiSize, 0);

	Convert16to8();

	Invalidate(FALSE);

}

void CChildView::OnArithmeticDivide() // pixel value / 4
{
	if( dibData == NULL )
		return;

	short * src = (short*) srcData;
	short * dst = (short*) dstData;

	IppiSize roiSize;
	roiSize.width = width;
	roiSize.height = height;
	
	ippiDivC_16s_C1RSfs(src, srcStep, 3, dst, srcStep, roiSize, 0);

	Convert16to8();

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
	memset(dstData, 0, srcStep * height);
	short * src = (short*) srcData;
	short * dst = (short*) dstData;

	IppiSize roiSize;
	roiSize.width = width;
	roiSize.height = height;
	
	ippiMirror_16s_C1R(src, srcStep, dst, srcStep, roiSize, ippAxsHorizontal);

	Convert16to8();

	Invalidate(FALSE);
}

void CChildView::OnGeometricFlipH() // flip horizontally
{
	memset(dstData, 0, srcStep * height);
	short * src = (short*) srcData;
	short * dst = (short*) dstData;

	IppiSize roiSize;
	roiSize.width = width;
	roiSize.height = height;
	
	ippiMirror_16s_C1R(src, srcStep, dst, srcStep, roiSize, ippAxsVertical);

	Convert16to8();

	Invalidate(FALSE);
}

void CChildView::OnGeometricRotateLeft() // Rotate Left
{
	memset(dstData, 0, srcStep * height);
	

	Invalidate(FALSE);
}

void CChildView::OnGeometricRotateRight() // Rotate Right
{
	memset(dstData, 0, srcStep * height);
	

	Invalidate(FALSE);
}

void CChildView::OnBlur()			// Filtering
{
	memset(dstData, 0, srcStep * height);
	short * src = (short*) srcData;
	short * dst = (short*) dstData;

	IppiSize roiSize;
	roiSize.width = width;
	roiSize.height = height;

	ippiFilterLowpass_16s_C1R(src, srcStep, dst, srcStep, roiSize, ippMskSize5x5);
	Convert16to8();

	Invalidate(FALSE);
}

void CChildView::OnSharpen()		// Filtering
{
	memset(dstData, 0, srcStep * height);
	short * src = (short*) srcData;
	short * dst = (short*) dstData;

	IppiSize roiSize;
	roiSize.width = width;
	roiSize.height = height;

	ippiFilterSharpen_16s_C1R(src, srcStep, dst, srcStep, roiSize);
	Convert16to8();

	Invalidate(FALSE);
}