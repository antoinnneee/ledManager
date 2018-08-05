#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ledmanager.h>
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
    void on_send_clicked();

    void on_vsB_sliderMoved(int position);

    void on_vsG_sliderMoved(int position);

    void on_vsR_sliderMoved(int position);

    void on_vsL_sliderMoved(int position);

    void    updateSlider();

private:
    Ui::MainWindow *ui;
    LedManager board;
};

#endif // MAINWINDOW_H
