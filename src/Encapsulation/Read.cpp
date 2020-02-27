/*
** EPITECH PROJECT, 2019
** Read.cpp
** File description:
** ${FILEDESCRIPTION}
*/

#include "Read.hpp"
#include <unistd.h>

Read::Read()
{
}

int Read::my_read(int fd, char *str, int size)
{
    return (read(fd, str, size));
}
