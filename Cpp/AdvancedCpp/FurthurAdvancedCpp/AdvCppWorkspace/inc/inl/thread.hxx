#ifndef NM_THREAD_HXX
#define NM_THREAD_HXX


#include <pthread.h> // pthread_create, pthread_join, pthread_exit
#include <stdexcept> // std::runtime_error
#include <tuple> // std::tuple, std::make_tuple
#include "tuple_unpack.hxx"


namespace nm
{

namespace advcpp
{

template <typename Func, typename ...Args>
void* Thread<Func, Args...>::Thread::Task(void* a_this)
{
    Thread<Func, Args...>* self = static_cast<Thread<Func, Args...>*>(a_this);
    self->m_task(self->m_args);
    meta::UnpackTupleAndCallFunc(self->m_task, self->m_args);
}


template <typename Func, typename ...Args>
Thread<Func, Args...>::Thread(Func a_task, Args... a_args)
: m_task(a_task)
, m_args(std::make_tuple(a_args...))
, m_isAvailableThread(new bool(true))
, m_threadID()
{
    int statusCode = pthread_create(&m_threadID, nullptr, Thread::Task, static_cast<void*>(this));
    if(statusCode < 0)
    {
        delete m_isAvailableThread;
        throw std::runtime_error("Failed while trying to create a thread");
    }
}


template <typename Func, typename ...Args>
Thread<Func,Args...>::Thread(Thread&& a_rvalue) noexcept
: m_task(a_rvalue.m_task)
, m_args(a_rvalue.m_args)
, m_isAvailableThread(a_rvalue.m_isAvailableThread)
, m_threadID(a_rvalue.m_threadID)
{
    a_rvalue.m_isAvailableThread = nullptr; // Move
}


template <typename Func, typename ...Args>
Thread<Func,Args...>& Thread<Func,Args...>::operator=(Thread&& a_rvalue) noexcept
{
    if(m_isAvailableThread)
    {
        try
        {
            Cancel();
        }
        catch(...)
        { // No need to handle (error would be thrown ONLY if the thread has finished already)
        }
    }

    delete m_isAvailableThread;

    m_task = a_rvalue.m_task;
    m_args = a_rvalue.m_args;
    m_threadID = a_rvalue.m_threadID;

    m_isAvailableThread = a_rvalue.m_isAvailableThread;
    a_rvalue.m_isAvailableThread = nullptr; // Move

    return *this;
}


template <typename Func, typename ...Args>
Thread<Func,Args...>::~Thread()
{
    delete m_isAvailableThread; // Would be nullptr if the Thread has moved
}


template <typename Func, typename ...Args>
void Thread<Func,Args...>::Join()
{
    if(*m_isAvailableThread)
    {
        void* taskReturnedValue = nullptr;
        int statusCode = pthread_join(m_threadID, &taskReturnedValue);
        if(statusCode != 0)
        {
            throw std::runtime_error("Failed while trying to join");
        }

        *m_isAvailableThread = false; // Not critical if an exception is thrown and this line is not executing
    }
}


template <typename Func, typename ...Args>
void Thread<Func,Args...>::Detach()
{
    if(*m_isAvailableThread)
    {
        int statusCode = pthread_detach(m_threadID);
        if(statusCode != 0)
        {
            throw std::runtime_error("Failed while trying to detach");
        }

        *m_isAvailableThread = false; // Not critical if an exception is thrown and this line is not executing
    }
}


template <typename Func, typename ...Args>
void Thread<Func,Args...>::Cancel()
{
    int statusCode = pthread_cancel(m_threadID);
    if(statusCode != 0)
    {
        throw std::runtime_error("Failed while trying to cancel (maybe thread had finished already)");
    }

    *m_isAvailableThread = false; // Not critical if an exception is thrown and this line is not executing
}

} // advcpp

} // nm


#endif // NM_THREAD_HXX
