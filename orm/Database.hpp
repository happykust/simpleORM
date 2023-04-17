#include "SimpleConnection.hpp"
#include "Statement.hpp"
#include "Table.hpp"

#ifndef SIMPLEORM_DATABASE_H
#define SIMPLEORM_DATABASE_H

namespace simpleOrm {

    class Database {
    private:
        SimpleConnection* connection;
    public:
        template<class... T>
        explicit Database(SimpleConnection* connection, T... tables) : connection(connection) {}

        auto query(Table table) {
            return nullptr;
        }

        void drop_all() {

        }

        void create_all() {

        }
    };

}// namespace simpleOrm


#endif//SIMPLEORM_DATABASE_H
