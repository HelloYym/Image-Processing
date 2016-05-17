
//���������Ҫ���ļ�

#include "stdafx.h"
#include "CImage.h"
#include "ChildView.h"
#include "InfoDlg.h"
#include <math.h>
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*------------------------------------------------------------------------------------------------------------
1.���������ǻ���MFC��������ʾ������ͼ���Ӧ�ó����ܣ�ͬѧ�ǿ����ڴ˿�ܵĻ����������ҵ����Ĺ��ܴ��롣
2.�����д���ͼ�������΢��MFC��������ṩ��CImage�࣬�����ṩ�˶�ȡ����ʾ���ָ�ʽͼ��ĺ��������Դ��򻯴�
  ��ͼ������еĹ�������ʹ��Ұ���Ҫ������������ҵ���еĹ���ʵ���ϡ�
3.ÿ����ҵ��Ӧ�Ų˵���Tools�µ�һ���˵��ÿ���˵����Ӧһ���հ׺���������ʵ��ÿ����ҵ�Ĺ��ܴ��롣
4.�����һ��ͼ���Ժ�ͼ�������洢��CImage���͵�imgOriginal�����У����CImage��ĳ�Ա������ǿ�󣬿�����MSDN
 ����F1�򿪣��в�ѯ�й����Ĳ�����imgOriginal�����Ǳ�������CChildView��˽�б��������������µĳ�Ա�����б����á�
  �й�ͼ���һЩ��������������imgOriginal.������()�ķ������ã������һ��ͼ�������imgOriginal.Load("x.jpg")��
  �������õĲ�������MSDN������CImage��
5.�����CChildView::OnToolsMakeBW��һ���򵥵����ӣ����ǲ˵���Tools�µĵ�һ���˵����Ӧ����Ϣ��Ӧ�������Ѳ�ɫͼ��
  תΪ�Ҷ�ͼ��
------------------------------------------------------------------------------------------------------------*/
void CChildView::OnToolsMakeBW(void)
{
	CWaitCursor wait;//�ں���ִ�й�����ʹ���ͼ���ɵȴ�ͼ��
	
	if (!imgOriginal.IsIndexed()) //�����ǰ�򿪵�ͼ���ÿ�����ش���8λ����û��ʹ��ɫ���������󲿷�ͼ���������֣�
	{
		//��ÿ�����شӲ�ɫתΪ�Ҷ�
		COLORREF pixel;//����һ�����ص�ɫ����Ϣ
		int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//��imgOriginalȡ��ͼ��ĳ�maxX�͸�maxY
		byte r,g,b,avg;//r,g,bֵ��ƽ���Ҷ�ֵ����
		for (int x=0; x<maxX; x++) //��ѭ��
		{
			for (int y=0; y<maxY; y++) //��ѭ��
			{
				pixel = imgOriginal.GetPixel(x,y);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
				r = GetRValue(pixel);//ȡ��pixel��rֵ
				g = GetGValue(pixel);//ȡ��pixel��gֵ
				b = GetBValue(pixel);//ȡ��pixel��bֵ
				avg = (double)r * 0.299 + (double)g * 0.587 + (double)b * 0.114;
				
				imgOriginal.SetPixelRGB(x,y,avg,avg,avg);//��λ��(x,y)λ���ϵ����ص�rgbɫ��ͨ����Ϊ(avg,avg,avg)����ת��Ϊ�Ҷ�
			}
		}
	} 
	//�°벿�ֵĴ����Ǵ���ͼ���ÿ������С��8λ�ģ�������ϸע��
	else
	{
		// the image uses an indexed palette, so we will just change the palette table entries to their B&W equivalents 
		int MaxColors = imgOriginal.GetMaxColorTableEntries();
		RGBQUAD* ColorTable;
		ColorTable = new RGBQUAD[MaxColors];

		imgOriginal.GetColorTable(0,MaxColors,ColorTable);
		for (int i=0; i<MaxColors; i++)
		{
			int avg = (double)ColorTable[i].rgbRed * 0.299 +  (double)ColorTable[i].rgbGreen * 0.587 + (double)ColorTable[i].rgbBlue * 0.114;//�ô�ʽ��rgb��ɫֵתΪ�Ҷ�ֵ
			ColorTable[i].rgbBlue = (BYTE)avg;
			ColorTable[i].rgbGreen = (BYTE)avg;
			ColorTable[i].rgbRed = (BYTE)avg;
		}
		imgOriginal.SetColorTable(0,MaxColors,ColorTable);
	
		delete[] ColorTable;
	}

	//ˢ����ʾͼ��
	Invalidate();
	UpdateWindow();
}


