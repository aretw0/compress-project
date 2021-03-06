# compress-project

Autor: [@aretw0](https://twitter.com/aretw0)


>Projeto de compressão de dados para a cadeira de sistemas multimídia. Implementação dos algoritmos de Shanon-Fano, Codificação por Carreira e Codificação de Huffman para compactação de imagens.


Descrição dos algoritmos
------
- Run-Length

    Técnica para comprimir cadeias de caracteres onde existem seqüências longas de caracteres repetidos.

- Shannon-Fano

    Método estatístico de compressão que gera códigos de tamanho variável para cada símbolo a ser comprimido de acordo com sua probabilidade de ocorrência.

- Huffman

    Método de compressão que usa as probabilidades de ocorrência dos símbolos a serem comprimidos para determinar códigos de tamanho variável para cada símbolo.


>Este trabalho foi desenvolvido utilizando a linguagem C++ (gcc 11), no sistema operacional Linux (Kubuntu 16.04).

Para utilizar execute o arquivo “Cmprss” de qualquer uma das pastas [Release](https://github.com/aretw0/compress-project/tree/master/Release) ou [Debug](https://github.com/aretw0/compress-project/tree/master/Debug) como se segue:
        
    Cmprss <alg> <inputfile>

O campo “\<alg>” pode ser “rule”, “huff” ou “shfa” e o “\<inputfile>” é o caminho do arquivo para compressão. **Não use arquivos que estão no mesmo local do executável e ao executar uma vez recolha ou apague os arquivos gerados**.
O “-h” como parâmetro mostra a seção de ajuda.

O objetivo é codificar o arquivo utilizando o algoritmo indicado nos parâmetros. O programa salva o resultado com a extensão equivalente ao algoritmo escolhido (.rule, .huff ou .shfe) e em seguida decodifica este arquivo salvando o resultado para verificar se o arquivo original e o descomprimido são os mesmos, o programa mostra o checksum de ambos os arquivos como também mostra o tempo e a taxa de compressão atingida.