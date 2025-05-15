#pragma once

#include <Poco/Net/Context.h>

namespace coronan::ssl_context {

Poco::Net::Context::Ptr create_ssl_context();

} // namespace coronan::ssl_context