void CChildView::OnToolsHomeworkIV(){
	
	/*
	// ���������Translation
	int x0, y0;
	x0 = 200;
	y0 = 200;
	CImage newimg;
	newimg.Create(imgOriginal.GetWidth() + x0,imgOriginal.GetHeight() + y0,24);

	//��ÿ�����شӲ�ɫתΪ�Ҷ�
	COLORREF pixel;//����һ�����ص�ɫ����Ϣ
	int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//��imgOriginalȡ��ͼ��ĳ�maxX�͸�maxY
	byte r,g,b,avg;//r,g,bֵ��ƽ���Ҷ�ֵ����
	for (int x=0; x<maxX; x++) //��ѭ��
	{
		for (int y=0; y<maxY; y++) //��ѭ��
		{
			pixel = imgOriginal.GetPixel(x,y);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
			r = GetRValue(pixel);//ȡ��pixel��rֵ
			g = GetGValue(pixel);//ȡ��pixel��gֵ
			b = GetBValue(pixel);//ȡ��pixel��bֵ

			newimg.SetPixelRGB(x + x0,y + y0,r,g,b);//��λ��(x,y)λ���ϵ����ص�rgbɫ��ͨ����Ϊ(avg,avg,avg)����ת��Ϊ�Ҷ�
		}
	}
	*/


	/*����һ����Mirro*/
	//CImage newimg;
	//newimg.Create(imgOriginal.GetWidth(),imgOriginal.GetHeight() * 2,24);

	////��ÿ�����شӲ�ɫתΪ�Ҷ�
	//COLORREF pixel;//����һ�����ص�ɫ����Ϣ
	//int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//��imgOriginalȡ��ͼ��ĳ�maxX�͸�maxY
	//byte r,g,b,avg;//r,g,bֵ��ƽ���Ҷ�ֵ����
	//for (int x=0; x<maxX; x++) //��ѭ��
	//{
	//	for (int y=0; y<maxY; y++) //��ѭ��
	//	{
	//		pixel = imgOriginal.GetPixel(x,y);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
	//		r = GetRValue(pixel);//ȡ��pixel��rֵ
	//		g = GetGValue(pixel);//ȡ��pixel��gֵ
	//		b = GetBValue(pixel);//ȡ��pixel��bֵ

	//		newimg.SetPixelRGB(x, maxY + (maxY - y) -1,r,g,b);//��λ��(x,y)λ���ϵ����ص�rgbɫ��ͨ����Ϊ(avg,avg,avg)����ת��Ϊ�Ҷ�
	//	}
	//}

	
	/* Rotate
	//��ÿ�����شӲ�ɫתΪ�Ҷ�
	COLORREF pixel;//����һ�����ص�ɫ����Ϣ
	int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//��imgOriginalȡ��ͼ��ĳ�maxX�͸�maxY
	byte r,g,b,avg;//r,g,bֵ��ƽ���Ҷ�ֵ����

	double t = 0.2;
	int outX = (int)(maxY * sin(t) + maxX * cos(t));
	int outY = (int)(maxX * sin(t) + maxY * cos(t));

	int x0 = maxY * sin(t);

	CImage newimg;
	newimg.Create(outX, outY, 24);

	
	for (int x=0; x<maxX; x++) //��ѭ��
	{
		for (int y=0; y<maxY; y++) //��ѭ��
		{
			pixel = imgOriginal.GetPixel(x,y);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
			r = GetRValue(pixel);//ȡ��pixel��rֵ
			g = GetGValue(pixel);//ȡ��pixel��gֵ
			b = GetBValue(pixel);//ȡ��pixel��bֵ
			cout << x << " " << y << endl;
			newimg.SetPixelRGB((int)(x * cos(t) - y * sin(t)) + x0, (int)(x * sin(t) + y * cos(t)), r, g, b);//��λ��(x,y)λ���ϵ����ص�rgbɫ��ͨ����Ϊ(avg,avg,avg)����ת��Ϊ�Ҷ�
		}
	}
	

	for (int x = 0; x < outX; x++)
		for (int y = 0; y < outY; y++){
			int x1 = (int)((x - x0) * cos(-t) - y * sin(-t));
			int y1 = (int)((x - x0) * sin(-t) + y * cos(-t));
			if (x1 < 0 || x1 >= maxX || y1 < 0 || y1 >= maxY) 
				continue;
			pixel = imgOriginal.GetPixel(x1, y1);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
			r = GetRValue(pixel);//ȡ��pixel��rֵ
			g = GetGValue(pixel);//ȡ��pixel��gֵ
			b = GetBValue(pixel);//ȡ��pixel��bֵ
			newimg.SetPixelRGB(x, y, r, g, b);
		}


	*/



	/*
	//Scale
	COLORREF pixel;//����һ�����ص�ɫ����Ϣ
	int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//��imgOriginalȡ��ͼ��ĳ�maxX�͸�maxY
	byte r,g,b,avg;//r,g,bֵ��ƽ���Ҷ�ֵ����

	double tx = 1.3;
	double ty = 0.8;

	int outX = (int)(tx * maxX);
	int outY = (int)(ty * maxY);

	CImage newimg;
	newimg.Create(outX, outY, 24);


	for (int x = 0; x < outX; x++)
		for (int y = 0; y < outY; y++){
			int x1 = (int)((double)x / tx);
			int y1 = (int)((double)y / ty);
			if (x1 < 0 || x1 >= maxX || y1 < 0 || y1 >= maxY) 
				continue;
			pixel = imgOriginal.GetPixel(x1, y1);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
			r = GetRValue(pixel);//ȡ��pixel��rֵ
			g = GetGValue(pixel);//ȡ��pixel��gֵ
			b = GetBValue(pixel);//ȡ��pixel��bֵ
			newimg.SetPixelRGB(x, y, r, g, b);
		}
	imgOriginal = newimg;
	*/
	

	//shear
	COLORREF pixel;//����һ�����ص�ɫ����Ϣ
	int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//��imgOriginalȡ��ͼ��ĳ�maxX�͸�maxY
	byte r,g,b,avg;//r,g,bֵ��ƽ���Ҷ�ֵ����

	double dx = 0.3;
	double dy = 0.3;

	int outX = (int)(maxX);
	int outY = (int)(maxY + dy * maxX);

	CImage newimg;
	newimg.Create(outX, outY, 24);


	for (int x = 0; x < outX; x++)
		for (int y = 0; y < outY; y++){
			int x1 = (int)((double)x);
			int y1 = (int)((double)y - x * dy);
			if (x1 < 0 || x1 >= maxX || y1 < 0 || y1 >= maxY) 
				continue;
			pixel = imgOriginal.GetPixel(x1, y1);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
			r = GetRValue(pixel);//ȡ��pixel��rֵ
			g = GetGValue(pixel);//ȡ��pixel��gֵ
			b = GetBValue(pixel);//ȡ��pixel��bֵ
			newimg.SetPixelRGB(x, y, r, g, b);
		}
	imgOriginal = newimg;

	
	//ˢ����ʾͼ��
	Invalidate();
	UpdateWindow();
}

