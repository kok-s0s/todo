#ifndef TODO_ITEM_H
#define TODO_ITEM_H

#include <string>

class TodoItem {
public:
    TodoItem(int id, const std::string& title, bool completed);

    int getId() const;
    std::string getTitle() const;
    bool isCompleted() const;
    void setCompleted(bool completed);

private:
    int id_;
    std::string title_;
    bool completed_;
};

#endif // TODO_ITEM_H
