# Zelda Rogue

Zelda Rogue es un juego de aventura por texto inspirado en la saga The Legend of Zelda y en los clásicos roguelike. El mundo, las aldeas, mazmorras e ítems se generan de forma aleatoria en cada partida.

## Estructura del Proyecto

```bash
.
├── build/ # Archivos objeto y ejecutables generados
├── src/ # Código fuente principal
│ ├── game/ # Lógica del juego
│ │ ├── game.c/h
│ │ ├── player/
│ │ ├── world/
│ │ │ ├── dungeon/
│ │ │ ├── items/
│ │ │ └── village/
│ │ └── world.c/h
│ ├── main.c # Punto de entrada del juego
│ ├── test.c # Pruebas unitarias
│ └── utils/ # Utilidades generales
├── Makefile # Script de compilación
└── README.md # Este archivo
```

## Compilación

Para compilar el juego, simplemente ejecuta:

```sh
make
```

Esto generará el ejecutable en `build/zelda_rogue.o`.

## Ejecución

Para ejecutar el juego:

```sh
make run
```

O directamente:

```sh
./build/zelda_rogue.o
```

## Pruebas

Para compilar y ejecutar los tests (si tienes implementados en `test.c`):

```sh
make test
```

## Clean Up

Para borrar el build

```sh
make clean
```

## Cómo Jugar

Al iniciar el juego, se te pedirá el número de aldeas a generar. El objetivo es derrotar todas las mazmorras de ambos mundos.

### Comandos disponibles en una aldea:

- `busq` : Buscar ítem oculto en la aldea o recibir una pista.
- `maz` : Ir a la mazmorra asociada a la aldea.
- `compr` : Acceder a la tienda (recuperar vida, comprar ítem de la primera mazmorra, o aumentar vida máxima).
- `trans` : Transportarse al mundo paralelo (si está desbloqueado).
- `ant` : Ir a la aldea anterior.
- `sig` : Ir a la aldea siguiente.

### Comandos disponibles en una mazmorra:

- `busq` : Buscar ítem oculto o encontrar dinero.
- `atac` : Atacar la mazmorra (requiere el ítem correcto).
- `ant` : Volver a la aldea.
- `sig` : Ir a la siguiente aldea.

### Objetivo

- Derrota las mazmorras necesarias para desbloquear el mundo paralelo.
- Derrota todas las mazmorras de ambos mundos para ganar.
- Si pierdes todas tus vidas, el juego termina.

## Créditos

- Proyecto académico para la materia CI-3825: Sistemas de Operación I.

---

¡Diviértete explorando y derrotando mazmorras en Zelda Rogue!
