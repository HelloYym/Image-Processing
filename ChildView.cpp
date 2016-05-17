
//本框架最主要的文件

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
1.本程序框架是基于MFC开发的显示及处理图像的应用程序框架，同学们可以在此框架的基础上完成作业所需的功能代码。
2.程序中处理图像的类是微软MFC基础类库提供的CImage类，该类提供了读取和显示各种格式图像的函数，可以大大简化处
  理图像过程中的工作量，使大家把主要精力集中在作业所列的功能实现上。
3.每个作业对应着菜单上Tools下的一个菜单项，每个菜单项对应一个空白函数，用于实现每个作业的功能代码。
4.当你打开一幅图像以后，图像句柄被存储在CImage类型的imgOriginal对象中，这个CImage类的成员函数很强大，可以在MSDN
 （按F1打开）中查询有关它的操作。imgOriginal对象是本程序中CChildView的私有变量，可以在以下的成员函数中被调用。
  有关图像的一些基础操作都可用imgOriginal.函数名()的方法调用，比如打开一幅图像可以用imgOriginal.Load("x.jpg")，
  更多有用的操作请在MSDN中搜索CImage。
5.下面的CChildView::OnToolsMakeBW是一个简单的例子，它是菜单上Tools下的第一个菜单项对应的消息响应函数，把彩色图像
  转为灰度图。
------------------------------------------------------------------------------------------------------------*/
void CChildView::OnToolsMakeBW(void)
{
	CWaitCursor wait;//在函数执行过程中使鼠标图标变成等待图标
	
	if (!imgOriginal.IsIndexed()) //如果当前打开的图像的每个像素大于8位，即没有使用色彩索引表（大部分图像都属于这种）
	{
		//把每个像素从彩色转为灰度
		COLORREF pixel;//保存一个像素的色彩信息
		int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//从imgOriginal取得图像的长maxX和高maxY
		byte r,g,b,avg;//r,g,b值和平均灰度值变量
		for (int x=0; x<maxX; x++) //列循环
		{
			for (int y=0; y<maxY; y++) //行循环
			{
				pixel = imgOriginal.GetPixel(x,y);//取得位于(x,y)位置上的像素的色彩信息
				r = GetRValue(pixel);//取得pixel的r值
				g = GetGValue(pixel);//取得pixel的g值
				b = GetBValue(pixel);//取得pixel的b值
				avg = (double)r * 0.299 + (double)g * 0.587 + (double)b * 0.114;
				
				imgOriginal.SetPixelRGB(x,y,avg,avg,avg);//将位于(x,y)位置上的像素的rgb色彩通道设为(avg,avg,avg)，即转换为灰度
			}
		}
	} 
	//下半部分的代码是处理图像的每个像素小于8位的，不再详细注解
	else
	{
		// the image uses an indexed palette, so we will just change the palette table entries to their B&W equivalents 
		int MaxColors = imgOriginal.GetMaxColorTableEntries();
		RGBQUAD* ColorTable;
		ColorTable = new RGBQUAD[MaxColors];

		imgOriginal.GetColorTable(0,MaxColors,ColorTable);
		for (int i=0; i<MaxColors; i++)
		{
			int avg = (double)ColorTable[i].rgbRed * 0.299 +  (double)ColorTable[i].rgbGreen * 0.587 + (double)ColorTable[i].rgbBlue * 0.114;//用此式将rgb彩色值转为灰度值
			ColorTable[i].rgbBlue = (BYTE)avg;
			ColorTable[i].rgbGreen = (BYTE)avg;
			ColorTable[i].rgbRed = (BYTE)avg;
		}
		imgOriginal.SetColorTable(0,MaxColors,ColorTable);
	
		delete[] ColorTable;
	}

	//刷新显示图像
	Invalidate();
	UpdateWindow();
}


