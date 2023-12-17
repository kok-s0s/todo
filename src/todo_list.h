#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <sqlite3.h>

#include <vector>

#include "todo_item.h"

class TodoList {
 public:
  TodoList();
  ~TodoList();

  void LoadTodoItemsFromDatabase();
  void AddTodoItem(const std::string &title);
  void RemoveTodoItem(int todoItemId);
  void ToggleTodoItemIsCompleted(int todoItemId);
  void MarkTodoItemCompleted(int todoItemId);
  void MarkTodoItemUnCompleted(int todoItemId);
  void UpdateTodoItemContent(int todoItemId, const std::string &newContent);
  void DeleteAllTodoItems();
  std::vector<TodoItem> &GetAllTodoItems();

 private:
  std::vector<TodoItem> todoItems_;
  sqlite3 *db_;
};

#endif  // TODO_LIST_H
