#ifndef SIMPLEORM_TABLE_HPP
#define SIMPLEORM_TABLE_HPP

#include "Column.hpp"
#include <any>
#include <string>
#include <utility>
#include <vector>

namespace simpleOrm {

    class Table {
    private:
        std::string table_name;
        std::vector<Column<std::any>> columns;

    public:
        template<class... T>
        explicit Table(
                std::string table_name,
                T... columns) : columns(columns...),
                                table_name(std::move(table_name)) {}
    };

}// namespace simpleOrm


#endif//SIMPLEORM_TABLE_HPP
