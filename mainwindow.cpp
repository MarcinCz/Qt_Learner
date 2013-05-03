#include <QMessageBox>
#include <QFileDialog>

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

void MainWindow::on_actionEdit_data_triggered()
{
        questionDialog->questionsModel->makeCopy();
        if(questionDialog->exec() == QDialog::Rejected)
        {
            questionDialog->questionsModel->setCopyAsDefault();

        }

}

void MainWindow::on_actionStart_triggered()
{
    question = questionDialog->questionsModel->getNextQuestion();
    if(question == NULL)
    {
        QMessageBox::warning(this,tr("Brak danych"),tr("Nie można rozpocząć z pustą bazą pytań."));
        return;
    }

    ui->plainTextEdit_Question->setPlainText(question->getQuestion());
    ui->pushButtonKnow->setEnabled(true);
    ui->pushButtonDontKnow->setEnabled(true);
    ui->pushButtonShowAnswer->setEnabled(true);
    return;
}

void MainWindow::on_pushButtonShowAnswer_clicked()
{
    ui->plainTextEdit_Answer->setPlainText(question->getAnswer());
}

void MainWindow::on_pushButtonKnow_clicked()
{
    question->know();
    question = questionDialog->questionsModel->getNextQuestion();
    ui->plainTextEdit_Question->setPlainText(question->getQuestion());
}

void MainWindow::on_pushButtonDontKnow_clicked()
{
    question->notKnow();
    question = questionDialog->questionsModel->getNextQuestion();
    ui->plainTextEdit_Question->setPlainText(question->getQuestion());
}

void MainWindow::on_actionLoad_data_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Wczytaj dane"), "./", tr("Pliki tekstowe (*.txt)"));
}

void MainWindow::on_actionSave_data_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Zapisz dane"), "./", tr("Pliki tekstowe (*.txt)"));
    if(!questionDialog->questionsModel->saveData(fileName))
        QMessageBox::warning(this,tr("Błąd zapisu"),tr("Nie można zapisać danych"));
}
