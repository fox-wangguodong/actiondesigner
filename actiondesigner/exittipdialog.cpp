#include "exittipdialog.h"
#include "ui_exittipdialog.h"

#include <QMouseEvent>
#include <QPainter>

ExitTipDialog::ExitTipDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExitTipDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    isExit = false;
}

ExitTipDialog::~ExitTipDialog()
{
    delete ui;
}

void ExitTipDialog::on_btn_exit_clicked()
{
    isExit = true;
    this->close();
}

void ExitTipDialog::on_btn_cancel_clicked()
{
    isExit = false;
    this->close();
}

void ExitTipDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        this->close();
    }
}

void ExitTipDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);// 反锯齿;


    QRect rect = this->rect();
    painter.setBrush(QBrush(Qt::gray)); // 灰色背景
    //painter.setPen(Qt::transparent);//画笔透明
    painter.drawRoundedRect(rect, 15, 15);//绘制圆角矩形

    QWidget::paintEvent(event);
}

bool ExitTipDialog::getIsExit() const
{
    return isExit;
}
