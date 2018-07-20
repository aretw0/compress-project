# compress-project
Projeto para compressão de dados para a cadeira de sistemas multimídia.

Indico usar as tasks descritas em tasks.json como também o visual studio code.

Uso: 

```
Cmprss <alg> <inputfile>
```

Detalhes:
    -h          Help
    <alg>       Algorithm: rule, huff or shfe
    <inputfile> Input file to compression/descompression

O objetivo é comprimir o arquivo utilizando o algoritmo indicado, salvando o com a extensão equivalente (.rule, .huff ou .shfe). O programa descomprime o arquivo e salva o resultado. Verifica se o arquivo original e o descomprimido são os mesmos e mostra o tempo e a taxa de compressão atingida.

Obs.: Não use arquivos que estão no mesmo local do executável.