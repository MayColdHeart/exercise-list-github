// Exercício 5 — Escalonamento

// Use novamente o cálculo de a[i] = x[i]^2 + y[i]^2 + z[i]^2, mas:

// a) Execute com schedule(static) e schedule(dynamic, 1000).
// b) Compare os tempos em diferentes quantidades de threads (2, 4, 8).
// c) Explique em quais situações static e dynamic são mais adequados.

#include <iostream>
#include <vector>
#include <iomanip>
#include <omp.h>

void parallel_static(const int THREADS_I) {
    const int N = 1'000'000;
    std::vector<int> x(N), y(N), z(N), a(N);

    //inicializa valores
    for (int i = 0; i < N; i++) {
        x[i] = i;
        y[i] = i + 1;
        z[i] = i + 2;
    }

    // Cria lista para guardar tempos de cada thread
    // omp_get_max_threads() aloca o "número máximo de threads" elementos
    std::vector<double> thread_times(omp_get_max_threads(), 0.0);
    int threads_usadas = 0;

    double T0 = omp_get_wtime();

    #pragma omp parallel num_threads(THREADS_I)
    {
                // execução única na primera thread utilizada
        #pragma omp single
        {
            threads_usadas = omp_get_num_threads();
        }

        // calculo de tempo da thread atual
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

    std::cout << "com o schedule(static)" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Threads: " << threads_usadas << "\n";
    std::cout << "Tempo total: " << total_time << "s\n";

    std::cout << "Tempo por thread:\n";
    for (int i = 0; i < threads_usadas; i++) {
        std::cout << "  Thread " << i << ": " << thread_times[i] << "s\n";
    }
}

void parallel_dynamic(const int THREADS_I) {
    const int N = 1'000'000;
    std::vector<int> x(N), y(N), z(N), a(N);

    //inicializa valores
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

    #pragma omp parallel num_threads(THREADS_I)
    {

        //executa apenas uma vez, na primera thread utilizada
        #pragma omp single 
        {
            threads_usadas = omp_get_num_threads();
        }

        // Usado para calcular tempo da thread atual
        double local_t0 = omp_get_wtime();

        // Faz a distribuição de um local com indices para cada thread.

        #pragma omp for schedule(dynamic, 1000)
        // Esses 1000 indíces serão solicitados pelas threads de forma dividida.
            // Depois de executado, solicita novamente outro pedaço desses 1000 que está ocioso
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

    std::cout << "com o schedule(dynamic, 1000)" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Threads: " << threads_usadas << "\n";
    std::cout << "Tempo total: " << total_time << "s\n";

    std::cout << "Tempo por thread:\n";
    for (int i = 0; i < threads_usadas; ++i) {
        std::cout << "  Thread " << i << ": " << thread_times[i] << "s\n";
    }
}

int main() {
    


    for (int thread_i = 2; thread_i <= 12; thread_i+=2) {
        std::cout << "\n";
        std::cout << "Execução com " << thread_i << " threads\n";
        std::cout << "\n";
        parallel_static(thread_i);
        std::cout << "\n";
        parallel_dynamic(thread_i);
        std::cout << "\n";
        std::cout << "\n\n";
    }
}

// c) Explique em quais situações static e dynamic são mais adequados.

// A diferença entre o static e dynamic está no balanceamento de carga e no custo de escalonamento.

//Em static
    // Indicado quando todas as iterações tem custo semelhante
        //A carga total é bem dividida entre as threads
        //Não há dependências entre iterações
        //Não há grandes variaçōes de tempo de cálculo entre índices
            //Usos: Calculos de expressões matemáticas, soma de vetores e operações sobre matrizes.

//Em dynamic 
    // Indicado quando o tempo de execução das iterações variam.
        // Algumas iterações são rápidas e outras são lentas
        // Não dá para saber quanto tempo cada índice vai levar.
            //Usos: loops com carga variável:
                //Busca em profundidade ou largura
                //Processamento de listas com tempos diferentes.
                //Loops com operações dependentess.


//Saida: 

// Execução com 2 threads

// com o schedule(static)
// Threads: 2
// Tempo total: 0.014934s
// Tempo por thread:
//   Thread 0: 0.014783s
//   Thread 1: 0.014781s

// com o schedule(dynamic, 1000)
// Threads: 2
// Tempo total: 0.010517s
// Tempo por thread:
//   Thread 0: 0.010464s
//   Thread 1: 0.010460s




// Execução com 4 threads

// com o schedule(static)
// Threads: 4
// Tempo total: 0.009355s
// Tempo por thread:
//   Thread 0: 0.009179s
//   Thread 1: 0.009179s
//   Thread 2: 0.009178s
//   Thread 3: 0.009178s

// com o schedule(dynamic, 1000)
// Threads: 4
// Tempo total: 0.009394s
// Tempo por thread:
//   Thread 0: 0.008282s
//   Thread 1: 0.008391s
//   Thread 2: 0.008280s
//   Thread 3: 0.006552s




// Execução com 6 threads

// com o schedule(static)
// Threads: 6
// Tempo total: 0.009197s
// Tempo por thread:
//   Thread 0: 0.009012s
//   Thread 1: 0.008991s
//   Thread 2: 0.008917s
//   Thread 3: 0.008868s
//   Thread 4: 0.008967s
//   Thread 5: 0.005846s

// com o schedule(dynamic, 1000)
// Threads: 6
// Tempo total: 0.009269s
// Tempo por thread:
//   Thread 0: 0.003240s
//   Thread 1: 0.008436s
//   Thread 2: 0.009159s
//   Thread 3: 0.008515s
//   Thread 4: 0.009052s
//   Thread 5: 0.009063s




// Execução com 8 threads

// com o schedule(static)
// Threads: 8
// Tempo total: 0.010267s
// Tempo por thread:
//   Thread 0: 0.009202s
//   Thread 1: 0.004330s
//   Thread 2: 0.009933s
//   Thread 3: 0.007197s
//   Thread 4: 0.009945s
//   Thread 5: 0.009904s
//   Thread 6: 0.009975s
//   Thread 7: 0.005226s

// Segmentation fault (core dumped)