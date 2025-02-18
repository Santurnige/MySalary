#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtWidgets>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_ui_addNote_button_clicked();

    void on_ui_screachNotes_button_clicked();

    void on_ui_deleteNote_button_clicked();

    void on_ui_selectAll_button_clicked();

private:
    //Методы
    QString getMonthName(int monthNumber);//Получить названия по номеру
    int getMonthNumber(QString monthName);//Получить названия по номеру
    void createDatabase(); //Создание Базы Данных(database.cpp)



    //Методы связанные с SQL
    void setTotalSalary();// Установливает QLCDNumber 'Всего Заработано' на главном меню


    //Sql Объекты
    QSqlDatabase sql_database;
    QSqlQuery *sql_query;
    QSqlQueryModel *sql_model;
    QString lastRequest; // Последний Sql запрос

    //Объекты Текущего дня
    int c_month;
    int c_day;
    int c_year;


    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
