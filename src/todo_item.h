#ifndef TODO_ITEM_H
#define TODO_ITEM_H

#include <string>

class TodoItem {
 public:
  TodoItem(int id, const std::string &content, bool completed);

  int GetId() const;
  std::string GetContent() const;
  void SetContent(std::string content);
  bool IsCompleted() const;
  void SetCompleted(bool completed);

 private:
  int id_;
  std::string content_;
  bool completed_;
};

#endif  // TODO_ITEM_H
