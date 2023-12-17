#include <array>
#include <memory>
#include <string>
#include <vector>

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"
#include "ftxui/util/ref.hpp"
#include "todo_list.h"

using namespace ftxui;

ButtonOption ButtonStyle() {
  auto option = ButtonOption::Ascii();
  option.transform = [](const EntryState& s) {
    auto element = text(s.label);
    if (s.focused) {
      element |= inverted;
    }
    return element | center | flex;
  };
  return option;
}

int main(int argc, char* argv[]) {
  TodoList todoList_;

  auto btn_hello_workd = Button(
      "Hello World", [&] {}, ButtonStyle());

  auto btn_reset = Button(
      "ReSet", [&] { todoList_.DeleteAllTodoItems(); }, ButtonStyle());

  std::string todo_content;
  Component input_todo_content = Input(&todo_content, "todo content");

  auto btn_add = Button(
      "Add", [&] { todoList_.AddTodoItem(todo_content); }, ButtonStyle());

  auto main_container = Container::Vertical({
      Container::Horizontal({btn_hello_workd}),
      Container::Horizontal({btn_reset}),
      Container::Horizontal({input_todo_content, btn_add}),
  });

  auto main_renderer = Renderer(main_container, [&] {
    return vbox({
               hbox({btn_hello_workd->Render()}),
               separator(),
               hbox({
                   text("「 kok-s0s's ToDo List 」") | bold | center |
                       size(WIDTH, EQUAL, 30),
                   separator(),
                   btn_reset->Render() | size(WIDTH, EQUAL, 8),
               }),
               separator(),
               hbox({
                   input_todo_content->Render() | center | flex |
                       size(WIDTH, EQUAL, 30),
                   separator(),
                   btn_add->Render() | size(WIDTH, EQUAL, 8),
               }),
               separator(),
           }) |
           border | size(WIDTH, EQUAL, 40);
  });

  auto screen = ScreenInteractive::FitComponent();
  screen.Loop(main_renderer);

  return 0;
}
