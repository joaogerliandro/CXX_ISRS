#include "navigationmenu.h"
#include "ui_navigationmenu.h"

Navigationmenu::Navigationmenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Navigationmenu)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
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

void Navigationmenu::on_minimize_button_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}

void Navigationmenu::on_resize_button_clicked()
{
    if(!maximized)
    {
        window_cur_size = this->size();
        window_cur_pos = this->pos();

        ui->resize_button->setStyleSheet
        (
            "QPushButton \n"
            "{\n	"
            "border: none;\n	"
            "border-image: url(:/button_images/assets/buttons/resize_button_unselected.png) 0 0 0 0 stretch stretch;\n"
            "}\n"
            "\n"
            "QPushButton:hover\n"
            "{\n	"
            "border: none;\n	"
            "border-image: url(:/button_images/assets/buttons/resize_button_selected.png) 0 0 0 0 stretch stretch;\n"
            "}"
        );

        this->setWindowState(Qt::WindowMaximized);
    }
    else
    {
        ui->resize_button->setStyleSheet
        (
            "QPushButton \n"
            "{\n	"
            "border: none;\n	"
            "border-image: url(:/button_images/assets/buttons/maximize_button_unselected.png) 0 0 0 0 stretch stretch;\n"
            "}\n"
            "\n"
            "QPushButton:hover\n"
            "{\n	"
            "border: none;\n	"
            "border-image: url(:/button_images/assets/buttons/maximize_button_selected.png) 0 0 0 0 stretch stretch;\n"
            "}"
        );

        this->resize(window_cur_size);
        this->move(window_cur_pos);
    }

    maximized = !maximized;
}

void Navigationmenu::on_quit_button_clicked()
{
    if(!exitwin_open)
    {
        exit_dialog = new ExitDialog(this);
        exit_dialog->show();
    }
}
