//
// Created by andreas on 5/31/25.
//
#include "../include/Vessel.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QWidget>
#include <QVBoxLayout>

#include <QApplication>
#include "../graphs/qt.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Vessel<double> v("Example 1");

    const auto lamda = 0.001;

    const auto A = v.add("A", 50);
    const auto B = v.add("B", 50);
    const auto C = v.add("C", 1);
    v.add((A+C) >> lamda >>= B + C);



    v.beginSimulation(2000);

    auto history = v.getStateHistory();
    auto* chartWidget = new StateHistoryChart(history);
    chartWidget->resize(800, 600);
    chartWidget->show();

    return app.exec();

    return 0;
}
