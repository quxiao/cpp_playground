#include <cstdio>
#include "string_splitter.h"

StringSplitter::StringSplitter(const char* str, char sep)
    : head_(str)
    , tail_(str)
    , str_tail_(str)
    , sep_(sep)
{
    _init();
}

void StringSplitter::_init()
{
    while (head_ != NULL && *head_ == sep_ && *head_ != '\0') { ++ head_; }
    tail_ = head_;
    while (head_ != NULL && *tail_ != sep_ && *tail_ != '\0') { ++ tail_; }
    while (head_ != NULL && *str_tail_ != '\0') { ++ str_tail_; }
}

StringSplitter::operator bool() const
{
    return head_ != NULL 
        && *head_ != '\0' 
        && head_ != str_tail_;
}

const char* StringSplitter::field() const
{
    return head_;
}

size_t StringSplitter::length() const
{
    return static_cast<size_t>(tail_ - head_);
}

StringSplitter& StringSplitter::operator++()
{
    head_ = tail_;
    while (*head_ == sep_ && *head_ != '\0' && head_ != str_tail_) { ++ head_; }
    tail_ = head_;
    while (*tail_ != sep_ && *tail_ != '\0' && tail_ != str_tail_) { ++ tail_; }

    return *this;
}

StringSplitter StringSplitter::operator++(int)
{
    StringSplitter tmp = *this;
    this->operator++();
    return tmp;
}
