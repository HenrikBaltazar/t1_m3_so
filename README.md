# T1 M3 SO
Henrik Baltazar
## Execução
Utilizado `platformio` para compilar para arduino uno e a extensão oficial do `wokwi` para `vscode` (velocidade de compilação otimizada, não é necessário aguardar na fila dos servidores wokwi)
### Build
`pio run`
### Simulação
Wokwi simulator para Visual Studio Code ou acessar o [projeto público](https://wokwi.com/projects/448982735703797761) ou opcionalmente copiar `src/main.cpp`, `diagram.json` e `libraries.txt` para um novo projeto no portal online `wokwi`.

## Solução proposta
A solução proposta se dá através de 3 tarefas (uma para cada LED), 2 interrupções (uma para cada botam, anexada a tarefa de seu respectivo LED) e 2 filas (uma para cada botão). As tarefas de LED controlável carregam o intervalo de ticks com `TickType_t` inicial convertendo de ms para ticks do FreeRTOS, possuem um loop infinito próprio e aguarda a fila de seu respectivo botão com `xQueueReceive` que assimila o botão e limpa-o da fila ao aceita-lo, enquanto o botão não é pressionado a tarefa permanecerá alternando o estado do LED, quando a fila é preenchida com o pressionamento do botão, a tarefa irá registrar o tempo decorrido e verificar qual seu intervalo de tick atual para alternar para o outro estado, assim, quando o loop retomar e a fila estiver limpa o led alternará o estado com o tick atualizado.


## Task
```
Sistemas Operacionais – Atividade 02 (Válida para a M3)
Descrição Geral
Implemente um sistema composto por três LEDs controlados por tarefas independentes.
Dois desses LEDs devem piscar com intervalos variáveis, alternando entre duas frequências
sempre que seus respectivos botões forem pressionados. O terceiro LED deve piscar com
intervalo fixo.
A detecção do acionamento dos botões deve ocorrer via interrupções, incluindo
tratamento de debounce para garantir que cada pressão seja registrada uma única vez.
Detalhamento das Funcionalidades
LEDs com intervalo variável
• LED Amarelo
 - Controlado pelo Botão 01.
 - Deve alternar entre 200 ms e 2 s a cada pressionamento.
• LED Verde
 - Controlado pelo Botão 02.
 - Deve alternar entre 500 ms e 1,5 s a cada pressionamento.
LED com intervalo fixo
• LED Azul
 - Deve piscar continuamente com intervalo de 1 s.
Requisitos Técnicos
• Cada LED deve ser controlado por uma tarefa separada (três tarefas no total).
• Os botões devem ser lidos exclusivamente por interrupção.
• É obrigatória a implementação de um mecanismo de debounce, garantindo que apenas
um evento seja registrado por pressão.
• Ao detectar um pressionamento, o sistema deve imprimir na Serial o tempo decorrido
(em segundos) desde a última vez em que aquele botão foi pressionado.
```