void CChildView::OnToolsHomeworkII(){
}

//Ϊ�˵��������Ϣ��Ӧ���������ʵ�ִ��루ϸ�ڲμ�ppt��
void CChildView::OnToolsHomeworkIII()
{
	OnToolsMakeBW();


	COLORREF pixel;//����һ�����ص�ɫ����Ϣ
	int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//��imgOriginalȡ��ͼ��ĳ�maxX�͸�maxY

	//int n[256];
	//memset(n, 0, sizeof(n));
	//for (int x=0; x<maxX; x++) //��ѭ��
	//{
	//	for (int y=0; y<maxY; y++) //��ѭ��
	//	{
	//		pixel = imgOriginal.GetPixel(x,y);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
	//		byte gray = GetRValue(pixel);//ȡ��pixel��rֵ
	//		n[gray]++;
	//	}
	//}

	//int N = maxX * maxY;
	//double p[256];
	//memset(p, 0, sizeof(p));
	//for (int i = 0; i < 256; i++)
	//	p[i] = (double) n[i] / N;

	//double s[256];
	//memset(s, 0, sizeof(s));
	//s[0] = p[0];
	//for (int i = 1; i < 256; i++)
	//	s[i] = s[i - 1] + p[i];

	//int f[256];
	//memset(f, 0, sizeof(f));
	//for (int i = 1; i < 256; i++)
	//	f[i] = s[i] * 255;



	//for (int x=0; x<maxX; x++)
	//	for (int y=0; y<maxY; y++) //��ѭ��
	//	{
	//		pixel = imgOriginal.GetPixel(x,y);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
	//		byte gray = GetRValue(pixel);
	//		gray = f[gray];
	//		imgOriginal.SetPixelRGB(x,y,gray,gray,gray);//��λ��(x,y)λ���ϵ����ص�rgbɫ��ͨ����Ϊ(avg,avg,avg)����ת��Ϊ�Ҷ�
	//	}
	//

	////ˢ����ʾͼ��
	//Invalidate();
	//UpdateWindow();



	int Lmax = 0, Lmin = 255;
	int h =6;
	for (int t = 0; t < h; t++) {
		for (int x=0; x<maxX; x++)
			for (int y=0; y<maxY; y++) //��ѭ��
			{
				pixel = imgOriginal.GetPixel(x,y);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
				byte gray = GetRValue(pixel);
				if (gray > Lmax) Lmax = gray;
				if (gray < Lmin) Lmin = gray;
			}

		for (int x=0; x<maxX; x++)
			for (int y=0; y<maxY; y++) //��ѭ��
			{
				pixel = imgOriginal.GetPixel(x,y);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
				byte gray = GetRValue(pixel);
				gray = log((double) gray / 255 + 1) / log((double) Lmax / 255 + 1) * 255;
				imgOriginal.SetPixelRGB(x,y,gray,gray,gray);
			}

	}
	Invalidate();
	UpdateWindow();

}




