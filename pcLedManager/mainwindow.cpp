#include <QSerialPort>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&board, SIGNAL(dataUpdated()), this, SLOT(updateSlider()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSlider()
{
    ui->vsR->setValue(board.getRed());
    ui->vsG->setValue(board.getGreen());
    ui->vsB->setValue(board.getBlue());
    ui->vsL->setValue(board.getLightIntensity());
}

void MainWindow::on_send_clicked()
{
    board.setColor(ui->vsR->value(), ui->vsG->value(), ui->vsB->value());
}

void MainWindow::on_vsB_sliderMoved(int position)
{
    board.setColor(ui->vsR->value(), ui->vsG->value(), position);

}

void MainWindow::on_vsG_sliderMoved(int position)
{
    board.setColor(ui->vsR->value(), position, ui->vsB->value());

}

void MainWindow::on_vsR_sliderMoved(int position)
{
    board.setColor(position, ui->vsG->value(), ui->vsB->value());

}

void MainWindow::on_vsL_sliderMoved(int position)
{
    board.setLight(position);

}
