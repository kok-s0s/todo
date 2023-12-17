#include "todo_item.h"

TodoItem::TodoItem(int id, const std::string &content, bool completed)
    : id_(id), content_(content), completed_(completed) {}

int TodoItem::getId() const { return id_; }

std::string TodoItem::getContent() const { return content_; }

void TodoItem::setContent(std::string content) { content_ = content; }

bool TodoItem::isCompleted() const { return completed_; }

void TodoItem::setCompleted(bool completed) { completed_ = completed; }
