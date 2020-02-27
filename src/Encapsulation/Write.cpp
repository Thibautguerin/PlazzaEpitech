/*
** EPITECH PROJECT, 2019
** Write.cpp
** File description:
** ${FILEDESCRIPTION}
*/

#include "Write.hpp"
#include <unistd.h>

Write::Write()
{
}

void Write::my_write(int fd, const char *str, int i)
{
    write(fd, str, i);
}
