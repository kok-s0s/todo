#ifndef TODO_CONTROLLER_H
#define TODO_CONTROLLER_H

#include "todo_list.h"

namespace todo {

class Controller {
 public:
  Controller(TodoList& todo_list);

  void AddTodoItem(const std::string& text);
  void RemoveTodoItem(int todo_item_id);
  void ToggleTodoItemGetCompleted(int todo_item_id);
  void UpdateTodoItemText(int todo_item_index,
                          const std::string& new_todo_text);
  void DeleteAllTodoItems();
  std::vector<TodoItem>& GetAllTodoItems();

 private:
  TodoList& todo_list_;
};

}  // namespace todo

#endif  // TODO_CONTROLLER_H
