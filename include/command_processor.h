#pragma once

#include "command_container.h"
#include "observer.h"

#include <ctime>
#include <fstream>
#include <string>
#include <vector>

class CommandProcessor : public Observer
{
public:
    CommandProcessor(size_t bulkSize);
    ~CommandProcessor();

    /**
     * @brief Добавление новой комманды
     * @param command Комманда для добавления
     */
    void newCommand(const std::string& command);

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
     * @brief Метод логгирования комманд в формате bulk<время получения первой команды из блока>.log
     */
    void logBlock();

private:
    size_t _bulkSize;
    size_t _blockCounter;
    std::time_t _timeStart;
    CommandContainer _store;
};