#include "posesettingwidget.h"
#include "ui_posesettingwidget.h"

PoseSettingWidget::PoseSettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PoseSettingWidget)
{
    ui->setupUi(this);
}

PoseSettingWidget::~PoseSettingWidget()
{
    delete ui;
}

void PoseSettingWidget::setOpenglView(OpenglView *openglView)
{
    this->openglView = openglView;
}

void PoseSettingWidget::on_head_doubleSpinBox_valueChanged(double arg1)
{
    openglView->g_HeadTheta = arg1;
    openglView->update();
}

void PoseSettingWidget::on_waist_doubleSpinBox_valueChanged(double arg1)
{
    openglView->g_NeckTheta = arg1;
    openglView->update();

}


void PoseSettingWidget::on_left_forword_high_doubleSpinBox_valueChanged(double arg1)
{
    openglView->g_dLFTheta1 = arg1;
    openglView->update();

}

void PoseSettingWidget::on_right_forword_high_doubleSpinBox_valueChanged(double arg1)
{
    openglView->g_dRFTheta1 = arg1;
    openglView->update();

}


void PoseSettingWidget::on_left_forword_mid_doubleSpinBox_valueChanged(double arg1)
{
    openglView->g_dLFTheta2 = arg1;
    openglView->update();

}

void PoseSettingWidget::on_right_forword_mid_doubleSpinBox_valueChanged(double arg1)
{
    openglView->g_dRFTheta2 = arg1;
    openglView->update();

}

void PoseSettingWidget::on_left_forword_low_doubleSpinBox_valueChanged(double arg1)
{
    openglView->g_dLFTheta3 = arg1;
    openglView->update();

}

void PoseSettingWidget::on_right_forword_low_doubleSpinBox_valueChanged(double arg1)
{
    openglView->g_dRFTheta3 = arg1;
    openglView->update();

}

void PoseSettingWidget::on_left_backword_high_doubleSpinBox_valueChanged(double arg1)
{
    openglView->g_dLHTheta1 = arg1;
    openglView->update();

}

void PoseSettingWidget::on_right_backword_high_doubleSpinBox_valueChanged(double arg1)
{
    openglView->g_dRHTheta1 = arg1;
    openglView->update();

}

void PoseSettingWidget::on_left_backword_mid_doubleSpinBox_valueChanged(double arg1)
{
    openglView->g_dLHTheta2 = arg1;
    openglView->update();

}

void PoseSettingWidget::on_right_backword_mid_doubleSpinBox_valueChanged(double arg1)
{
    openglView->g_dRHTheta2 = arg1;
    openglView->update();

}

void PoseSettingWidget::on_left_backword_low_doubleSpinBox_valueChanged(double arg1)
{
    openglView->g_dLHTheta3 = arg1;
    openglView->update();

}

void PoseSettingWidget::on_right_backword_low_doubleSpinBox_valueChanged(double arg1)
{
    openglView->g_dRHTheta3 = arg1;
    openglView->update();

}
