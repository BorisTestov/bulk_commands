#pragma once

#include "command_container.h"
#include "observer.h"

#include <ctime>
#include <fstream>

class BlockProcessor : public Observer
{
public:
    BlockProcessor();
    virtual ~BlockProcessor();

    /**
     * @brief Возвращает время первой команды
     * @return Время первой команды (time_t)
     */
    std::time_t getTime() const;

protected:
    virtual void handleCommand(const std::string& command) override;
    virtual void startBlock() override;
    virtual void finishBlock() override;

    /**
     * @brief Метод логгирования блока команд
     */
    void logBlock();

private:
    size_t _blockCounter;
    std::time_t _timeStart;
    CommandContainer _store;
};