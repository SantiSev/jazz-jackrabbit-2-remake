#include "manager_message_handler.h"

#include "../game_logic/matches_manager.h"

MatchesManagerMessageHandler::MatchesManagerMessageHandler(
        MatchesManager& matches_manager, Queue<std::shared_ptr<Message>>& lobby_queue):
        matches_manager(matches_manager), lobby_queue(lobby_queue) {}

void MatchesManagerMessageHandler::handle_recv_create_game(const CreateGameDTO& dto) {
    matches_manager.create_new_match(dto);
}

void MatchesManagerMessageHandler::handle_recv_join_match(const JoinMatchDTO& dto) {
    std::cout << "joining match message received "
              << "client id " << dto.id_client << " match id " << dto.id_match << std::endl;
    matches_manager.join_match(dto);
}

void MatchesManagerMessageHandler::handle_request_active_games(const RequestActiveGamesDTO& dto) {
    matches_manager.send_match_lists(dto);
}

void MatchesManagerMessageHandler::handle_recv_close_connection(const CloseConnectionDTO& dto) {
    matches_manager.delete_disconnected_client(dto.id_client);
}

void MatchesManagerMessageHandler::handle_recv_command(const CommandDTO& command) {
    id_client_t id_client = command.id_player;
    size_t id_match = matches_manager.get_client_by_id(id_client)->get_current_match_id();
    auto command_message = std::make_shared<RecvCommandMessage>(command);
    if (id_match != 0) {
        matches_manager.get_match_queue_by_id(id_match).try_push(command_message);
    }
}
