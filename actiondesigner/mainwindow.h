#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_lf_valueChanged(double arg1);
    void on_rf_valueChanged(double arg1);
    void on_lh_valueChanged(double arg1);
    void on_rh_valueChanged(double arg1);
};

#endif // MAINWINDOW_H
