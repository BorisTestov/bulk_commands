#include "stream.h"

Stream::Stream(std::istream& user_input) :
    _input(user_input)
{}

void Stream::run()
{
    std::string command;

    while (std::getline(_input, command))
    {
        std::for_each(_observers.begin(), _observers.end(), [command](auto ptrProcessor) {
            ptrProcessor->parseCommand(command);
        });
    };
}

void Stream::addObserver(observerPtr newObserver)
{
    _observers.push_back(newObserver);
}