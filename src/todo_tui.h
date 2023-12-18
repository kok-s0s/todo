#ifndef TODO_TUI_H
#define TODO_TUI_H

#include "ftxui/component/component.hpp"
#include "todo_item.h"
#include "todo_list.h"

class TodoTui {
 public:
  explicit TodoTui(TodoList &todo_list);
  ~TodoTui();

  void StartLoop();

 private:
  ftxui::Component NewTodoForm();
  ftxui::Component TodoItemComponent(TodoItem todo_item, int todo_item_index);
  void ReloadTodoListComponent();

 private:
  TodoList &todo_list_;
  std::string new_todo_text_;
  ftxui::Component todo_list_component_ = ftxui::Container::Vertical({});
};

#endif  // TODO_TUI_H
