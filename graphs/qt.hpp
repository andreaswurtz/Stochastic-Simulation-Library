// graphs/qt.hpp
#pragma once

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QWidget>
#include <QVBoxLayout>
#include <map>
#include <string>
#include <vector>

class StateHistoryChart : public QWidget {
public:
    StateHistoryChart(
        const std::vector<std::pair<double, std::map<std::string, double>>>& stateHistory,
        QWidget* parent = nullptr
    ) : QWidget(parent) {
        using namespace QtCharts;
        std::map<std::string, QLineSeries*> seriesMap;

        for (const auto& [time, state] : stateHistory) {
            for (const auto& [agent, value] : state) {
                if (!seriesMap.count(agent)) {
                    seriesMap[agent] = new QLineSeries();
                    seriesMap[agent]->setName(QString::fromStdString(agent));
                }
                seriesMap[agent]->append(time, static_cast<qreal>(value));
            }
        }

        QChart* chart = new QChart();
        for (auto& [_, series] : seriesMap) {
            chart->addSeries(series);
        }
        chart->createDefaultAxes();

        QChartView* chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        auto* layout = new QVBoxLayout(this);
        layout->addWidget(chartView);
        setLayout(layout);
    }
};