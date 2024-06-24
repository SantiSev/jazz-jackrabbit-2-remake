# Documentation

## Indice

El trabajo práctico se divide en cuatro partes principales:

* Physical engine
* Client
* Server
* Protocol

## Physical engine

## Client

## Server

## Protocol

El diseño del protocolo fue basado gracias a la clase y diapositiva de la clase de Protocolo de la materia Taller
de Programacion (Veiga).

### Mensajes

Los mensajes del protocolo tiene dos partes:

* Header: Permite distinguir los mensajes
* DTOs: Contiene la informacion del mensaje

### Headers

Los headers son de 2 bytes. El primer byte determina la categoria del mensaje. Existen tres categorias de
mensaje:

1. Connection events (0x00)
2. In game events (0x01)
3. Menu events (0x02)

El segundo byte, determina que mensaje es en si. Todos lo mensaje que hay son:

* NULL_MESSAGE (0x0000)
* ACPT_CONNECTION (0x0001)
* CLOSE_CONNECTION (0x0002)
* SEND_GAME_STATE (0x0100)
* RECV_COMMAND (0x0101)
* RECV_CHEAT_COMMAND (0x0102)
* RECV_LEAVE_MATCH (0x0103)
* SEND_FINISH_MATCH (0x0104)
* ADD_PLAYER (0x0105)
* RECV_REQUEST_ACTIVE_GAMES (0x0200)
* RECV_CREATE_GAME (0x0201)
* SEND_GAME_CREATED (0x0202)
* RECV_JOIN_MATCH (0x0203)
* SEND_GAME_JOINED (0x0204)
* RECV_ACTIVE_GAMES (0x0205)

### DTOs

#### DTOs: NULL_MESSAGE (0x0000)

Este mensaje existe por si llega un header invalido, no hacer nada.

#### DTOs: ACPT_CONNECTION (0x0001)

Este mensaje le envia el servidor al cliente, para decirle que lo acepta y le devuelve da un
`id_client` de 2 bytes.

#### DTOs: CLOSE_CONNECTION (0x0002)

Este mensaje se envia de forma bidireccional, para que el cliente le avise al servidor o
viceversa, que se van a cerrar.

#### DTOs: SEND_GAME_STATE (0x0100)

Este mensaje le envia el servidor al cliente, para darle la informacion al cliente de lo que
tiene que renderizar. Los Game states estan compuestos la siguiente forma:

```cpp
struct BulletDTO {
    uint64_t id;
    uint8_t bullet_type;
    uint8_t direction;
    uint16_t x_pos;
    uint16_t y_pos;
} __attribute__((packed));

struct EnemyDTO {
    uint16_t id;
    uint8_t character;
    uint8_t state;
    uint16_t x_pos;
    uint16_t y_pos;
} __attribute__((packed));

struct PlayerDTO {
    uint16_t id;
    char name[50];
    uint16_t health;
    character_t character;
    uint16_t points;
    uint8_t state;
    uint16_t x_pos;
    uint16_t y_pos;
    WeaponDTO weapons[NUM_OF_WEAPONS];
} __attribute__((packed));

struct GameStateDTO {
    uint8_t num_players;
    uint8_t num_enemies;
    uint8_t num_bullets;
    PlayerDTO players[MAX_PLAYERS];
    EnemyDTO enemies[MAX_ENEMIES];
    BulletDTO bullets[50 * MAX_PLAYERS];
    uint16_t seconds;
} __attribute__((packed));
```

#### DTOs: RECV_COMMAND (0x0101)

Este mensaje envia el cliente al server para saber que movimiento hizo el player en el juego.
La informacion es:

```cpp
struct CommandDTO {
    id_player_t id_player; // ID del player que hizo el movimiento
    command_t command; // Tipo de comando
} __attribute__((packed));
```

Los tipos de comandos son:

* MOVE_LEFT (0x00)
* MOVE_RIGHT (0x01)
* MOVE_LEFT_FAST (0x02)
* MOVE_RIGHT_FAST (0x03)
* JUMP (0x04)
* SPECIAL_ATTACK (0x05)
* CHANGE_WEAPON (0x06)
* LOOK_UP (0x07)
* DUCK_DOWN (0x08)
* SHOOT (0x09)
* PAUSE_GAME (0x10)
* TAUNT (0x11)