void CChildView::OnToolsHomeworkIV(){
	
	/*
	// 下面这段是Translation
	int x0, y0;
	x0 = 200;
	y0 = 200;
	CImage newimg;
	newimg.Create(imgOriginal.GetWidth() + x0,imgOriginal.GetHeight() + y0,24);

	//把每个像素从彩色转为灰度
	COLORREF pixel;//保存一个像素的色彩信息
	int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//从imgOriginal取得图像的长maxX和高maxY
	byte r,g,b,avg;//r,g,b值和平均灰度值变量
	for (int x=0; x<maxX; x++) //列循环
	{
		for (int y=0; y<maxY; y++) //行循环
		{
			pixel = imgOriginal.GetPixel(x,y);//取得位于(x,y)位置上的像素的色彩信息
			r = GetRValue(pixel);//取得pixel的r值
			g = GetGValue(pixel);//取得pixel的g值
			b = GetBValue(pixel);//取得pixel的b值

			newimg.SetPixelRGB(x + x0,y + y0,r,g,b);//将位于(x,y)位置上的像素的rgb色彩通道设为(avg,avg,avg)，即转换为灰度
		}
	}
	*/


	/*下面一段是Mirro*/
	//CImage newimg;
	//newimg.Create(imgOriginal.GetWidth(),imgOriginal.GetHeight() * 2,24);

	////把每个像素从彩色转为灰度
	//COLORREF pixel;//保存一个像素的色彩信息
	//int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//从imgOriginal取得图像的长maxX和高maxY
	//byte r,g,b,avg;//r,g,b值和平均灰度值变量
	//for (int x=0; x<maxX; x++) //列循环
	//{
	//	for (int y=0; y<maxY; y++) //行循环
	//	{
	//		pixel = imgOriginal.GetPixel(x,y);//取得位于(x,y)位置上的像素的色彩信息
	//		r = GetRValue(pixel);//取得pixel的r值
	//		g = GetGValue(pixel);//取得pixel的g值
	//		b = GetBValue(pixel);//取得pixel的b值

	//		newimg.SetPixelRGB(x, maxY + (maxY - y) -1,r,g,b);//将位于(x,y)位置上的像素的rgb色彩通道设为(avg,avg,avg)，即转换为灰度
	//	}
	//}

	
	/* Rotate
	//把每个像素从彩色转为灰度
	COLORREF pixel;//保存一个像素的色彩信息
	int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//从imgOriginal取得图像的长maxX和高maxY
	byte r,g,b,avg;//r,g,b值和平均灰度值变量

	double t = 0.2;
	int outX = (int)(maxY * sin(t) + maxX * cos(t));
	int outY = (int)(maxX * sin(t) + maxY * cos(t));

	int x0 = maxY * sin(t);

	CImage newimg;
	newimg.Create(outX, outY, 24);

	
	for (int x=0; x<maxX; x++) //列循环
	{
		for (int y=0; y<maxY; y++) //行循环
		{
			pixel = imgOriginal.GetPixel(x,y);//取得位于(x,y)位置上的像素的色彩信息
			r = GetRValue(pixel);//取得pixel的r值
			g = GetGValue(pixel);//取得pixel的g值
			b = GetBValue(pixel);//取得pixel的b值
			cout << x << " " << y << endl;
			newimg.SetPixelRGB((int)(x * cos(t) - y * sin(t)) + x0, (int)(x * sin(t) + y * cos(t)), r, g, b);//将位于(x,y)位置上的像素的rgb色彩通道设为(avg,avg,avg)，即转换为灰度
		}
	}
	

	for (int x = 0; x < outX; x++)
		for (int y = 0; y < outY; y++){
			int x1 = (int)((x - x0) * cos(-t) - y * sin(-t));
			int y1 = (int)((x - x0) * sin(-t) + y * cos(-t));
			if (x1 < 0 || x1 >= maxX || y1 < 0 || y1 >= maxY) 
				continue;
			pixel = imgOriginal.GetPixel(x1, y1);//取得位于(x,y)位置上的像素的色彩信息
			r = GetRValue(pixel);//取得pixel的r值
			g = GetGValue(pixel);//取得pixel的g值
			b = GetBValue(pixel);//取得pixel的b值
			newimg.SetPixelRGB(x, y, r, g, b);
		}


	*/



	/*
	//Scale
	COLORREF pixel;//保存一个像素的色彩信息
	int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//从imgOriginal取得图像的长maxX和高maxY
	byte r,g,b,avg;//r,g,b值和平均灰度值变量

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
			pixel = imgOriginal.GetPixel(x1, y1);//取得位于(x,y)位置上的像素的色彩信息
			r = GetRValue(pixel);//取得pixel的r值
			g = GetGValue(pixel);//取得pixel的g值
			b = GetBValue(pixel);//取得pixel的b值
			newimg.SetPixelRGB(x, y, r, g, b);
		}
	imgOriginal = newimg;
	*/
	

	//shear
	COLORREF pixel;//保存一个像素的色彩信息
	int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//从imgOriginal取得图像的长maxX和高maxY
	byte r,g,b,avg;//r,g,b值和平均灰度值变量

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
			pixel = imgOriginal.GetPixel(x1, y1);//取得位于(x,y)位置上的像素的色彩信息
			r = GetRValue(pixel);//取得pixel的r值
			g = GetGValue(pixel);//取得pixel的g值
			b = GetBValue(pixel);//取得pixel的b值
			newimg.SetPixelRGB(x, y, r, g, b);
		}
	imgOriginal = newimg;

	
	//刷新显示图像
	Invalidate();
	UpdateWindow();
}

