#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ///设置大小
    resize(800, 600);

    centralwidget = new QWidget(this);
    centralwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0)"));

    gridLayout =new QGridLayout(centralwidget);
    verticalLayout =new QVBoxLayout(centralwidget);
    gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

    horizontalLayout_btn=new QHBoxLayout(centralwidget);

    loadImageButton=new QPushButton(centralwidget);
    loadImageButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"
                                                     "color: rgb(255, 255, 255);"
                                                     "border-style:outset;"
                                                     "border-width: 2px;"
                                                     "border-color: rgb(200, 200, 200);"));

    loadImageButton->setMinimumSize(QSize(150,50));
    loadImageButton->setMaximumHeight(50);
    loadImageButton->setText(QString("LoadImage"));
    horizontalLayout_btn->addWidget(loadImageButton);

    readQRCodeButton=new QPushButton(centralwidget);
    readQRCodeButton->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"
                                                     "color: rgb(255, 255, 255);"
                                                     "border-style:outset;"
                                                     "border-width: 2px;"
                                                     "border-color: rgb(200, 200, 200);"));

    readQRCodeButton->setMinimumSize(QSize(150,50));
    readQRCodeButton->setMaximumHeight(50);
    readQRCodeButton->setText(QString("ReadQRCode"));
    horizontalLayout_btn->addWidget(readQRCodeButton);

    verticalLayout->addLayout(horizontalLayout_btn);

    imageWidget =new ImageWidget(centralwidget);
    imageWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
    verticalLayout->addWidget(imageWidget);

    mesLabel =new  QLabel(centralwidget);
    mesLabel->setMaximumHeight(30);
    mesLabel->setMinimumHeight(30);
    mesLabel->setText("---");
    mesLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
    verticalLayout->addWidget(mesLabel);

    this->setCentralWidget(centralwidget);

    ///链接信号
    connect(loadImageButton,SIGNAL(clicked()), this, SLOT(LoadImage()));
    connect(readQRCodeButton,SIGNAL(clicked()), this, SLOT(ReadQRCode()));

    ///初始化读码工具
    opencvReadCode =new  OpencvReadCode();
}

MainWindow::~MainWindow()
{
}

void MainWindow::LoadImage()
{
    QString curPath=QDir::currentPath();//获取系统当前目录

    //QString dlgTitle=QString::fromLocal8Bit("选择一个文件");  中文会编译不过
    //QString filter=QString::fromLocal8Bit("图片文件(*.jpg *.gif *.png *.bmp)"); //文件过滤器

    QString dlgTitle="choice one image";
    QString filter="image(*.jpg *.gif *.png *.bmp)"; //文件过滤器

    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,"",filter);

    if(aFileName!="")
    {
        imageWidget->setImage(aFileName);
        imageWidget->fitWindow();
    }
}

void MainWindow::ReadQRCode()
{
    if(imageWidget->_imageEixt==true)
    {
        ///给入图片
        opencvReadCode->SetImage(imageWidget->getImage());
        opencvReadCode->ReadQRCode();
        if(opencvReadCode->_code_str.length()>0)
        {
            QImage img_=opencvReadCode->GetResultImage();
            imageWidget->setImage(img_);
            imageWidget->fitWindow();
        }
        QString result_=QString::fromStdString(" 读码的结果:")+opencvReadCode->_code_str;
        mesLabel->setText(result_);

    }
}
