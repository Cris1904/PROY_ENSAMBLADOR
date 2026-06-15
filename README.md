# BitQuest - Proyecto Final de Lenguaje Ensamblador

**Materia:** Lenguaje Ensamblador  
**Maestro:** Irving Cardona Camacho  
**Grado y Grupo:** 4A  
**Fecha de Entrega:** Lunes 15 de junio de 2026  

### Integrantes del Equipo:
* Lopez Acevedo Tania Jaquelin
* Duron Mendoza Antonio
* Raygoza Castañeda Ulises
* Vázquez Delgado Cristian de Jesús

---

## 🎮 Descripción del Proyecto
**BitQuest** es un videojuego de aventura en consola desarrollado de manera híbrida utilizando el lenguaje **C** para la lógica estructurada, menús e interfaz de usuario, y **Lenguaje Ensamblador (NASM x64)** para optimizar funciones críticas de procesamiento del mapa, cálculos de puntaje y detección de objetos.

El juego consta de 3 niveles en los que el jugador debe moverse estratégicamente a través de un mapa de 60x60 celdas recopilando monedas, recolectando llave para abrir puertas y buscando la salida con el menor número de pasos posibles.

---

## 🛠️ Requisitos del Sistema
Para compilar y ejecutar este proyecto de forma nativa en Windows (x64), es necesario contar con las siguientes herramientas instaladas y configuradas en las variables de entorno (`PATH`):
1. **NASM:** Compilador para el código en ensamblador (`funciones.asm`).
2. **GCC (MinGW-w64):** Compilador de C para enlazar el código e interactuar con la API de Windows.

---

## 🚀 Compilación y Ejecución (Automatizada)

El proyecto incluye un script de automatización por lotes llamado `compile.bat` que simplifica todo el proceso de compilación, enlazado y ejecución en un solo comando.

### Instrucciones de Uso:

1. Abra una terminal de comandos de Windows (`cmd`) en la carpeta raíz del proyecto.
2. Ejecute el siguiente comando:
   "compile.bat"
   o en su caso
   ".\compile.bat"
   dependiendo de la terminal abierte