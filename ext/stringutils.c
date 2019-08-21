#include <stddef.h>
#include <string.h>

int startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre), lenstr = strlen(str);

    return lenstr < lenpre ? 0 : memcmp(pre, str, lenpre) == 0;
}
