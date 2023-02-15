#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;

        QPoint mouse_cur_pos;
        QPoint mouse_new_pos;

    private slots:
        void on_quit_button_clicked();

        void on_minimize_button_clicked();

        void mousePressEvent(QMouseEvent *mouse_press_event);

        void mouseMoveEvent(QMouseEvent *mouse_move_event);
};
