#ifndef ACTIONLISTVIEW_H
#define ACTIONLISTVIEW_H

#include <QListWidget>
#include <QMouseEvent>

namespace Ui {
class ActionListView;
}

class ActionListView : public QListWidget
{
    Q_OBJECT

public:
    explicit ActionListView(QWidget *parent = 0);
    ~ActionListView();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    Ui::ActionListView *ui;

    QPoint startPos;
};

#endif // ACTIONLISTVIEW_H
