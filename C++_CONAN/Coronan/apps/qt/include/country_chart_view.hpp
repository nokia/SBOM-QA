#pragma once

#include <QVXYModelMapper>
#include <QtCharts/QChartView>
#include <vector>

namespace coronan {
struct CountryData;
}

namespace coronan_ui {
class CountryDataModel;

class CountryChartView : public QChartView
{
  Q_OBJECT
public:
  explicit CountryChartView(CountryDataModel* data_model, QWidget* parent = nullptr);
  ~CountryChartView() override = default;

  void update_ui(CountryDataModel const& data_model);

private:
  std::vector<QVXYModelMapper> model_mappers{4};
};

} // namespace coronan_ui
