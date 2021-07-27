#ifndef USUARIO_H
#define USUARIO_H

#include <string>

using namespace std;

class Usuario{
	private:
        int userId; //identificador único para o usuário.
        string userNome; //O nome cadastrado pelo usuário, conforme o comando create-user
        string userEmail; //O email cadastrado pelo usuário, conforme o comando create-user
        string userSenha; //A senha cadastrada pelo usuário, conforme o comando create-user

    public:
        Usuario(int id, string email, string senha, string nome){
            this->userId = id;
            this->userNome = nome;
            this->userEmail = email;
            this->userSenha = senha;
        }

        string getEmail(){
            return userEmail;
        }

        string getNome(){
            return userNome;
        }

        string getSenha(){
            return userSenha;
        }

};

#endif
