#ifndef CLI_COMMAND_H
#define CLI_COMMAND_H

#include "Command.h"

class CliCommand : public Command
{
public:
    virtual int execute(int argc, char** argv) = 0;
};

#endif
