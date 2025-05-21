#include "country_chart_view.hpp"

#include "country_data_model.hpp"

#include <QDateTime>
#include <QDateTimeAxis>
#include <QLatin1String>
#include <QLineSeries>
#include <QLogValueAxis>
#include <QString>
#include <QValueAxis>
#include <qglobal.h>

namespace {
inline constexpr auto create_datetime_axis = []() {
  auto* const x_axis = new QDateTimeAxis{};
  x_axis->setFormat(QStringLiteral("yyyy-MM-dd  "));
  x_axis->setTitleText(QStringLiteral("Date"));
  return x_axis;
};

inline constexpr auto create_value_axis = [](quint32 min, quint32 max) {
  auto* const y_axis = new QValueAxis{};
  y_axis->setTitleText(QStringLiteral("Cases"));
  y_axis->setLabelFormat(QStringLiteral("%i  "));
  y_axis->setRange(min, max);
  return y_axis;
};

inline constexpr auto create_chart_title = [](auto const& country_name) {
  return QStringLiteral("Corona (Covid-19) Cases in ").append(country_name);
};

} // namespace

namespace coronan_ui {

CountryChartView::CountryChartView(CountryDataModel* const data_model, QWidget* parent) : QChartView(parent)
{
  auto* const chart = new QChart{};
  chart->setTitle(create_chart_title(data_model->country()));
  auto* const x_axis = create_datetime_axis();
  auto* const y_axis = create_value_axis(data_model->min_value(), data_model->max_value());

  chart->addAxis(x_axis, Qt::AlignBottom);
  chart->addAxis(y_axis, Qt::AlignLeft);
  chart->setTheme(QChart::ChartThemeDark);
  chart->legend()->setAlignment(Qt::AlignTop);
  chart->legend()->show();

  auto const create_series = [&](int column_index) {
    auto* const series = new QLineSeries{};
    series->setName(data_model->headerData(column_index).toString());

    auto& model_mapper = model_mappers.at(static_cast<size_t>(column_index - 1));
    model_mapper.setXColumn(CountryDataModel::date_column_index);
    model_mapper.setYColumn(column_index);
    model_mapper.setSeries(series);
    model_mapper.setModel(data_model);
    chart->addSeries(series);
    series->attachAxis(x_axis);
    series->attachAxis(y_axis);
  };

  create_series(CountryDataModel::deaths_column_index);
  create_series(CountryDataModel::confirmed_column_index);
  create_series(CountryDataModel::active_column_index);
  create_series(CountryDataModel::recovered_column_index);

  this->setChart(chart);
  this->setRenderHint(QPainter::Antialiasing, true);
}

void CountryChartView::update_ui(CountryDataModel const& data_model)
{
  this->chart()->setTitle(create_chart_title(data_model.country()));
  this->chart()->axes(Qt::Vertical).at(0)->setRange(data_model.min_value(), data_model.max_value());
  this->chart()->axes(Qt::Horizontal).at(0)->setRange(data_model.min_date(), data_model.max_date());
}

} // namespace coronan_ui
