#ifndef QUESTIONDIALOG_H
#define QUESTIONDIALOG_H

#include <QDialog>
#include "questionsmodel.h"

namespace Ui {
class QuestionDialog;
}

class QuestionDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit QuestionDialog(QWidget *parent = 0);
    ~QuestionDialog();
    
private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonDelete_clicked();

private:
    Ui::QuestionDialog *ui;
    QuestionsModel *questionsModel;
};

#endif // QUESTIONDIALOG_H
