#include <QMessageBox>
#include <QFileDialog>
#include <QDialog>
#include <QDebug>

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
    delete questionDialog;
}

//data edition click
void MainWindow::on_actionEdit_data_triggered()
{
        //ok
        if(questionDialog->exec() == QDialog::Accepted)
            questionDialog->questionsModel->setCopyAsDefault();
        //cancel
        else
            questionDialog->questionsModel->makeCopy();

        //stop current session
        ui->plainTextEdit_Answer->setPlainText("");
        ui->plainTextEdit_Question->setPlainText("");
        ui->pushButtonKnow->setEnabled(false);
        ui->pushButtonDontKnow->setEnabled(false);
        ui->pushButtonShowAnswer->setEnabled(false);
}

//start click
void MainWindow::on_actionStart_triggered()
{
    //try to get a question
    question = questionDialog->questionsModel->getNextQuestion();
    if(question == NULL)
    {
        QMessageBox::warning(this,tr("Brak danych"),tr("Nie można rozpocząć z pustą bazą pytań."));
        return;
    }

    //start
    ui->plainTextEdit_Question->setPlainText(question->getQuestion());
    ui->pushButtonKnow->setEnabled(true);
    ui->pushButtonDontKnow->setEnabled(true);
    ui->pushButtonShowAnswer->setEnabled(true);
    return;
}

//show answer click
void MainWindow::on_pushButtonShowAnswer_clicked()
{
    ui->plainTextEdit_Answer->setPlainText(question->getAnswer());
}

//know click
void MainWindow::on_pushButtonKnow_clicked()
{
    question->know();
    question = questionDialog->questionsModel->getNextQuestion();
    ui->plainTextEdit_Question->setPlainText(question->getQuestion());
}

//dont know click
void MainWindow::on_pushButtonDontKnow_clicked()
{
    question->notKnow();
    question = questionDialog->questionsModel->getNextQuestion();
    ui->plainTextEdit_Question->setPlainText(question->getQuestion());
}

//load data click
void MainWindow::on_actionLoad_data_triggered()
{
    //getting filename
    QString fileName = QFileDialog::getOpenFileName(this, tr("Wczytaj dane"), "./", tr("Pliki tekstowe (*.txt)"));
    if(fileName == "")
        return;
    if(!questionDialog->questionsModel->loadData(fileName))
    {
        QMessageBox::warning(this,tr("Błąd zapisu"),tr("Nie można wczytać danych"));
        return;
    }

    //stop current session
    ui->plainTextEdit_Answer->setPlainText("");
    ui->plainTextEdit_Question->setPlainText("");
    ui->pushButtonKnow->setEnabled(false);
    ui->pushButtonDontKnow->setEnabled(false);
    ui->pushButtonShowAnswer->setEnabled(false);

    ui->statusbar->showMessage(tr("Wczytano dane"),5000);
}

//save data click
void MainWindow::on_actionSave_data_triggered()
{
    //getting filename
    QString fileName = QFileDialog::getSaveFileName(this, tr("Zapisz dane"), "./", tr("Pliki tekstowe (*.txt)"));
    if(fileName == "")
        return;
    if(!questionDialog->questionsModel->saveData(fileName))
    {
        QMessageBox::warning(this,tr("Błąd zapisu"),tr("Nie można zapisać danych"));
        return;
    }
    ui->statusbar->showMessage(tr("Zapisano dane"),5000);

}
