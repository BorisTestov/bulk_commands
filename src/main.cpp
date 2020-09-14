#include "block_processor.h"
#include "command_processor.h"
#include "stream.h"
#include "version.h"

#include <iostream>
#include <map>

int main(int argc, char** argv)
{
    std::cout << "Current version: " << version() << std::endl;

    if (argc < 2)
    {
        std::cerr << "Wrong arguments count. Using: bulk <bulk_size>" << std::endl;
        return -1;
    }
    auto bulk_size(std::atoi(argv[1]));
    Stream console(std::cin);
    console.addObserver(std::make_shared<CommandProcessor>(bulk_size));
    console.addObserver(std::make_shared<BlockProcessor>());
    console.run();
    return 0;
}
