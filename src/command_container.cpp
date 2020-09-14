#include "command_container.h"

CommandContainer::CommandContainer(size_t size) :
    _commands()
{
    _commands.reserve(size);
}

void CommandContainer::addCommand(const std::string& strCommand)
{
    _commands.push_back(strCommand);
}

void CommandContainer::printCommands(std::ostream& out) const
{
    if (!_commands.empty())
    {
        std::string output("bulk:");

        std::for_each(_commands.begin(), _commands.end(), [&output](auto command) { output += command + ","; });
        output.resize(output.length() - 1);
        out << output << std::endl;
    };
}

void CommandContainer::clear()
{
    _commands.clear();
}

size_t CommandContainer::size() const
{
    return _commands.size();
}

bool CommandContainer::isEmpty() const
{
    return _commands.empty();
}