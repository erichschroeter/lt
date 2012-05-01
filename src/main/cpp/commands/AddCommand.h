#ifndef ADD_COMMAND_H
#define ADD_COMMAND_H

#include "CliCommand.h"

class AddCommand : public CliCommand
{
public:
    AddCommand();
    ~AddCommand();
    
    // CliCommand methods
    int execute(int argc, char** argv);
    // Command methods
    int execute();
};

#endif
