// Exercício 3 — Expressão Vetorial

// Implemente a expressão: a[i] = x[i]^2 + y[i]^2 + z[i]^2 para vetores de tamanho 1.000.000.

// a) Faça a versão sequencial.
// b) Paralelize com #pragma omp parallel for schedule(static).
// c) Mostre o tempo total de execução em cada versão.

#include <iostream>
#include <vector>
#include <iomanip>
#include <omp.h>


//construindo os vetores
void sequential_version() {
    const int N = 1'000'000;
    std::vector<int> x(N), y(N), z(N), a(N);

    // inicializa valores
    for (int i = 0; i < N; i++) {
        x[i] = i;
        y[i] = i + 1;
        z[i] = i + 2;
    }

    //Calculo da expressão
    double T0 = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
    }
    double T1 = omp_get_wtime();
    double total_time = T1 - T0;

    std::cout << "Versão sequencial" << std::endl;
    std::cout << std::fixed << std::setprecision(16);
    std::cout << "Tempo total: " << total_time << "s" << std::endl;
}

void parallel_static() {
    const int N = 1'000'000;
    std::vector<int> x(N), y(N), z(N), a(N);

    // inicializa valores
    for (int i = 0; i < N; i++) {
        x[i] = i;
        y[i] = i + 1;
        z[i] = i + 2;
    }

    double T0 = omp_get_wtime();

    //Faz a distribuição de um local com indices para cada thread.
        //Paralel for -> divide o loop entre as v[arias threads
        //schedule(static) -> Distribui blocos iguais de iterações paracada thread. Cada iteração é independente da outra.
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
    }
    double T1 = omp_get_wtime();
    double total_time = T1 - T0;

    std::cout << "Em paralelo" << std::endl;
    std::cout << std::fixed << std::setprecision(16);
    std::cout << "Tempo total: " << total_time << "s" << std::endl;
}

int main() {
    sequential_version();
    std::cout << "\n\n";
    parallel_static();

    // Saida:

    // Versão sequencial
    // Tempo total: 0.0163015609996364s

    // Em paralelo
    // Tempo total: 0.0094053000002532s
    // A paralelização reduz o tempo total de execução. Cada thread processa um bloco independente do vetor.

}