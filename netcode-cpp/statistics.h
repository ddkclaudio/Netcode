#ifndef STATISTICS_H
#define STATISTICS_H

#include <QObject>
#include <QMap>
#include <QDebug>

class Statistics : public QObject
{
    Q_OBJECT
public:
    explicit Statistics(QObject *parent = nullptr);

    static void update(const QString &clientId);

    static void show();

private:
    static inline QMap<QString, int> m_histogram;
};

#endif // STATISTICS_H
