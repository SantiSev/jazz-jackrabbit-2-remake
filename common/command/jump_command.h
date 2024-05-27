#ifndef TP_FINAL_JUMP_COMMAND_H
#define TP_FINAL_JUMP_COMMAND_H

#include "command.h"

class jump_command: public Command {
public:
    void execute() override;
};


#endif
