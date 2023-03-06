#ifndef OPENCVREADCODE_H
#define OPENCVREADCODE_H

#include <QObject>
#include <opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\types_c.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/imgproc/imgproc_c.h>
#include "opencv2/opencv.hpp"
#include "QImage"


using namespace std;
using namespace cv;

class OpencvReadCode : public QObject
{
    Q_OBJECT
public:
    explicit OpencvReadCode(QObject *parent = nullptr);
    void ReadQRCode();
    void SetImage(QImage image_);
    QImage GetResultImage();

    void ReadQRCodeTest();///读码测试

signals:

public:
    /**
@brief 条码的结果
*/
    QString _code_str;

    /**
@brief 原图
*/
    cv::Mat _source_image;
    /**
@brief 结果图片
*/
    cv::Mat _target_image;
};

#endif // OPENCVREADCODE_H
