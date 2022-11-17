# Projeto-dos-Trens
Trabalho da Segunda Unidade de Sistemas Operacionais

# Author(s)

<!-- TODO -->
Esther Maria da Silveira Wanderley
esther.wanderley@uol.com.br
Thuanny Carvalho Rolim de Albququerque
thuannyba@gmail.com


# Descrição do Projeto
    Este projeto consiste em fazer com que 5 trens andem pelo o mesmo espaço, sem colidir um com o outro, de maneira que cada um tenha a sua hora de passar e esta seja respeitada. <\br>

    Há 7 regiões críticas, onde é passível de se ter colisões e deadlocks. <\br>
    
    O objetivo do Trabalho é evitar as colisões e os deadlocks. 
    

# Descrição do tratamento de deadlocks e colisões

Para o tratamento dos deadlocks e colisões, mapeamos um mutex para cada região crítica, totalizando sete. <\br>

Para evitar as colisões, quando cada trem vai fazer o acesso a uma das regiões críticas, este trava o mutex referente àquela região, desbloqueando-o somente após sair dele.<\br>

Para evitar deadlocks, identificamos se dois ou três dos trilhos estão bloqueados antes de fazer o acesso à região crítica. Caso haja dois ou mais bloqueados, este trem esperará até que ao menos uma delas esteja livre, evitando os deadlocks.<\br>

# Falhas

Há dois casos de deadlocks que, apesar de tratados na teoria, não funcionaram na prática. O trem de número 4, que fica no canto superior esquerdo, deveria avançar no trilho em ambos os casos, no entanto, a região crítica sinalizada pelo mutex 1 está bloqueada, provavelmente pelo trem 1, sem necessidade, o que causa um pseudo-deadlock, uma vez que deveria ser possível que o trem 4 se movesse, de modo que não haveria deadlock algum. <\br>