# Trabalho Final - Descrição #
## TRABALHO FINAL DE REDES DE COMPUTADORES I - 2016/1 ##

**Prazo máximo para entrega do trabalho (pelo Moodle): 19/6 às 23:55**

O trabalho consiste em desenvolver um simulador de rede. O simulador deve receber como parâmetros de execução o nome de um arquivo de descrição de topologia (conforme formato especificado), um nó origem, um nó destino e uma mensagem. O simulador deve apresentar na saída as mensagens enviadas pelos nós e roteadores da topologia conforme o formato estabelecido, considerando o envio de um ping (ICMP Echo Request) do nó origem até o nó destino contendo a mensagem indicada por parâmetro. O simulador deverá realizar a transmissão da mensagem através do ping respeitando a topologia da rede e necessidade de fragmentação da mensagem conforme o MTU das interfaces de rede. O simulador considera o MTU somente para fragmentar o campo de dados do datagrama IP (cabeçalhos não são considerados no valor do MTU).

**Formato do arquivo de descrição de topologia**
```
#NODE
<node_name>,<MAC>,<IP>,<MTU>,<gateway>
#ROUTER
<router_name>,<num_ports>,<MAC0>,<IP0>,<MTU0>,<MAC1>,<IP1>,<MTU1>,<MAC2>,<IP2>,<MTU2> …
#ROUTERTABLE
<router_name>,<net_dest>,<nexthop>,<port>
```
**Formato de saída**
```
Pacotes ARP Request: <src_name> box <src_name> : ARP - Who has <dst_IP>? Tell <src_IP>;
Pacotes ARP Reply: <src_name> => <dst_name> : ARP - <src_IP> is at <src_MAC>;
Pacotes ICMP Echo Request: <src_name> => <dst_name> : ICMP - Echo (ping) request (src=<src_IP> dst=<dst_IP> ttl=<TTL> data=<msg>);
Pacotes ICMP Echo Reply: <src_name> => <dst_name> : ICMP - Echo (ping) reply (src=<src_IP> dst=<dst_IP> ttl=<TTL> data=<msg>);
Processamento final do ICMP Echo Request/Reply no nó: <dst_name> rbox <dst_name> : Received <msg>;
```
**Modo de execução do simulador**
```
$ simulador <topologia> <origem> <destino> <mensagem>
```
EXEMPLO:

*Arquivo topologia.txt*
```
#NODE
n1,00:00:00:00:00:01,192.168.0.2,5,192.168.0.1
n2,00:00:00:00:00:02,192.168.0.3,5,192.168.0.1
n3,00:00:00:00:00:03,192.168.1.2,5,192.168.1.1
n4,00:00:00:00:00:04,192.168.1.3,5,192.168.1.1
#ROUTER
r1,2,00:00:00:00:00:05,192.168.0.1,5,00:00:00:00:00:06,192.168.1.1,5
#ROUTERTABLE
r1,192.168.0.0,0.0.0.0,0
r1,192.168.1.0,0.0.0.0,1
```
Exemplos de execução:

