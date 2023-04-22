#ifndef SIMPLEORM_TABLE_HPP
#define SIMPLEORM_TABLE_HPP

#include "Column.hpp"
#include <any>
#include <boost/type_index.hpp>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace simpleOrm {

    class Table {
    public:
        std::vector<Column> columns;
        std::string table_name;

        template<class... T>
        explicit Table(
                std::string table_name,
                T... columns) : columns(columns...),
                                table_name(std::move(table_name)) {
        }
    };

}// namespace simpleOrm


#endif//SIMPLEORM_TABLE_HPP
