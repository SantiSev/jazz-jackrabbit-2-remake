class Message {
public:
    virtual void run() = 0;
};

class ConnectionMessage: public Message {
public:
    void run() override;
};

class InGameMessage: public Message {
public:
    void run() override;
};

class MenuMessage: public Message {
public:
    void run() override;
};
