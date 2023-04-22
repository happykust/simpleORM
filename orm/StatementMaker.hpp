#include "Table.hpp"
#include <sstream>
#include <utility>

namespace simpleOrm {

    class StatementMaker {
    private:
        Table table;
        std::string query;

        bool used_where = false;
        std::string where_condition;

        bool used_limit = false;
        int limit;

        bool used_offset = false;
        int offset;

        std::string join_string;

        bool used_create = false;
        bool used_update = false;
        bool used_remove = false;

    public:
        explicit StatementMaker(const Table &table) : table(table) {
            query = "SELECT * FROM " + table.table_name;
        }

        void add_where(const std::string &condition_string) {
            used_where = true;
            where_condition = condition_string;
        }

        void add_limit(int _limit) {
            used_limit = true;
            limit = _limit;
        }

        void add_offset(int _offset) {
            used_offset = true;
            offset = _offset;
        }

        void call_create(const std::string &values) {
            used_create = true;
            query = "INSERT INTO " + table.table_name + " VALUES (DEFAULT, " + values + ")";
        }

        void call_remove() {
            used_remove = true;
        }

        void call_update(const std::string& update_string, const std::string& condition) {
            used_update = true;
            query = "UPDATE " + table.table_name + " SET " + update_string + " WHERE " + condition;
        }

        std::string makeQuery() {

            if (used_create) {
                return query;
            }

            if (used_remove) {
                query = "DELETE FROM " + table.table_name;
                if (used_where) {
                    query += " WHERE " + where_condition;
                }
                return query;
            }

            if (used_where) {
                query += " WHERE " + where_condition;
            }
            if (used_offset) {
                query += " OFFSET " + std::to_string(offset);
            }
            if (used_limit) {
                query += " LIMIT " + std::to_string(limit);
            }

            return query;
        }
    };

}// namespace simpleOrm
