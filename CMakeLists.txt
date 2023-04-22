cmake_minimum_required(VERSION 3.24)
project(simpleORM)

set(CMAKE_CXX_STANDARD 17)

link_directories(${CMAKE_INCLUDE_CURRENT_DIR})
link_libraries(mysqlcppconn)

add_executable(simpleORM
        main.cpp
        orm/Table.hpp
        orm/SimpleConnection.hpp
        orm/Exception.hpp
        orm/Database.hpp
        orm/Column.hpp
        orm/Statement.hpp
        orm/Transaction.hpp orm/TabledResult.hpp orm/StatementMaker.hpp)