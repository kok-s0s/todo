#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <sqlite3.h>

#include <vector>

#include "todo_item.h"

class TodoList {
 public:
  TodoList();
  ~TodoList();

  void loadTodoItemsFromDatabase();
  void addTodoItem(const std::string &title);
  void removeTodoItem(int itemIndex);
  void markTodoItemCompleted(int itemIndex);
  std::vector<TodoItem> &getTodoItems();

 private:
  std::vector<TodoItem> todoItems_;
  sqlite3 *db_;
};

#endif  // TODO_LIST_H
