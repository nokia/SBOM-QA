#include "argument_parser.hpp"

#include <catch2/catch_test_macros.hpp>
#include <date/date.h>

namespace {
using namespace date;

TEST_CASE("argument parser called with ", "[HTTPClient]")
{
  using SuccessfullParse = std::tuple<std::string, std::optional<year_month_day>, std::optional<year_month_day>>;

  SECTION("-h (help) exits with success")
  {

    const auto result = coronan_cli::parse_commandline_arguments({"program_name", "-h"});

    REQUIRE(std::holds_alternative<int>(result));
    REQUIRE(std::get<int>(result) == EXIT_SUCCESS);
  }

  SECTION("wrong argument exits with failure")
  {
    const auto result = coronan_cli::parse_commandline_arguments({"program_name", "-i"});

    REQUIRE(std::holds_alternative<int>(result));
    REQUIRE(std::get<int>(result) == EXIT_FAILURE);
  }

  SECTION("no argument return country code CHE and no dates")
  {

    const auto result = coronan_cli::parse_commandline_arguments({"program_name"});

    REQUIRE(std::holds_alternative<SuccessfullParse>(result));
    const auto& [country, start_date, end_date] = std::get<SuccessfullParse>(result);
    REQUIRE(country == "CHE");
    REQUIRE_FALSE(start_date.has_value());
    REQUIRE_FALSE(end_date.has_value());
  }

  SECTION("-c (country iso) code return country code and no dates")
  {

    const auto result = coronan_cli::parse_commandline_arguments({"program_name", "-c", "CHN"});

    REQUIRE(std::holds_alternative<SuccessfullParse>(result));
    const auto& [country, start_date, end_date] = std::get<SuccessfullParse>(result);
    REQUIRE(country == "CHN");
    REQUIRE_FALSE(start_date.has_value());
    REQUIRE_FALSE(end_date.has_value());
  }

  SECTION("--country code return country code and no dates")
  {

    const auto result = coronan_cli::parse_commandline_arguments({"program_name", "--country", "CHN"});

    REQUIRE(std::holds_alternative<SuccessfullParse>(result));
    const auto& [country, start_date, end_date] = std::get<SuccessfullParse>(result);
    REQUIRE(country == "CHN");
    REQUIRE_FALSE(start_date.has_value());
    REQUIRE_FALSE(end_date.has_value());
  }

  SECTION("-s (start date) argument return country code CHE and start date")
  {

    const auto result = coronan_cli::parse_commandline_arguments({"program_name", "-s", "2020-01-01"});

    REQUIRE(std::holds_alternative<SuccessfullParse>(result));
    const auto& [country, start_date, end_date] = std::get<SuccessfullParse>(result);
    REQUIRE(country == "CHE");
    REQUIRE(start_date.has_value());
    REQUIRE(start_date == year_month_day{2020_y / January / 1_d});
    REQUIRE_FALSE(end_date.has_value());
  }

  SECTION("--start_date argument return country code CHE and start date")
  {

    const auto result = coronan_cli::parse_commandline_arguments({"program_name", "--start_date", "2020-01-01"});

    REQUIRE(std::holds_alternative<SuccessfullParse>(result));
    const auto& [country, start_date, end_date] = std::get<SuccessfullParse>(result);
    REQUIRE(country == "CHE");
    REQUIRE(start_date.has_value());
    REQUIRE(start_date == year_month_day{2020_y / January / 1_d});
    REQUIRE_FALSE(end_date.has_value());
  }

  SECTION("--start_date and country coder argument return country code and start date")
  {

    const auto result =
        coronan_cli::parse_commandline_arguments({"program_name", "--start_date", "2020-01-01", "-c", "CHN"});

    REQUIRE(std::holds_alternative<SuccessfullParse>(result));
    const auto& [country, start_date, end_date] = std::get<SuccessfullParse>(result);
    REQUIRE(country == "CHN");
    REQUIRE(start_date.has_value());
    REQUIRE(start_date == year_month_day{2020_y / January / 1_d});
    REQUIRE_FALSE(end_date.has_value());
  }

  SECTION("wrong --start_date exits with failure")
  {
    const auto result = coronan_cli::parse_commandline_arguments({"program_name", "--start_date", "blabla"});

    REQUIRE(std::holds_alternative<int>(result));
    REQUIRE(std::get<int>(result) == EXIT_FAILURE);
  }

  SECTION("-e (end date) argument return country code CHE and end date")
  {

    const auto result = coronan_cli::parse_commandline_arguments({"program_name", "-e", "2020-01-01"});

    REQUIRE(std::holds_alternative<SuccessfullParse>(result));
    const auto& [country, start_date, end_date] = std::get<SuccessfullParse>(result);
    REQUIRE(country == "CHE");
    REQUIRE(end_date.has_value());
    REQUIRE(end_date == year_month_day{2020_y / January / 1_d});
    REQUIRE_FALSE(start_date.has_value());
  }

  SECTION("--end_date argument return country code CHE and start date")
  {

    const auto result = coronan_cli::parse_commandline_arguments({"program_name", "--end_date", "2020-01-01"});

    REQUIRE(std::holds_alternative<SuccessfullParse>(result));
    const auto& [country, start_date, end_date] = std::get<SuccessfullParse>(result);
    REQUIRE(country == "CHE");
    REQUIRE(end_date.has_value());
    REQUIRE(end_date == year_month_day{2020_y / January / 1_d});
    REQUIRE_FALSE(start_date.has_value());
  }

  SECTION("--end_date and country coder argument return country code and start date")
  {

    const auto result =
        coronan_cli::parse_commandline_arguments({"program_name", "--end_date", "2020-01-01", "-c", "CHN"});

    REQUIRE(std::holds_alternative<SuccessfullParse>(result));
    const auto& [country, start_date, end_date] = std::get<SuccessfullParse>(result);
    REQUIRE(country == "CHN");
    REQUIRE(end_date.has_value());
    REQUIRE(end_date == year_month_day{2020_y / January / 1_d});
    REQUIRE_FALSE(start_date.has_value());
  }

  SECTION("wrong --end_date exits with failure")
  {
    const auto result = coronan_cli::parse_commandline_arguments({"program_name", "--end_date", "blabla"});

    REQUIRE(std::holds_alternative<int>(result));
    REQUIRE(std::get<int>(result) == EXIT_FAILURE);
  }

  SECTION("-passing all argumnets return country code, start date and end date")
  {

    const auto result = coronan_cli::parse_commandline_arguments(
        {"program_name", "--start_date", "2019-01-01", "--end_date", "2020-01-01", "-c", "CHN"});

    REQUIRE(std::holds_alternative<SuccessfullParse>(result));
    const auto& [country, start_date, end_date] = std::get<SuccessfullParse>(result);
    REQUIRE(country == "CHN");
    REQUIRE(start_date.has_value());
    REQUIRE(start_date == year_month_day{2019_y / January / 1_d});
    REQUIRE(end_date.has_value());
    REQUIRE(end_date == year_month_day{2020_y / January / 1_d});
  }
}

} // namespace
