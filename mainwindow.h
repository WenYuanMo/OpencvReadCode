#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include <QObject>
#include <QDir>
#include <QFileDialog>
#include <imagewidget.h>
#include <QGridLayout>
#include <opencvreadcode.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    /**
@brief 主要的控件
*/
    QWidget *centralwidget;

    /**
@brief 网格布局
*/
    QGridLayout *gridLayout;

    /**
@brief 主要的垂直布局
*/
    QVBoxLayout *verticalLayout;
    /**
@brief 按钮水平布局
*/
    QHBoxLayout *horizontalLayout_btn;

    /**
@brief 加载图片按钮
*/
    QPushButton *loadImageButton;
    /**
@brief 读码取qr码
*/
    QPushButton *readQRCodeButton;

    /**
@brief 图片显示控件
*/
   ImageWidget  *imageWidget;

   /**
@brief 信息提示
*/
   QLabel *mesLabel;

   /**
@breif opencv读码工具
*/
   OpencvReadCode *opencvReadCode;

public slots:
    /**
@brief 加载一张图片
*/
   void LoadImage();
   /**
@brief 读取qr码
*/
    void ReadQRCode();


};
#endif // MAINWINDOW_H
