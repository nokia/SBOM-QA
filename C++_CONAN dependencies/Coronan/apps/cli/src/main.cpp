#include "argument_parser.hpp"
#include "coronan/corona-api_client.hpp"
#include "coronan/corona-api_datatypes.hpp"
#include "coronan/http_client.hpp"
#include "coronan/ssl_client.hpp"

#include <chrono>
#include <cstdlib>
#include <date/date.h>
#include <exception>
#include <fmt/base.h>
#include <fmt/chrono.h>
#include <optional>
#include <string>
#include <string_view>

namespace {

using date::year_month_day;
// using std::chrono::year_month_day;

void print_data(coronan::CountryData const& country_data);
} // namespace

int main(int argc, char* argv[])
{
  try
  {

    auto const arguments_or_exit_code = coronan_cli::parse_commandline_arguments({argc, argv});
    if (std::holds_alternative<int>(arguments_or_exit_code))
    {
      return std::get<int>(arguments_or_exit_code);
    }
    auto const country_data = [&]() -> coronan::CountryData {
      auto const& [country, start_date, end_date] =

          std::get<std::tuple<std::string, std::optional<year_month_day>, std::optional<year_month_day>>>(
              arguments_or_exit_code);

      auto const latest_data = coronan::CoronaAPIClient{}.request_country_data(country, std::nullopt);
      auto region_info =
          coronan::RegionInfo{.name = "", .iso_code = country, .latitude = std::nullopt, .longitude = std::nullopt};
      if (start_date.has_value() && end_date.has_value())
      {
        return coronan::CountryData{.info = std::move(region_info),
                                    .latest = latest_data.latest,
                                    .timeline = coronan::CoronaAPIClient{}
                                                    .request_country_data(country, start_date.value(), end_date.value())
                                                    .timeline};
      }
      else if (start_date.has_value() && not end_date.has_value())
      {
        return coronan::CountryData{.info = std::move(region_info),
                                    .latest = latest_data.latest,
                                    .timeline =
                                        coronan::CoronaAPIClient{}
                                            .request_country_data(country, start_date.value(), latest_data.latest.date)
                                            .timeline};
      }
      return coronan::CountryData{
          .info = std::move(region_info), .latest = latest_data.latest, .timeline = {{latest_data.latest}}};
    }();

    print_data(country_data);
  }
  catch (coronan::SSLException const& ex)
  {
    fmt::print(stderr, "SSL Exception: {}\n", ex.what());
    return EXIT_FAILURE;
  }
  catch (coronan::HTTPClientException const& ex)
  {
    fmt::print(stderr, "HTTP Client Exception: {}\n", ex.what());
    return EXIT_FAILURE;
  }
  catch (std::exception const& ex)
  {
    fmt::print(stderr, "{}\n", ex.what());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

namespace {

void print_data(coronan::CountryData const& country_data)
{

  constexpr auto optional_to_string = [](auto const& value) -> std::string {
    return value.has_value() ? std::to_string(value.value()) : "--";
  };
  fmt::print("Covid Data for {}:\n", country_data.info.iso_code);
  fmt::print("datetime, confirmed, death, recovered, active\n");
  for (auto const& data_point : country_data.timeline)
  {
    fmt::print("{}, {}, {}, {}, {}\n", date::format("%Y-%m-%d", data_point.date),
               optional_to_string(data_point.confirmed), optional_to_string(data_point.deaths),
               optional_to_string(data_point.recovered), optional_to_string(data_point.active));
  }
}
} // namespace
