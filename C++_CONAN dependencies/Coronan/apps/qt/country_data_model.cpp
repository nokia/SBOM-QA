#include "country_data_model.hpp"

namespace {
inline constexpr auto columns = 5u;
}

namespace coronan_ui {

CountryDataModel::CountryDataModel(QObject* parent) : QAbstractTableModel(parent)
{
}

void CountryDataModel::populate_data(coronan::CountryData const& country_data)
{
  beginResetModel();
  country_name = QString::fromStdString(country_data.info.name);
  max = country_data.latest.confirmed.value_or(0);
  min = country_data.latest.deaths.value_or(0);
  country_timeline_data.clear();

  if (not country_data.timeline.empty())
  {
// Unfortunatelly QDate(std::chrono::year_month_weekday_last date) can not be used when the compiler (libstdc++)
// does not fully support C++ 20 even for Qt >= 6.4
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
    auto const start_qdate = QDate(static_cast<int>(country_data.timeline.front().date.year()),
                                   static_cast<unsigned>(country_data.timeline.front().date.month()),
                                   static_cast<unsigned>(country_data.timeline.front().date.day()));
    auto const end_qdate = QDate(static_cast<int>(country_data.timeline.back().date.year()),
                                 static_cast<int>(static_cast<unsigned>(country_data.timeline.back().date.month())),
                                 static_cast<int>(static_cast<unsigned>(country_data.timeline.back().date.day())));

#pragma GCC diagnostic pop

    start_date = QDateTime{start_qdate, QTime(1, 0)};
    end_date = QDateTime{end_qdate, QTime(1, 0)};
  }

  QTextStream qStdOut(stdout);

  for (auto const& data_point : country_data.timeline)
  {
    CountryTimelineData timeline_data;
    // Unfortunatelly QDate(std::chrono::year_month_weekday_last date) can not be used when the compiler (libstdc++)
    // does not fully support C++ 20 even for Qt >= 6.4
    auto const qdate = QDate(static_cast<int>(data_point.date.year()),
                             static_cast<int>(static_cast<unsigned>(data_point.date.month())),
                             static_cast<int>(static_cast<unsigned>(data_point.date.day())));
    timeline_data.date = QDateTime{qdate, QTime(1, 0)};
    timeline_data.deaths = data_point.deaths.has_value() ? QVariant{data_point.deaths.value()} : QVariant{};
    min = std::min(min, data_point.deaths.value_or(min));
    timeline_data.confirmed_cases =
        data_point.confirmed.has_value() ? QVariant{data_point.confirmed.value()} : QVariant{};
    timeline_data.active_cases = data_point.active.has_value() ? QVariant{data_point.active.value()} : QVariant{};
    timeline_data.recovered_cases =
        data_point.recovered.has_value() ? QVariant{data_point.recovered.value()} : QVariant{};
    country_timeline_data.push_back(timeline_data);
  }
  endResetModel();
}

int CountryDataModel::rowCount(QModelIndex const&) const
{
  return static_cast<int>(country_timeline_data.length());
}

int CountryDataModel::columnCount(QModelIndex const&) const
{
  return columns;
}

QVariant CountryDataModel::data(QModelIndex const& index, int role) const
{
  if (!index.isValid() || role != Qt::DisplayRole)
  {
    return {};
  }
  if (index.column() == date_column_index)
  {
    return country_timeline_data.at(index.row()).date;
  }
  else if (index.column() == deaths_column_index)
  {
    return country_timeline_data.at(index.row()).deaths;
  }
  else if (index.column() == confirmed_column_index)
  {
    return country_timeline_data.at(index.row()).confirmed_cases;
  }
  else if (index.column() == active_column_index)
  {
    return country_timeline_data.at(index.row()).active_cases;
  }
  else if (index.column() == recovered_column_index)
  {
    return country_timeline_data.at(index.row()).recovered_cases;
  }
  return {};
}

QVariant CountryDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
    if (section == date_column_index)
    {
      return QStringLiteral("Date");
    }
    else if (section == deaths_column_index)
    {
      return QStringLiteral("Death");
    }
    else if (section == confirmed_column_index)
    {
      return QStringLiteral("Confirmed");
    }
    else if (section == active_column_index)
    {
      return QStringLiteral("Active");
    }
    else if (section == recovered_column_index)
    {
      return QStringLiteral("Recovered");
    }
  }
  return {};
}

QString CountryDataModel::country() const
{
  return country_name;
}

} // namespace coronan_ui
