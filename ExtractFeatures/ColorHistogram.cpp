//计算HSV颜色直方图
//用十二维向量表示
#include "ColorHistogram.h"
#include "atlimage.h"
#include <iostream>
#include <string>
using namespace std;
#include <fstream>

#define MAX_IMAGE_NAME 100

void colorHistogram()
{
	ifstream inputFile("imagelist.txt", ios::in);//从文本文档中读入图片名
	ofstream outputFile("ColorHistogram.txt", ios::out);//将颜色直方图的结果写入该文件中
	char lineStr[MAX_IMAGE_NAME];//存放每行读入的字符串
	
	while (!inputFile.eof())
	{
		inputFile.getline(lineStr, MAX_IMAGE_NAME);
		//加载图片
		CImage image;

		int iHeight, iWidth;
		BYTE byteR, byteG, byteB;
		int colorHistogram[12] = { 0 };

		char imagePath[6 + MAX_IMAGE_NAME]="image/";
		for (int i = 0; i < MAX_IMAGE_NAME; i++)
			imagePath[6 + i] = lineStr[i];
		//转换为相对路径

		image.Load(imagePath);

		iHeight = image.GetHeight();
		iWidth = image.GetWidth();

		for (int iRow = 0; iRow<iWidth; iRow++)
			for (int iCol = 0; iCol<iHeight; iCol++)
			{
				COLORREF colorref = image.GetPixel(iRow, iCol);

				if (colorref == CLR_INVALID)
				{
					printf("Out of range!");
					continue;
				}

				byteR = GetRValue(colorref);
				byteG = GetGValue(colorref);
				byteB = GetBValue(colorref);

				double R = double(byteR) / 0xff;
				double G = double(byteG) / 0xff;
				double B = double(byteB) / 0xff;
				double tmp, minByte, maxByte, delta;

				tmp = R>G ? G : R;
				minByte = tmp>B ? B : tmp;
				tmp = R>G ? R : G;
				maxByte = tmp>B ? tmp : B;

				//RGB转换为HSV
				double iV, iS, iH;
				delta = maxByte - minByte;
				iV = maxByte;//V
				if (maxByte != 0)
					iS = delta / maxByte;//S
				else
				{
					iS = 0;
					iH = 0;
				}
				if (delta == 0)
				{
					iH = 0;
				}
				else if (R == maxByte)
				{
					if (G >= B)
						iH = (G - B) / delta;
					else
						iH = (G - B) / delta + 6.0;
				}
				else if (G == maxByte)
					iH = 2.0 + (B - R) / delta;
				else if (B == maxByte)
					iH = 4.0 + (R - G) / delta;
				iH *= 60.0;

				if (iH <= 60.0&&iS <= 0.5)
					colorHistogram[0]++;
				else if (iH <= 60.0&&iS>0.5)
					colorHistogram[1]++;
				else if (iH <= 120.0&&iS <= 0.5)
					colorHistogram[2]++;
				else if (iH <= 120.0&&iS>0.5)
					colorHistogram[3]++;
				else if (iH <= 180.0&&iS <= 0.5)
					colorHistogram[4]++;
				else if (iH <= 180.0&&iS>0.5)
					colorHistogram[5]++;
				else if (iH <= 240.0&&iS <= 0.5)
					colorHistogram[6]++;
				else if (iH <= 240.0&&iS>0.5)
					colorHistogram[7]++;
				else if (iH <= 300.0&&iS <= 0.5)
					colorHistogram[8]++;
				else if (iH <= 300.0&&iS>0.5)
					colorHistogram[9]++;
				else if (iH <= 360.0&&iS <= 0.5)
					colorHistogram[10]++;
				else
					colorHistogram[11]++;


				//printf("%Pixel at (%d,%d) is: R=0x%x,G=0x%x,B=0x%x\n",iRow, iCol, byteR, byteG, byteB);
				//printf("%Pixel at (%d,%d) is: iH=%lf,iS=%lf,iV=%lf\n",iRow, iCol, H, iS, iV);

			}
		int pixel = 0;
		for (int i = 0; i < 12; i++)
			pixel +=  colorHistogram[i];

		double percentageOfColor[12] = { 0.0 };

		outputFile << lineStr << '(';
		for (int i = 0; i < 12; i++)
		{
			percentageOfColor[i] = MAX_IMAGE_NAME * double(colorHistogram[i]) / double(pixel);
			outputFile << percentageOfColor[i] << ' ';
		}
		outputFile << ')' << endl;

		cout << lineStr << endl;

		image.GetBits();

		image.Destroy();

		//getchar();
	}
	inputFile.close();
	outputFile.close();
}
