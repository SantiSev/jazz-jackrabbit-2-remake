#ifndef TP_FINAL_SHOOT_COMMAND_H
#define TP_FINAL_SHOOT_COMMAND_H


#include "command.h"

class shoot_command: public Command {
public:
    void execute() override;
};


#endif
