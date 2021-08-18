#include "../include/sistema.h"
#include "../include/executor.h"
#include "../include/mensagem.h"
#include "../include/servidor.h"
#include "../include/usuario.h"
#include "../include/canaltexto.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;


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


int Sistema::checkServerExists(const string nomeServer){

    for(int i=0; i < sistemaServidores.size(); ++i){
        if(sistemaServidores[i].getServerNome() == nomeServer)
            return i;
    }

    return -1;
}


/****************************  COMANDOS   **********************/


string Sistema::create_user (const string email, const string senha, const string nome) {
    //se não há nenhum email cadastrado no sistema:
    if(checkEmail(email) == false){
        int id_novo_usuario = sistemaIds;
        Usuario novo_usuario(id_novo_usuario, email, senha, nome);
    
        sistemaUsuarios.push_back(novo_usuario);
        ++sistemaIds;
        
        return "Usuário criado com sucesso! \n";
    }

    else{
        return "Usuário já existe! Tente outro e-mail. \n";
    }
}


string Sistema::login(const string email, const string senha) {

    int login_id = checkLogin(email, senha);


    if(login_id != -1){//login_id == -1 implica que alguma informação fornecida está incorreta.
        if(sistemaUsuariosLogados.count(login_id) > 0){
            return "Você já está logado como " + email + ". \n";
        }
        
        else{
            sistemaUsuariosLogados.insert({login_id, make_pair("", "")});
            return "Login efetuado com sucesso. Logado como " + email + ". \n";
        }
    }

    else{
        return "Senha ou e-mail inválidos! \n";
    }
  
}


string Sistema::disconnect(int id) {

    if(sistemaUsuariosLogados.count(id) > 0){ //se tal usuário está logado.
        auto it = sistemaUsuariosLogados.begin();

        for(; it != sistemaUsuariosLogados.end(); ++it)// laço for verificando o local onde está o id do usuário a ser desconectado.
            if(it->first == id)
                break;

        sistemaUsuariosLogados.erase(it);

        return "Usuário " + sistemaUsuarios[id].getEmail() + " desconectado com sucesso. \n";
    }

    else{
        return "Este usuário não está conectado. \n";
    }


}


string Sistema::create_server(int id, const string nome) {

    if(sistemaUsuariosLogados.count(id) > 0){

        if(checkServerNome(nome) == true) /*se não houver um servidor com esse nome */{
            Servidor novo_servidor(nome, id);
            sistemaServidores.push_back(novo_servidor);

            return "Servidor [ " + novo_servidor.getServerNome() + " ] criado. \n"; 
        }   

        else{
            return "Servidor com esse nome já existe. \n";
        }        

    }

    else{
        return "Este usuário não está logado. \n";
    }


}


string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  
    if(sistemaUsuariosLogados.count(id) > 0){
        int ret = checkDonoServidor(nome ,id);

        if(ret != -1 && ret != -2){

            sistemaServidores[ret].setServerDesc(descricao);

            return "Descrição do servidor " + sistemaServidores[ret].getServerNome() + " modificado. \n";
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
        return "Este usuário não está logado. \n";
    }

}


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
                return "Você não pode alterar o código de convite de um servidor que não foi criado por você.\n";
            }

        }

    }
    else{
        return "Este usuário não está logado.\n";
    }


}


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


