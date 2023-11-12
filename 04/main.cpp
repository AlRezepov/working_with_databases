#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <vector>

class ClientManager {
public:
    ClientManager(pqxx::connection& connection) : conn(connection) {}

    // Метод для создания таблицы
    void createTable() {
        pqxx::work txn{ conn };
        std::string createTableQuery = "CREATE TABLE IF NOT EXISTS public.clients (id SERIAL PRIMARY KEY, first_name VARCHAR(255), last_name VARCHAR(255), email VARCHAR(255), phones VARCHAR[]);";
        txn.exec(createTableQuery);
        txn.commit();
    }

    // Метод для добавления нового клиента
    void addClient(const std::string& firstName, const std::string& lastName, const std::string& email) {
        pqxx::work txn{ conn };
        std::string addClientQuery = "INSERT INTO clients (first_name, last_name, email) VALUES ('" +
            txn.esc(firstName) + "', '" +
            txn.esc(lastName) + "', '" +
            txn.esc(email) + "');";
        txn.exec(addClientQuery);
        txn.commit();
    }

    // Метод для добавления нового клиента
    void addPhoneToClient(int clientId, const std::string& phone) {
        pqxx::work txn{ conn };
        std::string addPhoneQuery = "UPDATE clients SET phones = array_append(phones, to_char(" + txn.esc(std::to_string(clientId)) + ", '999999')) WHERE id = " + txn.esc(std::to_string(clientId)) + ";";
        txn.exec(addPhoneQuery);
        txn.commit();
    }

    // Метод для изменения данных клиента
    void updateClient(int clientId, const std::string& newFirstName, const std::string& newLastName, const std::string& newEmail) {
        pqxx::work txn{ conn };
        std::string updateClientQuery = "UPDATE clients SET first_name = '" + txn.esc(newFirstName) + "', last_name = '" + txn.esc(newLastName) + "', email = '" + txn.esc(newEmail) + "' WHERE id = " + txn.esc(std::to_string(clientId)) + ";";

        txn.exec(updateClientQuery);
        txn.commit();
    }

    // Метод для изменения данных клиента
    void deletePhoneFromClient(int clientId, const std::string& phone) {
        pqxx::work txn{ conn };
        std::string deletePhoneQuery = "UPDATE clients SET phones = array_remove(phones, " + txn.esc(phone) + ") WHERE id = " + txn.esc(std::to_string(clientId)) + ";";
        txn.exec(deletePhoneQuery);
        txn.commit();
    }

    // Метод для удаления клиента
    void deleteClient(int clientId) {
        pqxx::work txn{ conn };
        std::string deleteClientQuery = "DELETE FROM clients WHERE id = " + txn.esc(std::to_string(clientId)) + ";";
        txn.exec(deleteClientQuery);
        txn.commit();
    }

    // Метод для поиска клиента по данным
    void findClients(const std::string& searchParam) {
        pqxx::work txn(conn);
        std::string findClientQuery = "SELECT * FROM clients WHERE first_name = " + conn.quote(searchParam) + " OR last_name = " + conn.quote(searchParam) + " OR email = " + conn.quote(searchParam) + " OR " + conn.quote(searchParam) + " = ANY(phones);";
        pqxx::result result = txn.exec(findClientQuery);
        txn.commit();

        for (const auto& row : result) {
            std::cout << "Client ID: " << row["id"].as<int>() << std::endl;
            std::cout << "First Name: " << row["first_name"].c_str() << std::endl;
            std::cout << "Last Name: " << row["last_name"].c_str() << std::endl;
            std::cout << "Email: " << row["email"].c_str() << std::endl;
        }
    }

private:
    pqxx::connection& conn;
};

int main() {
    
    setlocale(LC_ALL, "ru_RU.UTF-8");

    try {
        pqxx::connection conn("hostaddr=127.0.0.1 "
            "port=5432 "
            "dbname=postgres "
            "user=postgres "
            "password=070053");

        pqxx::work txn{ conn };
        std::string createSchemaQuery = "CREATE SCHEMA IF NOT EXISTS public;";
        txn.exec(createSchemaQuery);
        txn.commit();

        ClientManager clientManager(conn);

        clientManager.createTable();
        clientManager.addClient("John", "Doe", "johndoe@example.com");
        clientManager.addPhoneToClient(1, "123456789");
        clientManager.updateClient(1, "NewJohn", "NewDoe", "new.email@example.com");
        clientManager.findClients("new.email@example.com");

    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
