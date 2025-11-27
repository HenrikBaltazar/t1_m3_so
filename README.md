# T1 M3 SO

## CMD
`pio run`

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