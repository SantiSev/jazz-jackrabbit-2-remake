#include "server_eventloop.h"

Server_Eventloop::Server_Eventloop(Queue<std::string>& eventQueue,
                                   Queue<std::string>& commandQueue):
        online(true), event_queue(eventQueue), command_queue(commandQueue) {}


void Server_Eventloop::run() {
    try {
        while (online) {
            std::string next_command;
            while (command_queue.try_pop(next_command)) {
                compute_command(next_command);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    } catch (const std::exception& err) {
        if (online) {
            std::cerr << "An exception was caught in gameloop: " << err.what() << "\n";
            stop();
        }
    }
}

void Server_Eventloop::stop() { online = false; }

void Server_Eventloop::compute_command(std::string basic_string) {
    uint8_t command_type =
            basic_string[0];  // ACA VA EL TIPO DE COMANDO CUANDO TENGA LA ESTRUCTURA CORRECTA
    uint8_t command = basic_string[1];
    filter_command_type(command_type);
    switch (command) {
        case MOVE_LEFT:
            std::cout << "Command: Move Left" << std::endl;
            break;
        case MOVE_RIGHT:
            std::cout << "Command: Move Right" << std::endl;
            break;
        case LOOK_UP:
            std::cout << "Command: Look Up" << std::endl;
            break;
        case DUCK_DOWN:
            std::cout << "Command: Duck Down" << std::endl;
            break;
        case JUMP:
            std::cout << "Command: Jump" << std::endl;
            break;
        case SHOOT:
            std::cout << "Command: Shoot" << std::endl;
            break;
        case SPECIAL_ATTACK:
            std::cout << "Command: Special Attack" << std::endl;
            break;
        case PICK_UP_ITEM:
            std::cout << "Command: Pick Up Item" << std::endl;
            break;
        case PAUSE_GAME:
            std::cout << "Command: Pause Game" << std::endl;
            break;
        case TAUNT:
            std::cout << "Command: Taunt" << std::endl;
            break;
        default:
            std::cout << "Unknown command" << std::endl;
            break;
    }
}

void Server_Eventloop::filter_command_type(uint8_t command_type_string) {
    switch (command_type_string) {
        case CONNECTION_EVENT:
            std::cout << "IS A PLAYER COMMAND" << std::endl;
            break;
        case IN_GAME_EVENT:
            std::cout << "IS A CHEAT COMMAND" << std::endl;
            break;
        default:
            std::cout << "unkown event" << std::endl;
            break;
    }
}