void CChildView::OnToolsHomeworkII(){
}

//为菜单项添加消息响应函数并添加实现代码（细节参加ppt）
void CChildView::OnToolsHomeworkIII()
{
	OnToolsMakeBW();


	COLORREF pixel;//保存一个像素的色彩信息
	int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//从imgOriginal取得图像的长maxX和高maxY

	//int n[256];
	//memset(n, 0, sizeof(n));
	//for (int x=0; x<maxX; x++) //列循环
	//{
	//	for (int y=0; y<maxY; y++) //行循环
	//	{
	//		pixel = imgOriginal.GetPixel(x,y);//取得位于(x,y)位置上的像素的色彩信息
	//		byte gray = GetRValue(pixel);//取得pixel的r值
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
	//	for (int y=0; y<maxY; y++) //行循环
	//	{
	//		pixel = imgOriginal.GetPixel(x,y);//取得位于(x,y)位置上的像素的色彩信息
	//		byte gray = GetRValue(pixel);
	//		gray = f[gray];
	//		imgOriginal.SetPixelRGB(x,y,gray,gray,gray);//将位于(x,y)位置上的像素的rgb色彩通道设为(avg,avg,avg)，即转换为灰度
	//	}
	//

	////刷新显示图像
	//Invalidate();
	//UpdateWindow();



	int Lmax = 0, Lmin = 255;
	int h =6;
	for (int t = 0; t < h; t++) {
		for (int x=0; x<maxX; x++)
			for (int y=0; y<maxY; y++) //行循环
			{
				pixel = imgOriginal.GetPixel(x,y);//取得位于(x,y)位置上的像素的色彩信息
				byte gray = GetRValue(pixel);
				if (gray > Lmax) Lmax = gray;
				if (gray < Lmin) Lmin = gray;
			}

		for (int x=0; x<maxX; x++)
			for (int y=0; y<maxY; y++) //行循环
			{
				pixel = imgOriginal.GetPixel(x,y);//取得位于(x,y)位置上的像素的色彩信息
				byte gray = GetRValue(pixel);
				gray = log((double) gray / 255 + 1) / log((double) Lmax / 255 + 1) * 255;
				imgOriginal.SetPixelRGB(x,y,gray,gray,gray);
			}

	}
	Invalidate();
	UpdateWindow();

}




