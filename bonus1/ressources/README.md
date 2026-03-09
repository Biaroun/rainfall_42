## bonusl 

### Analyse

le programme prend 2 arguments, il convertit le premier en nombre avec atoi. Il vérifie ensuite si ce nombre len est inférieur ou égal à 9, si c'est superieur le programme exit. Ensuite il multiplie len par 4 et rentre cette valeur comme taille pour memcpy et va copier les caractères de ton deuxième argument (argv[2]) et les coller dans un buffer prévu à cet effet. Puis le programme verifie si len est egale a 0x574f4c46 (FLOW en ascii), si c'est le cas il lance un terminal. il faut donc ecraser la variable len par le mot "FLOW".

Notre texte est copié à esp + 0x14. La distance jusqu'à len est de 0x3c - 0x14 = 0x28 en hexadécimal, soit 40 octets. Il faut donc copier 40 octets de remplissage + 4 octets pour le mot "FLOW", soit 44 octets au total. Pour avoir 44, il faudrait passer 11 en argument (11 * 4 = 44). Mais le programme a une sécurité qui nous empeche de mettre un nombre superieur a 9. On doit trouver un nombre négatif qui, une fois multiplié par 4, provoque un Integer Overflow et retombe exactement sur le chiffre 44.

UINT_MAX = 4294967295
UINT_MAX / 4 = 1073741823

pour avoir 44 bytes:
44 = (n * 4) mod 2^32
44 = (n * 4) mod 4294967296

avec: n = -1073741813
-1073741813 * 4 = -4294967252
En unsigned: 4294967296 - 4294967252 = 44 bytes

### Exploitation

./bonus1 -1073741813 $(python -c 'print "A"*40 + "FLOW"')

meemcpy copie les 40 A dans buffer puis deborde sur len, ecrase -1073741813 et y ecrit "FLOW"
