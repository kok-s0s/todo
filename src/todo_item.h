#ifndef TODO_ITEM_H
#define TODO_ITEM_H

#include <string>

class TodoItem {
 public:
  TodoItem(int id, const std::string &content, bool completed);

  int getId() const;
  std::string getContent() const;
  void setContent(std::string content);
  bool isCompleted() const;
  void setCompleted(bool completed);

 private:
  int id_;
  std::string content_;
  bool completed_;
};

#endif  // TODO_ITEM_H
