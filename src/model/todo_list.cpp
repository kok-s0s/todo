#include "todo_list.h"

TodoList::TodoList() {}

void TodoList::addTodoItem(const std::string& title) {
    int newId = todoItems_.size() + 1;
    todoItems_.emplace_back(newId, title, false);
}

void TodoList::removeTodoItem(int itemId) {
    todoItems_.erase(
        std::remove_if(todoItems_.begin(), todoItems_.end(),
            [itemId](const TodoItem& item) { return item.getId() == itemId; }),
        todoItems_.end());
}

void TodoList::markTodoItemCompleted(int itemId) {
    for (auto& item : todoItems_) {
        if (item.getId() == itemId) {
            item.setCompleted(true);
            break;
        }
    }
}

std::vector<TodoItem>& TodoList::getTodoItems() {
    return todoItems_;
}
