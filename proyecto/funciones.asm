section .text

    global contarCaracteres
    ; Función obligatoria 1: contarCaracteres
    ; Recibe desde C:
    ; RCX = Dirección inicial del mapa (char*)
    ; RDX = Número total de celdas (int)
    ; R8B = Carácter que se desea contar (char de 8 bits)
    ; Retorna:
    ; RAX = Cantidad de veces que aparece el carácter
contarCaracteres:
    xor rax, rax      ; Inicializamos el contador en 0
    xor r9, r9        ; Inicializamos el índice en 0

.ciclo_contar:
    cmp r9, rdx       ; Comparamos el índice actual con el total de celdas
    jge .fin_contar   ; Si el índice >= totalCeldas, terminamos el ciclo
    
    mov r10b, byte [rcx + r9] ; Leemos 1 byte (un carácter) del mapa
    cmp r10b, r8b     ; Es igual al carácter que estamos buscando?
    jne .siguiente_contar
    inc rax           ; Si es igual, incrementamos nuestro contador

.siguiente_contar:
    inc r9            ; Avanzamos a la siguiente celda
    jmp .ciclo_contar ; Repetimos el ciclo

.fin_contar:
    ret               ; Retornamos el total 

;-------------------------------------------------------------------------------------------
    global validarMovimiento
    ; Función obligatoria 2: validarMovimiento
    ; validarMovimiento(int*  mapa,int columnas, int nuevaFila, int nuevaColumna)
    ; RCX = puntero al mapa
    ; RDX = columnas (60)
    ; R8 = nuevaFila
    ;R9 = nuevaColumna

validarMovimiento:
    ;calcular el indice del mapa
    mov rax, r8 ;nuevaFila
    imul rax, rdx ;nuevaFila * columnas
    add rax, r9 ;nuevaFila * columnas + nuevaColumna
    ;Leemos el valor en esa posicion de memoria
    mov r10b, byte [rcx + rax]
    ;Si el valor es '#', es una pared, retornamos 0 (movimiento no valido)
    cmp r10b, 35 ;ASCII de '#'
    je .movimiento_invalido
    ;Si no es '#', el movimiento es valido, retornamos 1
    mov eax, 1
    ret

.movimiento_invalido:
    mov rax, 0
    ret

;-------------------------------------------------------------------------------------------
global calcularPuntaje
    ; Función obligatoria 3: calcular puntaje
    ; Recibe desde C en arquitectura x64 (Windows):
    ; RCX = Monedas recolectadas (int)
    ; RDX = Pasos realizados (int)
    ; R8  = Niveles completados (int)
    ; Retorna:
    ; RAX = Puntaje final calculado

calcularPuntaje:
    ; Fórmula de puntaje: (Monedas * 100) - Pasos + (Niveles * 500)
    mov rax, rcx        ; RAX = Monedas recolectadas
    imul rax, 100       ; RAX = Monedas * 100
    sub rax, rdx        ; RAX = (Monedas * 100) - Pasos
    mov r9, r8          ; R9 = Niveles completados
    imul r9, 500        ; R9 = Niveles * 500
    add rax, r9         ; RAX = puntaje + bonificacion por niveles
    cmp rax, 0          ; Si rax >= 0, terminar
    jge .finPuntaje
    mov rax, 0          ; RAX = 0 (puntaje negativo
    
    .finPuntaje:
    ret                 ; Retornamos el puntaje final

;-------------------------------------------------------------------------------------------
global detectarObjeto
    ; Función obligatoria 4: detectarObjeto
    ; Recibe desde C 5 parámetros:
    ; RCX = Dirección inicial del mapa (char*)
    ; RDX = Número de columnas (int)
    ; R8  = Fila a revisar (int)
    ; R9  = Columna a revisar (int)
    ; [rsp + 40] = Objeto a buscar 
    ; Retorna:
    ; RAX = 1 si el objeto está, 0 si no está.

detectarObjeto:
    ; Guardamos el objeto a buscar en r10b
    mov r10b, byte [rsp + 40] ; Objeto a buscar (

    ; Calculamos el índice del mapa
    mov rax, r8 ; Fila a revisar
    imul rax, rdx ; Fila a revisar * columnas
    add rax, r9 ; Fila a revisar * columnas + Columna a revisar

    ; Leemos el valor en esa posición de memoria
    mov r11b, byte [rcx + rax]

    ; Comparamos el valor con el objeto a buscar
    cmp r11b, r10b
    je .objetoEncontrado ; Si es igual, el objeto está presente

.objetoNoEncontrado:
    mov rax, 0 ; Retornamos 0 (objeto no encontrado)        
    ret

.objetoEncontrado:
    mov rax, 1 ; Retornamos 1 (objeto encontrado)   
    ret

;-------------------------------------------------------------------------------------------
    global contarCeldasLibres
    ; Función obligatoria 5: contar celdas libres
    ; Recibe desde C:
    ; RCX = Dirección inicial del mapa (char*)
    ; RDX = Número total de celdas (int)
    ; Retorna:
    ; RAX = Cantidad de celdas libres ('.')

contarCeldasLibres:
    xor rax, rax      ; Inicializamos el contador en 0
    xor r9, r9        ; Inicializamos el índice en 0

    .cicloLibres:
    cmp r9, rdx       ; Comparamos el índice actual con el total de celdas
    jge .finLibres    ; Si el índice >= totalCeldas, terminamos el ciclo
    
    mov r10b, byte [rcx + r9] ; Leemos 1 byte (un carácter) del mapa
    cmp r10b, 46      ; Es igual a '.'?
    jne .siguiente_libre
    inc rax           ; Si es igual, incrementamos nuestro contador

.siguiente_libre:
    inc r9            ; Avanzamos a la siguiente celda
    jmp .cicloLibres  ; Repetimos el ciclo

.finLibres:
    ret               ; Retornamos el total 

;-------------------------------------------------------------------------------------------
