/*
** EPITECH PROJECT, 2019
** Thread.hpp
** File description:
** ${FILEDESCRIPTION}
*/

#ifndef CCP_PLAZZA_2018_THREAD_HPP
#define CCP_PLAZZA_2018_THREAD_HPP

#include <thread>

class IThread {
    public:
    virtual ~IThread() = default;
    virtual void join() = 0;
    virtual void detach() = 0;
    virtual void swap(std::thread thread) = 0;
    virtual std::thread::id getId() = 0;
    //virtual std::thread &getThread() const = 0;
};

class Thread : public IThread {
    public:
    Thread();
    ~Thread();
    void join();
    void detach();
    void swap(std::thread thread);
    std::thread::id getId();
    //Thread &operator=(Thread const &thread);


    private:
    std::thread _thread;
};

#endif //CCP_PLAZZA_2018_THREAD_HPP
