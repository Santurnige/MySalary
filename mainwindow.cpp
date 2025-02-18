#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    c_day = QDate::currentDate().day();
    c_month = QDate::currentDate().month();
    c_year = QDate::currentDate().year();

    // Прочие Настройки
    ui->ui_mainTabWidget->setCurrentIndex(0);

    ui->ui_currentMonth_Label->setText(getMonthName(c_month));// Текст Текущий Месяц
    ui->ui_text_thisMonth_label->setText("За " + getMonthName(c_month));
    ui->ui_chooseYear_spinBox->setValue(c_year);
    ui->ui_addMonth_comboBox->setCurrentText(getMonthName(c_month));
    ui->ui_addYear_spinBox->setValue(c_year);
    ui->ui_addDay_spinBox->setValue(c_day);
    ui->ui_chooseMonth_comboBox->setCurrentIndex(c_month-1);

    // Время На главном меню
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout,[this](){

        ui->ui_currentTime_Label->setText(QDateTime::currentDateTime().toString("hh:mm:ss"));
    });
    timer->start(1000);


    createDatabase();// Создаем Базу Данных
    on_ui_screachNotes_button_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}


QString MainWindow::getMonthName(int monthNumber) //Получить названия по номеру
{
    // Список названий месяцев
    QStringList month = {"", "Январь", "Февраль", "Март", "Апрель", "Май",
                         "Июнь", "Июль", "Август", "Сентябрь",
                         "Октябрь", "Ноябрь", "Декабрь"};

    // Проверяем, что номер месяца находится в допустимом диапазоне (1-12)
    return monthNumber > 0 && monthNumber < 13 ? month[monthNumber] : "";
}

