#include "statistics.h"

Statistics::Statistics(QObject *parent)
    : QObject(parent)
{
}

void Statistics::update(const QString &clientId)
{
    if (!m_histogram.contains(clientId))
    {
        m_histogram[clientId] = 0;
    }
    m_histogram[clientId]++;
}

void Statistics::show()
{
    if (m_histogram.isEmpty())
        return;

    qDebug() << "--------- Statistics ---------";
    for (auto it = m_histogram.begin(); it != m_histogram.end(); ++it)
    {
        qDebug() << "Client ID:" << it.key() << " - Messages received:" << it.value();
    }

    // Cálculo da média
    double mean = 0;
    for (auto value : m_histogram.values())
    {
        mean += value;
    }
    mean /= m_histogram.size();

    // Cálculo da variância e desvio padrão
    double variance = 0;
    for (auto value : m_histogram.values())
    {
        variance += pow(value - mean, 2);
    }
    variance /= m_histogram.size();
    double stdDev = sqrt(variance);

    // Cálculo da mediana
    QList<int> values = m_histogram.values();
    std::sort(values.begin(), values.end());
    double median = 0;
    if (values.size() % 2 == 0)
    {
        median = (values[values.size() / 2 - 1] + values[values.size() / 2]) / 2.0;
    }
    else
    {
        median = values[values.size() / 2];
    }

    // Máximo e Mínimo
    int max = *std::max_element(values.begin(), values.end());
    int min = *std::min_element(values.begin(), values.end());

    qDebug() << "Média:" << mean;
    qDebug() << "Variância:" << variance;
    qDebug() << "Desvio Padrão:" << stdDev;
    qDebug() << "Mediana:" << median;
    qDebug() << "Máximo:" << max;
    qDebug() << "Mínimo:" << min;
    qDebug() << "------------------------------";
}
