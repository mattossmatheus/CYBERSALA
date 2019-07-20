# Sistema IOT WPAN LE 2019.2 @ IME, a.k.a. CYBERSALA.



OBJETIVO: Sistema que coleta dados de dispositivos IOT com tecnologia WPAN LE instalados em uma sala, armazena em banco local, e envia cópia para Google Cloud IOT.

FASE1: Coletar RFID.UID e salvar no banco local, que poderá ser acessado para controle dos registros.

FASE2: Enviar info para cloud, e acessar via mobile.



## Autor: 
1.	Daniel Benicio de F. Alves (beniciomail at gmail . com)

2.	Matheus Mattos (matheus . mattos18 at gmail . com)

3.

4.
    
	
## MIT License 
A short and simple permissive license with conditions only requiring preservation of copyright and license notices. Licensed works, modifications, and larger works may be distributed under different terms and without source code.

Permissions
+ Commercial use
+ Modification
+ Distribution
+ Private use
Limitations
+ Liability
+ Warranty

-------
Copyright (c) 2019 Daniel


Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-------



# Lista de Mudancas Principais
20/07/19 - Upload e versionamento fonte prototipo com GIT



# Operacao:

### (FALTA DOCUMENTAR)





# Arquitetura

## Modelagem do sistema:

### (FALTA DOCUMENTAR)



## Estrutura do Fonte:

### (FALTA DOCUMENTAR)




## Requisitos:

### (FALTA DOCUMENTAR)




## DEV ROADMAP:
Para sincronizar o fonte, efetuar os passos abaixo:\
1. Baixe e instale o GIT BASH a partir do site  https://git-scm.com/download/win 
2. Acesse a raiz \do servidor de páginas, conforme descrito anteriormente.
3. Clone o repositório com o comando
```bash
git clone https://github.com/dbeniciorj/RP-PID
```
<br/>    
OBS: Mais instruções para operações com GIT em https://rogerdudler.github.io/git-guide/ 






///////////////////////////////	INST. REQS.

S.O. UBUNTU 18.04 LTS
sudo apt-get install php7.2 apache2 php7.2-mysql mysql-server unzip bluez



///////////////////////////////	REDEF. MYSQL-SERVER PASS @ DEBIAN-LIKE

sudo service mysql stop

sudo mkdir /var/run/mysqld

sudo chmod 777  /var/run/mysqld

sudo /usr/bin/mysqld_safe --skip-grant-tables --daemonize --pid-file=/run/mysqld/mysqld.pid 2>/dev/null &  
  
mysql -b mysql -u root -e "UPDATE user SET plugin='mysql_native_password' WHERE User='root'"

mysql -b mysql -u root -e "update user set authentication_string=PASSWORD('XXXXXXXX') where User='root'"

mysql -b mysql -u root -e "flush privileges"

sudo pkill -9 mysqld

sudo rm -r /var/run/mysqld

sudo service mysql start


/////////////////////////////// INSTALL SQL ADMIN APP

cd /var/www/

sudo rm -r html/

sudo git clone https://github.com/Frecuencio/sqlbuddy-php7.git

sudo mv sqlbuddy-php7 html


/////////////////////////////// BASE

mysql -u root -p -e "CREATE DATABASE iot"

mysql -u root -p -e "CREATE USER 'iot'@'localhost' IDENTIFIED BY '3fedfwre@KD&'"

mysql -u root -p -e "GRANT ALL PRIVILEGES ON iot.* TO 'iot'@'localhost'"

mysql -u root -p -e "CREATE TABLE iot.presenca ( id int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,timeStamp TIMESTAMP NOT NULL , uid varchar (11) NOT NULL)"

mysql -u root -p -e "CREATE TABLE iot.cartao ( uid varchar(11) NOT NULL PRIMARY KEY, nome varchar (45) NOT NULL)"


/////////////////////////////// SHELLSCRIPT
// Script simulação do sensor criado abaixo, com anterior (DHT11) desabilitado.
// Ver atual no repositório.
////////////////////////////////////////////

echo '#!/bin/bash
BTMAC="24:0A:C4:9A:E8:EA"
DB=iot
DBPWD="3fedfwre@KD&"
# READ="$(gatttool -b $BTMAC --char-read --handle=0x002a 2>&1)"
# if [[ $READ =~ "refused" ]]; then
#      logger –t $0 "DEV $BTMAC nao encontrado."
# else
#     ANSW="$(echo $READ | cut -d : -f2| xxd -r -p)"
#     # echo ANSW= $ANSW
#     TEMP=$(echo $ANSW|cut -d "," -f1)
#     HUMD=$(echo $ANSW|cut -d "," -f2)
#     # echo TEMP= $TEMP
#     # echo HUMD= $HUMD
#     mysql $DB -u $DB -p$DBPWD -e "insert into tempLog values (now()- INTERVAL 3 HOUR,$TEMP,$HUMD)" 2>&1 | logger -t $0
# 
# fi
hexchars="0123456789ABCDEF"
uid=$( for i in {1..6} ; do echo -n ${hexchars:$(( $RANDOM % 16 )):1} ; done | sed -e "s/\(..\)/:\1/g" )
mysql -s -u $DB -p$DBPWD -e "insert into $DB.presenca (timestamp,uid) values (now() - INTERVAL 3 HOUR,\"00$uid\")" 
' > ~/sensor.sh

sudo mv ~/sensor.sh /usr/local/bin/sensor.sh

chmod +x /usr/local/bin/sensor.sh

echo "*/2 * * * *   root    /usr/local/bin/sensor.sh" >> /etc/crontab

sudo service cron restart


/////////////////////////////// SENSOR

### (FALTA DOCUMENTAR)


