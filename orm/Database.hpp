#ifndef SIMPLEORM_DATABASE_HPP
#define SIMPLEORM_DATABASE_HPP

#include <utility>

#include "Statement.hpp"
#include "Table.hpp"

namespace simpleOrm {

    class Database {
    private:
        SimpleConnection* connection;
        std::vector<Table> tables;
        bool auto_create = true;
    public:
        template<class... T>
        explicit Database(
                SimpleConnection* connection,
                T... tables) : connection(connection), tables(tables...) {}

        template<class T>
        TabledStatement<T> query(const Table& table) {
            return {connection, table};
        }

        RawStatement raw_query(std::string sql_query) {
            return RawStatement(connection, std::move(sql_query));
        }

        void drop_all() {

        }

        void create_all() {

        }
    };

}// namespace simpleOrm


#endif//SIMPLEORM_DATABASE_HPP
