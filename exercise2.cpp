// Exercício 2 — Paralelizando um for simples

// a) Crie um vetor v de tamanho 100 e inicialize todos os elementos com o valor 1.
// b) Escreva um loop sequencial que soma todos os elementos.
// c) Refaça o loop com #pragma omp parallel for reduction(+:soma).
// d) Compare os resultados e explique por que a diretiva reduction é necessária.

#include <iostream>
#include <vector>
#include <omp.h>
#include <iomanip>

int main() {
    //definindo tamanho do vetor
    const int N = 100;
    std::vector<int> not_parallel_list(N, 1); // inicializa N elementos com valor 1


    // soma todos os valores de forma normal (sem threads)
    double T0 = omp_get_wtime(); //mede o tempo decorrido
    int total = 0;
    for (int i = 0; i < N; i++) {
        total += not_parallel_list[i];
    }
    double T1 = omp_get_wtime();
    double total_time = T1 - T0;

    std::cout << "Loop não paralelo" << std::endl;
    std::cout << "Soma total: " << total << std::endl;
    std::cout << std::fixed << std::setprecision(16);
    std::cout << "Tempo total: " << total_time << "s\n\n" << std::endl;

    
    // loop paralelo com o OpenMP

    std::vector parallel_list(N, 1);

    T0 = omp_get_wtime();
    total = 0;
    #pragma parallel for reduction(+:total) // cria uma cópia privada de total para cada thread
    for (int i = 0; i < N; i++) {
        total += parallel_list[i];
    }
    T1 = omp_get_wtime();
    total_time = T1 - T0;

    std::cout << "Loop em paralelo" << std::endl;
    std::cout << "Soma total: " << total << std::endl;
    std::cout << "Tempo total " << total_time << "s" << std::endl;
    return 0;
}

//Saida:
    // Loop em paralelo
    //Soma total: 100
    //Tempo total 0.0000004040002750s

    //Loop não paralelo
    //Soma total: 100
    //Tempo total: 0.0000004720000106s

    //por que a diretiva reduction é necessária? 
    //A reduction cria uma cópia privada da variável para cada thread e acumula os resultados localmente para depois combinar tudo no final.
    //Basicamente a reduction é necessária para evitar condições de corrida.