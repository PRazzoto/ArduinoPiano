# ArduinoPiano
Code for an Arduino Piano

Referências:
-Math;
-TimerOne;
-Volume1;
-ATmega328P datasheet;
-Tempered Frequencies (Michigan).

https://github.com/PaulStoffregen/TimerOne
https://reference.arduino.cc/reference/cs/language/functions/advanced-io/tone/
https://github.com/connornishijima/arduino-volume1/blob/master/src/Volume.cpp
https://www.tutorialspoint.com/arduino/arduino_math_library.htm#
https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
https://pages.mtu.edu/~suits/notefreqs.html
https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/



Bibliotecas:
A parte de software do projeto foi feita em C++, programado própria IDE no Arduíno. Além do código feito, foram usadas 2 bibliotecas, além de uma outra que foi modificada para que ela pudesse ser compilada com sucesso. Tais bibliotecas são:
- Math;
- TimerOne;
- Volume1(modificada).

Quando o Arduino IDE é baixado a biblioteca Math já está inclusa, no código ela é usada para que as oitavas sejam alteradas da maneira correta. A TimerOne é uma biblioteca feita por um usuário chamado "PaulStoffregen" e disponibilizada para acesso público através do GitHub. De forma similar, a Volume1 foi feita por um usuário chamada "connornishijima", porém foi necessário que algumas modificações fossem feitas nessa biblioteca. O problema dela é que ela estava usando os mesmos registradores de tempo/controle que a biblioteca TimerOne, e isso estava gerando um conflito entre tais bibliotecas. Incialmente a Volume1 foi simplesmente descartada e suas funcionalidades foram feitas de outra maneira, porém após diversos erros foi decidido que seria melhor utilizarmos tal biblioteca, e para isso mexemos com o código fonte dela alterando os registradores "TCCR1A", "TCCR1B","TCNT1", "OCR1A" e "TIMSK1" para "TCCR2A", "TCCR1B", "TCNT2" e "TIMSK2" respectivamente. Dessa maneira, usamos os registradores 2 do Arduino ao invés do 1. Isso poderia ter gerado um problema, pois os registradores originais são de 16 bits enquanto o que foi usado é de apenas 8 bits, porém como no nosso código não é necessário um uso maior do que 8 bits, essa lógica funciona.


Funcionalidades:

Volume:
Para emitir as notas, é usada uma função imbutida no próprio Arduino, a função tone(), que irá gerar uma onda quadrada com uma frequência específica e um duty cycle de 50%. E para realizar o controle do volume dessa está sendo usada a biblioteca de volume, porém modificado, a fim de evitar o conflito de bibliotecas.


Oitava:
Incialmente a ideia era que existisse um botão que aumentasse uma oitava a cada vez que fosse pressionado, porém com o desenvolvimento do projeto pensamos que seria melhor que esse controle fosse feito através de um potenciômetro, sendo o principal motivo disso facilitar a transição entre oitavas, pois dessa maneira é possível ir para uma oitava abaixo da atual sem a necessidade de percorrer todas as outras. Para fazer isso, recebemos um valor inteiro em uma das entradas do Arduino através do potenciômetro (0 até 1023), após isso dividimos esse valor por 204.6, obtendo assim somente cinco possíveis oitavas. A matemática por trás das frequências das oitavas foi baseada em uma pesquisa realizada pela Michigan State University, na qual é possível observar que a razão entre as frequências de duas oitavas consecutivas se aproxima muito de 2. Sendo assim, podemos usar a fórmula: "pow(2,octave)", que eleva 2 ao número da oitava que desejamos. No nosso projeto consideramos a primeira oitava partindo do C3(130.81 Hz) e última finalizando no B7(3951,07 Hz), isso foi definido empiricamente, através de testes com o alto falante utilizado.

Reverb:
Como dito anteriormente foi feita toda uma alteração na biblioteca para que seu uso fosse possível e nela existe uma função chamada "FadeOut()", tal função determina por quanto tempo a nota tocada continuará soando (em milissegundos), logo bastou usar essa função e como parâmetro é passado um float que tem seu valor determinado por um potenciômetro que tem seu valor divido por 100, assim é possível controlar através do potênciometro por quanto tempo a nota tocada fica soando, dando o efeito de reverberação desejado.


Loop:
A funcionalidade de Loop foi desenvolvida através da biblioteca TimerOne e de uma função chamada AttachInterrupt, que irá fazer com que o Loop principal do código seja interrompido, realizando o que quer que esteja na função criada através da "AttachInterrupt()". No nosso código essa função, denominada "Recorder()" é responsável por fazer a leitura de qual botão está sendo pressionado e atribuir a frequência correta à essa nota, além disso, caso o programa reconheça que está em modo gravação essa função irá armazenar a última nota tocada à um vetor de até 100 posições. A TimerOne serve como um temporizador, ditando de quanto em quanto tempo essa função deverá ser chamada. No nosso caso, essa função é chamada a cada 250ms. Outra coisa que a "Recorder()" faz é, caso esteja em modo de tocar as notas gravadas, a própria função irá chamar a tone(), fazendo com que as notas armazenadas no vetor sejam tocadas, e toda vez que o índice do vetor atinge seu máximo ele é reiniciado, ou seja, o código ficará repetindo as notas do vetor infinitamente. Para que tudo isso funcione, é necessário que a o loop principal seja responsável por checar em qual dos dois modos (gravação ou play) o programa está, além de reiniciar o índice do vetor de notas armazenadas e tocar a nota pressionada, caso esteja em modo gravação.
Com tudo isso rodando da maneira certa, o piano consegue tocar as notas pressionadas na hora que foram pressionadas, além de constantemente estar armazenando essas notas, caso o usuário queira repetir os últimos segundos tocados. 

