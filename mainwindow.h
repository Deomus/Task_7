#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    bool checkValue(QTableWidgetItem *item);

    void changeColor(int row, int column);

    void on_spinBox_apexes_valueChanged(int arg1);

    void on_pushButton_clear_clicked();

    void on_pushButton_random_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void on_pushButton_result_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
