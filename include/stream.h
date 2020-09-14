#pragma once

#include "observer.h"

#include <algorithm>
#include <exception>
#include <iostream>
#include <vector>

class Stream
{
public:
    Stream(std::istream& user_input);
    void run();
    void addObserver(observerPtr newObserver);

private:
    std::istream& _input;
    std::vector<observerPtr> _observers;
};
