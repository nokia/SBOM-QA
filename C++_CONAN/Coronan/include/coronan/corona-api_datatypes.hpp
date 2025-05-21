#pragma once

#include <cstdint>
#include <date/date.h>
#include <optional>
#include <string>
#include <vector>

namespace coronan {

using date::year_month_day;
// using std::chrono::year_month_day;

/**
 * Holds general country information
 */
struct RegionInfo
{
  std::string name;                     /**< Region/Country name */
  std::string iso_code;                 /**< ISO Country Code , e.g. CHE */
  std::optional<std::string> latitude;  /**< latitude */
  std::optional<std::string> longitude; /**< longitude */
};

/**
 * Holds general province information
 */
struct ProvinceInfo
{
  std::string country_name;             /**< Region/Country name */
  std::string country_iso_code;         /**< ISO Country Code , e.g. CHE */
  std::string name;                     /**< province name*/
  std::optional<std::string> latitude;  /**< latitude */
  std::optional<std::string> longitude; /**< longitude */
};

/**
 * Holds the the covid-19 case data of the country for a specific date/time
 */
struct CovidData
{
  year_month_day date;                   /**< iso date string (last updated) */
  std::optional<uint32_t> deaths;        /**< number of deaths */
  std::optional<int32_t> deaths_diff;    /**< number of death difference to previous data*/
  std::optional<uint32_t> confirmed;     /**< number of confirmed cases */
  std::optional<int32_t> confirmed_diff; /**< confirmed cases difference to previous data*/
  std::optional<uint32_t> recovered;     /**< number of recovered cases */
  std::optional<int32_t> recovered_diff; /**< recovered cases difference to previous data*/
  std::optional<double> fatality_rate;   /**< calculated fatality rate */
  std::optional<uint32_t> active;        /**< number total of covid-19 cases */
  std::optional<int32_t> active_diff;    /**< active cases difference to previous data*/
};

/**
 * Holds the covid-19 case data of a single country
 */
struct CountryData
{

  RegionInfo info{}; /**< region information (name, code, location) */

  /**
   * Holds the latest available covid-19 case data of the country
   */

  CovidData latest{}; /**< Lates actual cases  */

  std::vector<CovidData> timeline; /**< Timeline data (list of daily data) */
};

using RegionListObject = std::vector<RegionInfo>;
using ProvinceListObject = std::vector<ProvinceInfo>;

} // namespace coronan
