#include "observer.h"

Observer::Observer()
{
    //ctor
}

void Observer::parseCommand(const std::string& command)
{
    if (command.empty())
        handleCommand(command);
    else
        switch (command.at(0))
        {
            case controlChars::blockStart:
            {
                startBlock();
                break;
            }
            case controlChars::blockFinish:
            {
                finishBlock();
                break;
            }
            default:
                handleCommand(command);
        }
}