void CChildView::OnToolsHomeworkV(){
	CWaitCursor wait;//�ں���ִ�й�����ʹ���ͼ���ɵȴ�ͼ��
	OnToolsMakeBW();


	/*	ʵ��6 BilateralFilter    
		����û��ʵ�����İ�ť���ʽ�ʵ��6д��ʵ��5��λ��
	*/

	double	sigmaS = 20;		//Space
	double	sigmaR = 50;		//Intencity
	int		nWindow = 15;	//�˲����ڴ�С
	int		a = (nWindow - 1) / 2;


	COLORREF pixel;//����һ�����ص�ɫ����Ϣ
	int maxY = imgOriginal.GetHeight();
	int maxX = imgOriginal.GetWidth();


	double distance;
	double graydiff;

	byte out[1000][1000];

	for (int x = 0; x < maxX; x++) {
		for (int y = 0; y < maxY; y++) {
			pixel = imgOriginal.GetPixel(x, y);
			double gray = GetRValue(pixel);		//��ǰ���ĻҶ�

			double data = 0;
			double total = 0;

			for (int i = -a; i <= a; i++)
				for (int j = -a; j <= a; j++)
					if (x + i >= 0 && x + i < maxX && y + j >= 0 && y + j < maxY){
						pixel = imgOriginal.GetPixel(x + i, y + j);
						double gray1 = GetRValue(pixel);

						//����Ҷ����ƶ�
						graydiff = fabs(gray1 - gray);
						graydiff = exp(-0.5 * graydiff * graydiff / (sigmaR * sigmaR));

						//����ռ����ƶ�
						distance = i * i + j * j;
						distance = exp(-0.5 * distance / (sigmaS * sigmaS));

						data += gray1 * graydiff * distance;	 
						total += graydiff * distance;    //��Ȩϵ����ͣ����й�һ�� 
					}

			data = data / total;
			out[x][y] = data;
		}
	}

	for (int x = 0; x < maxX; x++) 
		for (int y = 0; y < maxY; y++) {
			byte gray = out[x][y];
			imgOriginal.SetPixelRGB(x,y,gray,gray,gray);
		}



	//image mean filtering
	//int filter[9][9] = {
	//	{1, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 1, 1, 1, 1, 1, 1, 1, 1}
	//};

	//int a = 4;
	//int b = 4;
	//int c = 81;

	//COLORREF pixel;//����һ�����ص�ɫ����Ϣ
	//int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//��imgOriginalȡ��ͼ��ĳ�maxX�͸�maxY
	//for (int x=0; x<maxX; x++) {
	//	for (int y=0; y<maxY; y++) {
	//		int sum = 0;
	//		for (int i = -a; i <= a; i++)
	//			for (int j = -b; j <= b; j++)
	//				if (x + i >= 0 && x + i < maxX && y + j >= 0 && y + j < maxY){
	//					pixel = imgOriginal.GetPixel(x + i, y + j);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
	//					byte gray = GetRValue(pixel);//ȡ��pixel��rֵ
	//					sum += filter[a + i][b + j] * gray;
	//				}
	//		byte gray = (double)sum / (double)c;
	//		imgOriginal.SetPixelRGB(x,y,gray,gray,gray);
	//	}
	//}




	
	//// Laplacian
	//int mask[3][3] = {
	//	{1, 1,  1},
	//	{1, -8, 1},
	//	{1, 1,  1}
	//};

	//int a = 1;
	//int b = 1;

	//COLORREF pixel;//����һ�����ص�ɫ����Ϣ
	//int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//��imgOriginalȡ��ͼ��ĳ�maxX�͸�maxY

	//int ans[500][500];
	//
	//int maxG = -1000;
	//int minG = 1000;

	//for (int x=0; x<maxX; x++) {
	//	for (int y=0; y<maxY; y++) {

	//		//int sum = 0;
	//		ans[x][y] = 0;
	//		for (int i = -a; i <= a; i++)
	//			for (int j = -b; j <= b; j++)
	//				if (x + i >= 0 && x + i < maxX && y + j >= 0 && y + j < maxY){
	//					pixel = imgOriginal.GetPixel(x + i, y + j);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
	//					int gray = GetRValue(pixel);//ȡ��pixel��rֵ
	//					ans[x][y] += mask[a + i][b + j] * gray;
	//				}

	//		//if (ans[x][y] < 0) ans[x][y] = 0;
	//		//if (ans[x][y] > 255) ans[x][y] = 255;
	//		//ans[x][y] = sum;
	//	}
	//}



	////for (int x=0; x<maxX; x++) {
	////	for (int y=0; y<maxY; y++) {

	////		int sum = 0;
	////		for (int i = -a; i <= a; i++)
	////			for (int j = -b; j <= b; j++)
	////				if (x + i >= 0 && x + i < maxX && y + j >= 0 && y + j < maxY){
	////					pixel = imgOriginal.GetPixel(x + i, y + j);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
	////					int gray = GetRValue(pixel);//ȡ��pixel��rֵ
	////					sum += mask[a + i][b + j] * gray;
	////				}
	////		ans[x][y] = (double)(sum - minG)/(double)(maxG - minG) * 255;
	////	}
	////}
	////

	//minG = 1000;
	//maxG = -1000;
	//for (int x=0; x<maxX; x++) {
	//	for (int y=0; y<maxY; y++) {
	//		pixel = imgOriginal.GetPixel(x, y);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
	//		int gray = GetRValue(pixel);//ȡ��pixel��rֵ
	//		int a = gray - ans[x][y];
	//		//if (gray1 < 0) gray1 = 0;
	//		//imgOriginal.SetPixelRGB(x,y,gray1,gray1,gray1);
	//		if (a > maxG)
	//			maxG = a;
	//		if (a < minG)
	//			minG = a;
	//		if (gray - ans[x][y] < 0)
	//			ans[x][y] = 0;
	//		else if (gray - ans[x][y] > 255)
	//			ans[x][y] = 255;
	//		else
	//			ans[x][y] = gray - ans[x][y];
	//	}
	//}

	//for (int x=0; x<maxX; x++) {
	//	for (int y=0; y<maxY; y++) {
	//		//pixel = imgOriginal.GetPixel(x, y);//ȡ��λ��(x,y)λ���ϵ����ص�ɫ����Ϣ
	//		//int gray = GetRValue(pixel);//ȡ��pixel��rֵ
	//		//ans[x][y] = (double)((gray - ans[x][y]) - minG)/(double)(maxG - minG) * 255;
	//		byte gray1 = ans[x][y];
	//		imgOriginal.SetPixelRGB(x,y,gray1,gray1,gray1);
	//	}
	//}



	//ˢ����ʾͼ��
	Invalidate();
	UpdateWindow();
}

