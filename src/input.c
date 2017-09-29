#include <header.h>


char* getInput()
{
    size_t buffer = 0;
    char* in;
    getline(&in, &buffer, stdin);
    return in;
}