void CChildView::OnToolsHomeworkV(){
	CWaitCursor wait;//在函数执行过程中使鼠标图标变成等待图标
	OnToolsMakeBW();


	/*	实验6 BilateralFilter    
		由于没有实验六的按钮，故将实验6写在实验5的位置
	*/

	double	sigmaS = 20;		//Space
	double	sigmaR = 50;		//Intencity
	int		nWindow = 15;	//滤波窗口大小
	int		a = (nWindow - 1) / 2;


	COLORREF pixel;//保存一个像素的色彩信息
	int maxY = imgOriginal.GetHeight();
	int maxX = imgOriginal.GetWidth();


	double distance;
	double graydiff;

	byte out[1000][1000];

	for (int x = 0; x < maxX; x++) {
		for (int y = 0; y < maxY; y++) {
			pixel = imgOriginal.GetPixel(x, y);
			double gray = GetRValue(pixel);		//当前中心灰度

			double data = 0;
			double total = 0;

			for (int i = -a; i <= a; i++)
				for (int j = -a; j <= a; j++)
					if (x + i >= 0 && x + i < maxX && y + j >= 0 && y + j < maxY){
						pixel = imgOriginal.GetPixel(x + i, y + j);
						double gray1 = GetRValue(pixel);

						//计算灰度相似度
						graydiff = fabs(gray1 - gray);
						graydiff = exp(-0.5 * graydiff * graydiff / (sigmaR * sigmaR));

						//计算空间相似度
						distance = i * i + j * j;
						distance = exp(-0.5 * distance / (sigmaS * sigmaS));

						data += gray1 * graydiff * distance;	 
						total += graydiff * distance;    //加权系数求和，进行归一化 
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

	//COLORREF pixel;//保存一个像素的色彩信息
	//int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//从imgOriginal取得图像的长maxX和高maxY
	//for (int x=0; x<maxX; x++) {
	//	for (int y=0; y<maxY; y++) {
	//		int sum = 0;
	//		for (int i = -a; i <= a; i++)
	//			for (int j = -b; j <= b; j++)
	//				if (x + i >= 0 && x + i < maxX && y + j >= 0 && y + j < maxY){
	//					pixel = imgOriginal.GetPixel(x + i, y + j);//取得位于(x,y)位置上的像素的色彩信息
	//					byte gray = GetRValue(pixel);//取得pixel的r值
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

	//COLORREF pixel;//保存一个像素的色彩信息
	//int maxY = imgOriginal.GetHeight(), maxX = imgOriginal.GetWidth();//从imgOriginal取得图像的长maxX和高maxY

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
	//					pixel = imgOriginal.GetPixel(x + i, y + j);//取得位于(x,y)位置上的像素的色彩信息
	//					int gray = GetRValue(pixel);//取得pixel的r值
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
	////					pixel = imgOriginal.GetPixel(x + i, y + j);//取得位于(x,y)位置上的像素的色彩信息
	////					int gray = GetRValue(pixel);//取得pixel的r值
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
	//		pixel = imgOriginal.GetPixel(x, y);//取得位于(x,y)位置上的像素的色彩信息
	//		int gray = GetRValue(pixel);//取得pixel的r值
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
	//		//pixel = imgOriginal.GetPixel(x, y);//取得位于(x,y)位置上的像素的色彩信息
	//		//int gray = GetRValue(pixel);//取得pixel的r值
	//		//ans[x][y] = (double)((gray - ans[x][y]) - minG)/(double)(maxG - minG) * 255;
	//		byte gray1 = ans[x][y];
	//		imgOriginal.SetPixelRGB(x,y,gray1,gray1,gray1);
	//	}
	//}



	//刷新显示图像
	Invalidate();
	UpdateWindow();
}

/*-------------------------------------------------------------------------------------------------
以下代码是本基础框架包含的现成的函数，如打开、显示、存储图像文件的代码，同学们可以不去深入研究
--------------------------------------------------------------------------------------------------*/

// CChildView的构造函数和析构函数以及消息映射表(更详细的内容请参考C++及MFC的经典书籍)

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
// 程序中的大部分按钮对应的现成的函数
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

//本段代码在每一次消息循环中被调用来以一定大小比例显示当前图片
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

//本段代码实现打开文件对话框并选择一个图片文件并显示
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
//本段代码实现将当前的图片存储至本地
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



//本段代码查询图像相关信息
void CChildView::OnImageInfo()
{
	CInfoDlg infoDlg(imgOriginal);
	infoDlg.DoModal();
}

//本段代码改变图像显示大小
void CChildView::OnChangeSize(UINT nID)
{
	m_nImageSize = (SizesEnum)(nID - ID_SIZE_BASE);
	Invalidate();
	UpdateWindow();
}

//下面四段代码以不同的大小显示图片
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



