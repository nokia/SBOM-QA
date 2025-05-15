#pragma once

#include <chrono>
#include <date/date.h>
#include <lyra/args.hpp>
#include <optional>
#include <string>
#include <tuple>
#include <variant>

using namespace date;

namespace coronan_cli {

std::variant<std::tuple<std::string, std::optional<year_month_day>, std::optional<year_month_day>>, int>
parse_commandline_arguments(lyra::args const& args);

} // namespace coronan_cli
