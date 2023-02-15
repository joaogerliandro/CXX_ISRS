#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_quit_button_clicked()
{
    this->close();
}

void MainWindow::on_minimize_button_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}

void MainWindow::mousePressEvent(QMouseEvent *mouse_press_event)
{
    mouse_cur_pos = mouse_press_event->globalPosition().toPoint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *mouse_move_event)
{
    mouse_new_pos = QPoint(mouse_move_event->globalPosition().toPoint() - mouse_cur_pos);
    this->move(this->x() + mouse_new_pos.x(), this->y() + mouse_new_pos.y());
    mouse_cur_pos = mouse_move_event->globalPosition().toPoint();
}



