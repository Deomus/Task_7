#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_clear->click();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// проверка на правильное число
bool MainWindow::checkValue(QTableWidgetItem *item)
{
    if (item != nullptr)
    {
        bool flag;
        double value = item->text().toDouble(&flag);
        if (flag && !qIsInf(value) && !qIsNaN(value))
            return true;
    }
    return false;
}

// изменение цвета
void MainWindow::changeColor(int row, int column)
{
    QTableWidgetItem *item = new  QTableWidgetItem;
    item = ui->tableWidget->item(row, column);

    if (!checkValue(item))
        item->setBackground(Qt::red);
    else
        item->setBackground(Qt::white);
}

// высчет результата
void MainWindow::on_pushButton_result_clicked()
{
    // очистка предыдущего результата
    ui->label_per_val->clear();
    ui->label_sqr_val->clear();

    int rowCount = ui->tableWidget->rowCount();
    int columnCount = ui->tableWidget->columnCount();
    // проверка ввода
    bool error = false;
    for (int i = 0; i < rowCount; ++i)
    {
        for (int j = 0; j < columnCount; ++j)
        {
            // подстановка пустых айтемов
            QTableWidgetItem *item = new  QTableWidgetItem;
            if (ui->tableWidget->item(i, j) == nullptr)
                ui->tableWidget->setItem(i, j, item);
            else
                item = ui->tableWidget->item(i, j);

            // проверка числа
            if(!checkValue(item))
            {
                changeColor(i, j);
                error = true;
                continue;
            }
            else if (error)
                continue;
        }
    }
    if (error)
    {
       QMessageBox::information(this, "Ошибка", "Введено неправильное число");
       return;
    }

    // установка первых координат

    double square = 0, perimeter = 0;
    double x0 = ui->tableWidget->item(rowCount-1, 0)->text().toDouble();
    double y0 = ui->tableWidget->item(rowCount-1, 1)->text().toDouble();
    double x;
    double y;

    // вычисление перимтра и площади
    for (int i = 0; i < rowCount; ++i)
    {
        x = ui->tableWidget->item(i, 0)->text().toDouble();
        y = ui->tableWidget->item(i, 1)->text().toDouble();

        perimeter += sqrt((pow((x-x0),2) + pow((y-y0),2)));
        square += ((x0 * y - x * y0)/2);

        x0 = x;
        y0 = y;

    }

    ui->label_per_val->setNum(perimeter);

    // проверка на пересчение
    if (fabs(perimeter) < 1e-10 || fabs(square) < 1e-10)
        QMessageBox::information(this, "Ошибка", "Многоугольник пересекающийся");
    else
        ui->label_sqr_val->setNum(fabs(square));
}

// изменение количества строк
void MainWindow::on_spinBox_apexes_valueChanged(int arg1)
{
    ui->tableWidget->setRowCount(arg1);
}

// очистка
void MainWindow::on_pushButton_clear_clicked()
{
    ui->label_per_val->clear();
    ui->label_sqr_val->clear();
    ui->tableWidget->clearContents();

}

// заполнение рандомными числами
void MainWindow::on_pushButton_random_clicked()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        for (int j = 0; j < ui->tableWidget->columnCount(); ++j)
        {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(rand() % 201 - 100));
            ui->tableWidget->setItem(i, j, item);
        }
    }
}

// изменение цвета при неправильном вводе
void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    changeColor(row, column);
}


