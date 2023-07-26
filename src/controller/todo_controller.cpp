#include "todo_controller.h"

#include <sqlite3.h>

#include <iostream>

TodoController::TodoController() {}

void TodoController::run() {
  bool running = true;

  while (running) {
    todoView_.showTodoList(todoList_.getTodoItems());

    int action = todoView_.askForAction();

    switch (action) {
      case 1: {
        std::string title = todoView_.askForNewTodoTitle();
        todoList_.addTodoItem(title);
        break;
      }
      case 2: {
        int todoItemIndex = todoView_.askForTodoItemIndexToRemove();
        todoList_.removeTodoItem(todoItemIndex);
        break;
      }
      case 3: {
        int todoItemIndex = todoView_.askForTodoIndexToMarkAsCompleted();
        todoList_.markTodoItemCompleted(todoItemIndex);
        break;
      }
      case 4:
        running = false;
        break;
      default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        break;
    }
  }
}
