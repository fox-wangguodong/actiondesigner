#include "actionlistview.h"
#include "poselistview.h"
#include "ui_actionlistview.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>

ActionListView::ActionListView(QWidget *parent) :
    QListWidget(parent),
    ui(new Ui::ActionListView)
{
    ui->setupUi(this);
    setAcceptDrops(true);    //允许拖放
}

ActionListView::~ActionListView()
{
    delete ui;
}

void ActionListView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        startPos = event->pos();    //获取鼠标按下时候的坐标
    }
    QListWidget::mousePressEvent(event);
}

void ActionListView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance()){

            QListWidgetItem *item = currentItem();    //当前被拖动的选项
            if (item) {

                QMimeData *mimeData = new QMimeData;
                mimeData->setText(item->text());

                QDrag *drag = new QDrag(this);
                drag->setMimeData(mimeData);
                if (drag->exec(Qt::MoveAction) == Qt::MoveAction){        //进行拖动操作
                    delete item;
                }
            }
        }
    }
    QListWidget::mouseMoveEvent(event);
}

void ActionListView::dragEnterEvent(QDragEnterEvent *event)
{
//    PoseListView *source = qobject_cast<PoseListView *>(event->source());
//    if (source) {
//        event->setDropAction(Qt::MoveAction);//确认是一个移动的操作
//        event->accept();
//    }
}

void ActionListView::dragMoveEvent(QDragMoveEvent *event)
{
//    PoseListView *source = qobject_cast<PoseListView *>(event->source());
//    if (source) {
//        event->setDropAction(Qt::MoveAction);
//        event->accept();
//    }
}

void ActionListView::dropEvent(QDropEvent *event)
{
    PoseListView *source = qobject_cast<PoseListView *>(event->source());
//    if (source) {

//        const QMimeData *localMimeData = event->mimeData();
//        addItem(localMimeData->text());//得到数据并增加到列表中

//        event->setDropAction(Qt::MoveAction);
//        event->accept();
//    }
}

