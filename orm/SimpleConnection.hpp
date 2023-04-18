#ifndef SIMPLEORM_CONNECTION_HPP

#include "Exception.hpp"
#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <string>
#include <utility>

namespace simpleOrm {

    class SimpleConnection {
    private:
        bool connected = false;
        std::string connectionString;
        std::string user;
        std::string password;
        std::string database;
        sql::Connection *connection;
    public:
        SimpleConnection(
                const std::string &host,
                std::string user,
                std::string password,
                std::string database,
                const std::string &port) : user(std::move(user)),
                                           password(std::move(password)),
                                           database(std::move(database)),
                                           connectionString("tcp://" + host + ":" + port){};

        void connect() {
            if (connected) {
                return;
            }

            try {
                sql::Connection *con = get_driver_instance()->connect(connectionString, user, password);
                con->setSchema(database);
                this->connection = con;
                this->connected = true;
            } catch (sql::SQLException &e) {
                throw SimpleOrmException(std::string("Couldn't connect to database: ") + e.what());
            }
        };

        void disconnect() {
            if (!connected) {
                return;
            }
            delete this->connection;
            this->connected = false;
        };

        bool isConnected() { return connected; };

        sql::Connection *getConnection() { return connection; };
    };

}// namespace simpleOrm


#endif//SIMPLEORM_CONNECTION_HPP
