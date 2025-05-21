
#include "coronan/ssl_client.hpp"

#include "coronan/ssl_context.hpp"

#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/NetSSL.h>
#include <Poco/Net/SSLManager.h>
#include <utility>

namespace coronan {

SSLClient::SSLClient(Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> cert_handler,
                     Poco::Net::Context::Ptr net_context)
    : certificate_handler{std::move(cert_handler)}, context{std::move(net_context)}
{
  Poco::Net::initializeSSL();
}

SSLClient::~SSLClient()
{
  Poco::Net::uninitializeSSL();
}

void SSLClient::initialize()
{
  Poco::Net::SSLManager::instance().initializeClient(nullptr, certificate_handler, context);
}

std::unique_ptr<SSLClient>
// cppcheck-suppress unusedFunction
SSLClient::create_with_accept_certificate_handler()
{
  static constexpr auto handle_errors_on_server_side = false;

  // Using `new` to access a non-public constructor.
  auto cert_handler = Poco::SharedPtr<Poco::Net::InvalidCertificateHandler>{
      new Poco::Net::AcceptCertificateHandler{handle_errors_on_server_side}};
  auto ssl_client =
      std::unique_ptr<SSLClient>{new SSLClient{std::move(cert_handler), coronan::ssl_context::create_ssl_context()}};

  ssl_client->initialize();
  return ssl_client;
}

} // namespace coronan
