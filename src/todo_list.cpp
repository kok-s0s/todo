#include "todo_list.h"

#include <iostream>

TodoList::TodoList() : db_(nullptr) {
  int rc = sqlite3_open("todo_database.db", &db_);

  if (rc != SQLITE_OK) {
    std::cout << "Can't open database: " << sqlite3_errmsg(db_) << std::endl;
    db_ = nullptr;  // Set db_ to nullptr on failure
  } else {
    // Create the 'todo_items' table if it doesn't exist
    const char *createTableSQL =
        "CREATE TABLE IF NOT EXISTS todo_items ("
        "id INTEGER PRIMARY KEY,"
        "title TEXT NOT NULL,"
        "completed INTEGER NOT NULL"
        ");";

    rc = sqlite3_exec(db_, createTableSQL, nullptr, nullptr, nullptr);

    if (rc != SQLITE_OK) {
      std::cout << "Error creating table: " << sqlite3_errmsg(db_) << std::endl;
    } else {
      loadTodoItemsFromDatabase();
    }
  }
}

TodoList::~TodoList() {
  if (db_) {
    sqlite3_close(db_);
  }
}

void TodoList::loadTodoItemsFromDatabase() {
  if (!db_) {
    return;
  }

  // Read todo items from the 'todo_items' table and update todoItems_
  const char *selectSQL = "SELECT id, title, completed FROM todo_items;";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db_, selectSQL, -1, &stmt, nullptr);
  if (rc == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      int id = sqlite3_column_int(stmt, 0);
      const unsigned char *title = sqlite3_column_text(stmt, 1);
      int completed = sqlite3_column_int(stmt, 2);

      todoItems_.emplace_back(
          id, std::string(reinterpret_cast<const char *>(title)), completed);
    }
    sqlite3_finalize(stmt);
  } else {
    std::cout << "Error reading todo items: " << sqlite3_errmsg(db_)
              << std::endl;
  }
}

void TodoList::addTodoItem(const std::string &title) {
  if (!db_) {
    return;
  }

  // Insert the new todo item into the 'todo_items' table with AUTOINCREMENT id
  std::string insertSQL =
      "INSERT INTO todo_items (title, completed) VALUES ('" + title + "', 0);";

  int rc = sqlite3_exec(db_, insertSQL.c_str(), nullptr, nullptr, nullptr);

  if (rc != SQLITE_OK) {
    std::cout << "Error inserting todo item: " << sqlite3_errmsg(db_)
              << std::endl;
  } else {
    // Read the automatically generated id for the newly inserted todo item
    int newId = static_cast<int>(sqlite3_last_insert_rowid(db_));
    todoItems_.emplace_back(newId, title, false);
  }
}

void TodoList::removeTodoItem(int todoItemIndex) {
  if (!db_) {
    return;
  }

  if (0 < todoItemIndex && todoItemIndex <= todoItems_.size()) {
    // Delete the todo item from the 'todo_items' table
    std::string deleteSQL =
        "DELETE FROM todo_items WHERE id = " +
        std::to_string(
            todoItems_[static_cast<std::vector<
                           TodoItem, std::allocator<TodoItem>>::size_type>(
                           todoItemIndex) -
                       1]
                .getId()) +
        ";";

    int rc = sqlite3_exec(db_, deleteSQL.c_str(), nullptr, nullptr, nullptr);

    if (rc != SQLITE_OK) {
      std::cout << "Error deleting todo item: " << sqlite3_errmsg(db_)
                << std::endl;
    } else {
      todoItems_.erase(todoItems_.begin() + todoItemIndex - 1);
    }
  }
}

void TodoList::markTodoItemCompleted(int todoItemIndex) {
  if (!db_) {
    return;
  }

  if (0 < todoItemIndex && todoItemIndex <= todoItems_.size()) {
    // Update the completion status of the todo item in the 'todo_items' table
    std::string updateSQL =
        "UPDATE todo_items SET completed = 1 WHERE id = " +
        std::to_string(
            todoItems_[static_cast<std::vector<
                           TodoItem, std::allocator<TodoItem>>::size_type>(
                           todoItemIndex) -
                       1]
                .getId()) +
        ";";

    int rc = sqlite3_exec(db_, updateSQL.c_str(), nullptr, nullptr, nullptr);

    if (rc != SQLITE_OK) {
      std::cout << "Error updating todo item: " << sqlite3_errmsg(db_)
                << std::endl;
    } else {
      todoItems_[static_cast<std::vector<TodoItem, std::allocator<TodoItem>>::
                                 size_type>(todoItemIndex) -
                 1]
          .setCompleted(true);
    }
  }
}

void TodoList::markTodoItemUnCompleted(int todoItemIndex) {
  if (!db_) {
    return;
  }

  if (0 < todoItemIndex && todoItemIndex <= todoItems_.size()) {
    // Update the completion status of the todo item in the 'todo_items' table
    std::string updateSQL =
        "UPDATE todo_items SET completed = 0 WHERE id = " +
        std::to_string(
            todoItems_[static_cast<std::vector<
                           TodoItem, std::allocator<TodoItem>>::size_type>(
                           todoItemIndex) -
                       1]
                .getId()) +
        ";";

    int rc = sqlite3_exec(db_, updateSQL.c_str(), nullptr, nullptr, nullptr);

    if (rc != SQLITE_OK) {
      std::cout << "Error updating todo item: " << sqlite3_errmsg(db_)
                << std::endl;
    } else {
      todoItems_[static_cast<std::vector<TodoItem, std::allocator<TodoItem>>::
                                 size_type>(todoItemIndex) -
                 1]
          .setCompleted(false);
    }
  }
}

void TodoList::updateTodoItemContent(int todoItemIndex,
                                     const std::string &newContent) {
  if (!db_) {
    return;
  }

  if (0 < todoItemIndex && todoItemIndex <= todoItems_.size()) {
    int itemId =
        todoItems_[static_cast<std::vector<TodoItem, std::allocator<TodoItem>>::
                                   size_type>(todoItemIndex) -
                   1]
            .getId();

    // Update the title of the todo item in the 'todo_items' table
    std::string updateSQL = "UPDATE todo_items SET title = '" + newContent +
                            "' WHERE id = " + std::to_string(itemId) + ";";

    int rc = sqlite3_exec(db_, updateSQL.c_str(), nullptr, nullptr, nullptr);

    if (rc != SQLITE_OK) {
      std::cout << "Error updating todo item: " << sqlite3_errmsg(db_)
                << std::endl;
    } else {
      todoItems_[static_cast<std::vector<TodoItem, std::allocator<TodoItem>>::
                                 size_type>(todoItemIndex) -
                 1]
          .setContent(newContent);
    }
  }
}

void TodoList::deleteAllTodos() {
  if (!db_) {
    return;
  }

  // Delete all todo items from the 'todo_items' table
  const char *deleteAllSQL = "DELETE FROM todo_items;";
  int rc = sqlite3_exec(db_, deleteAllSQL, nullptr, nullptr, nullptr);

  if (rc != SQLITE_OK) {
    std::cout << "Error deleting all todo items: " << sqlite3_errmsg(db_)
              << std::endl;
  } else {
    todoItems_.clear();
  }
}

std::vector<TodoItem> &TodoList::getTodoItems() { return todoItems_; }
