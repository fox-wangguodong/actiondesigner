#ifndef POSELIBVIEW_H
#define POSELIBVIEW_H

#include <QListWidget>

namespace Ui {
class PoseLibView;
}

class PoseLibView : public QListWidget
{
    Q_OBJECT
public:
    explicit PoseLibView(QWidget *parent = 0);
    ~PoseLibView();



protected:
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::PoseLibView *ui;
};

#endif // POSELIBVIEW_H
