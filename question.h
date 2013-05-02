#ifndef QUESTION_H
#define QUESTION_H
#include <QVector>
#include <QString>

class Question
{
public:
    Question();
    Question(QString,QString,int prob=10);

    //setters
    void setQuestion(QString);
    void setAnswer(QString);
    void setProbabilityModifier(int);

    //getters
    QString getQuestion();
    QString getAnswer();
    int getProbabilityModifier();

    void modifyProbabilityModifier(int);

private:
    QString question;
    QString answer;
    int probabilityModifier;
};

#endif // QUESTION_H
