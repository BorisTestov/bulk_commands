#include "command_processor.h"

CommandProcessor::CommandProcessor(size_t bulkSize) :
    Observer(),
    _bulkSize(bulkSize),
    _blockCounter(0),
    _store(bulkSize)
{
}

CommandProcessor::~CommandProcessor()
{
    if (!_store.isEmpty())
    {
        _store.printCommands();
        logBlock();
        _store.clear();
    }
}

void CommandProcessor::newCommand(const std::string& newCommand)
{
    _store.addCommand(newCommand);
}

void CommandProcessor::startBlock()
{
    if (0 == _blockCounter && 0 < _store.size())
    {
        _store.printCommands();
        logBlock();
        _store.clear();
    }
    ++_blockCounter;
}

void CommandProcessor::finishBlock()
{
    if (_blockCounter > 0)
        --_blockCounter;
}

void CommandProcessor::handleCommand(const std::string& command)
{
    if (_blockCounter == 0)
    {
        if (_store.isEmpty())
            _timeStart = std::time(nullptr);
        newCommand(command);
        if (_bulkSize == _store.size())
        {
            _store.printCommands();
            logBlock();
            _store.clear();
        }
    }
}

void CommandProcessor::logBlock()
{
    std::ofstream fileLog("bulk" + std::to_string(_timeStart) + ".log");
    _store.printCommands(fileLog);
}

std::time_t CommandProcessor::getTime() const
{
    return _timeStart;
}