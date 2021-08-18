#ifndef mensagem_h
#define mensagem_h

#include <string>
#include <ctime>
#include "sistema.h"

using namespace std;
/*
Ok
O formato de documentação não foi o do doxygen, mas vou considerar
*/
class Mensagem{
    private:
        string dataHora; //Um texto representando um timestamp com a data e hora em que a mensagem foi enviada no formato <DD/MM/AAAA - HH:MM>, exemplo: <08/03/2021 - 11:53>
        int enviadaPor; //Id do usuário que enviou a mensagem
        string conteudo; //Conteúdo da mensagem
        string enviadaPor_nome; //Nome de quem enviou a mensagem
    public:

        /*! Construtor.
            @param id id do usuário que enviou a mensagem.
            @param conteudo conteúdo da mensagem enviada
            @param enviadaPor_nome nome de quem enviou a mensagem
        */
        Mensagem(int id, const string conteudo, const string enviadaPor_nome);

        /*! Exibe uma mensagem de maneira formatada, com as informações sobre tal mensagem.
        */
        void show();
};


#endif //mensagem_h