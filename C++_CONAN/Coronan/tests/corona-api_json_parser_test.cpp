#include "coronan/corona-api_parser.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace date;

namespace {

TEST_CASE("The corona-api parser parsing an empty region total json", "[corona-api parser]")
{
  static constexpr auto test_json = "{ \"data\": [] }";

  auto const json_object = coronan::api_parser::parse_region_total(test_json);

  SECTION("returns no data")
  {

    REQUIRE(json_object.has_value() == false);
  }
}

TEST_CASE("The corona-api parser parsing an invalid json", "[corona-api parser]")
{
  static constexpr auto test_json = "{ \"data\": }";

  auto const json_object = coronan::api_parser::parse_region_total(test_json);

  SECTION("returns no data")
  {

    REQUIRE(json_object.has_value() == false);
  }
}

TEST_CASE("The corona-api parser parsing an region total json with invalide date", "[corona-api parser]")
{
  static constexpr auto test_json = "{ \
  \"data\": { \
        \"date\": \"2023-13-30\" \
  } \
}";

  SECTION("throws exception")
  {
    REQUIRE_THROWS_AS(coronan::api_parser::parse_region_total(test_json), coronan::api_parser::DateParseException);
  }
}

TEST_CASE("The corona-api parser parsing a full region total json", "[corona-api parser]")
{
  static constexpr auto test_json = "{ \
          \"data\": { \
                \"date\": \"2023-03-09\", \
                \"confirmed\": 4413911, \
                \"deaths\": 14210, \
                \"recovered\": 4013, \
                \"confirmed_diff\": 0, \
                \"deaths_diff\": 1, \
                \"recovered_diff\": 0, \
                \"last_update\": \"2023-03-10 04:21:03\", \
                \"active\": 4399701, \
                \"active_diff\": -1, \
                \"fatality_rate\": 0.0032 \
          } \
      }";

  auto const json_object = coronan::api_parser::parse_region_total(test_json).value();

  SECTION("returns the latest data")
  {
    REQUIRE(json_object.date == 2023_y / March / 9_d);
    REQUIRE(json_object.deaths == 14210);
    REQUIRE(json_object.confirmed == 4413911);
    REQUIRE(json_object.recovered == 4013);
    REQUIRE(json_object.active == 4399701);
    REQUIRE(json_object.deaths_diff == 1);
    REQUIRE(json_object.confirmed_diff == 0);
    REQUIRE(json_object.recovered_diff == 0);
    REQUIRE(json_object.active_diff == -1);
    REQUIRE(json_object.fatality_rate == 0.0032);
  }
}

TEST_CASE("The corona-api country parser parsing a region list", "[corona-api parser]")
{
  static constexpr auto test_country_json = "{ \
        \"data\": [ \
            { \
                \"iso\": \"AUT\", \
                \"name\": \"Austria\" \
            }, \
            { \
                \"iso\": \"ITA\", \
                \"name\": \"Italy\" \
            }, \
            { \
                \"iso\": \"CHE\", \
                \"name\": \"Switzerland\" \
            } \
        ] \
    }";

  auto const countries = coronan::api_parser::parse_regions(test_country_json);
  SECTION("returns the regions")
  {
    REQUIRE(countries[0].name == "Austria");
    REQUIRE(countries[0].iso_code == "AUT");
    REQUIRE(countries[1].name == "Italy");
    REQUIRE(countries[1].iso_code == "ITA");
    REQUIRE(countries[2].name == "Switzerland");
    REQUIRE(countries[2].iso_code == "CHE");
  }
}

TEST_CASE("The corona-api country parser parsing a empty region list", "[corona-api parser]")
{
  static constexpr auto test_country_json = "{ \"data\": [ ] }";

  auto const countries = coronan::api_parser::parse_regions(test_country_json);

  SECTION("returns no regions")
  {
    REQUIRE(countries.empty());
  }
}

TEST_CASE("The corona-api country parser parsing a invalid json", "[corona-api parser]")
{
  static constexpr auto test_country_json = "{ \"data\": }";

  auto const countries = coronan::api_parser::parse_regions(test_country_json);

  SECTION("returns no regions")
  {
    REQUIRE(countries.empty());
  }
}

TEST_CASE("The corona-api provinces parser parsing a provinces list", "[corona-api parser]")
{
  static constexpr auto test_country_json = "{ \
              \"data\": [ \
                  { \
                    \"iso\": \"USA\", \
                    \"name\": \"US\", \
                    \"province\": \"Norfolk County, MA\", \
                    \"lat\": \"42.1767\", \
                    \"long\": \"-71.1449\" \
                  }, \
                  {  \
                      \"iso\": \"USA\", \
                      \"name\": \"US\", \
                      \"province\": \"Alabama\", \
                      \"lat\": \"32.3182\", \
                      \"long\": \"-86.9023\" \
                  }, \
                  {  \
                      \"iso\": \"USA\", \
                      \"name\": \"US\", \
                      \"province\": \"Alameda County, CA\", \
                      \"lat\": \"37.6017\", \
                      \"long\": \"-121.7195\" \
                    } \
              ] \
          }";

  auto const provinces = coronan::api_parser::parse_provinces(test_country_json);
  SECTION("returns the provinced")
  {
    REQUIRE(provinces.size() == 3);
    REQUIRE(provinces[0].country_name == "US");
    REQUIRE(provinces[0].country_iso_code == "USA");
    REQUIRE(provinces[0].name == "Norfolk County, MA");
    REQUIRE(provinces[0].latitude == "42.1767");
    REQUIRE(provinces[0].longitude == "-71.1449");
    REQUIRE(provinces[1].country_name == "US");
    REQUIRE(provinces[1].country_iso_code == "USA");
    REQUIRE(provinces[1].name == "Alabama");
    REQUIRE(provinces[1].latitude == "32.3182");
    REQUIRE(provinces[1].longitude == "-86.9023");
    REQUIRE(provinces[2].country_name == "US");
    REQUIRE(provinces[2].country_iso_code == "USA");
    REQUIRE(provinces[2].name == "Alameda County, CA");
    REQUIRE(provinces[2].latitude == "37.6017");
    REQUIRE(provinces[2].longitude == "-121.7195");
  }
}

TEST_CASE("The corona-api provinces parser parsing a empty provinces list", "[corona-api parser]")
{
  static constexpr auto test_country_json = "{ \"data\": [ ] }";

  auto const provinces = coronan::api_parser::parse_provinces(test_country_json);

  SECTION("returns no provinces")
  {
    REQUIRE(provinces.empty());
  }
}

TEST_CASE("The corona-api provinces parser parsing a invalid json", "[corona-api parser]")
{
  static constexpr auto test_country_json = "{ \"data\": }";

  auto const provinces = coronan::api_parser::parse_provinces(test_country_json);

  SECTION("returns no provinces")
  {
    REQUIRE(provinces.empty());
  }
}

} // namespace
