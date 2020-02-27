/*
** EPITECH PROJECT, 2019
** Pipe.cpp
** File description:
** ${FILEDESCRIPTION}
*/

#include "Pipe.hpp"
#include <unistd.h>
#include <Pipe.hpp>

Pipe::Pipe()
{
}

std::vector<int> *Pipe::my_pipe(std::vector<int> *cook_array)
{
    int fd[2];
    int fd1[2];
    int fd2[2];
    
    if (pipe(fd) < 0 or pipe(fd1) < 0 or pipe(fd2) < 0)
        return (nullptr);
    (*cook_array).push_back(fd[0]);
    (*cook_array).push_back(fd[1]);
    (*cook_array).push_back(fd1[0]);
    (*cook_array).push_back(fd1[1]);
    (*cook_array).push_back(fd2[0]);
    (*cook_array).push_back(fd2[1]);
    return (cook_array);
}
