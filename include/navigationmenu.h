#pragma once

#include <common.h>
#include <exitdialog.h>

namespace Ui {
class Navigationmenu;
}

class Navigationmenu : public QMainWindow
{
    Q_OBJECT

    public:
        explicit Navigationmenu(QWidget *parent = nullptr);
        ~Navigationmenu();

    private:
        Ui::Navigationmenu *ui;

        QPoint mouse_cur_pos;
        QPoint mouse_new_pos;
        QPoint window_cur_pos;

        bool maximized = false;
        bool exitwin_open = false;

        QSize window_cur_size;

        ExitDialog *exit_dialog;

        void connect_slots();

    signals:
        void back_to_login_signal();

    private slots:
        void mousePressEvent(QMouseEvent *mouse_press_event);

        void mouseMoveEvent(QMouseEvent *mouse_move_event);

        void on_minimize_button_clicked();

        void on_resize_button_clicked();

        void on_quit_button_clicked();

        void exit_yes_slot();

        void exit_no_slot();
        void on_logoff_button_clicked();
};

