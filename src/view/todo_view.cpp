#include "todo_view.h"
#include <iostream>

TodoView::TodoView() {}

void TodoView::showTodoList(const std::vector<TodoItem>& todoItems) {
    std::cout << "Todo List:" << std::endl;
    for (const auto& item : todoItems) {
        std::cout << "[" << item.getId() << "] ";
        if (item.isCompleted()) {
            std::cout << "[X] ";
        }
        else {
            std::cout << "[ ] ";
        }
        std::cout << item.getTitle() << std::endl;
    }
}

int TodoView::askForAction() {
    int choice;
    std::cout << "\nChoose an action:" << std::endl;
    std::cout << "1. Add new todo" << std::endl;
    std::cout << "2. Remove todo" << std::endl;
    std::cout << "3. Mark todo as completed" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Your choice: ";
    std::cin >> choice;
    return choice;
}

std::string TodoView::askForNewTodoTitle() {
    std::string title;
    std::cout << "\nEnter the title of the new todo: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    return title;
}

int TodoView::askForTodoIdToRemove() {
    int id;
    std::cout << "\nEnter the ID of the todo to remove: ";
    std::cin >> id;
    return id;
}

int TodoView::askForTodoIdToMarkAsCompleted() {
    int id;
    std::cout << "\nEnter the ID of the todo to mark as completed: ";
    std::cin >> id;
    return id;
}
