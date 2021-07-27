#ifndef mensagem_h
#define mensagem_h

#include <string>

using namespace std;

class Mensagem{
    private:
        string dataHora; //Um texto representando um timestamp com a data e hora em que a mensagem foi enviada no formato <DD/MM/AAAA - HH:MM>, exemplo: <08/03/2021 - 11:53>
        int enviadaPor; //Id do usuário que enviou a mensagem
        string conteudo; //Conteúdo da mensagem

};


#endif //mensagem_h