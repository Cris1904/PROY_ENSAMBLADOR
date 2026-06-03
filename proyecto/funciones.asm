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
    ;Como cada ountero ocupa 4 bytes, multiplicamos por 4
    imul rax, 4
    ;Leemos el valor en esa posicion de memoria
    mov eax,dword [rcx + rax]
    ;Si el valor es 1, es una pared, retornamos 0 (movimiento no valido)
    cmp eax, 1
    je .movimiento_invalido
    ;Si no es 1 el movimiento es valido, retornamos 1
    mov eax, 1
    ret

.movimiento_invalido:
    mov rax, 0
    ret