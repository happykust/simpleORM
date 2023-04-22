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

        void drop_tables() {
            for (auto& table : tables) {
                try {
                    stmt = connection->getConnection()->createStatement();
                    stmt->execute("DROP TABLE IF EXISTS " + table.table_name);
                } catch (sql::SQLException &e) {
                    if (e.what() != std::string("")) {
                        throw SimpleOrmException(e.what());
                    }
                }
            }
        }

        void create_tables() {
            if (!auto_create) {
                return ;
            }
            for (auto& table : tables) {

                std::string query = "CREATE TABLE IF NOT EXISTS " + table.table_name + " (";
                std::string pk;

                for (auto& column : table.columns) {
                    query += column.column_name + " " + column.sql_type + ", ";
                    if (column.primary_key) {
                        pk = "PRIMARY KEY (" + column.column_name + ")";
                    }
                }
                query += pk + ")";

                try {
                    stmt = connection->getConnection()->createStatement();
                    stmt->execute(query);
                } catch (sql::SQLException &e) {
                    if (e.what() != std::string("")) {
                        throw SimpleOrmException(e.what());
                    }
                }
            }
        }
    };

}// namespace simpleOrm


#endif//SIMPLEORM_DATABASE_HPP
