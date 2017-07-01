#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include "hello_world.h"

#define HELLO "Hello, World"

void hello(char *buffer, const char *name)
{
    if (name == NULL)
        name = "World";
    sprintf(buffer, "Hello, %s!", name);
}
