#include "exitdialog.h"
#include "ui_exitdialog.h"

ExitDialog::ExitDialog(QWidget *parent, CXX_ISRS::DialogType dialog_type) :
    QDialog(parent),
    ui(new Ui::ExitDialog),
    type(dialog_type)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    this->setAttribute(Qt::WA_DeleteOnClose, true);
}

ExitDialog::~ExitDialog()
{
    delete ui;
}

void ExitDialog::mousePressEvent(QMouseEvent *mouse_press_event)
{
    mouse_cur_pos = mouse_press_event->globalPosition().toPoint();
}

void ExitDialog::mouseMoveEvent(QMouseEvent *mouse_move_event)
{
    mouse_new_pos = QPoint(mouse_move_event->globalPosition().toPoint() - mouse_cur_pos);
    this->move(this->x() + mouse_new_pos.x(), this->y() + mouse_new_pos.y());
    mouse_cur_pos = mouse_move_event->globalPosition().toPoint();
}

void ExitDialog::on_yes_button_clicked()
{
    emit exit_yes_signal();
}

void ExitDialog::on_no_button_clicked()
{
    emit exit_no_signal();
}

