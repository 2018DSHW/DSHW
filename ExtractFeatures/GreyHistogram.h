#ifndef GREYHISTOGRAM_H
#define GREYHISTOGRAM_H
#include <cv.h>
#include <highgui.h>

class colorHistogram
{
private:
	int histSize[1]; // 项的数量
	float hranges[2]; // 统计像素的最大值和最小值
	const float* ranges[1];
	int channels[1]; // 仅计算一个通道

public:
	colorHistogram()
	{
		// 准备直灰度方图的参数
		histSize[0] = 256;
		hranges[0] = 0.0f;
		hranges[1] = 255.0f;

		ranges[0] = hranges;
		channels[0] = 0;
	}

	cv::MatND getHistogram(const Mat &image)
	{
		MatND hist;
		// 计算直方图
		calcHist(&image,// 要计算图像的
			1,                // 只计算一幅图像的直方图
			channels,        // 通道数量
			Mat(),            // 不使用掩码
			hist,            // 存放直方图
			1,                // 1D直方图
			histSize,        // 统计的灰度的个数
			ranges);        // 灰度值的范围
		return hist;
	}

	cv::Mat getHistogramImage(const Mat &image)
	{
		MatND hist = getHistogram(image);

		// 最大值，最小值
		double maxVal = 0.0f;
		double minVal = 0.0f;

		minMaxLoc(hist, &minVal, &maxVal);

		//显示直方图的图像
		//cv::Mat histImg(histSize[0], histSize[0], CV_8U, Scalar(255));

		// 设置最高点为nbins的90%
		int hpt = static_cast<int>(0.9 * histSize[0]);
		//每个条目绘制一条垂直线
		for (int h = 0; h < histSize[0]; h++)
		{
			float binVal = hist.at<float>(h);
			int intensity = static_cast<int>(binVal * hpt / maxVal);
			// 两点之间绘制一条直线
			//line(histImg, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar::all(0));
		}
		return histImg;
	}
};

#endif
