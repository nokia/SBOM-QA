#pragma once
#include "coronan/corona-api_datatypes.hpp"
#include "country_data_model.hpp"
#include "country_overview_table_model.hpp"

#include <QTableView>
#include <QtCharts/QChartGlobal>
#include <QtWidgets/QWidget>
#include <string>

using date::year_month_day;
// using std::chrono::year_month_day;

QT_BEGIN_NAMESPACE
class Ui_CoronanWidgetForm;
QT_END_NAMESPACE

namespace coronan_ui {
class CountryChartView;
class CountryOverviewTablewModel;

class CoronanWidget : public QWidget
{
  Q_OBJECT

public:
  explicit CoronanWidget(QWidget* parent = nullptr);
  ~CoronanWidget() override;
  CoronanWidget(CoronanWidget const&) = delete;
  CoronanWidget& operator=(CoronanWidget const&) = delete;
  CoronanWidget(CoronanWidget&&) = delete;
  CoronanWidget& operator=(CoronanWidget&&) = delete;

private:
  coronan::CountryData get_country_data(std::string const& country_code, year_month_day const& start_date,
                                        year_month_day const& end_date);
  void populate_country_box();
  void populate_date_boxes();

  CountryChartView* chartView = nullptr;
  Ui_CoronanWidgetForm* ui = nullptr;

  CountryOverviewTablewModel overview_model;
  CountryDataModel country_data_model;

private Q_SLOTS:
  void update_ui();
};

} // namespace coronan_ui
