#include "todo_list.h"
#include <sqlite3.h> // Include the SQLite header file
#include <iostream>

TodoList::TodoList() {
    // Open the SQLite database
    sqlite3* db;
    int rc = sqlite3_open("todo_database.db", &db);

    if (rc) {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        // Create the 'todo_items' table if it doesn't exist
        const char* createTableSQL = "CREATE TABLE IF NOT EXISTS todo_items ("
            "id INTEGER PRIMARY KEY,"
            "title TEXT NOT NULL,"
            "completed INTEGER NOT NULL"
            ");";

        rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, nullptr);

        if (rc != SQLITE_OK) {
            std::cout << "Error creating table: " << sqlite3_errmsg(db) << std::endl;
        }
        else {
            // Read todo items from the 'todo_items' table and update todoItems_
            const char* selectSQL = "SELECT id, title, completed FROM todo_items;";
            sqlite3_stmt* stmt;

            rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr);
            if (rc == SQLITE_OK) {
                while (sqlite3_step(stmt) == SQLITE_ROW) {
                    int id = sqlite3_column_int(stmt, 0);
                    const unsigned char* title = sqlite3_column_text(stmt, 1);
                    int completed = sqlite3_column_int(stmt, 2);

                    todoItems_.emplace_back(id, std::string(reinterpret_cast<const char*>(title)), completed);
                }
                sqlite3_finalize(stmt);
            }
            else {
                std::cout << "Error reading todo items: " << sqlite3_errmsg(db) << std::endl;
            }
        }
    }

    sqlite3_close(db); // Close the database when it's no longer needed
}


void TodoList::addTodoItem(const std::string& title) {
    int newId = todoItems_.size() + 1;
    todoItems_.emplace_back(newId, title, false);

    // Open the SQLite database
    sqlite3* db;
    int rc = sqlite3_open("todo_database.db", &db);

    if (rc) {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        // Insert the new todo item into the 'todo_items' table
        std::string insertSQL = "INSERT INTO todo_items (title, completed) VALUES ('" + title + "', 0);";

        rc = sqlite3_exec(db, insertSQL.c_str(), nullptr, nullptr, nullptr);

        if (rc != SQLITE_OK) {
            std::cout << "Error inserting todo item: " << sqlite3_errmsg(db) << std::endl;
        }
    }

    sqlite3_close(db); // Close the database when it's no longer needed
}

void TodoList::removeTodoItem(int itemId) {
    todoItems_.erase(
        std::remove_if(todoItems_.begin(), todoItems_.end(),
            [itemId](const TodoItem& item) { return item.getId() == itemId; }),
        todoItems_.end());

    // Open the SQLite database
    sqlite3* db;
    int rc = sqlite3_open("todo_database.db", &db);

    if (rc) {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        // Delete the todo item from the 'todo_items' table
        std::string deleteSQL = "DELETE FROM todo_items WHERE id = " + std::to_string(itemId) + ";";

        rc = sqlite3_exec(db, deleteSQL.c_str(), nullptr, nullptr, nullptr);

        if (rc != SQLITE_OK) {
            std::cout << "Error deleting todo item: " << sqlite3_errmsg(db) << std::endl;
        }
    }

    sqlite3_close(db); // Close the database when it's no longer needed
}

void TodoList::markTodoItemCompleted(int itemId) {
    for (auto& item : todoItems_) {
        if (item.getId() == itemId) {
            item.setCompleted(true);
            break;
        }
    }

    // Open the SQLite database
    sqlite3* db;
    int rc = sqlite3_open("todo_database.db", &db);

    if (rc) {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        // Update the completion status of the todo item in the 'todo_items' table
        std::string updateSQL = "UPDATE todo_items SET completed = 1 WHERE id = " + std::to_string(itemId) + ";";

        rc = sqlite3_exec(db, updateSQL.c_str(), nullptr, nullptr, nullptr);

        if (rc != SQLITE_OK) {
            std::cout << "Error updating todo item: " << sqlite3_errmsg(db) << std::endl;
        }
    }

    sqlite3_close(db); // Close the database when it's no longer needed
}

std::vector<TodoItem>& TodoList::getTodoItems() {
    return todoItems_;
}