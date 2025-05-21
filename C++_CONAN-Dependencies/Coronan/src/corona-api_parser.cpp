#include "coronan/corona-api_parser.hpp"

#include <chrono>
#include <cstdint>
#include <ctime>
#include <date/date.h>
#include <fmt/base.h>
#include <iomanip>
#include <optional>
#include <rapidjson/allocators.h>
#include <rapidjson/document.h>
#include <rapidjson/encodings.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/reader.h>
#include <vector>

using namespace date;

namespace coronan::api_parser {

namespace {

template <typename Ret_T, typename DOM_T>
std::optional<Ret_T> get_value(DOM_T const& json_dom_object, std::string const& name)
  requires std::is_arithmetic_v<Ret_T>
{
  if (auto member_it = json_dom_object.FindMember(name.c_str()); member_it != json_dom_object.MemberEnd())
  {
    if (auto const& value = member_it->value; value.IsNumber())
    {
      if constexpr (std::is_floating_point_v<Ret_T>)
      {
        return value.GetDouble();
      }
      else if constexpr (std::is_same_v<Ret_T, unsigned>)
      {
        return value.GetUint();
      }
      // cppcheck-suppress identicalConditionAfterEarlyExit
      // cppcheck-suppress multiCondition
      else if constexpr (std::is_same_v<Ret_T, int>)
      {
        return value.GetInt();
      }
      else if constexpr (std::is_same_v<Ret_T, uint64_t>)
      {
        return value.GetUint64();
      }
      else if constexpr (std::is_same_v<Ret_T, int64_t>)
      {
        return value.GetInt64();
      }
    }
  }
  return std::nullopt;
}

template <typename Ret_T, typename DOM_T>
Ret_T get_value(DOM_T const& json_dom_object, std::string const& name)
  requires(std::is_same_v<Ret_T, std::string>)
{
  if (auto member_it = json_dom_object.FindMember(name.c_str()); member_it != json_dom_object.MemberEnd())
  {
    auto const& value = member_it->value;
    if (value.IsString())
    {
      return value.GetString();
    }
    if (value.IsNumber())
    {
      return value.IsDouble() ? std::to_string(value.GetDouble()) : std::to_string(value.GetInt64());
    }
  }
  return "";
}

year_month_day parse_date(std::string const& date_string)
{
  year_month_day ymd{};
  std::istringstream iss{date_string};
  iss >> parse("%Y-%m-%d", ymd);
  if (iss.fail())
  {
    return {};
  }
  return ymd;
}

} // namespace

DateParseException::DateParseException(std::string exception_msg) : msg{std::move(exception_msg)}
{
}

char const* DateParseException::what() const noexcept
{
  return msg.c_str();
}

std::optional<CovidData> parse_region_total(std::string const& json)
{
  rapidjson::Document document;
  if (document.Parse<rapidjson::kParseFullPrecisionFlag>(json.c_str()).HasParseError())
  {
    fmt::print(stderr, "parse_region_total: JSON parse failure: {} ({})\n", static_cast<int>(document.GetParseError()),
               document.GetErrorOffset());
    return {};
  }
  if (document.HasMember("data") && document["data"].IsObject())
  {
    auto covid_data = CovidData{};
    auto const covid_data_object = document["data"].GetObject();
    covid_data.date = parse_date(get_value<std::string>(covid_data_object, "date"));
    if (not covid_data.date.ok())
    {
      throw DateParseException{"Failed to parse date."};
    }
    covid_data.deaths = get_value<uint32_t>(covid_data_object, "deaths");
    covid_data.confirmed = get_value<uint32_t>(covid_data_object, "confirmed");
    covid_data.recovered = get_value<uint32_t>(covid_data_object, "recovered");
    covid_data.active = get_value<uint32_t>(covid_data_object, "active");
    covid_data.deaths_diff = get_value<int32_t>(covid_data_object, "deaths_diff");
    covid_data.confirmed_diff = get_value<int32_t>(covid_data_object, "confirmed_diff");
    covid_data.recovered_diff = get_value<int32_t>(covid_data_object, "recovered_diff");
    covid_data.active_diff = get_value<int32_t>(covid_data_object, "active_diff");
    covid_data.fatality_rate = get_value<double>(covid_data_object, "fatality_rate");
    return covid_data;
  }
  return {};
}

RegionListObject parse_regions(std::string const& json)
{
  rapidjson::Document document;
  if (document.Parse(json.c_str()).HasParseError())
  {
    fmt::print(stderr, "parse_regions: JSON parse error {} at position {}\n",
               static_cast<int>(document.GetParseError()), document.GetErrorOffset());
    return {};
  }
  auto region_list = RegionListObject{};
  if (document.HasMember("data"))
  {
    for (auto const& region_data : document["data"].GetArray())
    {
      RegionInfo region;
      region.name = get_value<std::string>(region_data, "name");
      region.iso_code = get_value<std::string>(region_data, "iso");
      region_list.emplace_back(region);
    }
  }
  return region_list;
}

ProvinceListObject parse_provinces(std::string const& json)
{
  rapidjson::Document document;
  if (document.Parse(json.c_str()).HasParseError())
  {
    fmt::print(stderr, "parse_provinces: JSON parse error {} at position {}\n",
               static_cast<int>(document.GetParseError()), document.GetErrorOffset());
    return {};
  }
  auto province_list = ProvinceListObject{};
  if (document.HasMember("data"))
  {
    for (auto const& province_data : document["data"].GetArray())
    {
      ProvinceInfo province;
      province.country_name = get_value<std::string>(province_data, "name");
      province.country_iso_code = get_value<std::string>(province_data, "iso");
      province.name = get_value<std::string>(province_data, "province");
      province.latitude = get_value<std::string>(province_data, "lat");
      province.longitude = get_value<std::string>(province_data, "long");
      province_list.emplace_back(province);
    }
  }
  return province_list;
}

} // namespace coronan::api_parser
