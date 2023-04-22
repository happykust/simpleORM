#ifndef SIMPLEORM_STATEMENT_HPP
#define SIMPLEORM_STATEMENT_HPP

#include "SimpleConnection.hpp"
#include "StatementMaker.hpp"
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
        SimpleConnection *connection;

    public:
        explicit Statement(SimpleConnection *connection) : connection(connection) {}
    };

    template<class T>
    class TabledStatementFinal : public Statement {
    private:
        Table table;
        StatementMaker maker;

    public:
        TabledStatementFinal(SimpleConnection *connection,
                             Table  table,
                             StatementMaker maker) : Statement(connection),
                                                     table(std::move(table)),
                                                     maker(std::move(maker)){}

        TabledResult<T> execute() {
            try {
                stmt = connection->getConnection()->createStatement();
                res = stmt->executeQuery(maker.makeQuery());
                return TabledResult<T>(table, res);
            } catch (sql::SQLException &e) {
                throw SimpleOrmException(e.what());
            }
        }
    };

    template<class T>
    class TabledStatement : public Statement {
    private:
        Table table;
        StatementMaker maker;

    public:
        TabledStatement(SimpleConnection *connection, const Table& table) : Statement(connection), table(table), maker(table) {}

        TabledResult<T> execute() {
            try {
                stmt = connection->getConnection()->createStatement();
                res = stmt->executeQuery(maker.makeQuery());
                return TabledResult<T>(table, res);
            } catch (sql::SQLException &e) {
                throw SimpleOrmException(e.what());
            }
        }

        TabledStatement where(const std::string& condition_string) {
            maker.add_where(condition_string);
            return *this;
        }

        TabledStatement limit(int limit) {
            maker.add_limit(limit);
            return *this;
        }

        TabledStatement offset(int offset) {
            maker.add_offset(offset);
            return *this;
        }

        TabledStatement join(const Table& join_table, const std::string& on_string) {
            maker.add_join(join_table, on_string);
            return *this;
        }

        TabledStatementFinal<T> update() {
        }
    };

    class RawStatement : public Statement {
    private:
        std::string sql;
    public:
        explicit RawStatement(SimpleConnection *connection, std::string sql_query) : Statement(connection) {
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
