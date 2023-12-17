#include "todo_list.h"
#include "todo_tui.h"

int main(int argc, char* argv[]) {
  TodoList todo_list;
  // todo_list.DeleteAllTodoItems();
  TodoTui todo_tui(todo_list);
  todo_tui.StartLoop();
  return 0;
}
