#include "../include/sistema.h"
#include "../include/usuario.h"
#include "../include/servidor.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo do concordo...";
}



bool Sistema::checkEmail(const string email){
    //cada id do sistema é incremental. logo, possui a quantidade de usuários cadastrados.
    for(int i=0; i < sistemaIds; ++i){
        if(sistemaUsuarios[i].getEmail() == email)
            return true;
    }

    return false;
}


bool Sistema::checkSenha(const string senha){
    //cada id do sistema é incremental. logo, possui a quantidade de usuários cadastrados.
    for(int i=0; i < sistemaIds; ++i){

        if(sistemaUsuarios[i].getSenha() == senha)
            return true;

    }

    return false;
}


int Sistema::checkLogin(const string email, const string senha){

    for(int i=0; i < sistemaIds; ++i){
        if((sistemaUsuarios[i].getEmail() == email) && (sistemaUsuarios[i].getSenha() == senha)){
            return i;
        }
    }

    return -1;

}


bool Sistema::checkServerNome(const string nome){

    for(int i=0; i < sistemaServidores.size(); ++i){

        if(nome == sistemaServidores[i].getServerNome()){
           return false;
        }

    }
    return true;
}


int Sistema::checkDonoServidor(const string nome, int id){
    
        for(int i=0; i < sistemaServidores.size(); ++i){

            if(sistemaServidores[i].getServerNome() == nome){

                if(sistemaServidores[i].getUsuarioDonold() == id){
                    return i; // caso seja o dono
                }

                else{
                    return -2; // caso ele não seja o dono
                }

            }

        }

        return -1;// caso servidor não exista.
}

/*
A1.2 ok
*/
string Sistema::create_user (const string email, const string senha, const string nome) {
    //se não há nenhum email cadastrado no sistema:
    if(checkEmail(email) == false){
        int id_novo_usuario = sistemaIds;
        Usuario novo_usuario(id_novo_usuario, email, senha, nome);
    
        sistemaUsuarios.push_back(novo_usuario);
        ++sistemaIds;
        
        return "Usuário criado com sucesso!";
    }

    else{
        return "Usuário já existe! Tente outro e-mail.";
    }
}


/*
A1.3 ok
*/
string Sistema::login(const string email, const string senha) {

    int login_id = checkLogin(email, senha);

    if(login_id != -1){//login_id == -1 implica que alguma informação fornecida está incorreta.
        sistemaUsuariosLogados.insert({login_id, make_pair("", "")});
        return "Login efetuado com sucesso. Logado como " + email + ".";
    }

    else{
        return "Senha ou e-mail inválidos!";
    }
  
}

/*
A2.1 ok
*/
string Sistema::disconnect(int id) {

    if(sistemaUsuariosLogados.count(id) > 0){ //se tal usuário está logado.
        auto it = sistemaUsuariosLogados.begin();

        for(; it != sistemaUsuariosLogados.end(); ++it)// laço for verificando o local onde está o id do usuário a ser desconectado.
            if(it->first == id)
                break;

        sistemaUsuariosLogados.erase(it);

        return "Usuário " + sistemaUsuarios[id].getEmail() + " desconectado com sucesso.";
    }

    else{
        return "Este usuário não está conectado.";
    }


}

/*
A2.2 ok
*/
string Sistema::create_server(int id, const string nome) {

    if(sistemaUsuariosLogados.count(id) > 0){

        if(checkServerNome(nome) == true) /*se não houver um servidor com esse nome */{
            Servidor novo_servidor(nome, id);
            sistemaServidores.push_back(novo_servidor);

            //**************************************
            //não era um requisito, como falamos o usuário só passa a visualizar se ele estiver no servidor
            //nesse caso como ele não fez enter-server não tem sentido estar visualizando, a menos que vc adicionasse
            //esse usuário ao servidor.
            sistemaUsuariosLogados[id].first = nome; 
            //USUÁRIO PASSA A VISUALIZAR O SERVIDOR.

            return "Servidor [ " + novo_servidor.getServerNome() + " ] criado."; 
        }   

        else{
            return "Servidor com esse nome já existe.";
        }        

    }

    else{
        return "Este usuário não está logado.";
    }


}

