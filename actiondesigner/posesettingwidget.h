#ifndef POSESETTINGWIDGET_H
#define POSESETTINGWIDGET_H


#include "openglview.h"

#include <QWidget>

namespace Ui {
class PoseSettingWidget;
}


class PoseSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PoseSettingWidget(QWidget *parent = 0);
    ~PoseSettingWidget();


    void setOpenglView(OpenglView *openglView);



private slots:
    void on_left_forword_high_doubleSpinBox_valueChanged(double arg1);

    void on_right_forword_high_doubleSpinBox_valueChanged(double arg1);

    void on_head_doubleSpinBox_valueChanged(double arg1);

    void on_waist_doubleSpinBox_valueChanged(double arg1);

    void on_left_forword_mid_doubleSpinBox_valueChanged(double arg1);

    void on_right_forword_mid_doubleSpinBox_valueChanged(double arg1);

    void on_left_forword_low_doubleSpinBox_valueChanged(double arg1);

    void on_right_forword_low_doubleSpinBox_valueChanged(double arg1);

    void on_left_backword_high_doubleSpinBox_valueChanged(double arg1);

    void on_right_backword_high_doubleSpinBox_valueChanged(double arg1);

    void on_left_backword_mid_doubleSpinBox_valueChanged(double arg1);

    void on_right_backword_mid_doubleSpinBox_valueChanged(double arg1);

    void on_left_backword_low_doubleSpinBox_valueChanged(double arg1);

    void on_right_backword_low_doubleSpinBox_valueChanged(double arg1);

private:
    Ui::PoseSettingWidget *ui;

    OpenglView *openglView;

};

#endif // POSESETTINGWIDGET_H
