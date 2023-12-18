#include "todo_item.h"

TodoItem::TodoItem(int id, const std::string &text, bool completed)
    : id_(id), text_(text), completed_(completed) {}

int TodoItem::GetId() const { return id_; }

std::string TodoItem::GetText() const { return text_; }

void TodoItem::SetText(std::string text) { text_ = text; }

bool TodoItem::IsCompleted() const { return completed_; }

void TodoItem::SetCompleted(bool completed) { completed_ = completed; }
