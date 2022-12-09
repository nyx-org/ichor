#include <ichor/debug.h>
#include <ichor/syscalls.h>
#include <stdarg.h>
#include <stdc-shim/stdlib.h>
#include <stdc-shim/string.h>

static void vsprintf(char *buffer, const char *fmt, va_list args)
{
    const char *s = fmt;
    while (*s)
    {
        if (*s == '%')
        {
            s++;
            switch (*s)
            {
            case 'd':
            {
                char buf[100];
                int64_t value = va_arg(args, int64_t);
                strncat(buffer, itoa(value, buf, 10), strlen(buf));
                break;
            }
            case 'u':
            {
                char buf[100];
                uint64_t value = va_arg(args, uint64_t);
                strncat(buffer, utoa(value, buf, 10), strlen(buf));
                break;
            }
            case 'x':
            case 'p':
            {
                char buf[100];
                uint64_t value = va_arg(args, uint64_t);
                strncat(buffer, utoa(value, buf, 16), strlen(buf));
                break;
            }

            case 's':
            {
                const char *value = va_arg(args, const char *);
                strncat(buffer, value, strlen(value));
                break;
            }
            case 'c':
            {
                char value = va_arg(args, int);
                char tmp[] = {value, 0};
                strncat(buffer, tmp, 1);
                break;
            }
            case '%':
            {
                strncat(buffer, "%", 1);
                break;
            }
            default:
            {
                break;
            }
            }
        }
        else
        {
            char tmp[] = {*s, 0};
            strncat(buffer, tmp, strlen(tmp));
        }
        s++;
    }
}

void ichor_debug(const char *fmt, ...)
{

    va_list args;
    va_start(args, fmt);
    char buf[4096] = {0};
    vsprintf(buf, fmt, args);
    sys_log(buf);
    va_end(args);
}