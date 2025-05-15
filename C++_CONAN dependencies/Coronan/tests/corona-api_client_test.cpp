#include "coronan/corona-api_client.hpp"

#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <chrono>
#include <date/date.h>
#include <mutex>
#include <tuple>

using namespace date;
;

namespace {

using Catch::Matchers::Equals;

class TestHTTPClient
{
public:
  static coronan::HTTPResponse get(std::string const& url)
  {
    std::lock_guard<std::mutex> lk(TestHTTPClient::mtx);
    auto const& [response_status, response_payload] = responses.at(get_called);
    ++get_called;
    get_urls.emplace_back(url);
    return coronan::HTTPResponse{Poco::Net::HTTPResponse{response_status}, response_payload};
  }

  static std::tuple<bool, std::string> get_was_called_with(std::string_view url)
  {
    std::lock_guard<std::mutex> lk(TestHTTPClient::mtx);
    return std::make_tuple((get_called == 1) && (get_urls.at(0) == url), get_urls.at(0));
  }

  static std::tuple<bool, std::string> get_was_called_with(std::vector<std::string> const& urls)
  {
    std::lock_guard<std::mutex> lk(TestHTTPClient::mtx);
    for (auto const& expected_url : urls)
    {
      if (not std::ranges::any_of(get_urls, [expected_url](auto const& url) { return url == expected_url; }))
      {
        return std::make_tuple(false, expected_url);
      }
    }
    return std::make_tuple(true, "");
  }

  static size_t get_called;
  static std::vector<std::string> get_urls;

