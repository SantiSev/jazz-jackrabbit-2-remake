#include <cstdint>
#include <string>

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
private:
    uint16_t id_player;
    uint8_t id_command;

public:
    RecvCommandMessage(uint16_t id_player, uint8_t id_command);
    void run() override;
    ~RecvCommandMessage();
};

class RecvCheatCommandMessage: public Message {
private:
    uint16_t id_player;
    uint8_t id_cheat_command;

public:
    RecvCheatCommandMessage(uint16_t id_player, uint8_t id_cheat_command);
    void run() override;
    ~RecvCheatCommandMessage();
};

class RecvUnjoinMatchMessage: public Message {
private:
    uint16_t id_player;

public:
    explicit RecvUnjoinMatchMessage(uint16_t id_player);
    void run() override;
    ~RecvUnjoinMatchMessage();
};

class RecvCreateGameMessage: public Message {
private:
    uint16_t id_player;
    std::string match_name;

public:
    RecvCreateGameMessage(uint16_t id_player, const std::string& match_name);
    void run() override;
    ~RecvCreateGameMessage();
};

class RecvJoinMatchMessage: public Message {
private:
    uint16_t id_player;
    uint16_t id_match;
    uint8_t player_character;

public:
    RecvJoinMatchMessage(uint16_t id_player, uint16_t id_match, uint8_t player_character);
    void run() override;
    ~RecvJoinMatchMessage();
};

class InvalidMessage: public Message {
public:
    InvalidMessage();
    void run() override;
    ~InvalidMessage();
};
