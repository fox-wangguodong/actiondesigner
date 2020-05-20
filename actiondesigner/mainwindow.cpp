#include "exittipdialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags (Qt::Window | Qt::FramelessWindowHint);
    showFullScreen ();
    ui->splitter_3->setGeometry(this->rect());//设置布局位置大小


    ui->poseSettingWidget->setOpenglView(ui->openglView);


    ui->actionListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 隐藏滚动条
    for(int i=0;i<10;i++)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->actionListView);
        item->setText("项目"+QString::number(i));
        item->setBackgroundColor(QColor(255,255,0,200));


        QImage img;
        img.load(":/img/timg.jpg");
        QBrush brush;
        brush.setTextureImage(img);
        item->setBackground(brush);
        item->setSizeHint(QSize(60, 62));

        ui->actionListView->setItemWidget(item,new QWidget());
        ui->actionListView->addItem(item);
    }

    ui->poseListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for(int i=0;i<10;i++)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->poseListView);
        item->setText("项目"+QString::number(i));
        item->setBackgroundColor(QColor(255,255,0,200));
        item->setSizeHint(QSize(60, 30));
        ui->poseListView->addItem(item);
    }

    ui->poseLibView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for(int i=0;i<30;i++)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->poseLibView);
        item->setText("项目"+QString::number(i));
        item->setBackgroundColor(QColor(255,255,0,200));
        item->setSizeHint(QSize(60, 30));
        ui->poseLibView->addItem(item);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        ExitTipDialog dialog;
        dialog.exec();
        if(dialog.getIsExit() == true)
        {
            this->close();
        }else{

        }
    }
}

void MainWindow::on_lf_valueChanged(double arg1)
{
    ui->openglView->modelInverse.g_dLFPositionX = arg1;
    ui->openglView->modelInverse.GetLFAngle(ui->openglView->g_dLFTheta1,ui->openglView->g_dLFTheta2,ui->openglView->g_dLFTheta3);
    ui->openglView->update();
}

void MainWindow::on_rf_valueChanged(double arg1)
{
    ui->openglView->modelInverse.g_dLFPositionX = arg1;
    ui->openglView->modelInverse.GetRFAngle(ui->openglView->g_dRFTheta1,ui->openglView->g_dRFTheta2,ui->openglView->g_dRFTheta3);
    ui->openglView->update();
}

void MainWindow::on_lh_valueChanged(double arg1)
{

}

void MainWindow::on_rh_valueChanged(double arg1)
{

}
