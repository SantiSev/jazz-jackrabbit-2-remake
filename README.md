# tp-final-veiga (Jazz Jackrabbit 2)

## Participants

- Maximo Damian Utrera - 109651 - <mutrera@fi.uba.ar>
- Agustín Barbalase - 109071 - <abarbalase@fi.uba.ar>
- Santiago Sevitz - 107520 - <ssevitz@fi.uba.ar>
- Nicolas Ramiro Sanchez - 99872 - <nrsanchez@fi.uba.ar>

## Librerias externas

### Librerias externas: Threads

Este trabajo practico utiliza librerias externas provistas por la Catedra de Taller de programacion I (Veiga) FIUBA
(eldipa). Cuyo codigo, esta bajo la licencia: GPL v2. Dichas librerias implementan Threads y Queues (thread-safe)
[https://github.com/eldipa/hands-on-threads](https://github.com/eldipa/hands-on-threads)

### Librerias externas: Sockets

Este trabajo practico utiliza librerias externas provistas por la Catedra de Taller de programacion I (Veiga) FIUBA
(eldipa). Cuyo codigo, esta bajo la licencia: GPL v2. Dichas librerias implementan Sockets en C++ para ser utilizados
con un protocolo en particular. El link al repositorio es:
[https://github.com/eldipa/sockets-en-cpp](https://github.com/eldipa/sockets-en-cpp)

## Game requirements

```bash
sudo apt install -y \
libsdl2-dev \
libsdl2-image-dev \
libsdl2-ttf-dev \
libsdl2-mixer-dev \
libyaml-cpp-dev \
cmake \
catch2
```

Para instalar y compilar el juego se puede usar el script `build.sh`, con el comando `./build.sh -debug log`

Esta secuencia compilara dos archivos: `server` y `client`. Para ejecutar `server` es

```bash
./server <port>
```

Para ejecutar uno o varios `client` es

```bash
./client <servname> <port>
```

## Devs requirements

```bash
sudo apt install -y \
pre-commit \
cppcheck \
valgrind

pre-commit install

TIBURONCIN_SRC="https://github.com/eldipa/tiburoncin.git"

install_tiburoncin() {
  git clone $TIBURONCIN_SRC > /dev/null
  cd tiburoncin
  make 1> /dev/null
  sudo cp tiburoncin /usr/bin/
  cd ..
  rm -rf tiburoncin
}
```

```txt
How to run tests:
Antes que nada, hace

 1. Hacer build del proyecto
 2. Entrar a la carpeta cmake-build-debug & ejectutar "./tests" 
    <br> En caso de ejecutar una sola prueba, debe ingresar el nombre de su prueba como argumento

En caso de querer agregar mas archivos de pruebas, coloquelos en el Cmake File de la carpeta tests
```

## Valgrind notes

Valgrind detectara falsos positivos relacionados a la libreria SDL2, ya que deja memoria sin liberar
pero que luego esta se libera al cerrar la aplicacion por el sistema operativo.

Para suprimirlos primero generar archivo valgrind.log y procesarlo con el script valgrind_to_suppressions.py. Una
vez hecho eso simplemente correr valgrind con el archivo de supresiones generado.

```bash
valgrind --leak-check=full --show-leak-kinds=all --gen-suppressions=all --log-file=valgrind.log ./program
python3 valgrind_to_suppressions.py valgrind.log suppressions.supp
valgrind --leak-check=full --suppressions=suppressions.supp --your-other-flags ./program
```
