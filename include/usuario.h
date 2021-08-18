#ifndef USUARIO_H
#define USUARIO_H

#include <string>

using namespace std;

/*
Ok
O formato de documentação não foi o do doxygen, mas vou considerar
*/
class Usuario{
	private:
        int userId; //identificador único para o usuário.
        string userNome; //O nome cadastrado pelo usuário, conforme o comando create-user
        string userEmail; //O email cadastrado pelo usuário, conforme o comando create-user
        string userSenha; //A senha cadastrada pelo usuário, conforme o comando create-user

    public:
        /* Construtor. 
            @param id id do usuário.
            @param email email do usuário
            @param senha senha do usuário
            @param nome nome do usuário
            
        */
        Usuario(int id, string email, string senha, string nome);


        /*! Método que retorna o email do usuário
            @return email do usuário
        */
        string getEmail();


        /*!  Método que retorna o nome do usuário
            @return nome do usuário.
        */
        string getNome();


        /*! Método que retorna a senha do usuário
            @return senha do usuário.
        */
        string getSenha();


        /*! Método que retorna o id do usuário.
            @return id do usuário.
        */
        int getID();

};

#endif