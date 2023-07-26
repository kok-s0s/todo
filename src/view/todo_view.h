#ifndef TODO_VIEW_H
#define TODO_VIEW_H

#include <vector>

#include "model/todo_item.h"

class TodoView {
 public:
  TodoView();

  void showTodoList(const std::vector<TodoItem> &todoItems);
  int askForAction();
  std::string askForNewTodoTitle();
  int askForTodoItemIndexToRemove();
  int askForTodoIndexToMarkAsCompleted();
};

#endif  // TODO_VIEW_H
