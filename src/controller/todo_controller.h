#ifndef TODO_CONTROLLER_H
#define TODO_CONTROLLER_H

#include "model/todo_list.h"
#include "view/todo_view.h"

class TodoController {
 public:
  TodoController();

  void run();

 private:
  TodoList todoList_;
  TodoView todoView_;
};

#endif  // TODO_CONTROLLER_H
