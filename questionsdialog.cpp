#include "questionsdialog.h"
#include "ui_questiondialog.h"
#include <QMessageBox>
#include <QHeaderView>

QuestionDialog::QuestionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionDialog)
{
    ui->setupUi(this);

    //setting tableView
    questionsModel = new QuestionsModel();
    ui->tableView->setModel(questionsModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

QuestionDialog::~QuestionDialog()
{
    delete ui;
    questionsModel->clear();
    delete questionsModel;
}

void QuestionDialog::on_pushButtonAdd_clicked()
{
    int row = questionsModel->rowCount(QModelIndex());
    questionsModel->insertRows(row,1);

    QModelIndex index = questionsModel->index(row,0);
    ui->tableView->setCurrentIndex(index);
    ui->tableView->edit(index);
}

void QuestionDialog::on_pushButtonDelete_clicked()
{
    questionsModel->removeRows(ui->tableView->currentIndex().row(),1);
}
