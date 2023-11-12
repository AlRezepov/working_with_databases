#include <iostream>
#include <wt/dbo/dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

class Publisher {
public:
    int id = 0;
    std::string name = "";

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, id, "id");
        Wt::Dbo::field(a, name, "name");
    }
};

class Book {
public:
    int id = 0;
    std::string title = "";
    Wt::Dbo::ptr<Publisher> publisher;

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, id, "id");
        Wt::Dbo::field(a, title, "title");
        Wt::Dbo::belongsTo(a, publisher, "id_publisher");
    }
};

class Shop {
public:
    int id = 0;
    std::string name = "";

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, id, "id");
        Wt::Dbo::field(a, name, "name");
    }
};

class Stock {
public:
    int id = 0;
    Wt::Dbo::ptr<Book> book;
    Wt::Dbo::ptr<Shop> shop;
    int count = 0;

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, id, "id");
        Wt::Dbo::belongsTo(a, book, "id_book");
        Wt::Dbo::belongsTo(a, shop, "id_shop");
        Wt::Dbo::field(a, count, "count");
    }
};

class Sale {
public:
    int id = 0;
    int price = 0;
    Wt::Dbo::ptr<Stock> stock;
    int count = 0;
    std::string date_sale;

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, id, "id");
        Wt::Dbo::field(a, price, "price");
        Wt::Dbo::belongsTo(a, stock, "id_stock");
        Wt::Dbo::field(a, count, "count");
        Wt::Dbo::field(a, date_sale, "date_sale");
    }
};

int main() {
    try {
        std::string connectionString = "hostaddr=127.0.0.1 "
            "port=5432 "
            "dbname=postgres "
            "user=postgres "
            "password=070053";
        std::unique_ptr<Wt::Dbo::backend::Postgres> conn = std::make_unique<Wt::Dbo::backend::Postgres>(connectionString);

        std::cout << "hello";

        Wt::Dbo::Session session;
        session.setConnection(std::move(conn));

        session.mapClass<Publisher>("Publisher");
        session.mapClass<Book>("Book");
        session.mapClass<Shop>("Shop");
        session.mapClass<Stock>("Stock");
        session.mapClass<Sale>("Sale");

        session.createTables();
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
