#include "coronan/http_client.hpp"

#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>

using Poco::Net::HTTPMessage;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;

namespace {

struct TestHTTPRequest
{
  TestHTTPRequest(std::string const& request, std::string const& path, std::string const& type)
  {
    TestHTTPRequest::request_ = request;
    TestHTTPRequest::type_ = type;
    TestHTTPRequest::path_ = path;
  }

  inline static std::string request_{};
  inline static std::string type_{};
  inline static std::string path_{};
};

struct TestHTTPSession
{

  TestHTTPSession(std::string const& host, std::uint16_t port)
  {
    TestHTTPSession::port_ = port;
    TestHTTPSession::host_ = host;
  }

  std::ostream& sendRequest(TestHTTPRequest& /*unused*/)
  {
    return std::cout;
  }

  std::istream& receiveResponse(HTTPResponse& response)
  {
    if (throw_exception)
    {
      throw exception;
    }
    response.setStatusAndReason(TestHTTPSession::response_status_, TestHTTPSession::response_reason_);
    return TestHTTPSession::response_;
  }

  static void set_response_status(HTTPResponse::HTTPStatus status)
  {
    TestHTTPSession::response_status_ = status;
  }

  static void set_response_reason(std::string const& reason)
  {
    TestHTTPSession::response_reason_ = reason;
  }

  static void set_response(std::string const& response)
  {
    TestHTTPSession::response_ = std::istringstream{response};
  }

  static void set_throw_exception()
  {
    throw_exception = true;
  }

  inline static std::uint16_t port_{};
  inline static std::string host_{};
  inline static HTTPResponse::HTTPStatus response_status_{HTTPResponse::HTTP_OK};
  inline static std::string response_reason_{};
  inline static std::istringstream response_{""};
  inline static bool throw_exception{false};
  inline static std::exception exception{};
};

using TesteeT = coronan::HTTPClientType<TestHTTPSession, TestHTTPRequest, Poco::Net::HTTPResponse>;

TEST_CASE("HTTPClient get", "[HTTPClient]")
{
  SECTION("Initializes a session")
  {
    auto const* uri = "http://server.com:80/";
    auto response = TesteeT::get(uri);

    REQUIRE(TestHTTPSession::host_ == "server.com");
    REQUIRE(TestHTTPSession::port_ == 80);
  }

  SECTION("Creates a request")
  {
    auto const* uri = "http://server.com:80/test";
    auto const response = TesteeT::get(uri);
    REQUIRE(TestHTTPRequest::request_ == HTTPRequest::HTTP_GET);
    REQUIRE(TestHTTPRequest::type_ == HTTPMessage::HTTP_1_1);
    REQUIRE(TestHTTPRequest::path_ == "/test");
  }

  SECTION("Returns status, reason and response")
  {
    auto const expected_status = HTTPResponse::HTTP_FOUND;
    auto const* const expected_reason = "All ok";
    auto const* const expected_response = "Test";

    TestHTTPSession::set_response_status(expected_status);
    TestHTTPSession::set_response_reason(expected_reason);
    TestHTTPSession::set_response(expected_response);

    auto const* uri = "http://server.com:80/test";
    auto const response = TesteeT::get(uri);

    REQUIRE(response.status() == expected_status);
    REQUIRE(response.reason() == expected_reason);
    REQUIRE(response.response_body() == expected_response);
  }

  SECTION("Throws an HTTPClientException when Session throws exception")
  {
    TestHTTPSession::set_throw_exception();

    auto const* uri = "http://server.com:80/test";
    REQUIRE_THROWS_AS(TesteeT::get(uri), coronan::HTTPClientException);
  }
}

} // namespace
