#include "orm/Database.hpp"
#include "orm/Exception.hpp"

#include <iostream>

using namespace std;
using namespace simpleOrm;

struct Book {
    uint id;
    std::string title;
};

int main() {
    cout << endl;

    SimpleConnection conn("127.0.0.1", "user", "pass", "db", "3306");
    conn.connect();

    Table table_book("books", vector<std::any>{
                                      Column<uint>("id"),
                                      Column<std::string>("title")});

    Database db(&conn, vector<Table>{table_book});
    TabledResult result = db.query<Book>(table_book).all().execute();

    vector<Book> rows = result.rows();

    for (int i = 0; i < result.count(); i++) {
        cout << rows[i].title;
    }

    conn.disconnect();

    cout << endl;
}