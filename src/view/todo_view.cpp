#include "todo_view.h"

#include <iostream>

TodoView::TodoView() {}

void TodoView::showTodoList(const std::vector<TodoItem> &todoItems) {
  std::cout << "=-= Todo List =-=" << std::endl;
  for (size_t index = 0; const auto &item : todoItems) {
    std::cout << "[" << index + 1 << "] ";
    if (item.isCompleted()) {
      std::cout << "[X] ";
    } else {
      std::cout << "[ ] ";
    }
    std::cout << item.getContent() << std::endl;
    index++;
  }
}

int TodoView::askForAction() {
  std::string choice;
  std::cout << "\nChoose an action:" << std::endl;
  std::cout << "1. Add new todo" << std::endl;
  std::cout << "2. Remove todo" << std::endl;
  std::cout << "3. Mark todo as completed" << std::endl;
  std::cout << "4. Mark todo as uncompleted" << std::endl;
  std::cout << "5. Update todo's content" << std::endl;
  std::cout << "6. Delete all todos" << std::endl;
  std::cout << "7. Exit" << std::endl;
  std::cout << "Your choice: ";
  std::cin >> choice;
  int iChoice = std::atoi(choice.c_str());
  if (iChoice >= 1 && iChoice <= 7) {
    return iChoice;
  } else {
    return 8;
  }
}

std::string TodoView::askForNewTodoContent() {
  std::string content;
  std::cout << "\nEnter the content of the new todo: ";
  std::cin.ignore();
  std::getline(std::cin, content);
  return content;
}

int TodoView::askForTodoItemIndexToRemove() {
  int id;
  std::cout << "\nEnter the ID of the todo to remove: ";
  std::cin >> id;
  return id;
}

int TodoView::askForTodoIndexToMarkAsCompleted() {
  int id;
  std::cout << "\nEnter the ID of the todo to mark as completed: ";
  std::cin >> id;
  return id;
}

int TodoView::askForTodoIndexToMarkAsUnCompleted() {
  int id;
  std::cout << "\nEnter the ID of the todo to mark as uncompleted: ";
  std::cin >> id;
  return id;
}

int TodoView::askForTodoIndexToUpdateContent() {
  int id;
  std::cout << "\nEnter the ID of the todo to update content: ";
  std::cin >> id;
  return id;
}
