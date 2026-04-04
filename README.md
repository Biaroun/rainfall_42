<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/8/8d/42_Logo.svg" alt="42 logo" width="120"/>
  <h1>rainfall_42</h1>
  <p>Projet cybersecurite 42 : progression CTF Linux autour de failles locales, d'exploitation applicative et d'escalade de privileges</p>

  <p>
    <img src="https://img.shields.io/badge/Project-Rainfall-1f6feb?logo=hackthebox&logoColor=white" alt="Rainfall"/>
    <img src="https://img.shields.io/badge/Domain-Cybersecurity-bd2c00?logo=securityscorecard&logoColor=white" alt="Cybersecurity"/>
    <img src="https://img.shields.io/badge/Focus-Privilege%20Escalation-6f42c1?logo=gnu-bash&logoColor=white" alt="Privilege Escalation"/>
    <img src="https://img.shields.io/badge/Levels-0%20to%2014-2da44e?logo=probot&logoColor=white" alt="Levels"/>
    <img src="https://img.shields.io/badge/Bonus-0%20to%203-f59e0b?logo=probot&logoColor=white" alt="Bonus"/>
    <img src="https://img.shields.io/badge/School-42-black?logo=42&logoColor=white" alt="42"/>
  </p>
</div>

---

## Description

`rainfall_42` est un depot de progression du projet Rainfall de 42.

Le projet regroupe 15 niveaux (`level0` a `level14`) et 4 bonus (`bonus0` a `bonus3`) avec, pour chacun :

- un fichier `flag` contenant la preuve de validation
- un dossier `ressources/` avec l'analyse, les tests et la methode d'exploitation

Les writeups couvrent des vulnerabilites classiques :

- mauvaise gestion des permissions et exposition d'informations
- injection de commandes ou d'arguments
- detournement d'execution via variables d'environnement
- contournement de controles logiques avec debug et inspection binaire
- exploitation de conditions de course et de comportements non securises

---

## Architecture

- `level0/` a `level14/` : un dossier par niveau principal
- `bonus0/` a `bonus3/` : dossiers pour les exercices bonus
- `levelX/flag` et `bonusX/flag` : token recupere pour valider l'etape
- `levelX/ressources/README.md` et `bonusX/ressources/README.md` : explication detaillee, quand presente

---

## Utilisation

### Prerequis

- Environnement 42 compatible avec le projet Rainfall
- Outils Linux classiques : `find`, `cat`, `grep`, `strings`, `gdb`, `ltrace`, `nc`, `curl`

### Consulter une etape

Se placer dans le dossier du niveau ou du bonus voulu :

```bash
cd levelX
```

Puis ouvrir la documentation disponible :

```bash
cat ressources/README.md
```

Selon les dossiers, le document peut aussi etre nomme :

- `README.md`
- `readme.md`
- `explanation.md`

---

## Progression

- `level0` : lecture d'une valeur comparee dans le binaire
- `level1` : recuperation d'un hash et cassage du mot de passe
- `level2` : analyse de trafic et reconstruction d'un mot de passe
- `level3` : hijack d'executable via `PATH`
- `level4` : injection de commande via CGI
- `level5` : execution via script systeme
- `level6` : execution de code a travers une evaluation dangereuse
- `level7` : injection via variable d'environnement
- `level8` : contournement de filtre sur fichier via symlink
- `level9` : manipulation d'un chiffrement ou d'un encodage
- `level10` : exploitation TOCTOU avec `access()` et `open()`
- `level11` : injection de commande dans un service Lua
- `level12` : contournement d'un filtre avant execution Perl
- `level13` : bypass de verification d'identite via debug
- `level14` : patch runtime pour atteindre `getflag`
- `bonus0` : overflow de buffer avec shellcode place en variable d'environnement
- `bonus1` : overflow base sur un integer overflow pour ecraser une variable cle
- `bonus2` : overflow de `greetuser` exploitable via `LANG=fi` et ret2libc
- `bonus3` : contournement de comparaison via index nul pour lancer un shell

---

## Notes de securite

- Les flags ne sont pas exposes dans ce README.
- Ce depot est destine a un usage pedagogique sur environnement autorise.
- Ne pas reproduire ces techniques hors cadre controle.

---

## Outils utilises

- `find`, `grep`, `cat`, `strings`
- `gdb`, `ltrace`, `strace`
- `john`, `tcpdump`, Wireshark
- `curl`, `nc` (netcat)

---

## Auteur

- `biaroun` - 42

---

## Licence

Projet academique 42.
Usage pedagogique et personnel.
