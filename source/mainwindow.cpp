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
    connect(this, SIGNAL( fade_in_signal() ), this, SLOT( fade_in_slot() ));
    connect(this, SIGNAL( fade_out_signal() ), this, SLOT( fade_out_slot() ));

    config.connect_to_database();

    user_dao = new UserDAO(config.get_connection());
}

void MainWindow::on_quit_button_clicked()
{
    config.disconnect_to_database();

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
    try
    {
        std::string username = ui->username->text().toStdString();
        std::string password = ui->password->text().toStdString();

        if(!username.empty() & !password.empty())
        {
            User login_user = user_dao->get_user_by_username(username);

            if(!login_user.username.empty() & !login_user.password.empty())
            {
                if(login_user.status == CXX_ISRS::BLOCKED)
                    throw CXX_ISRS::LoginException("User blocked ! Try again later or contact support.", CXX_ISRS::ExceptionType::INFO);

                if(login_user.password == password)
                {
                    login_user.bad_password_count = 0;
                    user_dao->update_user(login_user);

                    navigation_menu = new Navigationmenu();
                    connect(navigation_menu, SIGNAL( back_to_login_signal() ), this, SLOT( back_to_login_slot() ));

                    navigation_menu->show();

                    clear_interface();

                    this->close();
                }
                else
                {
                    login_user.bad_password_count++;

                    if(login_user.bad_password_count >= 3)
                        login_user.status = CXX_ISRS::UserStatus::BLOCKED;

                    user_dao->update_user(login_user);

                    throw CXX_ISRS::LoginException("Login failed ! Wrong password !", CXX_ISRS::ExceptionType::ERROR);
                }
            }
            else
            {
                throw CXX_ISRS::LoginException("Login failed ! User not found !", CXX_ISRS::ExceptionType::ERROR);
            }
        }
        else
        {
            throw CXX_ISRS::LoginException("Can't login ! The credentials can't be empty !", CXX_ISRS::ExceptionType::WARNING);
        }
    }
    catch (CXX_ISRS::LoginException &ex)
    {
        throw_popup(ex);
    }
}

void MainWindow::back_to_login_slot()
{
    this->show();
}

void MainWindow::throw_popup(CXX_ISRS::LoginException &ex)
{
    ui->exception_message->setText(QString::fromStdString(ex.what()));

    switch(ex.what_type())
    {
        case CXX_ISRS::ExceptionType::INFO:
            show_popup(30, 124, 40);
            break;
        case CXX_ISRS::ExceptionType::WARNING:
            show_popup(250, 210, 50);
            break;
        case CXX_ISRS::ExceptionType::ERROR:
            show_popup(150, 2, 0);
            break;
    }
}

void MainWindow::clear_interface()
{
    ui->username->clear();
    ui->password->clear();

    ui->exception_popup->setStyleSheet("");
    ui->exception_message->setText("");
}

void MainWindow::show_popup(uint8_t r, uint8_t g, uint8_t b)
{
    std::string ex_stylesheet = std::format("background-color: rgb({}, {}, {});\n"
                                            "border-radius: 15px;", r, g, b);

    ui->exception_popup->setStyleSheet(QString::fromStdString(ex_stylesheet));

    emit fade_in_signal();
}

void MainWindow::fade_in_slot()
{
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    ui->exception_popup->setGraphicsEffect(effect);

    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    connect(animation, SIGNAL( finished() ), this, SLOT( fade_delay_slot() ));

    animation->setDuration(1500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setEasingCurve(QEasingCurve::InBack);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void MainWindow::fade_out_slot()
{
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    ui->exception_popup->setGraphicsEffect(effect);

    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(1500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void MainWindow::fade_delay_slot()
{
    QTimer::singleShot(2000, this, SLOT( fade_out_slot() ));
}

