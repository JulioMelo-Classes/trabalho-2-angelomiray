#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <string>
#include "canaltexto.h"
#include "usuario.h"
#include <vector>

using namespace std;

class Servidor{
	private:
       int usuarioDonold; //id do usuário que criou o servidor.
       string serverNome; // Nome do servidor, passado no comando create-server
       string serverDesc; //Descrição do servidor passada no comando set-server-desc
       string serverCodigoConvite; //O código de convite do servidor, se houver. Passado no comando set-server-invite-code. Por padrão deve ser uma deve ser uma string vazia.
       vector<CanalTexto> serverCanaisTexto; //Um vetor contendo todos os canais de texto deste servidor
       vector<int> serverParticipantesIDs; //Um vetor contendo os ids de todos os participantes deste servidor. Um usuário vira participante de um servidor após usar o comando enter-server.

    public:
        /*! Construtor. 
            @param serverNome nome do servidor
            @param usuarioDonold id do dono do servidor

        */
        Servidor(string serverNome, int usuarioDonold);

        /*! Método que retorna o id dono do servidor
            @return id do dono do servidor
        */
        int getUsuarioDonold();
        
        /*! Método que retorna o nome do servidor
            @return nome do servidor.
        */
        string getServerNome();

        /*! Método de que define a descrição do servidor.
            @param serverDesc nova descrição do servidor
        */
        void setServerDesc(const string serverDesc);

        /*! Método que retorna a descrição do servidor
        */
        string getServerDesc();

        /*  Método que altera o código de convite do servidor
            @param serverCodigoConvite novo código de convite.
        */
        void setServerCodigoConvite(const string serverCodigoConvite);
        
        /*!  Método de retorna o código de convite do servidor.
        */
        string getServerCodigoConvite();

        /*! Método que adiciona um novo usuário ao servidor
            @param id id do usuário que será adicionado.
        */
        void addUserToServer(int id);

        /*! Método que remove um usuário do servidor
            @param id id do usuário que será removido. 
            @return true caso o usuário tenha sido removido com sucesso; falso caso contrário(caso não esteja no servidor). 

        */
        bool removeUserFromServer(int id);

        /*!  Exibe uma lista com os usuários que estão no servidor
            @param sistema_usuarios todos os usuários do sistema, para verificar quais estão no servidor.

        */
        void printListaUsuariosServidor(vector<Usuario> &sistema_usuarios);

        /*! Exibe uma lista com todos os canais deste servidor
        */
        void printListaCanaisServidor();

        /*! Método que cria um novo canal de texto no servidor. 
            @param nome do canal de texto que será adicionado. 
            @return true caso seja criado com sucesso(caso não tenha nenhum outro canal com o mesmo nome); falso caso contrário.
        */
        bool addCanalTexto(const string nome);
        /*! Método que verifica se um canal existe.
            @param nome nome do canal que será verificada a existência
            @return true caso exista; falso caso contrário.
        */
        bool checkCanalExiste(const string nome);

        /* Método que adiciona uma mensagem no canal de texto do servidor
            @param id id do usuário que está adicionando a mensagem
            @param mensagem mensagem que será adicionada no canal
            @param nome_canal nome do canal de texto que terá a mensagem adicionada 
            @param who_send nome de quem enviou a mensagem
        */
        void addMsgToChannel(int id, string mensagem, const string nome_canal, const string who_send);

        /*  Exibe todas as mensagens enviada em um canal de texto
            @param nome_canal nome do canal de texto

        */
        void printMsgFromChannel(const string nome_canal);

        /*! Exclui todos os canais de texto quando um servidor é deletado.
        */
        void excluirCanaisTexto();
};

#endif //SERVIDOR_H