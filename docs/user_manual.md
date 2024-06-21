# User manual

## Indice

- Entorno
- Compilacion y uso
- Usabilidad del juego

## Entorno

Para la compilacion y uso del projecto dentro de un entorno Linux, necesitamos un kit de herramientas basicas. A contiunacion,
proveemos un comando, para aquel que quiera usar este projecto dentro de un entorno Linux:

```bash
$ sudo apt-get update
$ sudo apt-get install \
    make \
    git \
    gcc \
    g++ \
    gdb \
    build-essential \
    unzip \
    cmake
```

### Instalacion de librerias externas

Para la instalacion de librerias externas, se debe correr el siguiente comando:

```bash
sudo apt install -y \
  libsdl2-dev \
  libsdl2-image-dev \
  libsdl2-ttf-dev \
  libsdl2-mixer-dev \
  libyaml-cpp-dev \
```

Para la instalacion de las librerias relacionadas con el testing, se debe correr el siguiente comando:

```bash
sudo apt install -y \
  valgrind \
  catch2
```

Para la instalacion de [tiburoncin](https://github.com/eldipa/tiburoncin), se debe correr los siguientes comandos:

```bash
$ git clone https://github.com/eldipa/tiburoncin.git
$ cd tiburoncin
$ make
$ sudo cp tiburoncin /usr/bin/
$ cd ..
$ rm -rf tiburoncin
```

## Compilacion y uso

Para compilar a el juego se debe hacer:

```bash
$ mkdir ./build
$ cd ./build
$ cmake .. -DPRODUCTION=ON
$ make
```

Sin embargo, se provee un script para compilar el juego con el script `build.sh`, con el comando `./build.sh -debug log`

Esta secuencia compilara dos archivos: `server` y `client`. Para ejecutar `server` es

```bash
./server <port>
```

Mientras que, para ejecutar uno o varios `client` es

```bash
./client <servname> <port>
```

## Usabilidad del juego

Dentro del menu del juego, existen cuatro opciones:

1. Crear un partida
2. Unirse a un partida
3. Editar un mapa
4. Salir del juego

### Crear un partida y unirse a una partida

Tanto crear, como unirse a un partida, permite elegir uno de tres personajes que son:

- Jazz
- Spaz
- Lori

Cuando se crea una partida, te permite elegir un mapa, ya sea los default o los creados por el usuario. Mientras que,
unirse a una partida, permite elegir a que partida unirse.

Dentro del juego, los movimientos y sus correspondientes teclas son:

- Mover a izquierda (a)
- Mover a derecha (d)
- Saltar (space)
- Disparar (click izquierdo)
- Cambiar de arma (e)
