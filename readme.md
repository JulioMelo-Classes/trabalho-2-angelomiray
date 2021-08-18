# Compilação
Nesta sessão será abordada a forma de compilação do projeto.

## Dependências

- Compilador C++.

- cmake.

Entre no diretório `build`. 

    cd build

Execute o comando do cmake para compilar o projeto:

    cmake --build .


# Execução 
Para executar o projeto: 

    ./concordo 

Para interagir com o programa, segue a lista de comandos: 

    Sair do sistema : comando quit

    Criar usuário : comando create-user <email> <senha_sem_espaços> <nome com espaços>

    Entrar no sistema : login <email> <senha>

    Desconectar do Concordo : comando disconnect <id-de-usuario-logado>
    
    Criar servidores : comando create-server <id-de-usuario-logado> <nome>

    Setar código de convite para o servidor : comando set-server-invite-code <id-de-usuario-logado> <nome> <codigo>

    Listar servidores : comando list-servers <id-de-usuario-logado> 

    Remover servidor: comando remove-server <id-de-usuario-logado>  <nome>

    Entrar em um servidor: comando enter-server <id-de-usuario-logado> <nome>

    Sair de um servidor: comando leave-server <id-de-usuario-logado> <nome>

    Listar pessoas no servidor: comando list-participants <id-de-usuario-logado>

    Listar canais do servidor : comando list-channels <id-de-usuario-logado>

    Criar um canal no servidor : comando create-channel <id-de-usuario-logado> <nome> 
    
    Entrar em um canal do servidor: comando 
    enter-channel <id-de-usuario-logado> <nome> 

    Sair do canal : comando leave-channel <id-de-usuario-logado>

    Enviar mensagem para o canal : comando send-message <id-de-usuario-logado> <mensagem>

    Visualizar mensagens do canal : comando list-messages <id-de-usuario-logado>

Além da interação em tempo de execução, pode-se interagir através de um arquivo de texto com os comando. Para isso, crie um arquivo em `build/test_cases` e insira um comando por linha. Nesta mesma pasta há outros arquivos de testes que podem servir como exemplo.
Sendo assim, para executar via arquivo: 

    ./concordo < test_cases/nome_arquivo.txt


# Execução dos arquivos de teste
<!--casos de teste ok-->
Nesta sessão serão abordados os resultados dos arquivos de testes que estão inseridos em `build/test_cases`.

## base_test
Cria um usuário e executa todos os outros comandos. 

- input:
``` 
    create-user jack@email.com jacksenha Jack
    login jack@email.com jacksenha
    create-server 0 SERVER-DO-JACK
    list-servers 0 
    set-server-invite-code 0 SERVER-DO-JACK CODIGOJACK
    enter-server 0 SERVER-DO-JACK CODIGOJACK
    list-participants 0
    create-channel 0 channel1
    list-channels 0
    enter-channel 0 channel1
    send-message 0 Something in the way
    send-message 0 High hopes
    list-messages 0
    leave-channel 0
    leave-server 0 SERVER-DO-JACK
    remove-server 0 SERVER-DO-JACK 
    disconnect 0
    quit
```
- output:
``` 
    Usuário criado com sucesso!

    Login efetuado com sucesso. Logado como jack@email.com.

    Servidor [ SERVER-DO-JACK ] criado.

    SERVER-DO-JACK

    Código de convite do servidor SERVER-DO-JACK modificado!

    Entrou no servidor com sucesso.

    Jack

    Canal de texto [ channel1 ] criado com sucesso. 

    # Canais de texto 
    channel1

    Entrou no canal [ channel1 ] com sucesso. 

    Mensagem enviada. 

    Mensagem enviada. 

    Jack<10/08/21 - 01:33> : Something in the way
    Jack<10/08/21 - 01:33> : High hopes

    Você saiu do canal [ channel1 ].

    Usuário removido do servidor [ SERVER-DO-JACK ] com sucesso.

    Servidor [ SERVER-DO-JACK ] removido.

    Usuário jack@email.com desconectado com sucesso.

    Saindo do concordo...

```
    
## special_case.txt
Arquivo testando situações sucetíveis à erros, visando verificar a corretude do comportamento do programa.

