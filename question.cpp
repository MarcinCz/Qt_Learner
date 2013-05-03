#include "question.h"


Question::Question()
{
}

/**
 * @brief Question::Question
 * @param question
 * @param answer
 * @param prob - default is 10
 */
Question::Question(QString question, QString answer, int prob)
{
    this->question = question;
    this->answer = answer;
    this->probabilityModifier = prob;
}

QString Question::getQuestion()
{
    return this->question;
}

void Question::setQuestion(QString question)
{
    this->question = question;
}

QString Question::getAnswer()
{
    return this->answer;
}

void Question::setAnswer(QString answer)
{
    this->answer=answer;
}

int Question::getProbabilityModifier()
{
    return this->probabilityModifier;
}

void Question::setProbabilityModifier(int prob)
{
    this->probabilityModifier = prob;
}

void Question::know()
{
    probabilityModifier -= 2;
    if(probabilityModifier < 0) probabilityModifier = 0;
}

void Question::notKnow()
{
    probabilityModifier += 2;
    if(probabilityModifier >20) probabilityModifier = 20;
}

void Question::unused()
{
    probabilityModifier += 1;
    if(probabilityModifier >20) probabilityModifier = 20;
}

Question* Question::getCopy()
{
    return new Question(question, answer, probabilityModifier);
}
