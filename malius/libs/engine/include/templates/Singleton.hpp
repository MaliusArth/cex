#pragma once
#include <iostream>
#include <memory>

namespace ma
{
    template <class T>
    class Singleton
    {
    public:
        // TODO: return std::unique_ptr<T>
        template <typename... Args>
        static T* get_instance(Args&&... args)
        //static std::unique_ptr<T> get_instance(Args&&... args)
        {
            if (!_instance)
            {
                _instance = new T(std::forward<Args>(args)...);
                // TODO: use std::make_unique<T>
                //_instance = std::make_unique<T>(args);
                //_instance = std::unique_ptr<T>(new T(std::forward<Args>(args)...));
            }

            return _instance;
        }

        static void destroy_instance()
        {
            delete _instance;
            //_instance.reset();
            // TODO: is this needed?
            _instance = nullptr;
        }

    private:
        static T* _instance;
        //static std::unique_ptr<T> _instance;
    };

    template <class T>
    T * Singleton<T>::_instance = nullptr;
    //std::unique_ptr<T> Singleton<T>::_instance = nullptr;
}
