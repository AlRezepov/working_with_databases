#include <iostream>
#include <wt/dbo/dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

class Publisher {
public:
    std::string name = "";

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, name, "name");
    }
};

class Book {
public:
    std::string title = "";
    Wt::Dbo::ptr<Publisher> publisher;

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, title, "title");
        Wt::Dbo::belongsTo(a, publisher, "id_publisher");
    }
};

class Shop {
public:
    std::string name = "";

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, name, "name");
    }
};

class Stock {
public:
    Wt::Dbo::ptr<Book> book;
    Wt::Dbo::ptr<Shop> shop;
    int count = 0;

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::belongsTo(a, book, "id_book");
        Wt::Dbo::belongsTo(a, shop, "id_shop");
        Wt::Dbo::field(a, count, "count");
    }
};

class Sale {
public:
    int price = 0;
    Wt::Dbo::ptr<Stock> stock;
    int count = 0;
    std::string date_sale;

    template<class Action>
    void persist(Action& a) {
        Wt::Dbo::field(a, price, "price");
        Wt::Dbo::belongsTo(a, stock, "id_stock");
        Wt::Dbo::field(a, count, "count");
        Wt::Dbo::field(a, date_sale, "date_sale");
    }
};

int main() {
    
    setlocale(LC_ALL, "ru_RU.UTF-8");


    try {
        std::string connectionString = "hostaddr=127.0.0.1 "
            "port=5432 "
            "dbname=postgres "
            "user=postgres "
            "password=070053";
        std::unique_ptr<Wt::Dbo::backend::Postgres> conn = std::make_unique<Wt::Dbo::backend::Postgres>(connectionString);

        Wt::Dbo::Session session;
        session.setConnection(std::move(conn));

        session.mapClass<Publisher>("Publisher");
        session.mapClass<Book>("Book");
        session.mapClass<Shop>("Shop");
        session.mapClass<Stock>("Stock");
        session.mapClass<Sale>("Sale");

        session.createTables();

        // Заполняем таблицы тестовыми данными
        Wt::Dbo::Transaction transaction(session);

        auto publisher = session.add(std::make_unique<Publisher>());
        publisher.modify()->name = "Publisher_01";

        auto book = session.add(std::make_unique<Book>());
        book.modify()->title = "Book_01";
        book.modify()->publisher = publisher;

        auto shop = session.add(std::make_unique<Shop>());
        shop.modify()->name = "Bookstore_01";

        auto stock = session.add(std::make_unique<Stock>());
        stock.modify()->book = book;
        stock.modify()->shop = shop;
        stock.modify()->count = 10;

        transaction.commit();

        // Вводим имя издателя
        std::string targetPublisherName;
        std::cout << "Enter the name of the publisher: ";
        std::cin >> targetPublisherName;

        // Выполняем запрос
        Wt::Dbo::Transaction queryTransaction(session);
        auto shops = session.find<Shop>().where("id IN (SELECT stock.id_shop FROM Stock stock INNER JOIN Book book ON stock.id_book = book.id INNER JOIN Publisher publisher ON book.id_publisher = publisher.id WHERE publisher.name = ?)").bind(targetPublisherName);

        std::cout << "Stores that sell the publisher's books " << targetPublisherName << ":" << std::endl;

        for (const auto& shop : shops.resultList()) {
            std::cout << shop.modify()->name << std::endl;
        }

        queryTransaction.commit();

    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
