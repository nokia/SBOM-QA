#include "argument_parser.hpp"

#include <date/date.h>
#include <fmt/base.h>
#include <fmt/chrono.h>
#include <iomanip>
#include <lyra/cli.hpp>
#include <lyra/cli_parser.hpp>
#include <lyra/help.hpp>
#include <lyra/opt.hpp>
#include <lyra/parser.hpp>
#include <sstream>

using date::year_month_day;
// using std::chrono::year_month_day;

namespace {
year_month_day parse_date(std::string const& date_string)
{
  year_month_day ymd{};
  std::istringstream date_iss{date_string};
  date_iss >> parse("%Y-%m-%d", ymd);

  if (date_iss.fail())
  {
    return {};
  }
  return ymd;
}

} // namespace

namespace coronan_cli {

std::variant<std::tuple<std::string, std::optional<year_month_day>, std::optional<year_month_day>>, int>
parse_commandline_arguments(lyra::args const& args)
{
  std::string country = "CHE";
  std::string start_date_string;
  std::string end_date_string;
  bool help_request = false;
  const auto command_line_parser =
      lyra::cli_parser() | lyra::help(help_request) | lyra::opt(country, "country")["-c"]["--country"]("Country Code") |
      lyra::opt(start_date_string, "start date")["-s"]["--start_date"]("Date format yyyy-mm-dd") |
      lyra::opt(end_date_string, "end date")["-e"]["--end_date"]("Date format yyyy-mm-dd");

  std::stringstream usage;
  usage << command_line_parser;

  if (auto const result = command_line_parser.parse(args); !result)
  {
    fmt::print(stderr, "Error in comman line: {}\n", result.message());
    fmt::print("{}\n", usage.str());
    return EXIT_FAILURE;
  }

  if (help_request)
  {
    fmt::print("{}\n", usage.str());
    return EXIT_SUCCESS;
  }

  std::optional<year_month_day> start_date = std::nullopt;
  if (not start_date_string.empty())
  {
    if (auto const ymd = parse_date(start_date_string); ymd.ok())
    {
      start_date = ymd;
    }
    else
    {
      fmt::print(stderr, "Start date could not be parsed, please enter in format yyyy-mm-dd.\n");
      fmt::print("{}\n", usage.str());
      return EXIT_FAILURE;
    }
  }

  std::optional<year_month_day> end_date = std::nullopt;
  if (not end_date_string.empty())
  {
    if (auto const ymd = parse_date(end_date_string); ymd.ok())
    {
      end_date = ymd;
    }
    else
    {
      fmt::print(stderr, "End date could not be parsed, please enter in format yyyy-mm-dd.\n");
      fmt::print("{}\n", usage.str());
      return EXIT_FAILURE;
    }
  }

  return std::make_tuple(country, start_date, end_date);
}

} // namespace coronan_cli
