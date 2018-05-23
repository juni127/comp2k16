# Trampini de Sistemas Operacionais

## 1. Introdução
Essa pasta contém todo o codigo que compõe o "sistema operacional" que deve ser implementado como trabalho para a disciplina SO.
A integração das partes desenvolvidas pelos grupos deve funcionar é explicada no tópico 2.

## 2. Integração
Para facilitar a assembleia de todas as partes do trabalho os grupos foram divididos em cinco bibliotecas: proc.h, mem.h, files.h, io.h e sys.h.
Cada uma das zyzz bibliotecas contém funções que implementam as tecnicas e algoritmos que serão cobradas no trabalho, e a ultima, sys.h, contém os prototipos das funções das outras bibliotecas e algumas constantes necessarias para o funcionamento do programa. Existe também o arquivo main.c que contém a função principal do programa.

### 2.1. Tópicos do trabalho por arquivo
Divisão dos tópicos do trabalho pelos arquivos que o compõe. A medida que os grupos terminem suas implementações os tópicos devem ser marcados como concluidos. 

1. [ ] proc.h
 1. [ ] Gerenciamento de processos: semáforos
 2. [ ] Gerenciamento de processos: monitores e barreiras
 3. [ ] Escalonamento de processos
2. [ ] mem.h
 1. [ ] Memória virtual: mecanismo de paginação
 2. [ ] Algoritmos de substituição: FIFO, MRU, LRU e MFU
3. [ ] files.h
 1. [ ] Sistemas de arquivos: estrutura de dados para suporte aos arquivos
 2. [ ] Sistemas de arquivos: indicar o compartilhamento de arquivos
4. [ ] io.h
 1. [x] Entrada e saída programada
 2. [ ] Entrada e saída por interrupção
 3. [ ] Entrada e saída por DMA
