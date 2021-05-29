Objetivo:
Este trabajo consiste en realizar un juego del tipo plataformas logrando que un personaje se mueva y salte a través de los pisos, evadiendo enemigos y llegando a la puerta de salida antes de que finalice un tiempo preestablecido, aplicando en código los conceptos estudiados de pilas y colas. 

Funcionalidad:
Las plataformas pueden ser atravesados por el player de abajo hacia arriba con la opción de salto. Las plataformas solo se pueden subir una a una. No se puede volver a plataformas inferiores.
El player inicia el juego en el piso cero (0) y debe finalizar el juego colisionando con la puerta de salida que está ubicada en el piso seis (6).
Colocar un contador en reversa de treinta (30) segundos (límite para alcanzar el objetivo).
Colocar los enemigos en cada piso. Los enemigos se desplazan de derecha a izquierda o viceversa. Máximo de enemigos por piso: cuatro (4).
Un solo enemigo a la vez puede desplazarse en un piso. Cuando ese enemigo termine de desplazarse recién ahí inicia el desplazamiento de otro.
Aplicar en tres (3) pisos a los enemigos la siguiente funcionalidad de colas, emplear una cola para insertarle como nodos Sprites de los enemigos.
Cuando el player es tocado por algún enemigo, este debe caer hasta el piso cero 0.
Las condiciones de fin de juego son dos:
- Tiempo en cero (0), derrota.
- Colisionar contra la puerta de salida, victoria.

Representación visual de la cola en un piso:
![image](https://user-images.githubusercontent.com/83043304/120076726-77e6ee00-c07d-11eb-8b56-ab2124d76c89.png)

A medida que el tiempo avanza, se producen los siguientes estados o pasos:
![image](https://user-images.githubusercontent.com/83043304/120076732-7e756580-c07d-11eb-843f-79d6d62a2a9a.png)

Estado 1: El enemigo del nodo apuntado como primero se quita de la cola y avanza por el piso.
Estado 2: El enemigo llega al final de la pantalla, para este caso la izquierda.
Estado 3: Simulando la entrada desde la derecha, este enemigo se inserta nuevamente en la  cola.
Estos tres pasos se repiten con cada uno de los enemigos del piso.

En los pisos restantes agregar la funcionalidad de pilas, en este caso empleando dos (2) pilas en las cuales se insertarán como valor los Sprites de los enemigos.
Representación del estado inicial de las pilas en un piso:
![image](https://user-images.githubusercontent.com/83043304/120076739-8503dd00-c07d-11eb-9819-60a29c90363a.png)

A medida que el tiempo avanza se van produciendo los siguientes estados:
![image](https://user-images.githubusercontent.com/83043304/120076744-8a612780-c07d-11eb-911d-82283158d581.png)

Estado 1: El enemigo que se ubica al tope de la pila 2 se mueve de derecha a izquierda.
Estado 2: Cuando el enemigo llega al final de la pantalla, se ubica como nodo en la pila 1. Luego se repiten el estado 1 y 2 para cada uno de los enemigos restantes de la misma pila.
Estado 3: Todos los enemigos deben finalizar como nodos de la pila 1. Cuando esto ocurre, se repiten los estados de 1 a 3 pero, en esta caso para regresarlos a la pila original.
