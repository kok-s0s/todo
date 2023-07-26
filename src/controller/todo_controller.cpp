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
        std::string content = todoView_.askForNewTodoContent();
        todoList_.addTodoItem(content);
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
      case 4: {
        int todoItemIndex = todoView_.askForTodoIndexToMarkAsUnCompleted();
        todoList_.markTodoItemUnCompleted(todoItemIndex);
        break;
      }
      case 5: {
        int todoItemIndex = todoView_.askForTodoIndexToUpdateContent();
        std::string content;
        std::cout << "\nEnter new content: ";
        std::cin >> content;
        todoList_.updateTodoItemContent(todoItemIndex, content);
        break;
      }
      case 6:
        running = false;
        break;
      default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        break;
    }
  }
}
