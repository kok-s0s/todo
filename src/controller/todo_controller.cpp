#include "todo_controller.h"
#include <sqlite3.h>
#include <iostream>

TodoController::TodoController() {
    // Initialize and connect to the SQLite database
    sqlite3* db;
    int rc = sqlite3_open("todo_database.db", &db);

    if (rc) {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "Opened database successfully" << std::endl;
    }

    sqlite3_close(db); // Close the database when it's no longer needed
}

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
            int todoId = todoView_.askForTodoIdToRemove();
            todoList_.removeTodoItem(todoId);
            break;
        }
        case 3: {
            int todoId = todoView_.askForTodoIdToMarkAsCompleted();
            todoList_.markTodoItemCompleted(todoId);
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
