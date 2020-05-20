#ifndef POSELISTVIEW_H
#define POSELISTVIEW_H

#include <QLabel>
#include <QListWidget>
#include <QMouseEvent>
#include <QWidget>

namespace Ui {
class PoseListView;
}

class PoseListView : public QListWidget
{
    Q_OBJECT
public:
    explicit PoseListView(QWidget *parent = 0);
    ~PoseListView();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    Ui::PoseListView *ui;
    QLabel* mLabel;             //高度设为2，用做指示线

};

#endif // POSELISTVIEW_H
