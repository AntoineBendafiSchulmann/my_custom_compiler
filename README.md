#  My Custom Compiler

 Un compilateur écrit en C pour transformer un langage custom ```.mcc``` en C standard 

```
my_custom_compiler/
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

├── examples/             # Fichiers source en langage custom (.mcc)
│   ├── hello.mcc         #  let + print
│   └── math.mcc          # `x + y` (non supporté actuellement)

├── out/                  # Fichiers générés
│   ├── hello.c           # code c généré à partir de hello.mcc
│   ├── hello.out         # exécutable généré à partir de hello.mcc via gcc
│   ├── math.c          
│   └── math.out
```


#### 🛠️ Fonctionnalités actuelles :

-  ```let x = 5;``` – Déclarations de variables entières

- ```print(x);``` – Affichage d'une variable

- ⚠️  ```let z = x + y```  – Non encore pris en charge (voir TODO)

#### 🚧 TODO
- Expressions binaires : ```x + y```

- Structures de contrôle : ```if```, ```while```

- Fonctions utilisateur : ```fn```, ```return```

- Types : ```int```, ```bool```, etc.


