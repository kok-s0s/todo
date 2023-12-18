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
  ftxui::Component UpdateTodoForm();
  ftxui::Component BottomBar();
  void ReloadTodoListComponent();

 private:
  TodoList &todo_list_;
  std::string new_todo_text_;
  std::string selected_todo_item_index_;
  std::string update_todo_text_;
  ftxui::Component todo_list_component_ = ftxui::Container::Vertical({});
};

#endif  // TODO_TUI_H
