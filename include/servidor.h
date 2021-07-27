#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <string>
#include "../include/canaltexto.h"
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
        Servidor(string serverNome, int usuarioDonold){
            this->serverNome = serverNome;
            this->usuarioDonold = usuarioDonold;
        }


        int getUsuarioDonold(){
            return usuarioDonold;
        }
        

        string getServerNome(){
            return serverNome;
        }


        void setServerDesc(const string serverDesc){
            this->serverDesc = serverDesc;  
        }


        string getServerDesc(){
            return this->serverDesc;
        }


        string setServerCodigoConvite(const string serverCodigoConvite){
            this->serverCodigoConvite = serverCodigoConvite;
        }
};

#endif //SERVIDOR_H
