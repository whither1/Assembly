global strcopy

strcopy:
    mov ecx, edx
    cmp edi, esi
    jl copy

    add edi, ecx
    add esi, ecx
    std

copy:
    rep movsb
    cld
    ret