#include <cstring>

class StringSplitter
{
public:
    StringSplitter(const char* str, char sep);
    operator bool() const;
    StringSplitter& operator++();
    StringSplitter operator++(int);
    const char* field() const;
    size_t length() const;

private:
    //forbidden
    StringSplitter();

    void _init();

    const char* head_;
    const char* tail_;
    const char* str_tail_;
    const char sep_;
};
