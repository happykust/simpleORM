#include "orm/Database.hpp"
#include "orm/Exception.hpp"

#include <iostream>
#include <utility>

using namespace std;
using namespace simpleOrm;

class Book {
public:
    uint id;
    char * title;

    Book(uint id, char * title) : id(id), title(title) {}

    static Book create(std::string id, char * title) {
        return {static_cast<uint>(std::stoi(id)), title};
    }

    static constexpr unsigned long int fieldsCount() { return 2; }
};

int main() {
    cout << endl;

    SimpleConnection conn("127.0.0.1", "user", "pass", "db", "3306");
    conn.connect();

    Table table_book("books", std::vector<Column>{
            Column("id", typeid(uint).name(), true),
            Column("title", typeid(char*).name())
    });

    Table table_lol("lol", std::vector<Column>{
            Column("id", typeid(uint).name(), true),
            Column("title", typeid(char*).name())
    });

    Database db(&conn, vector<Table>{table_book, table_lol});
    db.create_tables();
    //TabledResult result = db.query<Book>(table_book).limit(1).execute();

    //vector<Book> rows = result.rows();

    //for (int i = 0; i < result.count(); i++) {
    //    cout << rows[i].title << endl;
    //}

    //db.query<Book>(table_book).create("'Hellhole'").execute();

    //db.query<Book>(table_book).update("title = 'Hellhole'", "id = 1").execute();

    conn.disconnect();

    cout << endl;
}