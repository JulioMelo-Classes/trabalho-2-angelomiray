#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include <string>
#include <vector>
#include "../include/mensagem.h"

using namespace std;
/*
Ok
O formato de documentação não foi o do doxygen, mas vou considerar
*/
class CanalTexto{
	private:
        string ctNome; //O nome do canal, conforme o comando create-channel
        vector<Mensagem> ctMensagens; //Um vector com mensagens que foram enviadas neste canal
    public:
        /*! Construtor. 
                @param nome Nome do canal de texto.
        */
        CanalTexto(string nome);

        /*! Função que retorna o atributo nome do canal de texto. 
            @return ctNome nome do canal de texto.
        */
        string getCtNome();

        /*! Adiciona uma mensagem ao canal de texto. 
            @param nova_mensagem mensagem que será adicionada ao canal de texto. 
        */
        
        void addMsg(Mensagem nova_mensagem);

        /*! 
            Mostra todas as mensagens do canal de texto, caso tenha alguma mensagem no canal. Caso contrário, imprime uma mensagem de que não há mensagens. 
        */
        void allMsg();

        /* Exclui todas as mensagens de um canal de texto
        */
        void excluirMensagensCanalTexto();
};

#endif