/*-------------------------------------------------------------------------------------------------
���´����Ǳ�������ܰ������ֳɵĺ�������򿪡���ʾ���洢ͼ���ļ��Ĵ��룬ͬѧ�ǿ��Բ�ȥ�����о�
--------------------------------------------------------------------------------------------------*/

// CChildView�Ĺ��캯�������������Լ���Ϣӳ���(����ϸ��������ο�C++��MFC�ľ����鼮)

CChildView::CChildView()
{
	m_nImageSize = SIZE_NONE;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_OPENIMAGE, OnFileOpenimage)
	ON_COMMAND(ID_FILE_SAVEIMAGE, OnFileSaveImage)
	ON_COMMAND(ID_TOOLS_MAKEBW, OnToolsMakeBW)
	ON_COMMAND(ID_FILE_IMAGEINFO, OnImageInfo)
	ON_UPDATE_COMMAND_UI(ID_SIZE_HALF,OnUpdateSizeHalf)
	ON_UPDATE_COMMAND_UI(ID_SIZE_ORIGINAL,OnUpdateSizeOriginal)
	ON_UPDATE_COMMAND_UI(ID_SIZE_DOUBLE,OnUpdateSizeDouble)
	ON_UPDATE_COMMAND_UI(ID_SIZE_FILL,OnUpdateSizeFill)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVEIMAGE,OnUpdateImage)
	ON_UPDATE_COMMAND_UI(ID_FILE_IMAGEINFO,OnUpdateImage)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_MAKEBW,OnUpdateImage)
	ON_COMMAND_RANGE(ID_SIZE_HALF,ID_SIZE_FILL,OnChangeSize)
	ON_COMMAND(ID_TOOLS_HOMEWORKIII, &CChildView::OnToolsHomeworkIII)
	ON_COMMAND(ID_TOOLS_HOMEWORKII, &CChildView::OnToolsHomeworkII)
	ON_COMMAND(ID_TOOLS_HOMEWORKIV, &CChildView::OnToolsHomeworkIV)
	ON_COMMAND(ID_TOOLS_HOMEWORKV, &CChildView::OnToolsHomeworkV)
