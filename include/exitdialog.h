#pragma once

#include <common.h>

namespace Ui {
class ExitDialog;
}

class ExitDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit ExitDialog(QWidget *parent = nullptr);
        ~ExitDialog();

    private:
        Ui::ExitDialog *ui;

        QPoint mouse_cur_pos;
        QPoint mouse_new_pos;

    signals:
        void exit_yes_signal();

        void exit_no_signal();

    private slots:
        void mousePressEvent(QMouseEvent *mouse_press_event);

        void mouseMoveEvent(QMouseEvent *mouse_move_event);

        void on_yes_button_clicked();

        void on_no_button_clicked();
};

