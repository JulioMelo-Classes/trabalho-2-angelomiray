#include "../include/sistema.h"
#include "../include/executor.h"
#include "../include/mensagem.h"
#include "../include/servidor.h"
#include "../include/usuario.h"
#include "../include/canaltexto.h"
#include <string>

using namespace std;

Usuario::Usuario(int id, string email, string senha, string nome){
    this->userId = id;
    this->userNome = nome;
    this->userEmail = email;
    this->userSenha = senha;
}


string Usuario::getEmail(){
    return userEmail;
}


string Usuario::getNome(){
    return userNome;
}


string Usuario::getSenha(){
    return userSenha;
}


int Usuario::getID(){
    return userId;
}