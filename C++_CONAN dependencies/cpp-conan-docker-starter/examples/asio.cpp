// https://think-async.com/Asio/asio-1.16.1/doc/asio/tutorial.html

#include <iostream>
#include <ctime>
#include <string>

#include <asio.hpp>
#include <fmt/format.h>

using asio::ip::tcp;


std::string make_daytime_string(){
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}


int main() {
    try {
        asio::io_context iocontext;
        tcp::acceptor acceptor(iocontext, tcp::endpoint(tcp::v4(), 5000));

        for(;;){
            tcp::socket socket(iocontext);
            acceptor.accept(socket);

            std::cout << fmt::format("new client connected") << std::endl;

            std::string message = make_daytime_string();
            asio::error_code ec;
            asio::write(socket, asio::buffer(message), ec);
        }
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
    
}