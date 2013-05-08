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

    //other things
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Anuluj"));
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

}

QuestionDialog::~QuestionDialog()
{
    delete ui;
    questionsModel->clear();
    delete questionsModel;
}

//add click
void QuestionDialog::on_pushButtonAdd_clicked()
{
    //insert row
    int row = questionsModel->rowCount(QModelIndex());
    questionsModel->insertRows(row,1);

    //go to inserted
    QModelIndex index = questionsModel->index(row,0);
    ui->tableView->setCurrentIndex(index);
    ui->tableView->edit(index);
}

//delete click
void QuestionDialog::on_pushButtonDelete_clicked()
{
    //get selected
    QModelIndexList selectedList = ui->tableView->selectionModel()->selectedRows();

    //remove selected
    qSort(selectedList.begin(),selectedList.end());
    for(int i=selectedList.count()-1; i>-1; i--)
    {
        questionsModel->removeRows(selectedList.at(i).row(),1);
    }

}

//apply click
void QuestionDialog::on_pushButtonApply_clicked()
{
    questionsModel->setCopyAsDefault();
}
