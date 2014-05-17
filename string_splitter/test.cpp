#include <cstdio>
#include "string_splitter.h"

int main(int argc, char** argv)
{
    StringSplitter splitter("1111,2222,333", ',');
    for (; splitter; ++ splitter)
    {
        printf("sub len: %zu\n", splitter.length());
        printf("%.*s\n", (int)splitter.length(), splitter.field());
    }

    return 0;
}
