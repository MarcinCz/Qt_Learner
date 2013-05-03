#ifndef QUESTIONSMODEL_H
#define QUESTIONSMODEL_H

#include <Qt>
#include <QAbstractTableModel>
#include <QVector>

#include "question.h"

class QuestionsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit QuestionsModel(QObject *parent = 0);

    //overriden functions
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void clear();
    Question* getNextQuestion();
    void makeCopy();
    void setCopyAsDefault();


private:
    QVector<Question*> *questionsVector;
    QVector<Question*> *copyVector;
    
signals:
    //void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

public slots:
    
};

#endif // QUESTIONSMODEL_H
