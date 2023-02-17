#pragma once

#include <common.h>

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

    private slots:
        void mousePressEvent(QMouseEvent *mouse_press_event);

        void mouseMoveEvent(QMouseEvent *mouse_move_event);
};

