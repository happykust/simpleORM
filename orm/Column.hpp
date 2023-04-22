#ifndef SIMPLEORM_COLUMN_HPP
#define SIMPLEORM_COLUMN_HPP

#include "Exception.hpp"
#include <any>
#include <ctime>
#include <string>
#include <utility>
#include <variant>
#include <boost/core/demangle.hpp>

namespace simpleOrm {

    std::string getColumnSQLType(const std::string& type_name) {
        if (type_name == "char*")
            return "TEXT";

        if (type_name == "bool")
            return "BOOLEAN";

        if (type_name == "int")
            return "INT";

        if (type_name == "unsigned int")
            return "INT UNSIGNED";

        throw SimpleOrmException(std::string("Field type is unsupported!"));
    }

    class Column {
    public:
        std::string column_name;
        std::string sql_type;
        bool primary_key;
        bool unique;

        explicit Column(std::string column_name,
                        const char * type_name,
                        bool primary_key = false,
                        bool unique = false) : column_name(std::move(column_name)),
                                               sql_type(getColumnSQLType(boost::core::demangle(type_name))),
                                               primary_key(primary_key),
                                               unique(unique) {}
    };

}// namespace simpleOrm


#endif//SIMPLEORM_COLUMN_HPP
