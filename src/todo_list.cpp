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
      LoadTodoItemsFromDatabase();
    }
  }
}

TodoList::~TodoList() {
  if (db_) {
    sqlite3_close(db_);
  }
}

void TodoList::LoadTodoItemsFromDatabase() {
  if (!db_) {
    return;
  }

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

void TodoList::AddTodoItem(const std::string &title) {
  if (!db_) {
    return;
  }

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

void TodoList::RemoveTodoItem(int todoItemId) {
  if (!db_) {
    return;
  }

  std::string deleteSQL =
      "DELETE FROM todo_items WHERE id = " + std::to_string(todoItemId) + ";";

  int rc = sqlite3_exec(db_, deleteSQL.c_str(), nullptr, nullptr, nullptr);

  if (rc != SQLITE_OK) {
    std::cout << "Error deleting todo item: " << sqlite3_errmsg(db_)
              << std::endl;
  } else {
    todoItems_.erase(std::remove_if(todoItems_.begin(), todoItems_.end(),
                                    [&todoItemId](const TodoItem &todoItem) {
                                      return todoItem.GetId() == todoItemId;
                                    }),
                     todoItems_.end());
  }
}

void TodoList::ToggleTodoItemIsCompleted(int id) {
  auto found_todo_item = std::find_if(
      todoItems_.begin(), todoItems_.end(),
      [&id](const TodoItem &todoItem) { return todoItem.GetId() == id; });

  if (found_todo_item != todoItems_.end())
    found_todo_item->SetCompleted(!found_todo_item->IsCompleted());
}

void TodoList::MarkTodoItemCompleted(int todoItemId) {
  if (!db_) {
    return;
  }

  // Update the completion status of the todo item in the 'todo_items' table
  std::string updateSQL = "UPDATE todo_items SET completed = 1 WHERE id = " +
                          std::to_string(todoItemId) + ";";

  int rc = sqlite3_exec(db_, updateSQL.c_str(), nullptr, nullptr, nullptr);

  if (rc != SQLITE_OK) {
    std::cout << "Error updating todo item: " << sqlite3_errmsg(db_)
              << std::endl;
  } else {
    auto found_todo_item =
        std::find_if(todoItems_.begin(), todoItems_.end(),
                     [&todoItemId](const TodoItem &todoItem) {
                       return todoItem.GetId() == todoItemId;
                     });

    if (found_todo_item != todoItems_.end())
      found_todo_item->SetCompleted(true);
  }
}

void TodoList::MarkTodoItemUnCompleted(int todoItemId) {
  if (!db_) {
    return;
  }

  // Update the completion status of the todo item in the 'todo_items' table
  std::string updateSQL = "UPDATE todo_items SET completed = 0 WHERE id = " +
                          std::to_string(todoItemId) + ";";

  int rc = sqlite3_exec(db_, updateSQL.c_str(), nullptr, nullptr, nullptr);

  if (rc != SQLITE_OK) {
    std::cout << "Error updating todo item: " << sqlite3_errmsg(db_)
              << std::endl;
  } else {
    auto found_todo_item =
        std::find_if(todoItems_.begin(), todoItems_.end(),
                     [&todoItemId](const TodoItem &todoItem) {
                       return todoItem.GetId() == todoItemId;
                     });

    if (found_todo_item != todoItems_.end())
      found_todo_item->SetCompleted(false);
  }
}

void TodoList::UpdateTodoItemContent(int todoItemId,
                                     const std::string &newContent) {
  if (!db_) {
    return;
  }

  // Update the title of the todo item in the 'todo_items' table
  std::string updateSQL = "UPDATE todo_items SET title = '" + newContent +
                          "' WHERE id = " + std::to_string(todoItemId) + ";";

  int rc = sqlite3_exec(db_, updateSQL.c_str(), nullptr, nullptr, nullptr);

  if (rc != SQLITE_OK) {
    std::cout << "Error updating todo item: " << sqlite3_errmsg(db_)
              << std::endl;
  } else {
    // todoItems_[todoItemIndex].SetContent(newContent);
  }
}

void TodoList::DeleteAllTodoItems() {
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

std::vector<TodoItem> &TodoList::GetAllTodoItems() { return todoItems_; }
