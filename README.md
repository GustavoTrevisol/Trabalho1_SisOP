# Trabalho1_SisOP
Este é um trabalho da disciplina de Sistemas Operacionais. O intuito dele é de fazer comparações de desempenho entre diferentes métodos de codificação, processo e threads. Foram testados simultaneamente 2,4 e 8 threads e 2,4 e 8 processos, ambos com versoes utilizando sincronização e não usando sincronização.
No código de threads, a meneira de sincronizar foi com o mutex. Já no código com processos, foi utilizado o método de semaforo.


## Hardware Overview

      Model Name: MacBook Air
      Model Identifier: Mac14,2
      Model Number: MLXW3LL/A
      Chip: Apple M2
      Total Number of Cores: 8 (4 Performance and 4 Efficiency)
      Memory: 8 GB
      System Firmware Version: 13822.81.10
      OS Loader Version: 13822.81.10
      Serial Number (system): LN9RR60CVG
      Hardware UUID: 16B427CA-C346-5EAE-9C82-6916470836A4
      Provisioning UDID: 00008112-001425210108C01E
      Activation Lock Status: Enabled


## Count com threads

### Threads sem sincronização

2 threads s/ mutex:
Valor final do contador: 501442590
./threads_counter 2 1  2.09s user 0.01s system 198% cpu 1.055 total

4 threads s/ mutex:
Valor final do contador: 269256293
./threads_counter 4 1  2.88s user 0.01s system 391% cpu 0.738 total

8 threads s/ mutex:
Valor final do contador: 191359426
./threads_counter 8 1  11.04s user 0.03s system 762% cpu 1.452 total

### Threads com sincronização

2 threads c/ mutex:
Valor final do contador: 1000000000
./threads_counter 2 2  9.03s user 9.05s system 158% cpu 11.415 total

4 threads c/ mutex:
Valor final do contador: 1000000000
./threads_counter 4 2  216.90s user 25.77s system 377% cpu 1:04.24 total

8 threads c/ mutex:
Valor final do contador: 1000000000
./threads_counter 8 2  19.55s user 127.04s system 599% cpu 24.469 total

## Count com processos

### Processos sem sincronização

2 processos s/ semaforo:
Valor final do contador: 502882054
./process_counter 2 1  2.19s user 0.01s system 199% cpu 1.102 total

4 processos s/ semaforo:
Valor final do contador: 251664966
./process_counter 4 1  2.25s user 0.01s system 394% cpu 0.573 total

8 processos s/ semaforo:
Valor final do contador: 127146515
./process_counter 8 1  4.85s user 0.02s system 746% cpu 0.651 total

### Processos com sincronização

2 processos c/ semaforo:
Valor final do contador: 1000000000
./process_counter 2 2  194.51s user 1281.68s system 100% cpu 24:31.61 total

4 processos c/ semáforo:
Valor final do contador: 1000000000
./process_counter 4 2  215.66s user 1365.54s system 100% cpu 26:07.99 total

8 processos c/ semaforo:
Valor final do contador: 1000000000
./process_counter 8 2  340.16s user 2087.62s system 100% cpu 40:19.29 total
