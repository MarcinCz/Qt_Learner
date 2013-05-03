#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "questionsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void on_actionEdit_data_triggered();

    void on_actionStart_triggered();

    void on_pushButtonShowAnswer_clicked();

    void on_pushButtonKnow_clicked();

    void on_pushButtonDontKnow_clicked();

private:
    Ui::MainWindow *ui;
    QuestionDialog *questionDialog;
    Question *question;
};

#endif // MAINWINDOW_H
