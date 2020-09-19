#include "block_processor.h"

BlockProcessor::~BlockProcessor()
{
    //dtor
}

void BlockProcessor::startBlock()
{
    if (0 == _blockCounter)
        _timeStart = std::time(nullptr);
    ++_blockCounter;
}

void BlockProcessor::finishBlock()
{
    if (_blockCounter > 0)
        --_blockCounter;

    if (_blockCounter == 0)
    {
        _store.printCommands();
        logBlock();
        _store.clear();
    }
}

void BlockProcessor::handleCommand(const std::string& command)
{
    if (0 < _blockCounter)
        _store.addCommand(command);
}

void BlockProcessor::logBlock()
{
    std::ofstream fileLog("bulk" + std::to_string(_timeStart) + ".log");
    _store.printCommands(fileLog);
}

std::time_t BlockProcessor::getTime() const
{
    return _timeStart;
}