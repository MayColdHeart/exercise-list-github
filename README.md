# Lista de Exercícios — Programação Paralela (OpenMP)
Prof. Rodrifo Gonçalves.



##### Exercício 1 — Hello World Paralelo

1. Crie uma região paralela com #pragma omp parallel.
2. Cada thread deve imprimir uma mensagem indicando seu número (omp_get_thread_num()) e o total de threads (omp_get_num_threads()).
3. Configure o programa para rodar com 4 threads.

---

##### Exercício 2 — Paralelizando um for simples

1. Crie um vetor v de tamanho 100 e inicialize todos os elementos com o valor 1.
2. Escreva um loop sequencial que soma todos os elementos.
3. Refaça o loop com #pragma omp parallel for reduction(+:soma).
4. Compare os resultados e explique por que a diretiva reduction é necessária.

---

##### Exercício 3 — Expressão Vetorial
- Implemente a expressão: a[i] = x[i]^2 + y[i]^2 + z[i]^2 para vetores de tamanho 1.000.000.
1. Faça a versão sequencial.
2. Paralelize com #pragma omp parallel for schedule(static).
3. Mostre o tempo total de execução em cada versão.

---

##### Exercício 4 — Medindo tempo por thread
- Adapte o código do exercício anterior para:
1. Medir e exibir o tempo total de execução
2. Medir e exibir o tempo gasto por cada thread.
3. Mostrar quantas threads foram utilizadas no cálculo.

---

##### Exercício 5 — Escalonamento
- Use novamente o cálculo de a[i] = x[i]^2 + y[i]^2 + z[i]^2, mas:
1. Execute com schedule(static) e schedule(dynamic, 1000).
2. Compare os tempos em diferentes quantidades de threads (2, 4, 8).
3. Explique em quais situações static e dynamic são mais adequados.
