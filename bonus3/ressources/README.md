## bonus3 

### Analyse

le programme prend un arguments, Il appelle fopen pour ouvrir /home/user/end/.pass en mode lecture ("r"), Il utilise fread pour copier les 66 premiers octets du fichier .pass dans le début du buffer puis il prend ton argument (argv[1]), le transforme en nombre entier via atoi(). Ensuite, il prend ce nombre et s'en sert comme index pour injecter un \0 dans le buffer (buffer[index] = '\0'), Il utilise strcmp pour comparer le buffer avec ton argument argv[1], si la comparaison réussit, il fait un execl vers /bin/sh, sinon il affiche la seconde moitié du buffer avec puts.

### Exploitation

./bonus3 ""

En lancant le programme avec une chaine vide atoi renvoie 0 ce qui rend la comparaison d'strcmp entre buffer[0] = '\0' et argv[1] qui est une chaine vide. La comparaison est donc bonne et le sh se lance.
