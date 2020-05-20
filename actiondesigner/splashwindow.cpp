#include "splashwindow.h"
#include "ui_splashwindow.h"

#include <QPainter>

SplashWindow::SplashWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SplashWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
}

SplashWindow::~SplashWindow()
{
    delete ui;
}

void SplashWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::gray);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(10);

    painter.setPen(pen);
    //painter.drawChord(0,0,);
    painter.drawEllipse(5,5,this->width()-10,this->height()-10);

    QMainWindow::paintEvent(event);
}
