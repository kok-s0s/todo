#ifndef TODO_ITEM_H
#define TODO_ITEM_H

#include <string>

class TodoItem {
 public:
  TodoItem(int id, const std::string &text, bool completed);

  int GetId() const;
  std::string GetText() const;
  void SetText(std::string text);
  bool IsCompleted() const;
  void SetCompleted(bool completed);

 private:
  int id_;
  std::string text_;
  bool completed_;
};

#endif  // TODO_ITEM_H