```
$ simulador topologia.txt n1 n2 hello
n1 box n1 : ARP - Who has 192.168.0.3? Tell 192.168.0.2;
n2 => n1 : ARP - 192.168.0.3 is at 00:00:00:00:00:02;
n1 => n2 : ICMP - Echo (ping) request (src=192.168.0.2 dst=192.168.0.3 ttl=8 data=hello);
n2 rbox n2 : Received hello;
n2 => n1 : ICMP - Echo (ping) reply (src=192.168.0.3 dst=192.168.0.2 ttl=8 data=hello);
n1 rbox n1 : Received hello;
```
[Chart](http://mscgen.js.org/?lang=msgenny&msc=wordwraparcs%3Dtrue%2Chscale%3D2.0%3B%0An1%20box%20n1%20%3A%20ARP%20-%20Who%20has%20192.168.0.3%3F%20Tell%20192.168.0.2%3B%0An2%20%3D%3E%20n1%20%3A%20ARP%20-%20192.168.0.3%20is%20at%2000%3A00%3A00%3A00%3A00%3A02%3B%0An1%20%3D%3E%20n2%20%3A%20ICMP%20-%20Echo%20(ping)%20request%20(src%3D192.168.0.2%20dst%3D192.168.0.3%20ttl%3D8%20data%3Dhello)%3B%0An2%20rbox%20n2%20%3A%20Received%20hello%3B%0An2%20%3D%3E%20n1%20%3A%20ICMP%20-%20Echo%20(ping)%20reply%20(src%3D192.168.0.3%20dst%3D192.168.0.2%20ttl%3D8%20data%3Dhello)%3B%0An1%20rbox%20n1%20%3A%20Received%20hello%3B)

```
$ simulador topologia.txt n1 n2 helloworld
n1 box n1 : ARP - Who has 192.168.0.3? Tell 192.168.0.2;
n2 => n1 : ARP - 192.168.0.3 is at 00:00:00:00:00:02;
n1 => n2 : ICMP - Echo (ping) request (src=192.168.0.2 dst=192.168.0.3 ttl=8 data=hello);
n1 => n2 : ICMP - Echo (ping) request (src=192.168.0.2 dst=192.168.0.3 ttl=8 data=world);
n2 rbox n2 : Received helloworld;
n2 => n1 : ICMP - Echo (ping) reply (src=192.168.0.3 dst=192.168.0.2 ttl=8 data=hello);
n2 => n1 : ICMP - Echo (ping) reply (src=192.168.0.3 dst=192.168.0.2 ttl=8 data=world);
n1 rbox n1 : Received helloworld;
```
[Chart](http://mscgen.js.org/?lang=msgenny&msc=wordwraparcs%3Dtrue%2Chscale%3D2.0%3B%0An1%20box%20n1%20%3A%20ARP%20-%20Who%20has%20192.168.0.3%3F%20Tell%20192.168.0.2%3B%0An2%20%3D%3E%20n1%20%3A%20ARP%20-%20192.168.0.3%20is%20at%2000%3A00%3A00%3A00%3A00%3A02%3B%0An1%20%3D%3E%20n2%20%3A%20ICMP%20-%20Echo%20(ping)%20request%20(src%3D192.168.0.2%20dst%3D192.168.0.3%20ttl%3D8%20data%3Dhello)%3B%0An1%20%3D%3E%20n2%20%3A%20ICMP%20-%20Echo%20(ping)%20request%20(src%3D192.168.0.2%20dst%3D192.168.0.3%20ttl%3D8%20data%3Dworld)%3B%0An2%20rbox%20n2%20%3A%20Received%20helloworld%3B%0An2%20%3D%3E%20n1%20%3A%20ICMP%20-%20Echo%20(ping)%20reply%20(src%3D192.168.0.3%20dst%3D192.168.0.2%20ttl%3D8%20data%3Dhello)%3B%0An2%20%3D%3E%20n1%20%3A%20ICMP%20-%20Echo%20(ping)%20reply%20(src%3D192.168.0.3%20dst%3D192.168.0.2%20ttl%3D8%20data%3Dworld)%3B%0An1%20rbox%20n1%20%3A%20Received%20helloworld%3B)
```
$ simulador topologia.txt n1 n3 hello
n1 box n1 : ARP - Who has 192.168.0.1? Tell 192.168.0.2;
r1 => n1 : ARP - 192.168.0.1 is at 00:00:00:00:00:05;
n1 => r1 : ICMP - Echo (ping) request (src=192.168.0.2 dst=192.168.1.2 ttl=8 data=hello);
r1 box r1 : ARP - Who has 192.168.1.2? Tell 192.168.1.1;
n3 => r1 : ARP - 192.168.1.2 is at 00:00:00:00:00:03;
r1 => n3 : ICMP - Echo (ping) request (src=192.168.0.2 dst=192.168.1.2 ttl=7 data=hello);
n3 rbox n3 : Received hello;
n3 => r1 : ICMP - Echo (ping) reply (src=192.168.1.2 dst=192.168.0.2 ttl=8 data=hello);
r1 => n1 : ICMP - Echo (ping) reply (src=192.168.1.2 dst=192.168.0.2 ttl=7 data=hello);
n1 rbox n1 : Received hello;
```
[Chart](http://mscgen.js.org/?lang=msgenny&msc=wordwraparcs%3Dtrue%2Chscale%3D2.0%3B%0An1%20box%20n1%20%3A%20ARP%20-%20Who%20has%20192.168.0.1%3F%20Tell%20192.168.0.2%3B%0Ar1%20%3D%3E%20n1%20%3A%20ARP%20-%20192.168.0.1%20is%20at%2000%3A00%3A00%3A00%3A00%3A05%3B%0An1%20%3D%3E%20r1%20%3A%20ICMP%20-%20Echo%20(ping)%20request%20(src%3D192.168.0.2%20dst%3D192.168.1.2%20ttl%3D8%20data%3Dhello)%3B%0Ar1%20box%20r1%20%3A%20ARP%20-%20Who%20has%20192.168.1.2%3F%20Tell%20192.168.1.1%3B%0An3%20%3D%3E%20r1%20%3A%20ARP%20-%20192.168.1.2%20is%20at%2000%3A00%3A00%3A00%3A00%3A03%3B%0Ar1%20%3D%3E%20n3%20%3A%20ICMP%20-%20Echo%20(ping)%20request%20(src%3D192.168.0.2%20dst%3D192.168.1.2%20ttl%3D7%20data%3Dhello)%3B%0An3%20rbox%20n3%20%3A%20Received%20hello%3B%0An3%20%3D%3E%20r1%20%3A%20ICMP%20-%20Echo%20(ping)%20reply%20(src%3D192.168.1.2%20dst%3D192.168.0.2%20ttl%3D8%20data%3Dhello)%3B%0Ar1%20%3D%3E%20n1%20%3A%20ICMP%20-%20Echo%20(ping)%20reply%20(src%3D192.168.1.2%20dst%3D192.168.0.2%20ttl%3D7%20data%3Dhello)%3B%0An1%20rbox%20n1%20%3A%20Received%20hello%3B)
```
$ simulador topologia.txt n1 n3 helloworld
n1 box n1 : ARP - Who has 192.168.0.1? Tell 192.168.0.2;
r1 => n1 : ARP - 192.168.0.1 is at 00:00:00:00:00:05;
n1 => r1 : ICMP - Echo (ping) request (src=192.168.0.2 dst=192.168.1.2 ttl=8 data=hello);
n1 => r1 : ICMP - Echo (ping) request (src=192.168.0.2 dst=192.168.1.2 ttl=8 data=world);
r1 box r1 : ARP - Who has 192.168.1.2? Tell 192.168.1.1;
n3 => r1 : ARP - 192.168.1.2 is at 00:00:00:00:00:03;
r1 => n3 : ICMP - Echo (ping) request (src=192.168.0.2 dst=192.168.1.2 ttl=7 data=hello);
r1 => n3 : ICMP - Echo (ping) request (src=192.168.0.2 dst=192.168.1.2 ttl=7 data=world);
n3 rbox n3 : Received helloworld;
n3 => r1 : ICMP - Echo (ping) reply (src=192.168.1.2 dst=192.168.0.2 ttl=8 data=hello);
n3 => r1 : ICMP - Echo (ping) reply (src=192.168.1.2 dst=192.168.0.2 ttl=8 data=world);
r1 => n1 : ICMP - Echo (ping) reply (src=192.168.1.2 dst=192.168.0.2 ttl=7 data=hello);
r1 => n1 : ICMP - Echo (ping) reply (src=192.168.1.2 dst=192.168.0.2 ttl=7 data=world);
n1 rbox n1 : Received helloworld;
```
[Chart](http://mscgen.js.org/?lang=msgenny&msc=wordwraparcs%3Dtrue%2Chscale%3D2.0%3B%0An1%20box%20n1%20%3A%20ARP%20-%20Who%20has%20192.168.0.1%3F%20Tell%20192.168.0.2%3B%0Ar1%20%3D%3E%20n1%20%3A%20ARP%20-%20192.168.0.1%20is%20at%2000%3A00%3A00%3A00%3A00%3A05%3B%0An1%20%3D%3E%20r1%20%3A%20ICMP%20-%20Echo%20(ping)%20request%20(src%3D192.168.0.2%20dst%3D192.168.1.2%20ttl%3D8%20data%3Dhello)%3B%0An1%20%3D%3E%20r1%20%3A%20ICMP%20-%20Echo%20(ping)%20request%20(src%3D192.168.0.2%20dst%3D192.168.1.2%20ttl%3D8%20data%3Dworld)%3B%0Ar1%20box%20r1%20%3A%20ARP%20-%20Who%20has%20192.168.1.2%3F%20Tell%20192.168.1.1%3B%0An3%20%3D%3E%20r1%20%3A%20ARP%20-%20192.168.1.2%20is%20at%2000%3A00%3A00%3A00%3A00%3A03%3B%0Ar1%20%3D%3E%20n3%20%3A%20ICMP%20-%20Echo%20(ping)%20request%20(src%3D192.168.0.2%20dst%3D192.168.1.2%20ttl%3D7%20data%3Dhello)%3B%0Ar1%20%3D%3E%20n3%20%3A%20ICMP%20-%20Echo%20(ping)%20request%20(src%3D192.168.0.2%20dst%3D192.168.1.2%20ttl%3D7%20data%3Dworld)%3B%0An3%20rbox%20n3%20%3A%20Received%20helloworld%3B%0An3%20%3D%3E%20r1%20%3A%20ICMP%20-%20Echo%20(ping)%20reply%20(src%3D192.168.1.2%20dst%3D192.168.0.2%20ttl%3D8%20data%3Dhello)%3B%0An3%20%3D%3E%20r1%20%3A%20ICMP%20-%20Echo%20(ping)%20reply%20(src%3D192.168.1.2%20dst%3D192.168.0.2%20ttl%3D8%20data%3Dworld)%3B%0Ar1%20%3D%3E%20n1%20%3A%20ICMP%20-%20Echo%20(ping)%20reply%20(src%3D192.168.1.2%20dst%3D192.168.0.2%20ttl%3D7%20data%3Dhello)%3B%0Ar1%20%3D%3E%20n1%20%3A%20ICMP%20-%20Echo%20(ping)%20reply%20(src%3D192.168.1.2%20dst%3D192.168.0.2%20ttl%3D7%20data%3Dworld)%3B%0An1%20rbox%20n1%20%3A%20Received%20helloworld%3B)

**Detalhes para construção do simulador:**

- TTL inicial dos pacotes IP deve ser igual a 8

- a topologia somente utilizará redes usando o modelo de classes (A, B ou C), isto é, não serão utilizadas subredes

- a topologia não apresentará erros de configuração (loops, endereços errados)

- o simulador deve ser executado a partir de um terminal por linha de comando de acordo com o exemplo apresentado - não deve ser necessário utilizar uma IDE para executar o simulador!!!

- o simulador pode ser implementado em qualquer linguagem

- a entrada e saída devem respeitar EXATAMENTE os formatos apresentados

- o formato de saída é baseado na linguagem MsGenny. Sugere-se verificar se a saída está correta através do site https://sverweij.github.io/mscgen_js. Usar o cabeçalho “wordwraparcs=true,hscale=2.0;” para facilitar a visualização.

**Itens a serem entregues:**

- código fonte e executável

- relatório (em pdf) contendo: (i) detalhes de implementação (linguagem, classes, principais métodos); (ii) descrição de como utilizar o simulador; (iii) limitações do simulador implementado e dificuldades de implementação; (iv) exemplo de execução com 1 topologia composta por no mínimo 3 roteadores

**OBSERVAÇÕES**

- O trabalho deve ser realizado em grupos de no máximo 2 alunos.

- Não serão aceitos trabalhos atrasados e/ou enviados por e-mail.

- Trabalhos que não compilam ou que não executam não serão avaliados.

- Todos os trabalhos serão analisados e comparados. Caso seja identificada cópia de trabalhos, todos os trabalhos envolvidos receberão nota ZERO!

Última atualização: segunda, 9 Mai 2016, 14:11

http://moodle.pucrs.br/mod/page/view.php?id=1043712
