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
        clearTerminal();
        break;
      }
      case 2: {
        int todoItemIndex = todoView_.askForTodoItemIndexToRemove();
        todoList_.removeTodoItem(todoItemIndex);
        clearTerminal();
        break;
      }
      case 3: {
        int todoItemIndex = todoView_.askForTodoIndexToMarkAsCompleted();
        todoList_.markTodoItemCompleted(todoItemIndex);
        clearTerminal();
        break;
      }
      case 4: {
        int todoItemIndex = todoView_.askForTodoIndexToMarkAsUnCompleted();
        todoList_.markTodoItemUnCompleted(todoItemIndex);
        clearTerminal();
        break;
      }
      case 5: {
        int todoItemIndex = todoView_.askForTodoIndexToUpdateContent();
        std::string content = todoView_.askForNewContentToUpdateContent();
        todoList_.updateTodoItemContent(todoItemIndex, content);
        todoList_.markTodoItemUnCompleted(todoItemIndex);
        clearTerminal();
        break;
      }
      case 6: {
        todoList_.deleteAllTodos();
        std::cout << "\nDeleted." << std::endl;
        clearTerminal();
        break;
      }
      case 7: {
        clearTerminal();
        std::cout << "\n $$$$$$\\                            $$\\     $$\\     "
                     "              $$\\ ";
        std::cout << "\n$$  __$$\\                           \\$$\\   $$  |    "
                     "              $$ |";
        std::cout << "\n$$ /  \\__| $$$$$$\\   $$$$$$\\         \\$$\\ $$  "
                     "/$$$$$$\\  $$\\   $$\\ $$ |";
        std::cout << "\n\\$$$$$$\\  $$  __$$\\ $$  __$$\\         \\$$$$  /$$  "
                     "__$$\\ $$ |  $$ |$$ |";
        std::cout << "\n \\____$$\\ $$$$$$$$ |$$$$$$$$ |         \\$$  / $$ /  "
                     "$$ |$$ |  $$ |\\__|";
        std::cout << "\n$$\\   $$ |$$   ____|$$   ____|          $$ |  $$ |  "
                     "$$ |$$ |  $$ |    ";
        std::cout << "\n\\$$$$$$  |\\$$$$$$$\\ \\$$$$$$$\\           $$ |  "
                     "\\$$$$$$  |\\$$$$$$  |$$\\ ";
        std::cout << "\n \\______/  \\_______| \\_______|          \\__|   "
                     "\\______/  \\______/ \\__|";
        std::cout << "\n                                                       "
                     "               ";
        std::cout << "\n                                                       "
                     "               ";
        std::cout << "\n                                                       "
                     "               "
                  << std::endl;
        running = false;
        break;
      }
      default:
        clearTerminal();
        std::cout << "Invalid choice. Please try again." << std::endl;
        break;
    }
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