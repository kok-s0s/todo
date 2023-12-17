#include "todo_item.h"

TodoItem::TodoItem(int id, const std::string &content, bool completed)
    : id_(id), content_(content), completed_(completed) {}

int TodoItem::GetId() const { return id_; }

std::string TodoItem::GetContent() const { return content_; }

void TodoItem::SetContent(std::string content) { content_ = content; }

bool TodoItem::IsCompleted() const { return completed_; }

void TodoItem::SetCompleted(bool completed) { completed_ = completed; }
