#include <utility>
#include "Table.hpp"

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

        bool used_join = false;
        std::string join_string;


    public:
        explicit StatementMaker(const Table& table) : table(table) {
            query = "SELECT * FROM " + table.table_name;
        }

        void add_where(const std::string& condition_string) {
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

        void add_join(const Table& join_table, const std::string& on_string){
            used_join = true;
            join_string = "JOIN " + join_table.table_name + " ON " + on_string;
        }

        std::string makeQuery() {
            if (used_join) {
                query = query + " " + join_string;
            }
            if (used_where) {
                query = query + " WHERE " + where_condition;
            }
            if (used_offset) {
                query = query + " OFFSET " + std::to_string(offset);
            }
            if (used_limit) {
                query = query + " LIMIT " + std::to_string(limit);
            }

            return query;
        }
    };

}
