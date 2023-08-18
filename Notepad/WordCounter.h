#pragma once
#include<qobject.h>

class WordCounter : public QObject
{
    Q_OBJECT

public:
    explicit WordCounter(QObject* parent = nullptr);

public slots:
    void countWords(const QString& text);

signals:
    void wordCountResult(int count);
};