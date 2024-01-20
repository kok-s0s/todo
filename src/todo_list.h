#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <sqlite3.h>

#include <vector>

#include "todo_item.h"

namespace todo {

class TodoList {
 public:
  TodoList();
  ~TodoList();

  void LoadTodoItemsFromDatabase();
  void AddTodoItem(const std::string &text);
  void RemoveTodoItem(int todo_item_id);
  void UndoRemoveTodoItem();
  void ToggleTodoItemGetCompleted(int todo_item_id);
  void UpdateTodoItemText(int todo_item_index,
                          const std::string &new_todo_text);
  void DeleteAllTodoItems();
  std::vector<TodoItem> &GetAllTodoItems();

 private:
  std::vector<TodoItem> todo_items_;
  std::vector<TodoItem> removed_todo_items_;
  sqlite3 *db_;
};
}  // namespace todo

#endif  // TODO_LIST_H
