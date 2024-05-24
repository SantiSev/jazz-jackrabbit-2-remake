#ifndef TP_FINAL_COMMAND_H
#define TP_FINAL_COMMAND_H

class Command {

public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};


#endif
