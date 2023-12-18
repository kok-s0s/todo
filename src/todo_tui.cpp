#include "todo_tui.h"

#include <ftxui/component/screen_interactive.hpp>
#include <utility>
#include <vector>

TodoTui::TodoTui(TodoList& todo_list) : todo_list_(todo_list) {
  ReloadTodoListComponent();
}

TodoTui::~TodoTui() {}

void TodoTui::StartLoop() {
  auto screen = ftxui::ScreenInteractive::FitComponent();

  auto layout =
      ftxui::Container::Vertical(
          {NewTodoForm(),
           todo_list_component_ | ftxui::Renderer([&](ftxui::Element element) {
             return todo_list_.GetAllTodoItems().empty() ? ftxui::text("")
                                                         : std::move(element);
           }),
           UpdateTodoForm(), BottomBar()}) |
      ftxui::Renderer([](ftxui::Element element) {
        return ftxui::vbox({ftxui::text("「 kok-s0s's ToDo List 」") |
                                ftxui::center | ftxui::bold | ftxui::inverted,
                            ftxui::separator(),
                            std::move(element) | ftxui::yframe}) |
               ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 60);
      });

  screen.Loop(layout);
}

ftxui::Component TodoTui::NewTodoForm() {
  auto new_todo_input =
      ftxui::Input(&new_todo_text_, "Type new todo") |
      ftxui::Renderer([](ftxui::Element element) {
        return ftxui::hbox(
            {ftxui::text("New Todo: ") | ftxui::bold | ftxui::center,
             std::move(element) | ftxui::flex});
      });

  auto add_todo_button = ftxui::Button(
                             "Add",
                             [&] {
                               if (!new_todo_text_.empty()) {
                                 todo_list_.AddTodoItem(new_todo_text_);
                                 new_todo_text_ = "";
                                 ReloadTodoListComponent();
                               }
                             },
                             ftxui::ButtonOption::Ascii()) |
                         ftxui::color(ftxui::Color::Green) |
                         ftxui::Renderer([](ftxui::Element element) {
                           return ftxui::hbox({std::move(element)});
                         });

  return ftxui::Container::Horizontal(
             {new_todo_input | ftxui::flex, add_todo_button}) |
         ftxui::border;
}

ftxui::Component TodoTui::TodoItemComponent(TodoItem todo_item,
                                            int todo_item_index) {
  auto completed_button =
      ftxui::Button(todo_item.IsCompleted() ? " ✓ " : "   ",
                    [=] {
                      todo_list_.ToggleTodoItemIsCompleted(todo_item.GetId());
                      ReloadTodoListComponent();
                    }) |
      ftxui::color(todo_item.IsCompleted() ? ftxui::Color::Green
                                           : ftxui::Color::Blue);

  auto delete_button =
      ftxui::Button("Del",
                    [=] {
                      todo_list_.RemoveTodoItem(todo_item.GetId());
                      ReloadTodoListComponent();
                    }) |
      ftxui::color(ftxui::Color::Red);

  auto buttons =
      ftxui::Container::Horizontal({completed_button, delete_button});

  return ftxui::Renderer(buttons, [=] {
    return ftxui::hbox({ftxui::text(std::to_string(todo_item_index) + ". " +
                                    todo_item.GetText()) |
                            ftxui::border | ftxui::flex,
                        buttons->Render()});
  });
}

ftxui::Component TodoTui::UpdateTodoForm() {
  auto todo_item_index_input =
      ftxui::Input(&selected_todo_item_index_, "Idx") |
      ftxui::Renderer([](ftxui::Element element) {
        return ftxui::hbox({std::move(element)}) |
               ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 4);
      });

  auto new_todo_input =
      ftxui::Input(&update_todo_text_, "Type new todo") |
      ftxui::Renderer([](ftxui::Element element) {
        return ftxui::hbox({std::move(element) | ftxui::flex});
      });

  auto update_todo_button =
      ftxui::Button(
          "Update",
          [&] {
            if (!update_todo_text_.empty()) {
              todo_list_.UpdateTodoItemText(
                  std::stoi(selected_todo_item_index_), update_todo_text_);
              update_todo_text_ = "";
              ReloadTodoListComponent();
            }
          },
          ftxui::ButtonOption::Ascii()) |
      ftxui::color(ftxui::Color::Green) |
      ftxui::Renderer([](ftxui::Element element) {
        return ftxui::hbox({std::move(element)});
      });

  return ftxui::Container::Horizontal({todo_item_index_input,
                                       new_todo_input | ftxui::flex,
                                       update_todo_button}) |
         ftxui::border;
}

ftxui::Component TodoTui::BottomBar() {
  auto delete_all_todo_items_button =
      ftxui::Button(
          "* Reset *",
          [&] {
            todo_list_.DeleteAllTodoItems();
            ReloadTodoListComponent();
          },
          ftxui::ButtonOption::Ascii()) |
      ftxui::color(ftxui::Color::Red) |
      ftxui::Renderer([](ftxui::Element element) {
        return ftxui::hbox({std::move(element)});
      });

  auto renderer_non_focusable =
      ftxui::Renderer([&] { return ftxui::text("Have Fun!") | ftxui::center; });

  return ftxui::Container::Horizontal({
             delete_all_todo_items_button,
             renderer_non_focusable | ftxui::flex,
         }) |
         ftxui::border;
}

void TodoTui::ReloadTodoListComponent() {
  todo_list_component_->DetachAllChildren();
  int todo_item_index = 0;
  for (const auto& todo_item : todo_list_.GetAllTodoItems()) {
    auto todo_item_component = TodoItemComponent(todo_item, todo_item_index);
    todo_list_component_->Add(std::move(todo_item_component));
    todo_item_index++;
  }
}
