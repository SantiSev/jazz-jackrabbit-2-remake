# Documentation

## Indice

El trabajo práctico se divide en cuatro partes principales:

* Game engine
* Client
* Server
* Protocol

## Game engine

### Physics Engine
Para el diseño de la _"physics engine"_, decidi basarme en la implementacion de fisicas del motor de juegos **Godot** donde llegue al siguiente planteo

#### Collision Objects
Todos los objects del juego son `CollisionObject`'s que consiste en objects con 
```cpp
int hitbox_width;   // el ancho del hitbox del object0 
int hitbox_height;  // el alto del hitbox del objecto 
bool is_active = true; //el status para indicar si debe seguir detectando collisiones o no
```
[ un hitbox es utilizado para detectar colisiones entre los objetos de un juego ]

Para detectar dichas collisiones se utiliza los metodos protegidos `is_touching()` que tiene 2 variantes:
```cpp
    /*
     * This code determines which face of the calling
     * CollisionObject instance (i.e., *this or self)
     * is being touched by the other collision object.
     */
    CollisionFace is_touching(const CollisionObject* other) const;

    /*
     * This code is identical to the is_touching method,
     * but it returns a boolean value instead of a CollisionFace.
     */
    bool is_touching_bool(const CollisionObject* other) const;
```
`CollisionFace `es un enum que indica de que lado fue tocado mi objecto con respecto al otro. Esto es util para diferenciar collisiones entre paredes, suelos, etc
Hay objectos (como en balas e items) donde no es importante saber donde fue tocado sino que solo importa que haya ocurrido una colision.

### Abstraccion de Collision Object

 ```cpp
virtual void handle_colision(CollisionObject* other) = 0;
```
Este metodo es virtual puro porque CollisionObject no se debe poder instanciar en cualquier momento, el CollisionObject es la clase padre de todos los componentes del juego en donde todos sus clases hijos deben _handelear_ sus colisiones (dar la logica e indicar que ocurre cuando son colisionados). Hasta el momento hay solo 2 tipos:
- `Dyanmic_body`
- `Static_body`

### Collision Objects - Static Body
Static Body consiste en objetos que no se registra su movimiento y tampoco son movidos ó desaparecen.

### Collision Objects - Dyanmic Body
Dynamic Body consiste en objects que tienen movimiento (tanto horizontal como vertical), por lo tanto tienen el atributo:
```cpp 
Vector2D velocity;
```
Como los dyanmic bodies se mueven, se debe poder actualizar sus valores de posicion y/o velocidad, por lo tanto, tambien tienen una funcion virtual llamada:
```cpp
virtual void update_body();
```
Cuando se desee crear un objecto que se puede mover se debe implementar esta funcion sino nunca se actualizará sus valores de posicion / movimiento


### Collision Manager
Como vimos hasta el momento, todo es un CollisionObject, todo debe tener collisiones, etc. Pero aca viene la parte interesante ...

**¿Como se _detectan_ las colisiones?** --> A traves del `CollisionManager` !

El CollisionManager tiene como funcion recibir CollisionObjects, colocarlo en una grilla (luego explico como es la grilla) y activar los metodos de handle_collision cuando detecta una collision entre 2 objectos.

Principalmente detecta las colisiones de todos los objectos dinamicos. Si fuese a detectar cada colision de cada objeto, esto haria que el engine funcione muy pobre, por lo tanto decidí solo _trackear_ las colisiones de dynamicBodies y los StaticBodies solo estarán ahi para ser detectados.

### Collision Manager - Grid & Deteccion de Collisiones
La grilla del collisionManager es de la siguiente manera:
```cpp
std::vector<std::vector<std::shared_ptr<CollisionObject>>> grid;
```

Es una matriz de shared pointers de CollisionObjects, en donde cada celda de la grilla indica 
un pixel del juego. Al colocar un objecto en la grilla, en realidad estamos colocando en las posiciones desde (x ,y ) hasta (x+w , x+h ) shared pointers al mismo collision Object

Luego el CollisionManager realiza detecciones de los objetos Dyanmicos iterando alrededor de sus celdas y viendo si da nullpointer (no se detecto un objecto) o un shared pointer de otro CollisionObject (tanto statico o dyanmico). Al detectar una collision realiza un **double dispatch** donde se llama los metodos de handeleo de collisiones de ambos objectos detectas.

### Collision Manager - Detectar muchisimos bodies

Para nuestro juego, vamos a tener personajes (dyanmic bodies) que disparan desde sus armas distintas bullets (tambien dyanmic bodies), pero ... ¿El collision Manager no se va a realentizar al traquear tantos objetos? NO

