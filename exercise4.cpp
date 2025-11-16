
// Exercício 4 — Medindo tempo por thread

// Adapte o código do exercício anterior para:

// a) Medir e exibir o tempo total de execução.
// b) Medir e exibir o tempo gasto por cada thread.
// c) Mostrar quantas threads foram utilizadas no cálculo.

#include <iostream>
#include <vector>
#include <iomanip>
#include <omp.h>

void sequential_version() {
    const int N = 1'000'000;
    std::vector<int> x(N), y(N), z(N), a(N);

    // Inicializa valores
    for (int i = 0; i < N; i++) {
        x[i] = i;
        y[i] = i + 1;
        z[i] = i + 2;
    }

    double T0 = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        double local_t0 = omp_get_wtime();
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

    // lista para armazenar os tempos de cada thread
    // omp_get_max_threads() -> alocar o número máximo de threads
    std::vector<double> thread_times(omp_get_max_threads(), 0.0);
    int threads_usadas = 0;

    double T0 = omp_get_wtime();
    #pragma omp parallel
    {
        // execução única na primera thread utilizada
        #pragma omp single 
        {
            threads_usadas = omp_get_num_threads();
        }

        // Calcular tempo da thread atual
        double local_t0 = omp_get_wtime();

        // Faz a distribuição de um local com indices para cada thread.
            // Paralel for -> divide o loop entre as v[arias threads
            // schedule(static) -> Distribui blocos iguais de iterações paracada thread. Cada iteração é independente da outra.
        #pragma omp for schedule(static)
        for (int i = 0; i < N; i++) {
            a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
        }


        // armazena o tempo final da thread
            // cada thread salva seu tempo individual no vetor thread_times.
        int thread_id = omp_get_thread_num(); 
        double local_t1 = omp_get_wtime();
        thread_times[thread_id] = local_t1 - local_t0;
    }

    double T1 = omp_get_wtime();
    double total_time = T1 - T0;

    std::cout << "Em paralelo" << std::endl;
    std::cout << std::fixed << std::setprecision(16);
    std::cout << "Threads: " << threads_usadas << "\n";
    std::cout << "Tempo total: " << total_time << "s\n";

    std::cout << "Tempo p/thread:\n";
    for (int i = 0; i < threads_usadas; ++i) {
        std::cout << "  Thread " << i << ": " << thread_times[i] << "s\n";
    }
}

int main() {
    sequential_version();
    std::cout << "\n\n";
    parallel_static();

    // Saida
        // Versão sequencial
            // Tempo total: 0.0491525139996156s


        // Em paralelo
            // Threads: 4
            // Tempo total: 0.0097634329995344s
            // Tempo p/thread:
                // Thread 0: 0.0095508159993187s
                // Thread 1: 0.0095517070003552s
                // Thread 2: 0.0095507650003128s
                // Thread 3: 0.0095492669997839s
   
}
