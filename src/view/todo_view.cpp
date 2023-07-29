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
  return getContent("\nEnter the content of the new todo: ");
}

int TodoView::askForTodoItemIndexToRemove() {
  return getValidIntegerInput("\nEnter the ID of the todo to remove: ");
}

int TodoView::askForTodoIndexToMarkAsCompleted() {
  return getValidIntegerInput(
      "\nEnter the ID of the todo to mark as completed: ");
}

int TodoView::askForTodoIndexToMarkAsUnCompleted() {
  return getValidIntegerInput(
      "\nEnter the ID of the todo to mark as uncompleted: ");
}

int TodoView::askForTodoIndexToUpdateContent() {
  return getValidIntegerInput("\nEnter the ID of the todo to update content: ");
}

std::string TodoView::askForNewContentToUpdateContent() {
  return getContent("\nEnter the content to update: ");
}

int TodoView::getValidIntegerInput(const std::string &prompt) {
  int value;
  while (true) {
    std::cout << prompt;
    if (std::cin >> value) {
      // Check if there are any remaining characters in the input buffer
      if (std::cin.peek() == '\n') {
        break;
      }
    }
    // Clear the error flag and flush the input buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Invalid input. Please enter a valid integer.\n";
  }
  return value;
}

std::string TodoView::getContent(const std::string &prompt) {
  std::string content;
  std::cout << prompt;
  std::cin.ignore();
  std::getline(std::cin, content);
  return content;
}