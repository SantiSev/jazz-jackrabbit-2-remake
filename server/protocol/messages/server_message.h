class Message {
public:
    Message();
    virtual void run() = 0;
    ~Message();
};

class CloseConnectionMessage: public Message {
public:
    CloseConnectionMessage();
    void run() override;
    ~CloseConnectionMessage();
};

class RecvCommandMessage: public Message {
public:
    RecvCommandMessage();
    void run() override;
    ~RecvCommandMessage();
};

class RecvCheatCommandMessage: public Message {
public:
    RecvCheatCommandMessage();
    void run() override;
    ~RecvCheatCommandMessage();
};

class RecvUnjoinMatchMessage: public Message {
public:
    RecvUnjoinMatchMessage();
    void run() override;
    ~RecvUnjoinMatchMessage();
};

class RecvCreateGameMessage: public Message {
public:
    RecvCreateGameMessage();
    void run() override;
    ~RecvCreateGameMessage();
};

class RecvJoinMatchMessage: public Message {
public:
    RecvJoinMatchMessage();
    void run() override;
    ~RecvJoinMatchMessage();
};

class InvalidMessage: public Message {
public:
    InvalidMessage();
    void run() override;
    ~InvalidMessage();
};
