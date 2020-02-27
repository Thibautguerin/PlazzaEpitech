/*
** EPITECH PROJECT, 2019
** Mutex.cpp
** File description:
** ${FILEDESCRIPTION}
*/

#include "Mutex.hpp"

Mutex::~Mutex()
{
}

void Mutex::lock()
{
    this->mutex.lock();
}

void Mutex::unlock()
{
    this->mutex.unlock();
}

void Mutex::trylock()
{
    this->mutex.try_lock();
}