END_MESSAGE_MAP()



// CChildView message handlers
// �����еĴ󲿷ְ�ť��Ӧ���ֳɵĺ���
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

//���δ�����ÿһ����Ϣѭ���б���������һ����С������ʾ��ǰͼƬ
void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if (!imgOriginal.IsNull()) 
	{

		switch (m_nImageSize)
		{
			case SIZE_HALF:
				imgOriginal.StretchBlt(dc,0,0,imgOriginal.GetWidth()/2,imgOriginal.GetHeight()/2,SRCCOPY);
				break;
			case SIZE_ORIGINAL:
				imgOriginal.StretchBlt(dc,0,0,imgOriginal.GetWidth(),imgOriginal.GetHeight(),SRCCOPY);
				break;
			case SIZE_DOUBLE:
				imgOriginal.StretchBlt(dc,0,0,imgOriginal.GetWidth()*2,imgOriginal.GetHeight()*2,SRCCOPY);
				break;
			case SIZE_FILL:
				CRect rctWindowSize;
				GetClientRect(rctWindowSize);
				imgOriginal.StretchBlt(dc,0,0,rctWindowSize.Width(),rctWindowSize.Height(),SRCCOPY);
		};
	}

}

//���δ���ʵ�ִ��ļ��Ի���ѡ��һ��ͼƬ�ļ�����ʾ
void CChildView::OnFileOpenimage(void)
{
	// TODO: Add your command handler code here
	CString strFilter;
	CSimpleArray<GUID> aguidFileTypes;
	HRESULT hResult;

	hResult = imgOriginal.GetExporterFilterString(strFilter,aguidFileTypes);
	if (FAILED(hResult)) {
		CString fmt;
		fmt.Format("GetExporterFilter failed:\n%x - %s", hResult, _com_error(hResult).ErrorMessage());
		::AfxMessageBox(fmt);
		return;
	}

	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, strFilter);
	dlg.m_ofn.nFilterIndex = m_nFilterLoad;
	hResult = (int)dlg.DoModal();
	if(FAILED(hResult)) {
		return;
	}

	m_nFilterLoad = dlg.m_ofn.nFilterIndex;
	imgOriginal.Destroy();
	hResult = imgOriginal.Load(dlg.GetPathName());
	if (FAILED(hResult)) {
		CString fmt;
		fmt.Format("Load image failed:\n%x - %s", hResult, _com_error(hResult).ErrorMessage());
		::AfxMessageBox(fmt);
		return;
	}

	m_nImageSize = SIZE_ORIGINAL;
	Invalidate();
	UpdateWindow();

}
//���δ���ʵ�ֽ���ǰ��ͼƬ�洢������
void CChildView::OnFileSaveImage(void) 
{
	CString strFilter;
	CSimpleArray<GUID> aguidFileTypes;
	HRESULT hResult;


	strFilter = "Bitmap image|*.bmp|JPEG image|*.jpg|GIF image|*.gif|PNG image|*.png||";

	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER,strFilter);
	dlg.m_ofn.nFilterIndex = m_nFilterLoad;
	hResult = (int)dlg.DoModal();
	if (FAILED(hResult)) {
		return;
	}

    // Add the appropriate extension if the user didn't type one

	CString strFileName;
	CString strExtension;

	strFileName = dlg.m_ofn.lpstrFile;


	// add the file extension if the user didn't supply one
	if (dlg.m_ofn.nFileExtension == 0) 
	{
		switch (dlg.m_ofn.nFilterIndex)
		{
		case 1:
			strExtension = "bmp";
			break;
		case 2:
			strExtension = "jpg";
			break;
		case 3:
			strExtension = "gif";
			break;
		case 4:
			strExtension = "png";
			break;
		default:
			break;
		}

		strFileName = strFileName + '.' + strExtension;

	}

	// the extension on the file name will determine the file type that is saved
	hResult = imgOriginal.Save(strFileName);
	if (FAILED(hResult)) {
		CString fmt;
		fmt.Format("Save image failed:\n%x - %s", hResult, _com_error(hResult).ErrorMessage());
		::AfxMessageBox(fmt);
		return;
	}

}



