// Exercício 1 — “Hello World” Paralelo

// a) Crie uma região paralela com #pragma omp parallel.
// b) Cada thread deve imprimir uma mensagem indicando seu número (omp_get_thread_num()) e o total de threads (omp_get_num_threads()).
// c) Configure o programa para rodar com 4 threads.

#include <iostream>
#include <omp.h>

int main() {
    
    // Local com as 4 threads
    #pragma omp parallel num_threads(4)
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();

    // Executa uma thread por vez para ecitar juntar as saidas no console.
        #pragma omp critical
        std::cout << "Thread " << thread_id << " de " << total_threads << " threads\n";
    }

    return 0;
}


//saida:
//Thread 0 de 4 threads
//Thread 3 de 4 threads
//Thread 2 de 4 threads
//Thread 1 de 4 threads