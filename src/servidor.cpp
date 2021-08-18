#include <string>
#include "../include/sistema.h"
#include "../include/executor.h"
#include "../include/mensagem.h"
#include "../include/servidor.h"
#include "../include/usuario.h"
#include "../include/canaltexto.h"
#include <vector>
#include <algorithm>

using namespace std;

Servidor::Servidor(string serverNome, int usuarioDonold){
    this->serverNome = serverNome;
    this->usuarioDonold = usuarioDonold;
}


int Servidor::getUsuarioDonold(){
    return usuarioDonold;
}


string Servidor::getServerNome(){
            return serverNome;
}


void Servidor::setServerDesc(const string serverDesc){
    this->serverDesc = serverDesc;  
}


string Servidor::getServerDesc(){
    return this->serverDesc;
}


void Servidor::setServerCodigoConvite(const string serverCodigoConvite){
    this->serverCodigoConvite = serverCodigoConvite;
}


string Servidor::getServerCodigoConvite(){
    return serverCodigoConvite;
}


void Servidor::addUserToServer(int id){
    serverParticipantesIDs.push_back(id);
}


bool Servidor::removeUserFromServer(int id){

    for(int i=0; i < serverParticipantesIDs.size(); ++i)

        if(serverParticipantesIDs[i] == id){
            serverParticipantesIDs.erase(serverParticipantesIDs.begin()+i);

            return true;
        }

    return false;
}


void Servidor::printListaUsuariosServidor(vector<Usuario> &sistema_usuarios){

    for(int i=0; i < serverParticipantesIDs.size(); ++i){
        for(int j=0; j < sistema_usuarios.size(); ++j){
            if(serverParticipantesIDs[i] == sistema_usuarios[j].getID()){
                cout << sistema_usuarios[j].getNome() << endl;             
            }
        }
    }   
}


void Servidor::printListaCanaisServidor(){

    if(serverCanaisTexto.size() == 0)
        cout << "Ainda não há canais de texto para este servidor." <<endl;
    else{
        cout << "# Canais de texto " << endl;

        for(int i=0; i < serverCanaisTexto.size(); ++i){
            cout << serverCanaisTexto[i].getCtNome() << endl;
        }
    }
}


bool Servidor::addCanalTexto(const string nome){

    for(int i=0; i < serverCanaisTexto.size(); ++i){
        if(serverCanaisTexto[i].getCtNome() == nome)
            return false;
    }   

    CanalTexto novo_canalTexto(nome);
    serverCanaisTexto.push_back(novo_canalTexto);
    return true;
}

    
bool Servidor::checkCanalExiste(const string nome){

    for(int i=0; i < serverCanaisTexto.size(); ++i){
        if(serverCanaisTexto[i].getCtNome() == nome)
            return true;
    }

    return false;
}


void Servidor::addMsgToChannel(int id, string mensagem, const string nome_canal, const string who_send){

    for(int i=0; i < serverCanaisTexto.size(); ++i){
        if(serverCanaisTexto[i].getCtNome() == nome_canal){
            
            Mensagem nova_mensagem(id, mensagem, who_send);
            serverCanaisTexto[i].addMsg(nova_mensagem);
            break;
        }
    }
}


void Servidor::printMsgFromChannel(const string nome_canal){

    for(int i=0; i < serverCanaisTexto.size(); ++i){

        if(serverCanaisTexto[i].getCtNome() == nome_canal){
            //cout << "servidor - aqui 1.1 " << endl;
            serverCanaisTexto[i].allMsg();
            //cout << "servidor - aqui 2.1 " << endl;
            break;
        }
    }

}


void Servidor::excluirCanaisTexto(){
    for(int i=0; i < serverCanaisTexto.size(); ++i)
        serverCanaisTexto[i].excluirMensagensCanalTexto();
    serverCanaisTexto.clear();
}