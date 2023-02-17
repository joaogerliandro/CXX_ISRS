#include "navigationmenu.h"
#include "ui_navigationmenu.h"

Navigationmenu::Navigationmenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Navigationmenu)
{
    ui->setupUi(this);
}

Navigationmenu::~Navigationmenu()
{
    delete ui;
}

void Navigationmenu::mousePressEvent(QMouseEvent *mouse_press_event)
{
    mouse_cur_pos = mouse_press_event->globalPosition().toPoint();
}

void Navigationmenu::mouseMoveEvent(QMouseEvent *mouse_move_event)
{
    mouse_new_pos = QPoint(mouse_move_event->globalPosition().toPoint() - mouse_cur_pos);
    this->move(this->x() + mouse_new_pos.x(), this->y() + mouse_new_pos.y());
    mouse_cur_pos = mouse_move_event->globalPosition().toPoint();
}
