#include "actionlistview.h"
#include "poselibview.h"
#include "poselistview.h"
#include "ui_poselistview.h"
#include <QApplication>
#include <QDebug>
#include <QDrag>
#include <QMenu>
#include <QMimeData>
#include <QPainter>
#include <QTextOption>
#include <QTimer>

PoseListView::PoseListView(QWidget *parent) :
    QListWidget(parent),
    ui(new Ui::PoseListView)
{
    ui->setupUi(this);
    setAcceptDrops(true);    //允许拖放

    mLabel = new QLabel(this);
    mLabel->setFixedHeight(2);
    mLabel->setGeometry(1, 0, width(), 2);
    mLabel->setStyleSheet("border: 1px solid #8B7500;");
    mLabel->hide();
}

PoseListView::~PoseListView()
{
    delete ui;
}

void PoseListView::mousePressEvent(QMouseEvent *event)
{
    QListWidget::mousePressEvent(event);

    if(event->buttons() == Qt::RightButton)
    {
        QMenu menu;
        //添加菜单项，指定图标、名称、响应函数
        menu.addAction(QIcon("E:\\QtProjects\\untitled\\res\\obj\\timg.jpg"), QStringLiteral("添加"),this,SLOT(OnBscGroupRightAction()));
        //在鼠标位置显示
        menu.exec(QCursor::pos());
    }
}

void PoseListView::mouseMoveEvent(QMouseEvent *event)
{
    QListWidgetItem *move_item = currentItem();    //当前被拖动的选项

    QModelIndex localIndexFromItem = indexFromItem(move_item);
    qDebug()<<localIndexFromItem.row();

    if (event->buttons() == Qt::LeftButton)
    {
        if (move_item)
        {
            QMimeData *mimeData = new QMimeData;
            mimeData->setText(move_item->text());

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);

            QPixmap drag_img(width(),25);//构造一副图片
            drag_img.fill(QColor(255,255,255,200));
            QPainter painter(&drag_img);
            painter.setPen(QColor(0, 0, 0));
            painter.drawText(QRectF(0,0,width(),25),move_item->text(),QTextOption(Qt::AlignVCenter));
            drag->setPixmap(drag_img);
            mLabel->show();
            if (drag->exec(Qt::MoveAction) == Qt::MoveAction){        //进行拖动操作
                delete move_item;
            }
            mLabel->hide();
        }
    }
    QListWidget::mouseMoveEvent(event);
}

void PoseListView::dragEnterEvent(QDragEnterEvent *event)
{
    PoseLibView *source_PoseLibView = qobject_cast<PoseLibView *>(event->source());
    if (source_PoseLibView)
    {
        mLabel->show();

        event->acceptProposedAction();
        event->accept();//设置可接受flag
    }

    PoseListView *source_PoseListView = qobject_cast<PoseListView *>(event->source());
    if (source_PoseListView)
    {
        event->acceptProposedAction();
        event->accept();//设置可接受flag
    }
}

void PoseListView::dragMoveEvent(QDragMoveEvent *event)
{
    PoseLibView *source_PoseLibView = qobject_cast<PoseLibView *>(event->source());
    if (source_PoseLibView)
    {
        QListWidgetItem *localItem = this->itemAt(event->pos());
        QModelIndex localIndexFromItem = indexFromItem(localItem);
        mLabel->setGeometry(1, localIndexFromItem.row()*30, width() - 2, 2);

        event->acceptProposedAction();
        event->accept();//设置可接受flag
    }
    PoseListView *source_PoseListView = qobject_cast<PoseListView *>(event->source());
    if(source_PoseListView)
    {

        QListWidgetItem *localItem = this->itemAt(event->pos());
        QModelIndex localIndexFromItem = indexFromItem(localItem);
        mLabel->setGeometry(1, localIndexFromItem.row()*30, width() - 2, 2);

        event->acceptProposedAction();
        event->accept();//设置可接受flag
    }
}

void PoseListView::dropEvent(QDropEvent *event)
{
    PoseLibView *source_PoseLibView = qobject_cast<PoseLibView*>(event->source());
    if (source_PoseLibView)
    {
        const QMimeData *localMimeData = event->mimeData();

        /*构造新的item*/
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(localMimeData->text());
        item->setBackgroundColor(QColor(255,255,0,200));
        item->setSizeHint(QSize(60, 30));

        /*根据鼠标位置获取当前Item，根据item获取索引号，通过localIndexFromItem.row()获取当前处于列表的第几行*/
        QListWidgetItem *localItem = this->itemAt(event->pos());
        QModelIndex localIndexFromItem = indexFromItem(localItem);
        if(localIndexFromItem.row() != -1){
            insertItem(localIndexFromItem.row(),item);//在此处插入新的item
        }else {
            addItem(item);//在末尾添加Item
        }

        mLabel->hide();

        //设置可接受flag
        event->acceptProposedAction();
        event->accept();
    }

    PoseListView *source_PoseListView = qobject_cast<PoseListView *>(event->source());
    if(source_PoseListView)
    {
        const QMimeData *localMimeData = event->mimeData();

        /*创建新的Item*/
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(localMimeData->text());
        item->setBackgroundColor(QColor(255,255,0,200));
        item->setSizeHint(QSize(60, 30));

        /*根据鼠标位置获取当前Item，根据item获取索引号，通过localIndexFromItem.row()获取当前处于列表的第几行*/
        QListWidgetItem *localItem = this->itemAt(event->pos());
        QModelIndex localIndexFromItem = indexFromItem(localItem);
        if(localIndexFromItem.row() != -1){
            insertItem(localIndexFromItem.row(),item);//在此处插入新的item
        }else {
            addItem(item);//在末尾添加Item
        }

        //设置可接受flag
        event->acceptProposedAction();
        event->accept();
    }
}

