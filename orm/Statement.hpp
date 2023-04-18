#ifndef SIMPLEORM_STATEMENT_HPP
#define SIMPLEORM_STATEMENT_HPP

#include "SimpleConnection.hpp"
#include "Table.hpp"
#include "TabledResult.hpp"

#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <utility>

sql::Statement *stmt;
sql::ResultSet *res;

namespace simpleOrm {

    class Statement {
    protected:
        SimpleConnection* connection;
        std::string sql;
    public:
        explicit Statement(SimpleConnection* connection) : connection(connection) {}
    };

    template<class T>
    class TabledStatement : public Statement {
    private:
        Table table;
    public:
        TabledStatement(SimpleConnection* connection, Table table) : Statement(connection), table(std::move(table)) {}

        TabledResult<T> execute() {
            try {
                stmt = connection->getConnection()->createStatement();
                res = stmt->executeQuery(sql);
                return TabledResult<T>(table, res);
            } catch (sql::SQLException &e) {
                throw SimpleOrmException(e.what());
            }
        }

        TabledStatement all() {
            sql = "SELECT * FROM " + table.table_name;
            return *this;
        }

    };

    class RawStatement : public Statement {
        public:
            explicit RawStatement(SimpleConnection* connection, std::string sql_query) : Statement(connection) {
                sql = std::move(sql_query);
            }

            sql::ResultSet *execute() {
                try {
                    stmt = connection->getConnection()->createStatement();
                    res = stmt->executeQuery(sql);
                    return res;
                } catch (sql::SQLException &e) {
                    throw SimpleOrmException(e.what());
                }
            }
    };

}// namespace simpleOrm


#endif//SIMPLEORM_STATEMENT_HPP
