#include "todo_controller.h"

#include <sqlite3.h>

#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#define OS_WINDOWS
#include <windows.h>
#elif defined(__unix__) || defined(__unix)
#define OS_UNIX
#include <cstdlib>
#elif defined(__APPLE__) || defined(__MACH__)
#define OS_MACOS
#include <cstdlib>
#else
#error "Unsupported operating system"
#endif

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
      case 6: {
        todoList_.deleteAllTodos();
        std::cout << "\nDeleted." << std::endl;
        break;
      }
      case 7:
        running = false;
        break;
      default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        break;
    }

    clearTerminal();
  }
}

void TodoController::clearTerminal() {
#ifdef OS_WINDOWS
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(hStdOut, &csbi);
  COORD coord = {0, 0};
  DWORD dwCharsWritten;
  DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
  FillConsoleOutputCharacter(hStdOut, ' ', dwConSize, coord, &dwCharsWritten);
  GetConsoleScreenBufferInfo(hStdOut, &csbi);
  FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, dwConSize, coord,
                             &dwCharsWritten);
  SetConsoleCursorPosition(hStdOut, coord);
#elif defined(OS_UNIX) || defined(OS_MACOS)
  std::system("clear");
#endif
}