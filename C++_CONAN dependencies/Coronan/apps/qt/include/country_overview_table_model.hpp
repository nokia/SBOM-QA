#pragma once

#include "coronan/corona-api_datatypes.hpp"

#include <QAbstractTableModel>
#include <QList>
#include <QPair>
#include <QString>

namespace coronan_ui {

class CountryOverviewTablewModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  explicit CountryOverviewTablewModel(QObject* parent = nullptr);
  ~CountryOverviewTablewModel() override = default;
  CountryOverviewTablewModel(const CountryOverviewTablewModel&) = delete;
  CountryOverviewTablewModel& operator=(const CountryOverviewTablewModel&) = delete;
  CountryOverviewTablewModel(CountryOverviewTablewModel&&) = delete;
  CountryOverviewTablewModel& operator=(CountryOverviewTablewModel&&) = delete;

  void populate_data(coronan::CountryData const& country_data);

  [[nodiscard]] int rowCount(QModelIndex const& parent = QModelIndex()) const override;
  [[nodiscard]] int columnCount(QModelIndex const& parent = QModelIndex()) const override;

  [[nodiscard]] QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const override;

private:
  QList<QPair<QString, QString>> country_overview_data;
};

} // namespace coronan_ui
