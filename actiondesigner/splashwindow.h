#ifndef SPLASHWINDOW_H
#define SPLASHWINDOW_H

#include <QMainWindow>

namespace Ui {
class SplashWindow;
}

class SplashWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SplashWindow(QWidget *parent = 0);
    ~SplashWindow();

private:
    Ui::SplashWindow *ui;


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);


};

#endif // SPLASHWINDOW_H
