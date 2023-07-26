#include <QtWidgets/QApplication>

// #include "controller/todo_controller.h"
#include "todo_mainwindow.h"

int main(int argc, char *argv[]) {
  // TodoController todoController;
  // todoController.run();

  QApplication a(argc, argv);
  TodoMainWindow w;
  w.show();
  return a.exec();

  return 0;
}
