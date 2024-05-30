# Tp_final_Veiga

## Game requirements

```bash
sudo apt install -y \
libsdl2-dev \
libsdl2-image-dev \
libsdl2-ttf-dev \
libsdl2-mixer-dev \
cmake
```

## Devs requirements

```bash
sudo apt install \
pre-commit \
cppcheck

pre-commit install
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