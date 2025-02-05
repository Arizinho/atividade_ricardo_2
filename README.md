# Temporizador de um disparo

Este projeto implementa a configuração de um alarme (temporizador one shot) para controlar o desligamento em cascata de três LEDs (azul, vermelho e verde) utilizando a Raspberry Pi Pico W. Inicialmente, os LEDs são acesos através do pressionamento de um botão e, em seguida, desligados automaticamente, um após o outro, a cada 3 segundos pelo alarme.

---

## **Configuração dos Pinos GPIO** 

Os pinos GPIO da Raspberry Pi Pico W estão configurados conforme a tabela abaixo:

| GPIO  | Componente      | Função                                                                     |  
|-------|-----------------|----------------------------------------------------------------------------|  
| **5**  | Push Button     | Entrada digital para ativação de todos os LEDs e inicialização do alarme  |  
| **11** | LED Verde       | Emite cor verde (saída)                                                   |  
| **12** | LED Azul        | Emite cor azul (saída)                                                    |  
| **13** | LED Vermelho    | Emite cor vermelha (saída)                                                |  

---

## **Funcionamento do Código**

1. **Inicialização**: O programa aguarda o pressionamento do botão conectado ao GPIO 5.  
2. **Acionamento dos LEDs**: Quando o botão é pressionado, os LEDs Verde, Azul e Vermelho são acesos simultaneamente e o alarme (temporizador) é iniciado.  
3. **Desligamento dos LEDs**: Após 3 segundos, o alarme (temporizador one-shot) desliga cada LED de forma sequencial, com um intervalo de 3 segundos entre cada desligamento.  
4. **Cascata**: O desligamento dos LEDs ocorre de forma cascata: primeiro o LED Verde, depois o Azul, e por último o Vermelho.

---

## **Link do Vídeo**

Link do vídeo:

https://drive.google.com/file/d/1UXjkDk3WakhlzHwS9aigx_iaIrGgA5sP/view?usp=sharing
