#include <string>
#include <vector>
#include <utility>
#include "../include/sistema.h"
#include "../include/executor.h"
#include "../include/mensagem.h"
#include "../include/servidor.h"
#include "../include/usuario.h"
#include "../include/canaltexto.h"

using namespace std;


CanalTexto::CanalTexto(string nome){
    ctNome = nome;
}


string CanalTexto::getCtNome(){
    return this->ctNome;
}


void CanalTexto::addMsg(Mensagem nova_mensagem){
    ctMensagens.push_back(nova_mensagem);
}


void CanalTexto::allMsg(){
    int cnt=0;

    for(int i=0; i < ctMensagens.size(); ++i){
        //cout << "canal texto - aqui 1.1 " << endl;
        ctMensagens[i].show();
        //cout << "canal texto - aqui 2.1 " << endl;
        ++cnt;
    }
    
    if(cnt == 0){
        cout << "Sem mensagens para exibir." << endl;
    }

}


void CanalTexto::excluirMensagensCanalTexto(){
    ctMensagens.clear();
}