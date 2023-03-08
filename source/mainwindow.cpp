#include <mainwindow.h>
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    load_configuration();

    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_configuration()
{
    config.connect_to_database();

    user_dao = new UserDAO(config.get_connection());
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

void MainWindow::on_login_button_clicked()
{
    std::string username = ui->username->text().toStdString();
    std::string password = ui->password->text().toStdString();

    User login_user = user_dao->get_user_by_username(username);

    if(login_user.username == username & login_user.password == password)
    {
        std::cout << "Login sucess ! Welcome " << login_user.fullname << std::endl;

        navigation_menu = new Navigationmenu();
        connect(navigation_menu, SIGNAL( back_to_login_signal() ), this, SLOT( back_to_login_slot() ));

        navigation_menu->show();

        ui->username->clear();
        ui->password->clear();

        this->close();
    }
    else
    {
        std::cout << "Login failed !" << std::endl;
    }
}

void MainWindow::back_to_login_slot()
{
    this->show();
}