#### DTOs: RECV_CHEAT_COMMAND (0x0102)

Este mensaje envia el cliente al server para saber que cheat command hizo el player en el juego.
La informacion es:

```cpp
struct CheatCommandDTO {
    id_player_t id_player; // ID del player del cheat command
    cheat_command_t command; // Tipo de cheat command
} __attribute__((packed));
```

Los tipos de cheat commands:

* CHEAT_MAX_AMMO (0x00)
* CHEAT_MAX_HEALTH (0x01)
* CHEAT_INVINCIBLE (0x02)
* CHEAT_REVIVE (0x03)
* CHEAT_INFINITE_AMMO (0x04)
* CHEAT_REVIVE_ALL (0x05)
* CHEAT_KILL_ALL (0x06)

#### DTOs: RECV_LEAVE_MATCH (0x0103)

Este mensaje envia el cliente al server para que este ultimo sepa quien abandono la partida.
La informacion es:

```cpp
struct LeaveMatchDTO {
    id_player_t id_player; // ID del player que abandono la partida
} __attribute__((packed));
```

#### DTOs: SEND_FINISH_MATCH (0x0104)

Este mensaje envia el server al cliente, para avisar que termino la partida.

#### DTOs: ADD_PLAYER (0x0105)

Este mensaje, es un mensaje interno entre el `MatchManager` y una `Match`. Este permite, añadir un
jugador a la partida. La informacion que requiere es:

```cpp
struct AddPlayerDTO {
    char name[50]; // Nombre del jugador
    id_client_t id_client; // ID del cliente
    character_t player_character; // Que personaje eligio
    map_list_t map_name; // Que mapa elegio
} __attribute__((packed));
```

#### DTOs: RECV_REQUEST_ACTIVE_GAMES (0x0200)

Este mensaje envia el cliente al servidor, para pedirle al server las partidas actuales.

#### DTOs: RECV_CREATE_GAME (0x0201)

Este mensaje envia el cliente al servidor, para decirle al server que quiere crear un partida.
La informacion que le envia es:

```cpp
struct CreateGameDTO {
    id_client_t id_client; // ID del cliente
    character_t character_selected; // Que personaje eligio
    map_list_t map_name; // Que mapa elegio
    uint8_t max_players; // Cual es el maximo de players que puede haber
} __attribute__((packed));
```

#### DTOs: SEND_GAME_CREATED (0x0202)

Este mensaje envia el server al cliente, para decirle que la partida se creo.
La informacion que le envia es:

```cpp
struct ClientHasConnectedToMatchDTO {
    map_list_t map; // Que mapa es
} __attribute__((packed));
```

#### DTOs: RECV_JOIN_MATCH (0x0203)

Este mensaje envia el cliente al server, para pedirle que al server que un determinado cliente, quiere conectarse.
La informacion que le envia es:

```cpp
struct JoinMatchDTO {
    id_client_t id_client; // ID del cliente
    id_match_t id_match; // IDe de la partida que se quiere unir el cliente
    character_t player_character; // Que personaje eligio
} __attribute__((packed));
```

#### DTOs: SEND_GAME_JOINED (0x0204)

Este mensaje eniva el server al cliente, para decirle a este ultimo que su conexion a una determinada partida fue
exitosa. La informacion que le envia es:

```cpp
struct ClientHasConnectedToMatchDTO {
    map_list_t map; // Que mapa es
} __attribute__((packed));
```

#### DTOs: RECV_ACTIVE_GAMES (0x0205)

Este mensaje envia el server al client, para decirle a este ultimo la cantidad de partidas activas que hay. La
informacion que le envia es:

```cpp
struct ActiveGamesDTO {
    map_list_t map; // Que mapa es
    uint8_t players_ingame; // Numero de jugadores en partida
    uint8_t players_max; // Numero maximo de jugadores
} __attribute__((packed));

struct MatchInfoDTO {
    uint8_t num_games; // Numero de partidas
    ActiveGamesDTO active_games[MAX_MATCHES_TO_CREATE]; // Lista de las partidas
} __attribute__((packed));
```
