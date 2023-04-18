#include <cppconn/resultset.h>
#include <utility>
#include <variant>

namespace simpleOrm {

    template<class T>
    class TabledResult {
    private:
        Table table;
        sql::ResultSet *result;

    public:
        explicit TabledResult(Table table, sql::ResultSet *result) : table(std::move(table)), result(result){};

        sql::ResultSet *raw() {
            return result;
        }

        std::vector<T> rows() {
            std::vector<T> rows;
            std::vector<std::variant<uint, std::string>> columns_values;
            rows.reserve(result->rowsCount());
            while (result->next()) {

                for (auto & column : table.columns) {
                    columns_values.emplace_back(std::any_cast<Column<std::variant<uint, std::string>>>(column).column_name);
                }

                T el;
                std::apply([&el](auto &&...args) {
                    el = {args...};
                },columns_values);
                rows.push_back(el);
            }
            return rows;
        }

        size_t count() {
            return result->rowsCount();
        }
    };

}// namespace simpleOrm