- input:
``` 
    create-user isaacfranco@imd.ufrn.br senhalegal Isaac Franco Fernandes 
    create-user isaacfranco@imd.ufrn.br senhalegal Isaac Franco Fernandes
    create-user renan@imd.ufrn.br senha Renan
    create-user julio@imd.ufrn.br senha Julio
    login isaacfranco@imd.ufrn.br senhalegal
    disconnect 0
    disconnect 1
    login isaacfranco@imd.ufrn.br SENHA_ERRADA
    login isaacfranco@imd.ufrn.br senhalegal
    create-server 0 servidor-legal
    set-server-desc 0 servidor-legal Um servidor muito banaca e coisa e tal
    create-server 0 servidor-ruim
    set-server-desc 0 servidor-ruim Um servidor lixo total
    set-server-invite-code 0 servidor-legal 123
    disconnect 0
    set-server-invite-code 0 servidor-legal 456
    login renan@imd.ufrn.br senha Renan
    set-server-invite-code 1 servidor-legal 789
    login isaacfranco@imd.ufrn.br senhalegal
    set-server-invite-code 0 servidor-legal 321
    set-server-invite-code 0 servidor-legal
    set-server-invite-code 0 servidor-inexistente 123
    set-server-invite-code 0 servidor-inexistente
    disconnect 0
    list-servers
    login isaacfranco@imd.ufrn.br senhalegal
    list-servers
    remove-server 0 servidor-inexistente
    remove-server 0 servidor-legal
    list-servers
    disconnect 0
    remove-server 0 servidor-ruim
    login isaacfranco@imd.ufrn.br senhalegal
    remove-server 0 servidor-ruim
    create-server 0 servidor-bacana
    create-server 0 servidor-fuderoso
    list-servers
    enter-server 0 servidor-bacana
    leave-server 0 servidor-bacana
    list-servers
    login isaacfranco@imd.ufrn.br senhalegal
    remove-server 0 servidor-bacana
    enter-server 0 servidor-bacana
    list-participants 0
    login renan@imd.ufrn.br senha
    create-server 1 servidor-sinistro
    enter-server 1 servidor-sinistro
    login julio@imd.ufrn.br senha
    enter-server 2 servidor-sinistro
    login isaacfranco@imd.ufrn.br senhalegal
    enter-server 0 servidor-sinistro
    list-participants 0
    quit
    create-user naodeveprocessar@imd.ufrn.br naodevechegaraqui Não deve chegar aqui

```
- output:
``` 
    Usuário criado com sucesso! 

    Usuário já existe! Tente outro e-mail. 

    Usuário criado com sucesso! 

    Usuário criado com sucesso! 

    Login efetuado com sucesso. Logado como isaacfranco@imd.ufrn.br. 

    Usuário isaacfranco@imd.ufrn.br desconectado com sucesso. 

    Este usuário não está conectado. 

    Senha ou e-mail inválidos! 

    Login efetuado com sucesso. Logado como isaacfranco@imd.ufrn.br. 

    Servidor [ servidor-legal ] criado. 

    Descrição do servidor servidor-legal modificado. 

    Servidor [ servidor-ruim ] criado. 

    Descrição do servidor servidor-ruim modificado. 

    Código de convite do servidor servidor-legal modificado!

    Usuário isaacfranco@imd.ufrn.br desconectado com sucesso. 

    Este usuário não está logado.

    Login efetuado com sucesso. Logado como renan@imd.ufrn.br. 

    Você não pode alterar o código de convite de um servidor que não foi criado por você.

    Login efetuado com sucesso. Logado como isaacfranco@imd.ufrn.br. 

    Código de convite do servidor servidor-legal modificado!

    Código de convite do servidor servidor-legal removido!

    Servidor servidor-inexistente não existe.

    Servidor servidor-inexistente não existe.

    Usuário isaacfranco@imd.ufrn.br desconectado com sucesso. 

    Comando precisa ser precedido de um id [list-servers]
    Login efetuado com sucesso. Logado como isaacfranco@imd.ufrn.br. 

    Comando precisa ser precedido de um id [list-servers]
    Servidor [ servidor-inexistente ] não encontrado

    Servidor [ servidor-legal ] removido.

    Comando precisa ser precedido de um id [list-servers]
    Usuário isaacfranco@imd.ufrn.br desconectado com sucesso. 

    Este usuário não está logado.

    Login efetuado com sucesso. Logado como isaacfranco@imd.ufrn.br. 

    Servidor [ servidor-ruim ] removido.

    Servidor [ servidor-bacana ] criado. 

    Servidor [ servidor-fuderoso ] criado. 

    Comando precisa ser precedido de um id [list-servers]
    Entrou no servidor com sucesso.

    Usuário removido do servidor [ servidor-bacana ] com sucesso.

    Comando precisa ser precedido de um id [list-servers]
    Você já está logado como isaacfranco@imd.ufrn.br. 

    Servidor [ servidor-bacana ] removido.

    Servidor [ servidor-bacana ] não existe.

    Você não está visualizando qualquer servidor. 

    Você já está logado como renan@imd.ufrn.br. 

    Servidor [ servidor-sinistro ] criado. 

    Entrou no servidor com sucesso.

    Login efetuado com sucesso. Logado como julio@imd.ufrn.br. 

    Entrou no servidor com sucesso.

    Você já está logado como isaacfranco@imd.ufrn.br. 

    Entrou no servidor com sucesso.

    Renan
    Julio
    Isaac Franco Fernandes 

    Saindo do concordo...
```