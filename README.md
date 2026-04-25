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

### Gráficos de escalabilidade
**Threads**
<img width="822" height="453" alt="image" src="https://github.com/user-attachments/assets/9f057253-fb76-4237-b102-ac5142e8e47b" />

**Processos**
<img width="825" height="440" alt="image" src="https://github.com/user-attachments/assets/4ea5de86-f993-48ef-9f58-65fb7ac8b635" />

## Análise de Corrupção (T1 e P1)
Nos experimentos realizados sem mecanismo de sincronização, o valor final do contador ficou muito abaixo de 1.000.000.000. Esse comportamento se deve a condição de corrida, um problema que ocorre em sistemas concorrentes, em que duas ou mais unidades de execução acessam e modificam ao mesmo tempo um mesmo recurso compartilhado. 
A operação de incremento do contador (`contador++`) é uma operação simples , mas não é atômica no nível de execução. Ela é composta por três etapas diferentes: a primeira é a leitura do valor que reside atualmente na memória, em seguida, esse valor é incrementado no modo local e, por último, esse valor é escrito de volta na memória. Quando dois ou mais tópicos ou processos executam essa sequência ao mesmo tempo, um deles pode ler o valor desatualizado antes que outro tenha feito a escrita. 
O efeito resulta na sobrescrita de incrementos intermediário, levando à perda de atualizações. Esse efeito se torna ainda mais pronunciado a medida que aumenta o número de threads ou processos. Com mais unidades de execução acessando o mesmo recurso, aumenta a frequência de acessos não sincronizados a memória compartilhada, o que aumenta a ocorrência de coincidência e, consequentemente, aumenta a diferença entre o valor esperado e o valor obtido. Isso explica por que, nos testes com 4 e 8 unidades, os resultados foram progressivamente menores.
Além disso, o próprio hardware utilizado influencia esse comportamento. No ambiente de testes, que possui 8 núcleos físicos (Apple M2), há capacidade real de execução paralela. Isso significa que múltiplas threads ou processos podem de fato executar ao mesmo tempo, e não apenas de forma intercalada. Embora isso seja benéfico para desempenho em cenários bem sincronizados, também aumenta significativamente a probabilidade de condições de corrida quando não há mecanismos de controle, como mutexes ou semáforos.

## Análise dos Resultados
Os resultados obtidos mostram como a presença (ou ausência) de sincronização impacta diretamente tanto a corretude quanto o desempenho das execuções concorrentes.
No caso das threads, a execução sem mutex apresentou tempos curtos, indicando alta eficiência do ponto de vista de desempenho bruto. No entanto, esses resultados vieram acompanhados de valores finais incorretos para o contador, consequência direta das condições de corrida já discutidas anteriormente. Ou seja, embora o programa execute rapidamente, ele não produz resultados confiáveis, o que inviabiliza essa abordagem em cenários reais.
Quando o mutex é introduzido, observa-se que o valor final do contador passa a ser correto em todos os testes, atingindo consistentemente 1.000.000.000. Isso demonstra que o mecanismo de exclusão mútua cumpre seu papel ao garantir que apenas uma thread por vez acesse a variável compartilhada. Entretanto, essa garantia de consistência tem um custo significativo: o tempo de execução aumenta consideravelmente. Esse aumento ocorre devido ao overhead de sincronização, já que as threads passam a disputar o acesso ao mutex, gerando contenção. Em vez de executarem em paralelo de forma plena, elas acabam sendo parcialmente serializadas, aguardando sua vez de acessar o recurso crítico.
Em termos de escalabilidade, as threads não apresentaram ganho linear de desempenho com o aumento do número de unidades. Pelo contrário, em alguns casos o aumento de threads resultou em piora no tempo total. Isso ocorre porque mais threads significam mais competição pelo mutex, aumentando o tempo de espera e reduzindo os benefícios do paralelismo.
Já na análise com processos, o comportamento sem sincronização é bastante semelhante ao observado nas threads: os tempos de execução são baixos, porém os resultados finais são incorretos. Isso indica que o problema de condição de corrida não está relacionado ao tipo de unidade de execução em si, mas sim à ausência de mecanismos que controlem o acesso concorrente à memória compartilhada.
Quando se utiliza semáforo para sincronização entre processos, o contador volta a apresentar valores corretos, confirmando que o controle de acesso foi efetivo. No entanto, o impacto no desempenho é muito mais severo do que no caso das threads. Os tempos de execução aumentam drasticamente, chegando à ordem de minutos, o que evidencia um alto custo associado a esse modelo. Esse custo elevado pode ser explicado por dois fatores principais: o overhead de criação e gerenciamento de processos, que é naturalmente maior do que o de threads, e o custo adicional da comunicação entre processos (IPC), que envolve mecanismos como memória compartilhada e chamadas de sistema para controle de semáforos.
Em relação à escalabilidade, os processos apresentaram um comportamento bastante limitado. O aumento no número de processos não resultou em melhoria de desempenho; pelo contrário, houve um aumento significativo no tempo de execução. Isso indica que o custo de sincronização e comunicação cresce mais rapidamente do que os benefícios do paralelismo nesse modelo.

## Conclusão
Este experimento demonstrou o impacto da sincronização na execução concorrente. Observamos que, na ausência de mecanismos de controle, tanto threads quanto processos apresentaram tempos de execução mais baixos, porém produziram resultados incorretos devido à ocorrência de condições de corrida. Por outro lado, a introdução de mecanismos de sincronização garantiu a consistência dos dados, fazendo com que o contador atingisse corretamente o valor de 1.000.000.000 em todos os casos. No entanto, essa correção veio acompanhada de um aumento significativo no tempo de execução, evidenciando o custo associado ao controle de acesso concorrente.
No caso das threads, verificou-se um desempenho geral superior, principalmente devido ao menor overhead de criação e ao fato de compartilharem o mesmo espaço de memória, o que permite uma comunicação mais direta e eficiente. Ainda assim, o uso de mutex introduziu contenção entre as threads, limitando os ganhos de paralelismo e impactando a escalabilidade.
Já os processos, apesar de oferecerem maior isolamento e segurança, apresentaram um custo significativamente mais elevado. A criação de processos é mais pesada e a necessidade de utilizar mecanismos de comunicação entre processos, como memória compartilhada e semáforos, adiciona um overhead considerável. Isso ficou evidente nos tempos de execução muito superiores quando comparados às threads, especialmente nos cenários com sincronização.
Ao comparar diretamente threads e processos, fica evidente que as threads possuem vantagens em termos de desempenho e eficiência. Elas são mais leves, compartilham o mesmo espaço de memória e permitem comunicação direta, o que reduz significativamente o overhead. Por outro lado, processos são mais pesados, possuem espaços de memória isolados e dependem de mecanismos de comunicação explícitos, como IPC, que são mais custosos. Além disso, os mecanismos de sincronização utilizados também apresentam diferenças relevantes: o mutex, utilizado com threads, mostrou-se mais eficiente do que o semáforo utilizado com processos, principalmente devido ao menor custo de operação dentro de um mesmo espaço de memória.
De forma geral, os resultados demonstram que threads são mais adequadas para cenários que exigem alto desempenho e compartilhamento de dados. Em contrapartida, processos, apesar de proporcionarem maior isolamento, apresentam um custo elevado que pode comprometer a escalabilidade e a eficiência da aplicação. Assim, a escolha entre threads e processos deve considerar o equilíbrio entre desempenho, segurança e complexidade, de acordo com as necessidades específicas do sistema a ser desenvolvido.


