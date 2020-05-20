#ifndef EXITTIPDIALOG_H
#define EXITTIPDIALOG_H

#include <QDialog>

namespace Ui {
class ExitTipDialog;
}

class ExitTipDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExitTipDialog(QWidget *parent = 0);
    ~ExitTipDialog();

    bool getIsExit() const;

private slots:
    void on_btn_exit_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::ExitTipDialog *ui;

    bool isExit;


    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;


    void paintEvent(QPaintEvent *event);
};

#endif // EXITTIPDIALOG_H
