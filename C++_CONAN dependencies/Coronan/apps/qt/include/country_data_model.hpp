#pragma once

#include "coronan/corona-api_datatypes.hpp"

#include <QAbstractTableModel>
#include <QDateTime>
#include <QList>
#include <QVariant>
#include <cstdint>
#include <qglobal.h>

namespace coronan_ui {

class CountryDataModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  explicit CountryDataModel(QObject* parent = nullptr);
  ~CountryDataModel() override = default;
  CountryDataModel(const CountryDataModel&) = delete;
  CountryDataModel& operator=(const CountryDataModel&) = delete;
  CountryDataModel(CountryDataModel&&) = delete;
  CountryDataModel& operator=(CountryDataModel&&) = delete;

  void populate_data(coronan::CountryData const& country_data);

  [[nodiscard]] int rowCount(QModelIndex const& parent = QModelIndex()) const override;
  [[nodiscard]] int columnCount(QModelIndex const& parent = QModelIndex()) const override;

  [[nodiscard]] QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const override;
  [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation = Qt::Horizontal,
                                    int role = Qt::DisplayRole) const override;

  [[nodiscard]] QString country() const;

  [[nodiscard]] uint32_t max_value() const
  {
    return max;
  }

  [[nodiscard]] uint32_t min_value() const
  {
    return min;
  }

  [[nodiscard]] QDateTime max_date() const
  {
    return end_date;
  }

  [[nodiscard]] QDateTime min_date() const
  {
    return start_date;
  }

  static auto constexpr date_column_index = 0;
  static auto constexpr deaths_column_index = 1;
  static auto constexpr confirmed_column_index = 2;
  static auto constexpr active_column_index = 3;
  static auto constexpr recovered_column_index = 4;

private:
  QString country_name;
  uint32_t max{};
  uint32_t min{};
  QDateTime start_date{QDateTime::currentDateTime()};
  QDateTime end_date{QDateTime::currentDateTime()};
  struct CountryTimelineData
  {
    QDateTime date;
    QVariant deaths;
    QVariant confirmed_cases;
    QVariant active_cases;
    QVariant recovered_cases;
  };

  QList<CountryTimelineData> country_timeline_data;
};

} // namespace coronan_ui
