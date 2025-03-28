#  My Custom Compiler

Un compilateur écrit en C pour transformer un langage custom `.mcc` en C standard compilable avec `gcc`.

```
my_custom_compiler/       # Code source du compilateur

├── Makefile              # Script de compilation principal
├── README.md             # Documentation
├── .gitignore           

├── mycc                  # Le binaire compilé (généré par `make`)

├── src/                  # Code source du compilateur
│   ├── main.c            # Point d'entrée : lit les arguments et lance la compilation
│   ├── compiler.c/h      # Pipeline général : lex → parse → codegen
│
│   ├── lexer/            # Analyse lexicale (tokenisation)
│   │   ├── lexer.c
│   │   ├── lexer.h
│
│   ├── parser/           # Transforme les tokens en instructions
│   │   ├── parser.c/h    # Analyse la grammaire du langage
│   │   ├── ast.c/h       # Représente les instructions sous forme d'arbre (AST)
│
│   ├── codegen/          # Génération du code C
│   │   ├── codegen.c/h
│
│   └── utils/            # Fonctions utilitaires (log, erreurs...)
│       ├── utils.c/h

├── examples/             # Fichiers source en langage .mcc
│   ├── hello.mcc
│   ├── math.mcc
│   ├── while_loop.mcc
│   ├── if_else.mcc
│   ├── compare_ops.mcc
│   └── hello_string.mcc
        ect...

├── out/                  # Fichiers générés
│   ├── *.c               # Code C généré
│   └── *.out             # Exécutables compilés
```

#### 🛠️ Fonctionnalités actuelles :

- ✅ ```let x = 5;``` – Déclaration de variable
- ✅ ```x = x + 1;``` – Affectation sans redéclaration
- ✅ `let x = 5;` – Déclaration de variable
- ✅ `x = x + 1;` – Affectation sans redéclaration
- ✅ `let z = x + y;` – Déclaration avec expression
- ✅ `print(x);` – Affichage de variables
- ✅ `print("text");` – Affichage de chaînes de caractères
- ✅ `+ - * /` – Opérations arithmétiques
- ✅ `== != < > <= >=` – Comparateurs
- ✅ `if (...) {}` + `else {}` – Conditions
- ✅ `while (...) {}` – Boucles
- ✅ Analyse sémantique : erreur si variable non déclarée


#### 🚧 TODO
-  ```print("x =", x);``` – Affichage multi-arguments

-  ```fn add(a, b) { return a + b; }``` – Fonctions utilisateur

- Typage explicite (ex : int, bool, string)

- Portée et environnement (scope, bloc)

- ```for (...)``` + ```break```, continue

- CLI améliorée : ```./mycc -o out.c```

- Modules / import / gestion multi-fichiers .mcc


## 🚀 Utilisation

### compiler le compilateur
```bash
make clean && make
```

### compiler un fichier .mcc
```bash
./mycc examples/hello.mcc out/hello.c
```

### compiller  le C généré  
```bash
gcc out/hello.c -o out/hello.out
```

### Lance le programme
```bash
./out/hello.out
```
