#include "orm/Database.hpp"
#include "orm/Exception.hpp"

#include <iostream>
#include <utility>

using namespace std;
using namespace simpleOrm;

// Класс книги, который будет храниться в базе данных
class Book {
public:
    uint id;
    std::string title;

    // Конструктор по умолчанию
    Book(uint id, std::string title) : id(id), title(std::move(title)) {}

    // Метод, который будет вызываться при создании объекта из базы данных (ОБЯЗАТЕЛЬНО ДЛЯ ИМПЛЕМЕНТАЦИИ)
    // Все входящие параметры имеют тип std::string
    // Возвращаем конструктор класса с приведением типов
    static Book create(std::string id, std::string title) {
        return {static_cast<uint>(std::stoi(id)), std::move(title)};
    }

    // Метод, который хоанит количество полей в классе (ОБЯЗАТЕЛЬНО ДЛЯ ИМПЛЕМЕНТАЦИИ)
    static constexpr unsigned long int fieldsCount() { return 2; }
};

int main() {
    cout << endl;

    // Устанавливем соединение с базой данных
    SimpleConnection conn("mysql-database", "user", "pass", "db", "3306");
    conn.connect();

    // Создаем таблицу books, в которой будет два поля: id и title типа TEXT (char*) и первичный ключ id типа INT
    Table table_book("books", std::vector<Column>{
            Column("id", typeid(uint).name(), true),
            Column("title", typeid(char*).name())
    });

    // Создаем объект базы данных, передавая в конструктор объект соединения и вектор таблиц
    Database db(&conn, vector<Table>{table_book});

    // Создаем таблицы в базе данных
    db.create_tables();

    // Создаем пару книг и добавляем их в базу данных
    cout << "Create books:" << endl;
    cout << "ID: 1 Title: One simple book" << endl;
    cout << "ID: 2 Title: Second clear book" << endl;
    cout << "ID: 3 Title: One day, two day, three year" << endl;
    cout << "ID: 4 Title: Step by step to disappearing" << endl;
    db.query<Book>(table_book).create("'One simple book'").execute();
    db.query<Book>(table_book).create("'Second clear book'").execute();
    db.query<Book>(table_book).create("'One day, two day, three year'").execute();
    db.query<Book>(table_book).create("'Step by step to disappearing'").execute();

    // Получаем все книги из базы данных
    TabledResult result = db.query<Book>(table_book).execute();

    // Выводим все книги
    vector<Book> rows = result.rows();
    cout << endl << "All books:" << endl;
    for (int i = 0; i < result.count(); i++) {
        cout << "ID: " << rows[i].id << " Title: " <<rows[i].title << endl;
    }
    cout << endl;

    // Удаляем книгу с id = 1
    db.query<Book>(table_book).where("id = 1").remove().execute();

    // Получаем все книги из базы данных
    TabledResult result_after_delete = db.query<Book>(table_book).execute();

    // Выводим все книги
    vector<Book> rows_after_delete = result_after_delete.rows();
    cout << endl << "All books after delete book with id = 1:" << endl;
    for (int i = 0; i < result_after_delete.count(); i++) {
        cout << "ID: " << rows_after_delete[i].id << " Title: " << rows_after_delete[i].title << endl;
    }
    cout << endl;

    // Создаем ещё одну книгу и добавляем её в базу данных
    db.query<Book>(table_book).create("'And the last magic book'").execute();

    // Получаем все книги из базы данных
    TabledResult result_after_add = db.query<Book>(table_book).execute();

    // Выводим все книги
    vector<Book> rows_after_add = result_after_add.rows();
    cout << endl << "All books after add book 'And the last magic book':" << endl;
    for (int i = 0; i < result_after_add.count(); i++) {
        cout << "ID: " << rows_after_add[i].id << " Title: " << rows_after_add[i].title << endl;
    }
    cout << endl;

    // Обновляем книгу с id = 2
    db.query<Book>(table_book).update("title = 'NEW MEGA TITLEEEEE!!!!!!'", "id = 2").execute();

    // Получаем все книги из базы данных
    TabledResult result_after_update = db.query<Book>(table_book).execute();

    // Выводим все книги
    vector<Book> rows_after_update = result_after_update.rows();
    cout << endl << "All books after update book with id = 2:" << endl;
    for (int i = 0; i < result_after_update.count(); i++) {
        cout << "ID: " << rows_after_update[i].id << " Title: " << rows_after_update[i].title << endl;
    }
    cout << endl;

    // Выведем книги с лимитом 2
    TabledResult result_with_limit = db.query<Book>(table_book).limit(2).execute();
    vector<Book> rows_with_limit = result_with_limit.rows();
    cout << endl << "All books with limit 2:" << endl;
    for (int i = 0; i < result_with_limit.count(); i++) {
        cout << "ID: " << rows_with_limit[i].id << " Title: " << rows_with_limit[i].title << endl;
    }
    cout << endl;

    // Выведем книги с лимитом 2 и смещением 2
    TabledResult result_with_limit_and_offset = db.query<Book>(table_book).limit(2).offset(2).execute();
    vector<Book> rows_with_limit_and_offset = result_with_limit_and_offset.rows();
    cout << endl << "All books with limit 2 and offset 2:" << endl;
    for (int i = 0; i < result_with_limit_and_offset.count(); i++) {
        cout << "ID: " << rows_with_limit_and_offset[i].id << " Title: " << rows_with_limit_and_offset[i].title << endl;
    }

    // Удаляем все книги
    db.query<Book>(table_book).remove().execute();

    // Попробуем получить все книги из базы данных
    TabledResult result_after_remove = db.query<Book>(table_book).execute();

    // Выводим все книги
    vector<Book> rows_after_remove = result.rows();
    cout << endl << "All books after remove all books:" << endl;
    for (int i = 0; i < result_after_remove.count(); i++) {
        cout << "ID: " << rows_after_remove[i].id << " Title: " << rows_after_remove[i].title << endl;
    }
    cout << endl;

    // Удаляем таблицу books
    db.drop_tables();

    conn.disconnect();

    cout << endl;
}