# Project manual

## Indice

- Integrantes
- Distribucion
- Organizacion
- Librerias externas

## Integrantes

Los integrantes del proyecto son:

- [Maximo Damian Utrera](https://github.com/maxogod) (Maxo) - 109651 - <mutrera@fi.uba.ar>
- [Agustín Barbalase](https://github.com/agustinbarbalase) (Agus) - 109071 - <abarbalase@fi.uba.ar>
- [Santiago Sevitz](https://github.com/SantiSev) (Santi) - 107520 - <ssevitz@fi.uba.ar>
- [Nicolas Ramiro Sanchez](https://github.com/nrsanchezfiuba) (Niko) - 99872 - <nrsanchez@fi.uba.ar>

El corrector de este trabajo práctico es:

- [Martin Di Paola](https://github.com/eldipa) (eldipa) - <martinp.dipaola@gmail.com>

## Distribucion

Aqui se prensenta la distribucion de cada parte, para mas informacion acerca de cada parte, revisar la
[Documentacion](./documentation.md)

| Integrante | Parte principal |
|------------|-----------------|
| Maxo       | Graphics engine, Client & Map Editor          |
| Agus       | Protocol & Sound        |
| Santi      | Physics engine & Game logic |
| Niko       | Server, Commands & States logic          |

## Organizacion

### Semana 1

- Planificacion

### Semana 2

- Planificacion

### Semana 3

- Implementacion del Graphics engine
- Implementacion del Protocol
- Implementacion del Physics engine
- Implementacion del Server

### Semana 4

- Implementacion del Client & retoques de Graphics engine
- Implementacion del Protocol
- Implementacion del Game logic & retoques de Physics engine
- Implementacion del Server & states

### Semana 5

- Mejoras del Client & Server
- Integracion y testeo
- Arreglando bugs
- Implementacion de editor de mapas

### Semana 6

- Integracion, testeo & mejoras
- Arreglando bugs
- Documentacion

## Librerias externas

La lista de liberias externas es la siguiente:

- libsdl2-dev
- libsdl2-image-dev
- libsdl2-ttf-dev
- libsdl2-mixer-dev
- libyaml-cpp-dev

### Sockets

Este trabajo practico utiliza librerias externas provistas por la Catedra de Taller de programacion I (Veiga) FIUBA
(eldipa). Cuyo codigo, esta bajo la licencia: GPL v2. Dichas librerias implementan Sockets en C++ para ser utilizados
con un protocolo en particular. El link al repositorio es:
[https://github.com/eldipa/sockets-en-cpp](https://github.com/eldipa/sockets-en-cpp)

### Threads

Este trabajo practico utiliza librerias externas provistas por la Catedra de Taller de programacion I (Veiga) FIUBA
(eldipa). Cuyo codigo, esta bajo la licencia: GPL v2. Dichas librerias implementan Threads y Queues (thread-safe)
[https://github.com/eldipa/hands-on-threads](https://github.com/eldipa/hands-on-threads)

### Testing

Para el testeo se usaron las siguientes librerias y programas:

- valgrind: Testeo de memoria
- catch2: Testeo del Physics engine
- tiburoncin: Testeo del Protocol

### Tiburoncin

Este trabajo practico utiliza el programa provisto por la Catedra de Taller de programacion I (Veiga) FIUBA
(eldipa). Cuyo codigo, esta bajo la licencia: GPL v3.0. El link al repositorio es:
[https://github.com/eldipa/tiburoncin](https://github.com/eldipa/tiburoncin). Para su instalacion, revisar el
[Manual de usuario](./user_manual.md)
