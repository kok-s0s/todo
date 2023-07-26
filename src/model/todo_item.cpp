#include "todo_item.h"

TodoItem::TodoItem(int id, const std::string &title, bool completed)
    : id_(id), title_(title), completed_(completed) {}

int TodoItem::getId() const { return id_; }

std::string TodoItem::getTitle() const { return title_; }

bool TodoItem::isCompleted() const { return completed_; }

void TodoItem::setCompleted(bool completed) { completed_ = completed; }
