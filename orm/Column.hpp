#ifndef SIMPLEORM_COLUMN_HPP
#define SIMPLEORM_COLUMN_HPP

#include "Exception.hpp"
#include <any>
#include <ctime>
#include <string>
#include <utility>
#include <variant>

namespace simpleOrm {

    template<class Field>
    std::string getColumnSQLType() {
        if (std::is_same_v<Field, std::string> ||
            std::is_same_v<Field, char *> ||
            std::is_same_v<Field, char const *>)
            return "TEXT";
        else if (std::is_integral_v<Field>) {

            if constexpr (std::is_same_v<Field, bool>)
                return "BOOLEAN";
            else if constexpr (std::is_same_v<Field, int8_t>)
                return "TINYINT";
            else if constexpr (std::is_same_v<Field, uint8_t>)
                return "TINYINT UNSIGNED";
            else if constexpr (std::is_same_v<Field, int16_t>)
                return "SMALLINT";
            else if constexpr (std::is_same_v<Field, uint16_t>)
                return "SMALLINT UNSIGNED";
            else if constexpr (std::is_same_v<Field, int32_t>)
                return "INTEGER";
            else if constexpr (std::is_same_v<Field, uint32_t>)
                return "INTEGER UNSIGNED";
            else if constexpr (std::is_same_v<Field, int64_t>)
                return "BIGINT";
            else if constexpr (std::is_same_v<Field, uint64_t>)
                return "BIGINT UNSIGNED";
        } else if (std::is_same_v<Field, std::tm>) {
            return "DATETIME";
        }
        throw SimpleOrmException(std::string("Field type is unsupported!"));
    }

    template<class T>
    class Column {
    private:
        std::string sql_type;
    public:
        std::string column_name;
        explicit Column(std::string column_name) : column_name(std::move(column_name)) {
            sql_type = getColumnSQLType<T>();
        }
    };

}// namespace simpleOrm


#endif//SIMPLEORM_COLUMN_HPP
