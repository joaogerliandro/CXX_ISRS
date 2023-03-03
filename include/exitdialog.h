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

    private slots:
        void mousePressEvent(QMouseEvent *mouse_press_event);

        void mouseMoveEvent(QMouseEvent *mouse_move_event);

        void on_yes_button_clicked();
};