/*
A2.3 ok
*/
string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  
    if(sistemaUsuariosLogados.count(id) > 0){
        int ret = checkDonoServidor(nome ,id);

        if(ret != -1 && ret != -2){

            sistemaServidores[ret].setServerDesc(descricao);

            return "Descrição do servidor " + sistemaServidores[ret].getServerNome() + " modificado.";
        }

        else{

            if(ret == -1){
                return "Servidor " + nome + " não existe.\n";
            }

            else{
                return "Você não pode alterar a descrição de um servidor que não foi criado por você.\n";
            }

        }

    }

    else{
        return "Este usuário não está logado.";
    }

}

/*
A2.4 ok
*/
string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  
    if(sistemaUsuariosLogados.count(id) > 0){
        int ret = checkDonoServidor(nome, id);
        
        if(ret != -1 && ret != -2){

            if(!codigo.empty()){

                sistemaServidores[ret].setServerCodigoConvite(codigo);

                return "Código de convite do servidor " + sistemaServidores[ret].getServerNome() + " modificado!\n";
            }

            else{

                sistemaServidores[ret].setServerDesc("");
    
                return "Código de convite do servidor " + sistemaServidores[ret].getServerNome() + " removido!\n";
            }

        }   

        else{

            if(ret == -1){
                return "Servidor " + nome + " não existe.\n";
            }

            else{
                return "Você não pode alterar a descrição de um servidor que não foi criado por você.\n";
            }

        }

    }
    else{
        return "Este usuário não está logado.\n";
    }


}

/*
A2.5 ok!
*/
string Sistema::list_servers(int id) {
  
    if(sistemaUsuariosLogados.count(id) > 0){

        if(sistemaServidores.size() > 0){

            for(int i=0; i < sistemaServidores.size(); ++i){
                cout << sistemaServidores[i].getServerNome() << endl;    
            }

            return "";

        }

        else{
            return "Ainda não há servidores.\n";
        }
        

    }
    
    else{
        return "Este usuário não está logado.\n";
    }

}


/*
A2.6 ok
*/
string Sistema::remove_server(int id, const string nome) {
  
    if(sistemaUsuariosLogados.count(id) > 0){
        int ret = checkDonoServidor(nome, id);
        //remove o servidor e atualiza os usuários q estão visualizando-o.
        if(ret != -1 && ret != -2){
            //removendo servidor.
            for(int i=0; i < sistemaServidores.size(); ++i){

                if(sistemaServidores[i].getServerNome() == nome){

                    sistemaServidores.erase(sistemaServidores.begin()+i);
            
                }
                
            }    
            //removendo usuarios q visualizam o servidor

            for(auto it = sistemaUsuariosLogados.begin(); it != sistemaUsuariosLogados.end(); ++it){

                if(it->second.first == nome){ //aqui vc tb precisa setar o canal pra ""
                    it->second.first = "";
                }
            }

            return "Servidor [ " + nome + " ] removido.\n";
             
        }

        else{

            if(ret == -1){
                return "Servidor [ " + nome + " ] não encontrado\n";
            }

            else{ //caso ele não seja o dono
                return "Você não é dono do servidor [ " + nome + " ].\n";
            }

        }

    }
    
    else{
        return "Este usuário não está logado.\n";
    }

}


string Sistema::enter_server(int id, const string nome, const string codigo) {
  return "enter_server NÃO IMPLEMENTADO";
}


string Sistema::leave_server(int id, const string nome) {
  return "leave_server NÃO IMPLEMENTADO";
}


string Sistema::list_participants(int id) {
  return "list_participants NÃO IMPLEMENTADO";
}


string Sistema::list_channels(int id) {
  return "list_channels NÃO IMPLEMENTADO";
}


string Sistema::create_channel(int id, const string nome) {
  return "create_channel NÃO IMPLEMENTADO";
}


string Sistema::enter_channel(int id, const string nome) {
  return "enter_channel NÃO IMPLEMENTADO";
}


string Sistema::leave_channel(int id) {
  return "leave_channel NÃO IMPLEMENTADO";
}


string Sistema::send_message(int id, const string mensagem) {
  return "send_message NÃO IMPLEMENTADO";
}


string Sistema::list_messages(int id) {
  return "list_messages NÃO IMPLEMENTADO";
}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
