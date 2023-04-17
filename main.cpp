#include "orm/Exception.hpp"
#include "orm/SimpleConnection.hpp"

#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <iostream>

using namespace std;
using namespace simpleOrm;

int main() {
    cout << endl;

    try {
        sql::Statement *stmt;
        sql::ResultSet *res;

        SimpleConnection conn("127.0.0.1", "user", "pass", "db", "3306");
        conn.connect();

        stmt = conn.getConnection()->createStatement();
        res = stmt->executeQuery("SELECT * FROM books");
        while (res->next()) {
            cout << "\t... MySQL replies: ";
            /* Access column data by alias or column name */
            cout << res->getString("title") << endl;
            cout << "\t... MySQL says it again: ";
            /* Access column data by numeric offset, 1 is the first column */
            cout << res->rowsCount() << endl;
        }
        delete res;
        delete stmt;

    } catch (sql::SQLException &e) {
        throw simpleOrm::SimpleOrmException(e.what());
    }

    cout << endl;

    return EXIT_SUCCESS;
}