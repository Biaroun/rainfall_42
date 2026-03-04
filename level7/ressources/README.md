## Level7

### Analyse

Ce programme alloue deux objets sur le tas, chacun contenant un pointeur vers un espace de 8 octets, puis utilise la fonction sécurisée strcpy pour copier vos deux arguments (argv[1] et argv[2]) dans ces espaces respectifs avant de lire un fichier avec le flag, le stocker dans une variable global et de se terminer en appelant puts. La faille principale est un dépassement de tampon (Heap Overflow) : comme strcpy ne vérifie pas la longueur de votre premier argument, un texte assez long (20 octets) déborde de son espace alloué et vient écraser le pointeur du second objet pour le remplacer par l'adresse de puts dans la table GOT. Ensuite, lors du second appel à strcpy, le programme croit ranger sagement votre deuxième argument (qui contient l'adresse de la fonction cachée <m>) dans le second espace, mais il l'écrit en réalité directement dans la GOT, réalisant ainsi une attaque Write-What-Where ; en conséquence, quand le programme tente d'afficher son message de fin avec puts, il exécute à la place la fonction <m> et vous révèle le mot de passe secret.


### Exploitation


(python -c 'print "A"*20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
