# Capítulo 5

Respuestas capitulo 5

Integrantes: Pablo Andrés Barona 1831316, Julián David Sánchez 1827112, Santiago Ramírez Ruiz 1831310

## 1.
Archivo: [p1.c](p1.c)
el valor de la variable en el proceso hijo, es el mismo que en el proceso padre al inicio, sin embargo, al ser procesos independientes, las variables también lo son, es decir, cada uno tiene su propia variable X.

## 2.
Archivo: [p2.c](p2.c)
No, solo el padre logra acceder al descriptor retornado por el open(), puesto que este fue abierto en el proceso padre, no en el hijo, si se intenta escribir en ambos procesos el mismo archivo al mismo tiempo, dependiendo del método de escritura usado puede que se sobreescriba el archivo o se agregue al final del archivo lo que sea que se escriba a este.

## 3.
Archivo: [p3.c](p3.c)
Si se puede, por lo general se llamaría la función "delay", pero esta no aparece en las librerías de Linux, así que llamamos a la función "sleep", que cumple la misma función del delay, al generar una espera (esto es válido solo si se conoce el tiempo de ejecución del proceso a esperar).

## 4.
Archivo: [p4.c](p4.c)
Cada variación de la llamada exec() tiene un tipo de uso específico para el cual fue escrita, sin embargo puede usarse casi cualquiera de sus variaciones en cualquier caso con algunas modificaciones.

## 5.
Archivo: [p5.c](p5.c)
La función wait retorna el PID del proceso hijo cuando este cambia de estado, si se usa "wait()" en un proceso hijo, que no posee a su vez ningún otro proceso hijo, el wait recibe un -1, ya que no existe proceso hijo al cual esperar, por lo cual no se genera ninguna espera.

## 6.
Archivo: [p6.c](p6.c)
Es útil usar "waitpid" cuando se desea que el proceso espere que finalice otro proceso que no es necesariamente un proceso hijo, creado mediante un fork, pues con este método se puede esperar cualquier proceso específico que se desee.

## 7.
Archivo: [p7.c](p7.c)
No se logra imprimir nada, puesto que el stream de salida del proceso ha sido cerrado mediante la llamada de “close(STDOUT_FILENO);”.
