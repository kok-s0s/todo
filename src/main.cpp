#include "todo_controller.h"
#include "todo_list.h"
#include "todo_tui.h"

int main(int argc, char* argv[]) {
  todo::TodoList todo_list;
  todo::Controller controller(todo_list);
  todo::Tui tui(controller);
  tui.StartLoop();
  return 0;
}
