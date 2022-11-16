#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_cpp_qt_charts.h"

struct chartPoints
{
	double x, y;
};

class cpp_qt_charts : public QMainWindow
{
    Q_OBJECT

public:
	std::vector<chartPoints> cPts;
	QLineSeries *series_f;
	QChart *chart;
	QValueAxis *axisX, *axisY;
    cpp_qt_charts(QWidget *parent = nullptr);
    ~cpp_qt_charts();
	void makeChart(std::vector<chartPoints> pts);
	void createChartElements();

private:
    Ui::cpp_qt_chartsClass ui;

private slots:
	void btnAddValueClick();
};
