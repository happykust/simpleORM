#include "Column.hpp"
#include "Table.hpp"

#include <any>
#include <cppconn/resultset.h>
#include <set>
#include <utility>
#include <variant>
#include <cassert>

namespace simpleOrm {

    template <typename T, std::size_t... Indices>
    auto vectorToTupleHelper(const std::vector<T>& v, std::index_sequence<Indices...>) {
        return std::make_tuple(v[Indices]...);
    }

    template <std::size_t N, typename T>
    auto vectorToTuple(const std::vector<T>& v) {
        assert(v.size() >= N);
        return vectorToTupleHelper(v, std::make_index_sequence<N>());
    }

    template<typename F, typename Tuple, bool Enough, int TotalArgs, int... N>
    struct call_impl
    {
        auto static call(F f, Tuple&& t)
        {
            return call_impl<F, Tuple, TotalArgs == 1 + sizeof...(N),
                             TotalArgs, N..., sizeof...(N)
                             >::call(f, std::forward<Tuple>(t));
        }
    };

    template<typename F, typename Tuple, int TotalArgs, int... N>
    struct call_impl<F, Tuple, true, TotalArgs, N...>
    {
        auto static call(F f, Tuple&& t)
        {
            return f(std::get<N>(std::forward<Tuple>(t))...);
        }
    };

    template<typename F, typename Tuple>
    auto call(F f, Tuple&& t)
    {
        typedef typename std::decay<Tuple>::type type;
        return call_impl<F, Tuple, 0 == std::tuple_size<type>::value,
                         std::tuple_size<type>::value
                         >::call(f, std::forward<Tuple>(t));
    }

    template<class TableS>
    class TabledResult {
    private:
        Table table;
        sql::ResultSet *result;

    public:
        explicit TabledResult(Table table, sql::ResultSet *result) : table(std::move(table)), result(result){};

        sql::ResultSet *raw() {
            return result;
        }

        std::vector<TableS> rows() {
            std::vector<TableS> rows;
            rows.reserve(result->rowsCount());

            while (result->next()) {
                const int column_count = result->getMetaData()->getColumnCount();

                std::vector<std::string> columns_values;
                columns_values.reserve(column_count);

                for (int i = 1; i <= column_count; i++) {
                    columns_values.push_back(result->getString(i));
                }

                rows.push_back(call(TableS::create, vectorToTuple<TableS::fieldsCount()>(columns_values)));
            }

            return rows;
        }

        size_t count() {
            return result->rowsCount();
        }
    };

}// namespace simpleOrm
