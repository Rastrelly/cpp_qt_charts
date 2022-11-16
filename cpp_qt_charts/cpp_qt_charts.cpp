#include "stdafx.h"
#include "cpp_qt_charts.h"

cpp_qt_charts::cpp_qt_charts(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	createChartElements();

	cPts = {};

	//connect button
	connect(ui.btnAddValue, SIGNAL(clicked()), SLOT(btnAddValueClick()));

	makeChart({});
}

cpp_qt_charts::~cpp_qt_charts()
{}


void analyzeVector(double &xmin, double &xmax, double &ymin, double &ymax, std::vector<chartPoints> pts)
{
	xmin = 0;
	xmax = 0;
	ymin = 0;
	ymax = 0;
	int l = pts.size();
	if (l <= 0) return;

	xmin = pts[0].x;
	xmax = pts[l - 1].x;

	for (chartPoints pt : pts)
	{
		if (pt.y < ymin) ymin = pt.y;
		if (pt.y > ymax) ymax = pt.y;
	}
}

void cpp_qt_charts::makeChart(std::vector<chartPoints> pts)
{
	//make vector analysis
	double xmin = 0, ymin = 0, xmax = 0, ymax;
	analyzeVector(xmin, xmax, ymin, ymax, pts);

	//axii ranges
	axisX->setRange(xmin, xmax);
	axisY->setRange(ymin, ymax);	

	//add chart points
	series_f->clear();
	for (int i = 0; i < pts.size(); i++)
	{
		series_f->append(QPointF(pts[i].x, pts[i].y));
	}
}

void cpp_qt_charts::btnAddValueClick()
{
	double x = ui.spinX->value();
	double y = ui.spinY->value();
	cPts.push_back({ x,y });
	if (cPts.size() > 1) makeChart(cPts);
	ui.memoPoints->appendPlainText(QString::number(x) + ";" + QString::number(y));
}

void cpp_qt_charts::createChartElements()
{
	//create chart elements
	series_f = new QtCharts::QLineSeries();
	chart = new QChart();
	axisX = new QValueAxis();
	axisY = new QValueAxis();

	//SERIES	
	series_f->setName("f");

	//CHART OBJECT	
	chart->addSeries(series_f);
	chart->setTitle("Line example");
	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignRight);

	//AXII
	//X
	chart->addAxis(axisX, Qt::AlignBottom);
	//Y	
	chart->addAxis(axisY, Qt::AlignLeft);

	//Attach axii to series
	series_f->attachAxis(axisX);
	series_f->attachAxis(axisY);

	//assign chart to chart shower
	ui.chartDisplay->setChart(chart);
}