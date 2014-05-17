#include <cstring>

/*
 *
 * A utility for splitting string.
 * In the process of splitting, these functions don't modify the origin string.
 *
 * Usage:
 *      const char* str = ......;
 *      for (StringSplitter splitter(str, '\t'); splitter; ++ splitter)
 *      {
 *          printf("%.*s\n", splitter.length(), splitter.field());
 *      }
 *
 */


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
