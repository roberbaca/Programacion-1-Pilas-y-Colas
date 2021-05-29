Este trabajo consiste en realizar un juego del tipo plataformas, aplicando en código los conceptos estudiados de pilas y colas.

Objetivo:
Realizar el juego logrando que un personaje se mueva y salte a través de los pisos, evadiendo enemigos y llegando a la puerta de salida antes de que finalice un tiempo preestablecido.

Funcionalidad:
Crear seis (6) plataformas por donde nuestro personaje pueda desplazarse.
Las plataformas pueden ser atravesados por el player de abajo hacia arriba con la opción de salto. Las plataformas solo se pueden subir una a una. No se puede volver a plataformas inferiores.
El player inicia el juego en el piso cero (0) y debe finalizar el juego colisionando con la puerta de salida que está ubicada en el piso seis (6).
Colocar un contador en reversa de treinta (30) segundos (límite para alcanzar el objetivo).
Colocar los enemigos en cada piso. Los enemigos se desplazan de derecha a izquierda o viceversa. Máximo de enemigos por piso: cuatro (4).
Un solo enemigo a la vez puede desplazarse en un piso. Cuando ese enemigo termine de desplazarse recién ahí inicia el desplazamiento de otro.
Aplicar en tres (3) pisos a los enemigos la siguiente funcionalidad de colas, emplear una cola para insertarle como nodos Sprites de los enemigos.
Cuando el player es tocado por algún enemigo, este debe caer hasta el piso cero 0.
Las condiciones de fin de juego son dos:
Tiempo en cero (0), derrota.
Colisionar contra la puerta de salida, victoria.

Representación visual de la cola en un piso:

