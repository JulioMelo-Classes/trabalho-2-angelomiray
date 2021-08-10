#include <string>
#include <ctime>
#include "../include/sistema.h"
#include "../include/executor.h"
#include "../include/mensagem.h"
#include "../include/servidor.h"
#include "../include/usuario.h"
#include "../include/canaltexto.h"

using namespace std;

Mensagem::Mensagem(int id, const string conteudo, const string enviadaPor_nome){
    this->conteudo = conteudo;
    enviadaPor = id;
    this->enviadaPor_nome = enviadaPor_nome;
    
    time_t t;
    struct tm* info;
    char data[20];
    time(&t);
    info = localtime(&t);
    strftime(data, 20, "%d/%m/%y - %H:%M", info);//
    dataHora = data;
}


void Mensagem::show(){
    cout << enviadaPor_nome << "<" << dataHora << "> : " << conteudo << endl;
}