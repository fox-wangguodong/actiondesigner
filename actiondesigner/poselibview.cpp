#include "poselibview.h"
#include "poselistview.h"
#include "ui_poselibview.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QPainter>


PoseLibView::PoseLibView(QWidget *parent) :
    QListWidget(parent),
    ui(new Ui::PoseLibView)
{
    ui->setupUi(this);
}

PoseLibView::~PoseLibView()
{
    delete ui;
}


void PoseLibView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {

        QListWidgetItem *item = currentItem();    //当前被拖动的选项
        if (item)
        {
            QMimeData *mimeData = new QMimeData;
            mimeData->setText(item->text());

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);

            QPixmap drag_img(width(),25);//构造一副图片
            drag_img.fill(QColor(255,255,255,200));
            QPainter painter(&drag_img);
            painter.setPen(QColor(0, 0, 0));
            painter.drawText(QRectF(0,0,width(),25),item->text(),QTextOption(Qt::AlignVCenter));
            drag->setPixmap(drag_img);

            if (drag->exec(Qt::MoveAction) == Qt::MoveAction){        //进行拖动操作

            }
        }
    }
    QListWidget::mouseMoveEvent(event);
}
