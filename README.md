# Distância entre duas cidades
Exercício para a disciplina de Algoritmos e Estruturas de Dados com o intuito de ler um grafo de um arquivo texto que contém informações sobre nomes de cidades (vértices do grafo), suas respectivas distâncias (arestas do grafo) e calcular a menor distância entre duas cidades e o trajeto feito.

## Entrada
O modelo do arquivo de entrada segue o seguinte exemplo:
- **3** (número de estradas que serão informadas)
- **cidadeA cidadeB 2** (primeira estrada informada (indica a distância de 10km entre as cidades A e B))
- **cidadeA cidadeC 25**
- **cidadeB cidadeC 20** (ultima estrada informada)
- **cidadeA cidadeC** (trajeto que se deseja calcular)

Nesse caso de exemplo a resposta será **A -> B -> C** somando **22km**

### Limitações da entrada
O nome das cidades não pode ter mais de 20 caractéres e não pode ter espaços em branco, por exemplo:
> Belo Horizonte.
não é uma entrada válida, mas
> beloHorizonte.
	é.
