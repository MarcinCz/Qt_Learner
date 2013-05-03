#include <QtCore>
#include <stdlib.h>
#include <time.h>

#include "questionsmodel.h"
#include "question.h"

QuestionsModel::QuestionsModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    srand (time(NULL));

    //this->copyVector = new QVector<Question*>();
    //this->questionsVector = new QVector<Question*>();
    this->questionsVector.append(new Question("a?","tak"));
    this->questionsVector.append(new Question("c?","tak"));
    this->questionsVector.append(new Question("b?","nienienienienienienienienienienienienienienienienienienienienienienienienienienienienienienienienienienie"));
}

void QuestionsModel::clear()
{
    for(int i=0; i<questionsVector.size(); i++)
        delete questionsVector.at(i);

   // delete questionsVector;

    for(int i=0; i<copyVector.size(); i++)
        delete copyVector.at(i);

    //delete copyVector;
}

int QuestionsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    qDebug() << questionsVector.size();
    return this->questionsVector.size();

}

int QuestionsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant QuestionsModel::data(const QModelIndex &index, int role) const
{

    if(index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole))
    {
        switch(index.column())
        {
            case 0:
                return questionsVector.at(index.row())->getQuestion();
            case 1:
                return questionsVector.at(index.row())->getAnswer();
            default:
                return QVariant::Invalid;
        }

    }
    return QVariant::Invalid;
}

QVariant QuestionsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {

        if(role == Qt::DisplayRole)
        {
          if(orientation == Qt::Horizontal)
          {
              switch(section)
              {
                case 0:
                  return QString(tr("Pytanie"));
                case 1:
                  return QString(tr("Odpowiedź"));
                default:
                  return QVariant::Invalid;
              }
          }
          else if(orientation == Qt::Vertical)
          {
              return QString::number(section+1);
          }

        }

    }
    return QVariant::Invalid;
}

bool QuestionsModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);

     for (int row=0; row < rows; row++) {
         questionsVector.insert(position,new Question("",""));
     }
    endInsertRows();
    return true;
}

bool QuestionsModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; ++row) {
        delete questionsVector.at(position);
        questionsVector.remove(position);
    }

    endRemoveRows();
    return true;
}

bool QuestionsModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if(index.isValid() && role==Qt::EditRole)
    {
        switch(index.column())
        {
            case 0:
                questionsVector.at(index.row())->setQuestion(value.toString());
                break;
            case 1:
                questionsVector.at(index.row())->setAnswer(value.toString());
                break;
            default:
                return false;
        }

        emit(dataChanged(index, index));
        return true;
    }
    return false;
}

Qt::ItemFlags QuestionsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
     return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

Question* QuestionsModel::getNextQuestion()
{
    if(questionsVector.size()==0)
        return NULL;

    for(;;)
    {
        int rule = rand() % 21;
        int position = rand() % questionsVector.size();
        if(questionsVector.at(position)->getProbabilityModifier() >= rule)
        {
            for(int i=0; i<questionsVector.size(); i++)
            {
                if(i == position) continue;
                questionsVector.at(i)->unused();
            }
            return questionsVector.at(position);
        }

    }
}

void QuestionsModel::makeCopy()
{
    for(int i=0; i<copyVector.size(); i++)
        delete copyVector.at(i);

    copyVector.clear();

    foreach(Question* q, questionsVector)
    {
        copyVector.append(q->getCopy());
    }
}

void QuestionsModel::setCopyAsDefault()
{

    if(questionsVector.size()>0)
    {
        foreach(Question* q, questionsVector)
        {
            delete q;
        }
        beginRemoveRows(QModelIndex(),0,questionsVector.size()-1);
        questionsVector.clear();
        endRemoveRows();
    }

    if(copyVector.size()==0)
        return;

    beginInsertRows(QModelIndex(),0,copyVector.size()-1);
    for(int i=0; i<copyVector.size(); i++)
    {

        questionsVector.append(copyVector.at(i)->getCopy());

    }
    endInsertRows();
    qDebug() << questionsVector.size();
    return;
}

bool QuestionsModel::loadData(QString fileName)
{
    QFile file(fileName);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);



        stream.flush();
        file.close();
        return true;
    }

    return false;
}

bool QuestionsModel::saveData(QString fileName)
{
    QFile file(fileName);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);

        foreach(Question* q, questionsVector)
        {
            stream << q->getQuestion() << "\n";
            stream << q->getAnswer() << "\n";
            stream << q->getProbabilityModifier() << "\n";
        }
        stream.flush();
        file.close();
        return true;
    }

    return false;
}


