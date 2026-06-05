section .text

    global validarMovimiento
    ;validarMovimiento(int*  mapa,int columnas, int nuevaFila, int nuevaColumna)
    ;RCX = puntero al mapa
    ;RDX = columnas (60)
    ;R8 = nuevaFila
    ;R9 = nuevaColumna

validarMovimiento:

    ;calcular el indice del mapa
    mov rax, r8 ;nuevaFila
    imul rax, rdx ;nuevaFila * columnas
    add rax, r9 ;nuevaFila * columnas + nuevaColumna
    ;Leemos el valor en esa posicion de memoria
    mov al,byte [rcx + rax]
    ;Si el valor es '#', es una pared, retornamos 0 (movimiento no valido)
    cmp al, 35 ;ASCII de '#'
    je .movimiento_invalido
    ;Si no es '#', el movimiento es valido, retornamos 1
    mov eax, 1
    ret

.movimiento_invalido:
    mov rax, 0
    ret

    
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