con el metodo: 
```cpp
 void remove_inactive_bodies();
```
el collisionManager se ocupara de deshacerse de todos los bodies marcados como inactivos y serán quitadas del collisionManager.

### Collision Manager - Usos

Se utiliza como atributo en la clase `Match` que lo utiliza para:
- Cargar las colisiones de plataformas del mapa de una partida
- Traquear los movimientos de players, enemigos, items & balas en la partida 

Al cargar un mapa, se debe utilizar las funciones 
```cpp
void add_object(std::shared_ptr<StaticBody> obj);

void prepare_map();
```
`add_object` permite agregar objectos estaticos al collisionManager y luego, la funcion `prepare_map` realiza una limpeza de las collisiones desactivando collisiones inecesarias entre objectos para evitar problemas de paredes invisibles y problemas raras debido a como se creo el custom map.

Al insertar un player/enemy/item a la partida ó respawnearlo, se debe avisar al collisionManager con la funcion: 
```cpp
void track_dynamic_body(std::shared_ptr<DynamicBody> obj);
```

## Client

## Server

### Game Logic
Consiste en toda la logica realcionado con el juego en si, personajes, items, cheats, logica de las partidas, etc ...

### Game Logic - Componentes

Para nuestra logica de juego, con el uso de lo creado en Physics_Engine logramos crear varios tipos de componentes de juego, a continuacion explicaremos brevemente cada uno y como funciona

**Characters**
Para el juego, decidimos crear 2 tipos de characteres, `Players` & `Enemies`

Los Players son los jugadores de las partidas y los clientes pueden ejecutar distitnos tipos de acciones como mover izquierda/derecha, saltar ó disparar

Luego, tenemos los Enemies, que consta de characteres que van a tratar de atacar players que detecten, su movimiento es limitado (solo pudiendo mover izquiera o derecha) y caminan por determinado rango de de espacio

la clases Player & Enemy son clases padre para luego poder crear los distintos tipos de players y enemies.

**Tipos de Players:**
- Jazz
- Spaz
- Lori

**Tipos de Enemies:**
- Mad Hatter 
- Lizard Goon 

**Weapons**

Todos los Jugadores tienen 4 tipos de armas, donde cada uno tiene distitnos tipos de daño, velocidad, frecuencia de disparo y cantidad de ammunicion maxima (con excepcion de una arma que tiene ammo infinita)

Al disparar distitnos player o enemigos, el player recibirá puntos y si logra matar a un enemigo o player recibe puntos bonus.

**Collectables**

Los collecatables son los items del juego, constan de estos tipos:

**Ammo:**

Items que recargan la ammunicion de las armas, de esta clase, hay 3 clases hijos que representan distitnos tipos de Ammo de Armas
- AmmoGunOne
- AmmoGunTwo
- AmmoGunThree

**Health_items:**

Items que recuperan vida de los players, hasta el momento solo tenemos el item:
-  Meat

**Treasure:**

Items que da puntos al jugador que lo collecciona
item:
- Coin

**LA ZANAHORIA**

La zanahoria es un item _raro_ que no cae bajo una categoria en particular que hace lo siguiente.
Cuando un player lo colecciona, tiene 1/2 chance de ser intoxicado o tener invincibilidad por cierta cantidad de tiempo

- Al ser intoxicado, el jugador se moverá mas lento, no podrá saltar ni tampoco va a poder disparar.
- AL ser invincible al ser atacado por algun enemigo, player, etc no recibirá daño


**Platform**
El unico Platform hasta el momento, es el `Box_Platform` que consiste en bloques con Collision.


### GameLoop

El MatchesManager al recibir un mensaje del cliente de crear partida, lanza el hilo Match que es el game loop en sí, y añade al jugador a la partida. La Match puede continuar incluso si se van todos los jugadores, y pueden conectarse en cualquier momento cualquier jugador hasta que termine. La partida solo finaliza al llegar a cero el contador de partida, y tiene como límite una cantidad de jugadores que pueden unirse determinado por la configuracion del juego asignada en config.yaml.
Está configurada la partida para correr el juego a 60 fps, y se manda un estado de la partida por loop al cliente para poder renderizarla.
La partida además de los jugadores que pueden realizarse daño entre sí, contiene enemigos que patrullan de un lado a otro y realizan daño si haces contacto con ellos, aplicando también un knockback. Si los matas consigues puntos al igual que matar otro jugador (tambien puede configurarse estos valores en el confi.yaml).


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