string Sistema::remove_server(int id, const string nome) {
  
    if(sistemaUsuariosLogados.count(id) > 0){
        int ret = checkDonoServidor(nome, id);
        //remove o servidor e atualiza os usuários q estão visualizando-o.
        if(ret != -1 && ret != -2){
            //removendo servidor.
            for(int i=0; i < sistemaServidores.size(); ++i){

                if(sistemaServidores[i].getServerNome() == nome){
                    sistemaServidores[i].excluirCanaisTexto();
                    sistemaServidores.erase(sistemaServidores.begin()+i);
                    break;
                }
                
            }    
            //removendo usuarios q visualizam o servidor

            for(auto it = sistemaUsuariosLogados.begin(); it != sistemaUsuariosLogados.end(); ++it){
                if(it->second.first == nome){
                    it->second.first = "";
                    it->second.second = "";
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

/*
A2.7 0,6
Esse método permite que mais de uma cópia de um usuário entre no servidor, vou remover 20% por isso. Dá para
você testar fazendo enter-server id server duas vezes com o mesmo id no mesmo servidor.
*/
string Sistema::enter_server(int id, const string nome, const string codigo) {

    if(sistemaUsuariosLogados.count(id) > 0){
        
        /*o server é aberdo quando o código _DELE_ é diferente de vazio e não quando o usuário 
        envia o código vazio. Dessa forma que vc vez o sistema permite que usuários entrem
        no servidor mesmo que ele tenha senha, bastando mandar sem senha. Vou remover 20% por isso*/
        if(codigo.empty()){//se o server for aberto
            int ret = checkServerExists(nome);

            if(ret != -1){// ret == -1 implica que o servidor não existe.
                sistemaServidores[ret].addUserToServer(id);
                sistemaUsuariosLogados[id].first = nome;

                return "Entrou no servidor com sucesso.\n";
            }

            else{
                return "Servidor [ " + nome + " ] não existe.\n";
            }

        }

        else{
            int ret = checkServerExists(nome);

            if(ret != -1){//se o servidor existir

                if(sistemaServidores[ret].getUsuarioDonold() == id){//caso ele seja o dono, não precisa de convite
                    sistemaServidores[ret].addUserToServer(id);
                    sistemaUsuariosLogados[id].first = nome;

                    return "Entrou no servidor com sucesso.\n";
                }

                else{ //caso não seja o dono

                    if(sistemaServidores[ret].getServerCodigoConvite() == codigo){
                        sistemaServidores[ret].addUserToServer(id);
                        sistemaUsuariosLogados[id].first = nome;

                        return "Entrou no servidor com sucesso.\n";
                    }

                    else{
                        return "Código fornecido é inválido.\n";
                    }

                }
            }

            else{
                return "Servidor [ " + nome + " ] não existe.\n";
            }

        }

        return "";
    }

    else{
        return "Este usuário não está logado.\n";
    }

}


/*
A2.8 ok
*/
string Sistema::leave_server(int id, const string nome) {
    
    if(sistemaUsuariosLogados.count(id) > 0){
        int ret = checkServerExists(nome);
        //sistemaServidores[ret].addUserToServer(id);
        if(ret != -1){
            //caso o usuário tenha sido removido, retorna true
            if(sistemaServidores[ret].removeUserFromServer(id) == true){

                if(sistemaUsuariosLogados[id].first == nome){ //caso esteja visualizando o servidor.
                    sistemaUsuariosLogados[id].first = "";
                    sistemaUsuariosLogados[id].second = "";
                }

                return "Usuário removido do servidor [ " + sistemaServidores[ret].getServerNome() + " ] com sucesso.\n";
            }

            else{ //ele só não é removido se não estiver em tal servidor.
                return "Você não está no servidor [ " + sistemaServidores[ret].getServerNome() + " ].\n";
            }
        }

        else{
            return "Este servidor não existe.\n";
        }
    } 

    else{
        return "Este usuário não está logado.\n";
    }

}


/*
A2.9 ok
*/
string Sistema::list_participants(int id) {

    if(sistemaUsuariosLogados.count(id) > 0){

        if(sistemaUsuariosLogados[id].first != ""){ // se ele estiver visualizando algum servidor.        

            for(int i=0; i < sistemaServidores.size(); ++i){

                if(sistemaServidores[i].getServerNome() == sistemaUsuariosLogados[id].first){

                    sistemaServidores[i].printListaUsuariosServidor(sistemaUsuarios);
                    break;
                }     

            }   
                    
            return "";

        }

        else{
            return "Você não está visualizando qualquer servidor. \n";
        }

    }

    else{
        return "Este usuário não está logado. \n";
    }
}


/*
B1.1 ok
*/
string Sistema::list_channels(int id) {

    if(sistemaUsuariosLogados.count(id) > 0){

        if(sistemaUsuariosLogados[id].first != ""){ // se ele estiver visualizando algum servidor.        

            for(int i=0; i < sistemaServidores.size(); ++i){

                if(sistemaServidores[i].getServerNome() == sistemaUsuariosLogados[id].first){

                    sistemaServidores[i].printListaCanaisServidor();
                    break;
                }     

            }   
                    
            return "";

        }

        else{
            return "Você não está visualizando qualquer servidor. \n";
        }
    }

    else{
        return "Este usuário não está logado. \n";
    }


}

/*
B1.2 ok
*/
string Sistema::create_channel(int id, const string nome) {

    if(sistemaUsuariosLogados.count(id) > 0){

        if(sistemaUsuariosLogados[id].first != ""){ // se ele estiver visualizando algum servidor.        

            for(int i=0; i < sistemaServidores.size(); ++i){

                if(sistemaServidores[i].getServerNome() == sistemaUsuariosLogados[id].first){

                    if(sistemaServidores[i].addCanalTexto(nome) == true){ //não precisa comparar com true/false quando as funções retornam bool
                        return "Canal de texto [ " + nome + " ] criado com sucesso. \n";
                    }
                    else{
                        return "Canal de texto [ " + nome + " ] já existe! \n";
                    }
                    
                }     

            }   
                    
            return "";

        }

        else{
            return "Você não está visualizando qualquer servidor. \n";
        }   

    }

    else{
        return "Este usuário não está logado. \n";
    }
}

/*
B1.3 ok
*/
string Sistema::enter_channel(int id, const string nome) {
    
    if(sistemaUsuariosLogados.count(id) > 0){

        if(sistemaUsuariosLogados[id].first != ""){ // se ele estiver visualizando algum servidor.        

            for(int i=0; i < sistemaServidores.size(); ++i){

                if(sistemaServidores[i].getServerNome() == sistemaUsuariosLogados[id].first){

                    if(sistemaServidores[i].checkCanalExiste(nome) == true){
                        sistemaUsuariosLogados[id].second = nome;
                        return "Entrou no canal [ " + nome + " ] com sucesso. \n";
                    }
                    else{
                        return "Canal [ " + nome + " ] não existe. \n";
                    }

                }   

            }   
                    
            return "";

        }

        else{
            return "Você não está visualizando qualquer servidor. \n";
        }   

    }

    else{
        return "Este usuário não está logado. \n";
    }

}

/*
B1.4 ok
*/
string Sistema::leave_channel(int id) {
    
    if(sistemaUsuariosLogados.count(id) > 0){

        if(sistemaUsuariosLogados[id].first != ""){ // se ele estiver visualizando algum servidor.        

            if(sistemaUsuariosLogados[id].second != ""){
                cout << "Você saiu do canal [ " + sistemaUsuariosLogados[id].second + " ]." << endl;
                sistemaUsuariosLogados[id].second = "";
                return "";
            }

            else{
                return "Você não está visualizando qualquer canal. \n";
            }

        }

        else{
            return "Você não está visualizando qualquer servidor. \n";
        }   

    }

    else{
        return "Este usuário não está logado. \n";
    }
}

/*
B2.1 ok
*/
string Sistema::send_message(int id, const string mensagem) {
  
    if(sistemaUsuariosLogados.count(id) > 0){

        if(sistemaUsuariosLogados[id].first != ""){ // se ele estiver visualizando algum servidor.        

            if(sistemaUsuariosLogados[id].second != ""){ //se ele estiver visualizando algum canal
                
                for(int i=0; i < sistemaServidores.size(); ++i){

                    if(sistemaServidores[i].getServerNome() == sistemaUsuariosLogados[id].first){

                        for(int i=0; i < sistemaUsuarios.size(); ++i){ 
                            if(sistemaUsuarios[i].getID() == id){
                                string who_send = sistemaUsuarios[i].getNome();
                                sistemaServidores[i].addMsgToChannel(id, mensagem, sistemaUsuariosLogados[id].second, who_send);
                            
                                return "Mensagem enviada. \n";
                            }
                            
                        }

                        return "";
                    }
                }

                return "";

            }

            else{
                return "Você não está visualizando qualquer canal. \n";
            }

        }

        else{
            return "Você não está visualizando qualquer servidor. \n";
        }   
        
    }

    else{
        return "Este usuário não está logado. \n";
    }

}

/*
B2.2 0,5
Embora o sistema diga que as mensagens são envaidas eu não consegui testar, caso de teste adicionando na pasta data
vou considerar 50%
*/
string Sistema::list_messages(int id) {
  
    if(sistemaUsuariosLogados.count(id) > 0){

        if(sistemaUsuariosLogados[id].first != ""){ // se ele estiver visualizando algum servidor.        

            if(sistemaUsuariosLogados[id].second != ""){

                for(int i=0; i < sistemaServidores.size(); ++i){

                    if(sistemaServidores[i].getServerNome() == sistemaUsuariosLogados[id].first){
                        //cout << "sistema - aqui 1.1" << endl;
                        sistemaServidores[i].printMsgFromChannel(sistemaUsuariosLogados[id].second);
                        //cout << "sistema - aqui 2.1" << endl;

                        return "";
                    }
                }
                
                return "";

            }

            else{
                return "Você não está visualizando qualquer canal. \n";
            }

        }

        else{
            return "Você não está visualizando qualquer servidor. \n";
        } 
    }
    
    else{
        return "Este usuário não está logado. \n";
    }

}
