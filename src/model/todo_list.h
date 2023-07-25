#ifndef TODO_LIST_H
#define TODO_LIST_H

#include <vector>
#include "todo_item.h"

class TodoList {
public:
    TodoList();

    void addTodoItem(const std::string& title);
    void removeTodoItem(int itemId);
    void markTodoItemCompleted(int itemId);
    std::vector<TodoItem>& getTodoItems();

private:
    std::vector<TodoItem> todoItems_;
};

#endif // TODO_LIST_H
