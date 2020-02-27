/*
** EPITECH PROJECT, 2019
** Mutex.hpp
** File description:
** ${FILEDESCRIPTION}
*/

#ifndef CCP_PLAZZA_2018_MUTEX_HPP
#define CCP_PLAZZA_2018_MUTEX_HPP

#include <mutex>

class IMutex {
    public:
    virtual ~IMutex() = default;
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual void trylock() = 0;
};

class Mutex : public IMutex {
    public:
    ~Mutex();
    void lock();
    void unlock();
    void trylock();

    protected:
    std::mutex mutex;
};

#endif //CCP_PLAZZA_2018_MUTEX_HPP
