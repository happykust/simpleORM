cmake_minimum_required(VERSION 3.25)
project(simpleORM)

set(CMAKE_CXX_STANDARD 17)

# add_library(simpleORM SHARED main.cpp)
add_executable(simpleORM
        main.cpp
        utils/DateTime.cpp
        utils/DateTime.h
        orm/Table.hpp
        orm/SimpleConnection.hpp
        orm/Exception.hpp
        orm/Database.hpp
        orm/Column.hpp
        orm/Statement.hpp
        orm/Transaction.hpp orm/sql/Create.cpp orm/sql/Create.h orm/sql/Drop.cpp orm/sql/Drop.h)