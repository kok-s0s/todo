#include "todo_controller.h"

namespace todo {

Controller::Controller(TodoList& todo_list) : todo_list_(todo_list) {}

void Controller::AddTodoItem(const std::string& text) {
  todo_list_.AddTodoItem(text);
}

void Controller::RemoveTodoItem(int todo_item_id) {
  todo_list_.RemoveTodoItem(todo_item_id);
}

void Controller::UndoRemoveTodoItem() { todo_list_.UndoRemoveTodoItem(); }

void Controller::ToggleTodoItemGetCompleted(int todo_item_id) {
  todo_list_.ToggleTodoItemGetCompleted(todo_item_id);
}

void Controller::UpdateTodoItemText(int todo_item_index,
                                    const std::string& new_todo_text) {
  todo_list_.UpdateTodoItemText(todo_item_index, new_todo_text);
}

void Controller::DeleteAllTodoItems() { todo_list_.DeleteAllTodoItems(); }

std::vector<TodoItem>& Controller::GetAllTodoItems() {
  return todo_list_.GetAllTodoItems();
}

}  // namespace todo
