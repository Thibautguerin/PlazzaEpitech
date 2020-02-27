/*
** EPITECH PROJECT, 2019
** Thread.cpp
** File description:
** ${FILEDESCRIPTION}
*/

#include <iostream>
#include "Thread.hpp"

Thread::Thread()
{
}

Thread::~Thread()
{
    if (this->_thread.joinable())
        this->_thread.join();
}

void Thread::join()
{
    this->_thread.join();
}

void Thread::detach()
{
    this->_thread.detach();
}

void Thread::swap(std::thread thread)
{
    this->_thread.swap(thread);
}

std::thread::id Thread::getId()
{
    return (this->_thread.get_id());
}

