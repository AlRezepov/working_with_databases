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

        // ��������� ������� ��������� �������
        Wt::Dbo::Transaction transaction(session);

        auto publisher = session.add(std::make_unique<Publisher>());
        publisher.modify()->name = "Target Publisher";

        auto book = session.add(std::make_unique<Book>());
        book.modify()->title = "Sample Book";
        book.modify()->publisher = publisher;

        auto shop = session.add(std::make_unique<Shop>());
        shop.modify()->name = "Bookstore A";

        auto stock = session.add(std::make_unique<Stock>());
        stock.modify()->book = book;
        stock.modify()->shop = shop;
        stock.modify()->count = 10;

        transaction.commit();

        // ������ ��� ��������
        std::string targetPublisherName;
        std::cout << "������� ��� ��������: ";
        std::cin >> targetPublisherName;

        // ��������� ������
        Wt::Dbo::Transaction queryTransaction(session);
        auto shops = session.query<Shop>("WHERE id IN (SELECT id_shop FROM Stock WHERE id_book IN (SELECT id FROM Book WHERE id_publisher IN (SELECT id FROM Publisher WHERE name = ?)))").bind(targetPublisherName);

        std::cout << "��������, ��������� ����� �������� " << targetPublisherName << ":" << std::endl;

        for (const auto& shop : shops.resultList()) {
            std::cout << shop.name << std::endl;
        }

        queryTransaction.commit();
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