//���δ����ѯͼ�������Ϣ
void CChildView::OnImageInfo()
{
	CInfoDlg infoDlg(imgOriginal);
	infoDlg.DoModal();
}

//���δ���ı�ͼ����ʾ��С
void CChildView::OnChangeSize(UINT nID)
{
	m_nImageSize = (SizesEnum)(nID - ID_SIZE_BASE);
	Invalidate();
	UpdateWindow();
}

//�����Ķδ����Բ�ͬ�Ĵ�С��ʾͼƬ
void CChildView::OnUpdateSizeHalf(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!imgOriginal.IsNull());
	pCmdUI->SetCheck((UINT)(m_nImageSize == SIZE_HALF));
}

void CChildView::OnUpdateSizeOriginal(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!imgOriginal.IsNull());
	pCmdUI->SetCheck((UINT)(m_nImageSize == SIZE_ORIGINAL));
}

void CChildView::OnUpdateSizeDouble(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!imgOriginal.IsNull());
	pCmdUI->SetCheck((UINT)(m_nImageSize == SIZE_DOUBLE));
}

void CChildView::OnUpdateSizeFill(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!imgOriginal.IsNull());
	pCmdUI->SetCheck((UINT)(m_nImageSize == SIZE_FILL));
}

void CChildView::OnUpdateImage(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!imgOriginal.IsNull());
}



