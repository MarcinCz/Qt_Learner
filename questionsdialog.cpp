#include "questionsdialog.h"
#include "ui_questiondialog.h"
#include <QAbstractButton>
#include <QMessageBox>
#include <QHeaderView>
#include <algorithm>

QuestionDialog::QuestionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionDialog)
{
    ui->setupUi(this);

    //setting tableView
    questionsModel = new QuestionsModel();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
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

bool QuestionDialog::modelIndexCompare(QModelIndex i, QModelIndex j)
{
    return(i.row()>j.row());
}

void QuestionDialog::on_pushButtonDelete_clicked()
{
    //ui->tableView->;
    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();

    qSort(selectedList.begin(),selectedList.end());
    for(int i=selectedList.count()-1; i>-1; i--)
    {
        questionsModel->removeRows(selectedList.at(i).row(),1);
    }

}
