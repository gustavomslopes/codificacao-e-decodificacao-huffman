# 🌳 Codificador e Decodificador de Texto (Algoritmo de Huffman)

Este repositório contém uma implementação em linguagem C de um sistema de compressão e descompressão de texto baseado na **Árvore de Huffman**. 

O grande diferencial deste projeto é que a árvore e as frequências são construídas com base em **palavras inteiras** (e espaços) do texto, e não em caracteres individuais. O projeto utiliza manipulação direta de bits (bitfields) para garantir que a saída compactada seja gravada como bits reais em um arquivo binário, otimizando o armazenamento.

## 🚀 Funcionalidades

- **Codificação (Compressão):**
  - Tokenização do texto de entrada (`texto.txt`).
  - Cálculo de frequência de ocorrência de cada palavra.
  - Criação de uma Floresta que é progressivamente reduzida para montar a Árvore de Huffman.
  - Mapeamento de códigos binários otimizados para as palavras mais frequentes.
  - Empacotamento de bits usando `struct` com *bitfields* (`b0` a `b7`) para gerar um arquivo compactado real (`binario.dat`).
  - Exportação do dicionário de decodificação (`lista.dat`).

- **Decodificação (Descompressão):**
  - Leitura do dicionário de registros gerado (`lista.dat`).
  - Reconstrução exata da Árvore de Huffman em memória.
  - Leitura bit a bit do arquivo `binario.dat`.
  - Navegação na árvore (esquerda para `0`, direita para `1`) para traduzir os bits de volta ao texto original.

## 🛠️ Tecnologias e Estruturas de Dados Utilizadas

- **Linguagem:** C (Padrão GCC / MinGW)
- **Estruturas de Dados Abstratas (TADs):**
  - **Árvores Binárias** (`TADArvore.h`): Para navegação e mapeamento dos códigos de Huffman.
  - **Florestas** (`TADFloresta.h`): Fila de prioridade customizada em formato de lista encadeada de árvores.
  - **Listas Encadeadas Ordenadas** (`TADLIsta.h`): Para armazenamento do dicionário e ordenação de frequências.
- **Manipulação de Arquivos:** Escrita e leitura de arquivos binários (`.dat`).

## 📂 Estrutura do Projeto

* `codificacao.c`: Arquivo principal responsável por ler o texto, gerar a árvore, exibir a tabela de registros e salvar os arquivos binários.
* `decodificacao.c`: Arquivo principal responsável por ler os arquivos binários gerados, remontar a árvore e imprimir a frase decodificada.
* `TADArvore.h`: Definição e funções de manipulação dos nós da árvore binária.
* `TADFloresta.h`: Definição e funções para gerenciar a floresta de nós durante a montagem da árvore de Huffman.
* `TADLIsta.h`: Definição e funções para a lista encadeada de registros e dicionário.
* `texto.txt`: Arquivo de texto de exemplo para ser lido e codificado.

## ⚙️ Como Compilar e Executar

Certifique-se de ter um compilador C (como o GCC) instalado na sua máquina.

**1. Clone o repositório:**
```bash
git clone [https://github.com/gustavomslopes/nome-do-seu-repo.git](https://github.com/gustavomslopes/nome-do-seu-repo.git)
cd nome-do-seu-repo