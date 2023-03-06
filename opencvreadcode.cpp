#include "opencvreadcode.h"

OpencvReadCode::OpencvReadCode(QObject *parent) : QObject(parent)
{

}

void OpencvReadCode::ReadQRCode()
{
    if(_source_image.rows>0&&_source_image.cols>0)
    {
        _code_str=QString::fromStdString("");
        cv::QRCodeDetector qr_code;
        std::vector<cv::Point> list;
        cv::Mat point_code_,rectifiedImage_;

        _target_image=_source_image.clone();

        std::string code_data_ = qr_code.detectAndDecode(_target_image,
                                                         point_code_,
                                                         rectifiedImage_);
        ///判断条码结果
        if(code_data_.length()>0)
        {
            int n = point_code_.cols;
            for(int i = 0 ; i < n ; i++)
            {
                // 下面有点小问题，自己画线
                Point2i one_point_(point_code_.at<float>(i,0),
                                   point_code_.at<float>(i,1));

                Point2i two_point_(point_code_.at<float>(((i+1)%n),0),
                                   point_code_.at<float>((i+1) % n,1));
                line(_target_image,
                     one_point_,
                     two_point_,
                     Scalar(255,0,0), 3);
            }

            //rectifiedImage_.convertTo(rectifiedImage_, CV_8UC3);
            //imshow("Rectified QRCode", rectifiedImage_);
            //waitKey(0);
            _code_str=QString::fromStdString(code_data_);
        }

    }
}

void OpencvReadCode::SetImage(QImage image_)
{
    Mat mat = Mat::zeros(image_.height(), image_.width(),image_.format()); //初始化Mat
    switch(image_.format()) //判断image的类型
    {
    case QImage::QImage::Format_Grayscale8:  //灰度图
        mat = Mat(image_.height(), image_.width(),
                  CV_8UC1,(void*)image_.constBits(),image_.bytesPerLine());
        break;
    case QImage::Format_RGB888: //3通道彩色
        mat = Mat(image_.height(), image_.width(),
                  CV_8UC3,(void*)image_.constBits(),image_.bytesPerLine());
        break;
    case QImage::Format_ARGB32: //4通道彩色
        mat = Mat(image_.height(), image_.width(),
                  CV_8UC4,(void*)image_.constBits(),image_.bytesPerLine());
        break;

    case QImage::Format_Indexed8:
        mat = cv::Mat(image_.height(), image_.width(),
                             CV_8UC1, (void*)image_.bits(), image_.bytesPerLine());
        break;

    default:
        ;
    }
    _source_image=mat.clone();
    //     cv::namedWindow("sourceImage",1);
    //     cv::imshow("sourceImage",_source_image);
}

QImage OpencvReadCode::GetResultImage()
{
    if(_code_str.length()>0)
    {
        //判断m的类型，可能是CV_8UC1  CV_8UC2  CV_8UC3  CV_8UC4
        switch(_target_image.type())
        {
        //QIamge 构造函数, ((const uchar *data, 宽(列),高(行), 一行共多少个（字节）通道，宽度*字节数，宏参数)
        case CV_8UC1:
        {
            QImage img((uchar *)_target_image.data,_target_image.cols,_target_image.rows,_target_image.cols * 1,QImage::Format_Grayscale8);
            return img;
        }
            break;
        case CV_8UC3:   //一个像素点由三个字节组成
        {
            //cvtColor(m,m,COLOR_BGR2RGB); BGR转RGB
            QImage img((uchar *)_target_image.data,_target_image.cols,_target_image.rows,_target_image.cols * 3,QImage::Format_RGB888);
            return img.rgbSwapped(); //opencv是BGR  Qt默认是RGB  所以RGB顺序转换
        }
            break;
        case CV_8UC4:
        {
            QImage img((uchar *)_target_image.data,_target_image.cols,_target_image.rows,_target_image.cols * 4,QImage::Format_RGBA8888);
            return img;
        }
            break;
        default:
        {
            QImage img; //如果遇到一个图片均不属于这三种，返回一个空的图片
            return img;
        }
        }
    }
    else
    {
        QImage img; //如果遇到一个图片均不属于这三种，返回一个空的图片
        return img;
    }
}

void OpencvReadCode::ReadQRCodeTest()
{
     QImage image_;//当前的图片
     image_.load("C:\\Users\\Administrator\\Desktop\\tupian\\gray.bmp");

     Mat inputImage;
     //inputImage = imread("‪C:\\Users\\Administrator\\Desktop\\tupian\\1.bmp");
     switch(image_.format()) //判断image的类型
     {
     case QImage::QImage::Format_Grayscale8:  //灰度图
         inputImage = Mat(image_.height(), image_.width(),
                   CV_8UC1,(void*)image_.constBits(),image_.bytesPerLine());
         break;
     case QImage::Format_RGB888: //3通道彩色
         inputImage = Mat(image_.height(), image_.width(),
                   CV_8UC3,(void*)image_.constBits(),image_.bytesPerLine());
         break;
     case QImage::Format_ARGB32: //4通道彩色
         inputImage = Mat(image_.height(), image_.width(),
                   CV_8UC4,(void*)image_.constBits(),image_.bytesPerLine());
         break;
     case QImage::Format_Indexed8:
         inputImage = cv::Mat(image_.height(), image_.width(),
                              CV_8UC1, (void*)image_.bits(), image_.bytesPerLine());
         break;
     default:
         ;
     }

    if(inputImage.rows>0&&inputImage.cols>0)
    {
        QRCodeDetector qrDecoder;

        //namedWindow("Result",0);
        //imshow("Result", inputImage);

        Mat bbox, rectifiedImage;
        std::string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);

        if(data.length()>0)
        {
            int n = bbox.rows;
            for(int i = 0 ; i < n ; i++)
            {
                line(inputImage, Point2i(bbox.at<float>(i,0),bbox.at<float>(i,1)), Point2i(bbox.at<float>((i+1) % n,0), bbox.at<float>((i+1) % n,1)), Scalar(255,0,0), 3);
            }
            imshow("Result", inputImage);
            rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
            imshow("Rectified QRCode", rectifiedImage);
            waitKey(0);
        }
    }
}



