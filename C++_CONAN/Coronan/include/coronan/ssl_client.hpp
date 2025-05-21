#pragma once

#include <Poco/Net/Context.h>
#include <Poco/Net/InvalidCertificateHandler.h>
#include <Poco/Net/SSLException.h>
#include <Poco/SharedPtr.h>
#include <memory>

namespace coronan {

using SSLException = Poco::Net::SSLException;

/**
 * An RAII wrapper to initialize & uninitialize the POCO::Net SSL stuff
 * (Poco::Net::initializeSSL())
 */
class SSLClient final
{
public:
  /**
   * Return a SSLClient with an accept all certifcates handler
   * @return SSLClient which must be hold by the caler until no longer needed.
   */
  [[nodiscard]] static std::unique_ptr<SSLClient> create_with_accept_certificate_handler();

  ~SSLClient();

  SSLClient(SSLClient&&) = delete;
  SSLClient(SSLClient const&) = delete;
  SSLClient& operator=(SSLClient&&) = delete;
  SSLClient& operator=(SSLClient const&) = delete;

private:
  explicit SSLClient(Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> cert_handler,
                     Poco::Net::Context::Ptr net_context);

  void initialize();
  Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> certificate_handler{};
  Poco::Net::Context::Ptr context;
};

} // namespace coronan
