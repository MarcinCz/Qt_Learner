#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "questionsdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    questionDialog = new QuestionDialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionEdit_data_triggered()
{

        questionDialog->show();
        //QuestionDialog questionDialog;
        //questionDialog.exec();
}
