#include "todo_list.h"

#include <iostream>

namespace todo {

TodoList::TodoList() : db_(nullptr) {
  int rc = sqlite3_open("todo_database.db", &db_);

  if (rc != SQLITE_OK) {
    std::cout << "Can't open database: " << sqlite3_errmsg(db_) << std::endl;
    db_ = nullptr;
  } else {
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

      todo_items_.emplace_back(
          id, std::string(reinterpret_cast<const char *>(title)), completed);
    }
    sqlite3_finalize(stmt);
  } else {
    std::cout << "Error reading todo items: " << sqlite3_errmsg(db_)
              << std::endl;
  }
}

void TodoList::AddTodoItem(const std::string &text) {
  if (!db_) {
    return;
  }

  std::string insertSQL =
      "INSERT INTO todo_items (title, completed) VALUES ('" + text + "', 0);";

  int rc = sqlite3_exec(db_, insertSQL.c_str(), nullptr, nullptr, nullptr);

  if (rc != SQLITE_OK) {
    std::cout << "Error inserting todo item: " << sqlite3_errmsg(db_)
              << std::endl;
  } else {
    int newId = static_cast<int>(sqlite3_last_insert_rowid(db_));
    todo_items_.emplace_back(newId, text, false);
  }
}

void TodoList::RemoveTodoItem(int todo_item_id) {
  if (!db_) {
    return;
  }

  std::string deleteSQL =
      "DELETE FROM todo_items WHERE id = " + std::to_string(todo_item_id) + ";";

  int rc = sqlite3_exec(db_, deleteSQL.c_str(), nullptr, nullptr, nullptr);

  if (rc != SQLITE_OK) {
    std::cout << "Error deleting todo item: " << sqlite3_errmsg(db_)
              << std::endl;
  } else {
    todo_items_.erase(std::remove_if(todo_items_.begin(), todo_items_.end(),
                                     [&todo_item_id](const TodoItem &todoItem) {
                                       return todoItem.GetId() == todo_item_id;
                                     }),
                      todo_items_.end());
  }
}

void TodoList::ToggleTodoItemGetCompleted(int todo_item_id) {
  if (!db_) {
    return;
  }

  auto found_todo_item =
      std::find_if(todo_items_.begin(), todo_items_.end(),
                   [&todo_item_id](const TodoItem &todoItem) {
                     return todoItem.GetId() == todo_item_id;
                   });

  if (found_todo_item != todo_items_.end()) {
    int completed = found_todo_item->GetCompleted() ? 0 : 1;

    std::string updateSQL =
        "UPDATE todo_items SET completed = " + std::to_string(completed) +
        " WHERE id = " + std::to_string(todo_item_id) + ";";

    int rc = sqlite3_exec(db_, updateSQL.c_str(), nullptr, nullptr, nullptr);

    if (rc != SQLITE_OK) {
      std::cout << "Error updating todo item: " << sqlite3_errmsg(db_)
                << std::endl;
    } else {
      found_todo_item->SetCompleted(!found_todo_item->GetCompleted());
    }
  }
}

void TodoList::UpdateTodoItemText(int todo_item_index,
                                  const std::string &new_todo_text) {
  if (!db_) {
    return;
  }

  std::string updateSQL =
      "UPDATE todo_items SET title = '" + new_todo_text +
      "' WHERE id = " + std::to_string(todo_items_[todo_item_index].GetId()) +
      ";";

  int rc = sqlite3_exec(db_, updateSQL.c_str(), nullptr, nullptr, nullptr);

  if (rc != SQLITE_OK) {
    std::cout << "Error updating todo item: " << sqlite3_errmsg(db_)
              << std::endl;
  } else {
    todo_items_[todo_item_index].SetText(new_todo_text);
  }
}

void TodoList::DeleteAllTodoItems() {
  if (!db_) {
    return;
  }

  const char *deleteAllSQL = "DELETE FROM todo_items;";
  int rc = sqlite3_exec(db_, deleteAllSQL, nullptr, nullptr, nullptr);

  if (rc != SQLITE_OK) {
    std::cout << "Error deleting all todo items: " << sqlite3_errmsg(db_)
              << std::endl;
  } else {
    todo_items_.clear();
  }
}

std::vector<TodoItem> &TodoList::GetAllTodoItems() { return todo_items_; }

}  // namespace todo
