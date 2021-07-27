#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include <string>
#include <vector>
#include "mensagem.h"

using namespace std;

class CanalTexto{
	private:
        string ctNome; //O nome do canal, conforme o comando create-channel
        vector<Mensagem> ctMensagens; //Um vector com mensagens que foram enviadas neste canal
};

#endif
