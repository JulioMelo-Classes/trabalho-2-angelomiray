create-user billy2@florida.com billypass2 Billy2
create-user billy@florida.com billypass Billy
create-user mandy@detroit.com mandypass Mandy
create-user reaper@death.com reaperpass Reaper
create-user jimmy@jimmy.com jimmypass Jimmy
login billy@florida.com billypass
login mandy@detroit.com mandypass
login reaper@death.com reaperpass
create-server 1 TESTING123
create-server 1 TESTING123_pass
set-server-invite-code 1 TESTING123_pass pass
create-server 2 emos_only
create-server 3 Grim-Hideout
create-server 3 Bone-Enthusiasts
enter-server 1 TESTING123
enter-server 2 TESTING123
enter-server 3 TESTING123
create-channel 1 canal1
create-channel 1 canal1_2
enter-channel 1 canal1
enter-channel 2 canal1


#ctb2.1.1_ctb2.2.1 send message e list message
send-message 1 teste se funcionaaaaa!
send-message 2 funciono?
list-messages 1
list-messages 2

#ctb2.1.2 send message em canal vazio
send-message 3 não estou em qualquer canal

#ctb2.2.2 list message em canal vazio
list-messages 3

#ctb2.2.3 list message em canal vazio
enter-channel 1 canal1_2
list-messages 1

#ctb2.2.4 list message em usuario inexistente e usuario não logado
list-messages 4
list-messages 6

#ctb2.1.4 send message em usuario inexistente e usuario não logado
send-message 4 teste1!
send-message 6 wut?

quit
