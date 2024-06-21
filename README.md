# tp-final-veiga (Jazz Jackrabbit 2)

## Integrantes

Los integrantes del proyecto son:

- [Maximo Damian Utrera](https://github.com/maxogod) (Maxo) - 109651 - <mutrera@fi.uba.ar>
- [Agustín Barbalase](https://github.com/agustinbarbalase) (Agus) - 109071 - <abarbalase@fi.uba.ar>
- [Santiago Sevitz](https://github.com/SantiSev) (Santi) - 107520 - <ssevitz@fi.uba.ar>
- [Nicolas Ramiro Sanchez](https://github.com/nrsanchezfiuba) (Niko) - 99872 - <nrsanchez@fi.uba.ar>

El corrector de este trabajo práctico es:

- [Martin Di Paola](https://github.com/eldipa) (eldipa) - <martinp.dipaola@gmail.com>

## Informacion del projecto

- [Documentacion tecnica](./docs/documentation.md)
- [Manual de projecto](./docs/project_manual.md)
- [Manual de usuario](./docs/user_manual.md)

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
