# Comparativa BFS vs DFS

Este repositorio presenta una comparativa de rendimiento entre dos algoritmos fundamentales de recorrido de grafos: **Breadth-First Search (BFS)** y **Depth-First Search (DFS)**. El objetivo principal del proyecto es analizar el comportamiento de ambos enfoques al determinar todos los nodos alcanzables a partir de un nodo inicial, evaluando aspectos como el tiempo de ejecución, el uso de memoria y la eficiencia en distintos escenarios.

El proyecto está diseñado como una herramienta experimental y educativa que permite entender en profundidad las diferencias prácticas entre BFS y DFS más allá de la teoría clásica. Mientras BFS explora el grafo por niveles, garantizando encontrar la ruta más corta en grafos no ponderados, DFS profundiza en cada rama antes de retroceder, lo que puede resultar más eficiente en ciertos contextos, especialmente cuando la solución se encuentra lejos del nodo raíz.

La implementación está escrita en C++, haciendo uso de bibliotecas modernas para facilitar la concurrencia y la configuración. En particular, se emplea **Taskflow** para gestionar tareas paralelas de forma eficiente, lo que permite explorar mejoras de rendimiento en ejecuciones concurrentes, y **toml++** para la gestión de configuraciones mediante archivos TOML, ofreciendo flexibilidad a la hora de ajustar parámetros sin necesidad de recompilar.

Este repositorio no solo busca comparar resultados, sino también servir como base para experimentación. Está pensado para ser fácilmente extensible, permitiendo añadir nuevos algoritmos, modificar estructuras de datos o introducir variaciones en los grafos utilizados para las pruebas. Esto lo convierte en una herramienta útil tanto para aprendizaje como para investigación ligera en algoritmos.

## Dependencias

El proyecto depende de las siguientes librerías externas:

- **Taskflow (C++)**: utilizada para la ejecución de tareas en paralelo y la experimentación con concurrencia.
- **toml++**: utilizada para parsear archivos de configuración en formato TOML.

Ambas dependencias son ligeras, y se integran fácilmente en el flujo de compilación.

## Compilación

La compilación del proyecto es sencilla y sigue un flujo estándar basado en CMake.

Pasos:

1. Clonar el repositorio  
2. Crear un directorio de build  
3. Ejecutar CMake  
4. Compilar con `make`  

Ejemplo:

```bash
git clone <repo_url>
cd <repo>
mkdir build
cd build
cmake ..
make # (Linux)
```

En Windows, el proceso es similar, pero se recomienda utilizar Visual Studio para generar y compilar el proyecto. Aunque no es estrictamente obligatorio, facilita considerablemente la configuración y compilación, especialmente si no se tiene experiencia previa con entornos de construcción en Windows. CMake generará automáticamente una solución compatible con Visual Studio que puede abrirse y compilarse desde el IDE.

## Uso

Una vez compilado, el ejecutable permitirá lanzar pruebas comparativas entre BFS y DFS utilizando los parámetros definidos en los archivos de configuración. Estos parámetros pueden incluir el tamaño del grafo, el tipo de estructura, el nodo inicial y otras variables relevantes para el análisis.

El uso de archivos TOML permite modificar fácilmente estos parámetros sin necesidad de recompilar, lo que agiliza la experimentación.

## Licencia

Este proyecto está bajo la licencia MIT. Esto significa que puedes usar, copiar, modificar y distribuir el software libremente, incluso para fines comerciales, siempre que se incluya la licencia original en cualquier copia del software.
