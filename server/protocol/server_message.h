class Message {
public:
    virtual void run() = 0;
};

class CloseConnectionMessage: public Message {
public:
    void run() override;
};

class RecvCommandMessage: public Message {
public:
    void run() override;
};

class RecvCheatCommandMessage: public Message {
public:
    void run() override;
};

class RecvUnjoinMatchMessage: public Message {
public:
    void run() override;
};

class RecvCreateGameMessage: public Message {
public:
    void run() override;
};

class RecvJoinMatchMessage: public Message {
public:
    void run() override;
};
