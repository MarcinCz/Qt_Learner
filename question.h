#ifndef QUESTION_H
#define QUESTION_H
#include <QVector>
#include <QString>

class Question
{
public:
    Question();
    Question(QString question,QString answer,int prob=10);

    //setters
    void setQuestion(QString question);
    void setAnswer(QString answer);
    void setProbabilityModifier(int prob);

    //getters
    QString getQuestion();
    QString getAnswer();
    int getProbabilityModifier();

    void know();
    void notKnow();
    void unused();
    Question* getCopy();

private:
    QString question;
    QString answer;
    int probabilityModifier;
};

#endif // QUESTION_H
