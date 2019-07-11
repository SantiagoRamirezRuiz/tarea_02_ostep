# Shell
Archivo: [shellJPS.c](shellJPS.c)

Shell básico

Integrantes: Pablo Andrés Barona 1831316, Julián David Sánchez 1827112, Santiago Ramírez Ruiz 1831310

## Compilación
Para compilar el shell, que tiene por nombre "shellJPS.c" se debe primero tener las librerías disponibles, en linux mint la unica libreria que tenemos conocimiento que requiere ser agregada es "libreadline-dev", la cual se puede instalar con el siguiente comando:

```
sudo apt-get install libreadline-dev
```

Y para la compilación se debe usar el siguiente comando:

```
gcc shellJPS.c -L/usr/include -lreadline -o shellJPS
```

## Ejecución del shell
La ejecución del shell es igual a la de cualquier otro programa en C:

```
./shellJPS
```

Una vez dentro del shell se puede usar el comando "help" para obtener información sobre el shell y los comandos disponibles para usar.

