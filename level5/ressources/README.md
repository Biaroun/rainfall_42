## Level 5

### Analyse

L’analyse du binaire avec objdump révèle une faille de type Format String dans la fonction n.
Le programme réserve un buffer de 520 octets, lit une entrée utilisateur avec fgets de 512 octets, puis l’affiche directement avec printf(buf).Le binaire est conçu pour te bloquer sur les attaques classiques (Buffer Overflow de la pile).

L’absence de format fixe dans printf permet à un attaquant d’interpréter son entrée comme une chaîne de format, ouvrant la voie à une écriture arbitraire en mémoire via %n.
Puisque la fonction se termine par un appel strict à exit(), la seule façon de rediriger le flux d'exécution vers la fonction o est d'utiliser la vulnérabilité Format String (avec %n) pour écraser le pointeur de la fonction exit dans la Global Offset Table (GOT) avec l'adresse de o (0x080484a4).

en faisant objdump -R ./level5 | grep exit on récupere l'adresse memoire de la GOT pour exit


### Exploitation

 python -c "print '\x38\x98\x04\x08' + '%134513824x%4\$n'" > /tmp/exploit
 cat /tmp/exploit - | ./level5

 \x38\x98\x04\x08 : L'adresse de destination (GOT) formatée en Little Endian. l'adresse de base est 0x08049838, c'est l'adresse de exit.

 %134513824x : Le remplissage massif (Padding), on demande à printf d'afficher un nombre hexadécimal (x), mais en le forçant à prendre une largeur de 134 513 824 caractères (avec des espaces au début pour combler). On avait déjà écrit 4 octets (l'adresse GOT). On ajoute 134 513 824 caractères. Total : 134 513 824 + 4 = 134 513 828. si tu convertis 0x080484a4 l'adresse de la fonction o en hexadecimal tu obtiens 134 513 828.