  using Response_T = std::tuple<Poco::Net::HTTPResponse::HTTPStatus, std::string>;
  static std::vector<Response_T> responses;
  static std::mutex mtx;
};

size_t TestHTTPClient::get_called = 0;
std::vector<std::string> TestHTTPClient::get_urls = {};
std::vector<TestHTTPClient::Response_T> TestHTTPClient::responses = {{Poco::Net::HTTPResponse::HTTP_CONTINUE, ""}};
std::mutex TestHTTPClient::mtx = std::mutex{};

SCENARIO("CoronaAPIClient retrieves region list", "[CoronaAPIClient]")
{
  GIVEN("A corona-api client")
  {
    TestHTTPClient::get_called = 0;
    TestHTTPClient::get_urls = {};
    auto testee = coronan::CoronaAPIClientType<TestHTTPClient>{};

    WHEN("the http client returns an not OK response status")
    {

      TestHTTPClient::responses = {{Poco::Net::HTTPResponse::HTTP_NOT_FOUND, ""}};
      THEN("an exception is thrown")
      {
        CHECK_THROWS(testee.request_regions());
      }
    }

    WHEN("the http client returns an OK response status and a region list in the payload")
    {
      TestHTTPClient::responses = {{Poco::Net::HTTPResponse::HTTP_OK, "{ \
              \"data\": [ \
                  { \
                    \"iso\": \"USA\", \
                    \"name\": \"US\" \
                  }, \
                  { \
                      \"iso\": \"JPN\", \
                      \"name\": \"Japan\" \
                  }, \
                  { \
                      \"iso\": \"THA\", \
                      \"name\": \"Thailand\" \
                  } \
              ] \
          }"}};

      auto const countries = testee.request_regions();
      auto const& [called, url] = TestHTTPClient::get_was_called_with("https://covid-api.com/api/regions");

      INFO("HTTPClient::get was not called with the expected URL: " << url);
      CHECK(called);

      THEN("a list of regions names and iso country codes is returned.")
      {
        REQUIRE(countries.size() == 3);
        REQUIRE_THAT(countries[0].name, Equals("US"));
        REQUIRE_THAT(countries[0].iso_code, Equals("USA"));
        REQUIRE_THAT(countries[1].name, Equals("Japan"));
        REQUIRE_THAT(countries[1].iso_code, Equals("JPN"));
        REQUIRE_THAT(countries[2].name, Equals("Thailand"));
        REQUIRE_THAT(countries[2].iso_code, Equals("THA"));
      }
    }
  }
}

SCENARIO("CoronaAPIClient retrieves provinces list of region USA", "[CoronaAPIClient]")
{
  GIVEN("A corona-api client")
  {
    TestHTTPClient::get_called = 0;
    TestHTTPClient::get_urls = {};
    auto testee = coronan::CoronaAPIClientType<TestHTTPClient>{};

    WHEN("the http client returns an not OK response status")
    {

      TestHTTPClient::responses = {{Poco::Net::HTTPResponse::HTTP_NOT_FOUND, ""}};
      THEN("an exception is thrown")
      {
        CHECK_THROWS(testee.request_provinces("USA"));
      }
    }

    WHEN("the http client returns an OK response status and a provinces list in the payload")
    {
      TestHTTPClient::responses = {{Poco::Net::HTTPResponse::HTTP_OK, "{ \
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
          }"}};

      auto const provinces = testee.request_provinces("USA");
      auto const& [called, url] = TestHTTPClient::get_was_called_with("https://covid-api.com/api/provinces/USA");

      INFO("HTTPClient::get was not called with the expected URL: " << url);
      CHECK(called);

      THEN("a list of provinces for the region are returned.")
      {
        REQUIRE(provinces.size() == 3);
        REQUIRE_THAT(provinces[0].country_name, Equals("US"));
        REQUIRE_THAT(provinces[0].country_iso_code, Equals("USA"));
        REQUIRE_THAT(provinces[0].name, Equals("Norfolk County, MA"));
        REQUIRE_THAT(provinces[0].latitude.value_or(""), Equals("42.1767"));
        REQUIRE_THAT(provinces[0].longitude.value_or(""), Equals("-71.1449"));
        REQUIRE_THAT(provinces[1].country_name, Equals("US"));
        REQUIRE_THAT(provinces[1].country_iso_code, Equals("USA"));
        REQUIRE_THAT(provinces[1].name, Equals("Alabama"));
        REQUIRE_THAT(provinces[1].latitude.value_or(""), Equals("32.3182"));
        REQUIRE_THAT(provinces[1].longitude.value_or(""), Equals("-86.9023"));
        REQUIRE_THAT(provinces[2].country_name, Equals("US"));
        REQUIRE_THAT(provinces[2].country_iso_code, Equals("USA"));
        REQUIRE_THAT(provinces[2].name, Equals("Alameda County, CA"));
        REQUIRE_THAT(provinces[2].latitude.value_or(""), Equals("37.6017"));
        REQUIRE_THAT(provinces[2].longitude.value_or(""), Equals("-121.7195"));
      }
    }
  }
}

SCENARIO("CoronaAPIClient retrieves latest country data for Switzerland", "[CoronaAPIClient]")
{
  GIVEN("A corona-api client")
  {
    TestHTTPClient::get_called = 0;
    TestHTTPClient::get_urls = {};
    auto testee = coronan::CoronaAPIClientType<TestHTTPClient>{};

    WHEN("the http client returns an not OK response status")
    {

      TestHTTPClient::responses = {{Poco::Net::HTTPResponse::HTTP_NOT_FOUND, ""}};
      THEN("an exception is thrown")
      {
        CHECK_THROWS(testee.request_country_data("CH", std::nullopt));
      }
    }

    WHEN("the http client returns an OK response status and a payload with "
         "data for Switzerland")
    {
      TestHTTPClient::responses = {{Poco::Net::HTTPResponse::HTTP_OK, "{ \
          \"data\": { \
                \"date\": \"2023-03-09\", \
                \"confirmed\": 4413911, \
                \"deaths\": 14210, \
                \"recovered\": 0, \
                \"confirmed_diff\": 0, \
                \"deaths_diff\": 1, \
                \"recovered_diff\": 0, \
                \"last_update\": \"2023-03-10 04:21:03\", \
                \"active\": 4399701, \
                \"active_diff\": -1, \
                \"fatality_rate\": 0.0032 \
          } \
      }"}};

      auto const country_data = testee.request_country_data("CHE", std::nullopt);
      auto const& [called, url] =
          TestHTTPClient::get_was_called_with("https://covid-api.com/api/reports/total?iso=CHE");
      {
        INFO("HTTPClient::get was not called with the expected URL: " << url);
        CHECK(called);
      }

      THEN("the country data is returned.")
      {
        REQUIRE(country_data.latest.date == 2023_y / March / 9_d);
        REQUIRE(country_data.latest.deaths == 14210);
        REQUIRE(country_data.latest.confirmed == 4413911);
        REQUIRE(country_data.latest.recovered == 0);
        REQUIRE(country_data.latest.active == 4399701);
        REQUIRE(country_data.latest.deaths_diff == 1);
        REQUIRE(country_data.latest.confirmed_diff == 0);
        REQUIRE(country_data.latest.recovered_diff == 0);
        REQUIRE(country_data.latest.active_diff == -1);
        REQUIRE(country_data.latest.fatality_rate == 0.0032);
      }
    }
  }
}

SCENARIO("CoronaAPIClient retrieves country data for Switzerland on 2020-03-01", "[CoronaAPIClient]")
{
  GIVEN("A corona-api client")
  {
    TestHTTPClient::get_called = 0;
    TestHTTPClient::get_urls = {};

    auto testee = coronan::CoronaAPIClientType<TestHTTPClient>{};

    static constexpr year_month_day date = 2020_y / March / 1_d;

    WHEN("the http client returns an OK response status and a payload with no data for Switzerland")
    {
      TestHTTPClient::responses = {{Poco::Net::HTTPResponse::HTTP_OK, "{ \
        \"data\": [] \
      }"}};

      auto const country_data = testee.request_country_data("CHE", date);

      auto const& [called, url] =
          TestHTTPClient::get_was_called_with("https://covid-api.com/api/reports/total?date=2020-03-01&iso=CHE");

      {
        INFO("HTTPClient::get was not called with the expected URL: " << url);
        CHECK(called);
      }

      THEN("the country data is empty.")
      {
        REQUIRE(country_data.timeline.empty());
      }
    }

    WHEN("the http client returns an OK response status and a payload with "
         "data for Switzerland")
    {
      TestHTTPClient::responses = {{Poco::Net::HTTPResponse::HTTP_OK, "{ \
          \"data\": { \
                \"date\": \"2020-03-01\", \
                \"confirmed\": 27, \
                \"deaths\": 0, \
                \"recovered\": 0, \
                \"confirmed_diff\": 9, \
                \"deaths_diff\": 1, \
                \"recovered_diff\": 0, \
                \"last_update\": \"2020-03-01 23:23:02\", \
                \"active\": 27, \
                \"active_diff\": 9, \
                \"fatality_rate\": 0 \
          } \
      }"}};

      auto const country_data = testee.request_country_data("CHE", date);

      auto const& [called, url] =
          TestHTTPClient::get_was_called_with("https://covid-api.com/api/reports/total?date=2020-03-01&iso=CHE");

      {
        INFO("HTTPClient::get was not called with the expected URL: " << url);
        CHECK(called);
      }

      THEN("the country data is returned.")
      {
        REQUIRE(country_data.timeline.at(0).date == date);
        REQUIRE(country_data.timeline.at(0).deaths == 0);
        REQUIRE(country_data.timeline.at(0).confirmed == 27);
        REQUIRE(country_data.timeline.at(0).recovered == 0);
        REQUIRE(country_data.timeline.at(0).active == 27);
        REQUIRE(country_data.timeline.at(0).deaths_diff == 1);
        REQUIRE(country_data.timeline.at(0).confirmed_diff == 9);
        REQUIRE(country_data.timeline.at(0).recovered_diff == 0);
        REQUIRE(country_data.timeline.at(0).active_diff == 9);
        REQUIRE(country_data.timeline.at(0).fatality_rate == 0.0);
      }
    }
  }
}

SCENARIO("CoronaAPIClient retrieves timeline country data for Switzerland", "[CoronaAPIClient]")
{
  GIVEN("A corona-api client")
  {
    TestHTTPClient::get_called = 0;
    TestHTTPClient::get_urls = {};
    auto testee = coronan::CoronaAPIClientType<TestHTTPClient>{};

    static constexpr year_month_day start_date = 2020_y / March / 1_d;
    static constexpr year_month_day end_date = 2020_y / March / 3_d;

    WHEN("the client retrieves data from to 2020-03-01 until the 2020-03-03")
    {

      TestHTTPClient::responses = {{Poco::Net::HTTPResponse::HTTP_OK, "{ \
          \"data\": { \
                \"date\": \"2020-03-01\", \
                \"confirmed\": 27, \
                \"confirmed_diff\": 9, \
                \"deaths\": 0, \
                \"deaths_diff\": 0, \
                \"recovered\": 0, \
                \"recovered_diff\": 0, \
                \"last_update\": \"2020-03-01 23:23:02\", \
                \"active\": 27, \
                \"active_diff\": 9, \
                \"fatality_rate\": 0 \
            } \
          }"},
                                   {Poco::Net::HTTPResponse::HTTP_OK, "{ \
            \"data\": { \
                \"date\": \"2020-03-02\", \
                \"confirmed\": 42, \
                \"confirmed_diff\": 15, \
                \"deaths\": 0, \
                \"deaths_diff\": 0, \
                \"recovered\": 0, \
                \"recovered_diff\": 0, \
                \"last_update\": \"2020-03-02 22:33:09\", \
                \"active\": 42, \
                \"active_diff\": 15, \
                \"fatality_rate\": 0 \
            } \
        }"},
                                   {Poco::Net::HTTPResponse::HTTP_OK, "{ \
          \"data\": { \
                \"date\": \"2020-03-03\", \
                \"confirmed\": 56, \
                \"confirmed_diff\": 14, \
                \"deaths\": 1, \
                \"deaths_diff\": 1, \
                \"recovered\": 2, \
                \"recovered_diff\": 2, \
                \"last_update\": \"2020-03-03 16:43:02\", \
                \"active\": 54, \
                \"active_diff\": 12, \
                \"fatality_rate\": 0.2 \
          } \
      }"}};

      auto const country_data = testee.request_country_data("CHE", start_date, end_date);

      auto const& [called, url] =
          TestHTTPClient::get_was_called_with({"https://covid-api.com/api/reports/total?date=2020-03-01&iso=CHE",
                                               "https://covid-api.com/api/reports/total?date=2020-03-02&iso=CHE",
                                               "https://covid-api.com/api/reports/total?date=2020-03-03&iso=CHE"});

      {
        INFO("HTTPClient::get was not called with the expected URL: " << url);
        CHECK(called);
      }

      THEN("the country data is returned.")
      {
        REQUIRE(country_data.timeline.size() == 3);
        REQUIRE(country_data.timeline.at(0).date == start_date);
        REQUIRE(country_data.timeline.at(0).confirmed == 27);
        REQUIRE(country_data.timeline.at(0).confirmed_diff == 9);
        REQUIRE(country_data.timeline.at(0).deaths == 0);
        REQUIRE(country_data.timeline.at(0).deaths_diff == 0);
        REQUIRE(country_data.timeline.at(0).recovered == 0);
        REQUIRE(country_data.timeline.at(0).recovered_diff == 0);
        REQUIRE(country_data.timeline.at(0).active == 27);
        REQUIRE(country_data.timeline.at(0).active_diff == 9);
        REQUIRE(country_data.timeline.at(0).fatality_rate == 0.0);
        REQUIRE(country_data.timeline.at(1).date == year_month_day{start_date.year(), start_date.month(), 2_d});
        REQUIRE(country_data.timeline.at(1).confirmed == 42);
        REQUIRE(country_data.timeline.at(1).confirmed_diff == 15);
        REQUIRE(country_data.timeline.at(1).deaths == 0);
        REQUIRE(country_data.timeline.at(1).deaths_diff == 0);
        REQUIRE(country_data.timeline.at(1).recovered == 0);
        REQUIRE(country_data.timeline.at(1).recovered_diff == 0);
        REQUIRE(country_data.timeline.at(1).active == 42);
        REQUIRE(country_data.timeline.at(1).active_diff == 15);
        REQUIRE(country_data.timeline.at(1).fatality_rate == 0.0);
        REQUIRE(country_data.timeline.at(2).date == end_date);
        REQUIRE(country_data.timeline.at(2).confirmed == 56);
        REQUIRE(country_data.timeline.at(2).confirmed_diff == 14);
        REQUIRE(country_data.timeline.at(2).deaths == 1);
        REQUIRE(country_data.timeline.at(2).deaths_diff == 1);
        REQUIRE(country_data.timeline.at(2).recovered == 2);
        REQUIRE(country_data.timeline.at(2).recovered_diff == 2);
        REQUIRE(country_data.timeline.at(2).active == 54);
        REQUIRE(country_data.timeline.at(2).active_diff == 12);
        REQUIRE(country_data.timeline.at(2).fatality_rate == 0.2);
      }
    }
  }
}

} // namespace
