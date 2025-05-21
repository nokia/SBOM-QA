#include "coronan/config.hpp"
#include "coronan/http_client.hpp"
#include "coronan/ssl_client.hpp"
#include "mainwindow.h"

#include <QDebug>
#include <QString>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  QMainWindow window;
  try
  {
    window.show();
    auto const titel = "Co[ro]nan " + std::string{coronan::config::project_version} + " by bbv Software Services AG";
    window.setWindowTitle(titel.c_str());
    auto const window_width = 1600;
    auto const window_height = 1200;
    window.resize(window_width, window_height);
    auto* const widget = new coronan_ui::CoronanWidget();
    window.setCentralWidget(widget);
    return app.exec(); // NOLINT(readability-static-accessed-through-instance)
  }
  catch (coronan::HTTPClientException const& ex)
  {
    qCritical() << ex.what();
    QMessageBox::critical(&window, QStringLiteral("Http Exception"), QString{ex.what()});
    app.exit(EXIT_FAILURE);
  }
  catch (coronan::SSLException const& ex)
  {
    qCritical() << ex.what();
    QMessageBox::critical(&window, QStringLiteral("SSL Exception"), QString{ex.what()});
    app.exit(EXIT_FAILURE);
  }
  catch (std::exception const& ex)
  {
    qCritical() << ex.what();
    QMessageBox::critical(&window, QStringLiteral("Exception"), QString{ex.what()});
    app.exit(EXIT_FAILURE);
  }
}
