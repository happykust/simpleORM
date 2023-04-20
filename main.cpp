#include "orm/Database.hpp"
#include "orm/Exception.hpp"

#include <iostream>
#include <utility>

using namespace std;
using namespace simpleOrm;

class Book {
public:
    uint id;
    std::string title;

    Book(uint id, std::string title) : id(id), title(std::move(title)) {}

    static Book create(std::string id, std::string title) {
        return {static_cast<uint>(std::stoi(id)), std::move(title)};
    }

    static constexpr unsigned long int f() { return 2; }
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
        cout << rows[i].title << endl;
    }

    conn.disconnect();

    cout << endl;
}