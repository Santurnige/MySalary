// Тут Все что связанно с SQL

#include<mainwindow.h>
#include<ui_mainwindow.h>

void MainWindow::createDatabase()
{
    // Инициализация Sql Объектов и Насройка
    sql_database = QSqlDatabase::addDatabase("QSQLITE");
    sql_database.setDatabaseName("Note.db");

    if(!sql_database.open()){
        QMessageBox::warning(this,"Ошибка","Не удалось открыть базу данных!!\n"+sql_database.lastError().text());
    }

    sql_query = new QSqlQuery(sql_database);

    // SQL запрос на создание таблицы!

    QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS "Note" (
            "Id" INTEGER NOT NULL UNIQUE,
            "Year" INTEGER,
            "Month" VARCHAR(15),
            "Day" INTEGER,
            "Total" INTEGER,
            "About" TEXT,
            PRIMARY KEY("id")
        );
    )";

    if(!sql_query->exec(createTableQuery)){ //если не удалось создать таблицу
        QMessageBox::warning(this,"Ошибка","Не удалось создать таблицу!\n"+sql_query->lastError().text());
    }


    sql_model = new QSqlQueryModel(this);

    setTotalSalary();
    ui->ui_mainTableView->setModel(sql_model);
}


// При нажатии на кнопку "Добавить"
void MainWindow::on_ui_addNote_button_clicked()
{

    //Создаем Запрос
    QString queryRequest=QString("INSERT INTO Note('Year','Month','Day','Total','About') VALUES ('%1','%2','%3','%4','%5')")
                        .arg(ui->ui_addYear_spinBox->value())
                        .arg(ui->ui_addMonth_comboBox->currentText())
                        .arg(ui->ui_addDay_spinBox->value())
                        .arg(ui->ui_addTotal_spinBox->value())
                        .arg(ui->ui_addAbout->toPlainText());

    if(!sql_query->exec(queryRequest)){ //Если ошибка то..
        QMessageBox::warning(this,"Ошибка!","Ошибка При Добавлении!\n"+sql_query->lastError().text());
        qDebug()<<sql_query->lastError().text();
    }
    else{
        qDebug()<<"Запись добавлен";
    }
}

// Установливает QLCDNumber 'Всего Заработано' на главном меню
void MainWindow::setTotalSalary()
{
    QSqlQuery *query=new QSqlQuery(sql_database);
    // Запросы
    QString sumQuery = "SELECT SUM(Total) FROM Note";
    QString sumThisMonth = QString("SELECT SUM(Total) FROM Note WHERE Month='%1'").arg(getMonthName(c_month));

    // Запрос на получеие сумму всех зарплат
    query->exec(sumQuery);
    query->next();
    ui->ui_allSalary_lcdNumber->display(query->value(0).toInt());

    // Запрос на получеие сумму всех зарпла на текущем месяце
    query->exec(sumThisMonth);
    query->next();
    ui->ui_salaryThisMonth_lcdNumber->display(query->value(0).toInt());
}

// При нажатии на кнопку 'Поиск'
void MainWindow::on_ui_screachNotes_button_clicked()
{
    int year = ui->ui_chooseYear_spinBox->value();
    QString month = ui->ui_chooseMonth_comboBox->currentText();

    // Создаем запрос
    lastRequest = QString("SELECT * FROM Note WHERE Year=%1 AND Month='%2'").arg(year).arg(month);

    //Создаем модель запроса
    sql_model = new QSqlQueryModel(this);
    sql_model->setQuery(lastRequest);

    // Привязываем модель к таблице
    ui->ui_mainTableView->setModel(sql_model);
}

// При нажатии на кнопку 'Удалить'
void MainWindow::on_ui_deleteNote_button_clicked()
{
    if(QMessageBox::information(this,"Добавить?","Вы точно Хотите Удалить Запись?",QMessageBox::No,QMessageBox::Yes)==QMessageBox::Yes){
        QString request=QString("DELETE FROM Note WHERE Id=%1").arg(ui->ui_deleteId_spinBox->value());

        if(!sql_query->exec(request)){
            QMessageBox::warning(this,"Ошибка!","Не Удалось Удалить Запись!"+sql_query->lastError().text());
            qDebug()<<"Не Удалось Удалить Запись!"+sql_query->lastError().text();
        }
    }
}

// При нажатии на кнопку 'Показать Все Записи'
void MainWindow::on_ui_selectAll_button_clicked()
{
    // Создаем запрос
    lastRequest = QString("SELECT * FROM Note");

    //Создаем модель запроса
    sql_model = new QSqlQueryModel(this);
    sql_model->setQuery(lastRequest);

    ui->ui_mainTableView->setModel(sql_model);
}
