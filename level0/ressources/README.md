## Level 0

### Analyse
L'analyse du binaire via GDB nous a permis de comprendre la logique du programme. 
Une instruction cmp compare l'input à la valeur hexadécimale 0x1a7, qui correspond au nombre 423 en décimal

```bash
$ gdb ./level0
(gdb) disas main
...
    :   cmp    $0x1a7,%eax
...
```


### Exploitation
On exécute ```./level0 423``` pour valider la comparaison avec 0x1a7, ce qui déclenche un shell avec les privilèges de l'utilisateur suivant et permet de lire le fichier /home/user/level1/.pass

```bash
$ ./level0 423
$ cat /home/user/level1/.pass
```
