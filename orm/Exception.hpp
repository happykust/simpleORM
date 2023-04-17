#ifndef SIMPLEORM_EXCEPTION_HPP
#define SIMPLEORM_EXCEPTION_HPP

#include <cstring>
#include <string>
#include <utility>

namespace simpleOrm {

    class SimpleOrmException : public std::exception {
    private:
        std::string e_message;
    public:
        explicit SimpleOrmException(std::string  message) : e_message(std::move(message)) {}
        virtual const char* what() const noexcept override {
            return e_message.c_str();
        }
    };


}// namespace simpleOrm

#endif//SIMPLEORM_EXCEPTION_HPP
