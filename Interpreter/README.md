# Interpreter
## Aprasas
Iterpretatorius vieks kaip `interface`, kuris leis 'bendrauti' su musu softu.
## Ka jis daro?
1) Skaitys faila, kuriame bus programos kodas
2) Ikels jos koda i atminti (bite code)
3) prides programos pavadinima i komandu sarasa (kad butu galima ja iskviest)
4) Gales pasalinti is atminties
5) + tarkim tures opcija: spausdint atminties turini, registru reiksmes etc (panasiai kaip DOSbox)

## pvz be 5 punkto
```
\> load maxIs3.fileToCompile
\> maxIs3 2 4 3
4
\> delete maxIs3
\> maxIs3 2 4 3
[ERROR] maxIs3 not found.
\>
```

## pvz su 5 punktu
```
\> show load maxIs3.fileToCompile
memory 2DC2 -> 1011 1111 1011 1011
memory 2DC3 -> 1000 1100 1011 1011
...
\> show maxIs3 2 4 3
registrai:	A: 0000 B: 1001 SP: 1234
...
/
```
maxIs3.fileToCompile cia is lempos sugalvotas
# Compiler
Compiler reiks ir padaryt, tad galvoju as tuom uzsiimsiu 