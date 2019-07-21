# Sistema IOT WPAN LE 2019.2 @ IME, a.k.a. CYBERSALA.
<br/>
<br/>

OBJETIVO: Sistema que coleta dados de dispositivos IOT com tecnologia WPAN LE instalados em uma sala, armazena em banco local, e envia cópia para Google Cloud IOT.

FASE1: Coletar RFID.UID e salvar no banco local, que poderá ser acessado para controle dos registros.

FASE2: Enviar info para cloud, e acessar via mobile.

<br/>

## Autor: 
<br/>
1.	Daniel Benicio de F. Alves (beniciomail at gmail . com)
<br/>
2.	Matheus Mattos (matheus . mattos18 at gmail . com)
<br/>
3.
<br/>
4.
<br/>    
<br/>

## MIT License 
A short and simple permissive license with conditions only requiring preservation of copyright and license notices. Licensed works, modifications, and larger works may be distributed under different terms and without source code.
<br/>
###Permissions
+ Commercial use
+ Modification
+ Distribution
+ Private use
###Limitations
+ Liability
+ Warranty
<br/>
-------
<br/>
Copyright (c) 2019 Daniel
<br/>
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
<br/>
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
<br/>
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
<br/>
-------
<br/>
<br/>

# Lista de Mudancas Principais
20/07/19 - Upload e versionamento fonte prototipo com GIT
<br/>
<br/>

# Operacao:
<br/>
### (FALTA DOCUMENTAR)
<br/>
<br/>



# Arquitetura
<br/>
## Modelagem do sistema:
<br/>
### (FALTA DOCUMENTAR)
<br/>
<br/>

## Estrutura do Fonte:
<br/>
sensor.sh     - script que conecta ao sensor e salva as informações regularmente na base de dados.
<br/>
<br/>


## Requisitos:
<br/>
### (FALTA DOCUMENTAR)
<br/>
<br/>


## DEV ROADMAP:
Para sincronizar o fonte, efetuar os passos abaixo:\
1. Baixe e instale o GIT BASH a partir do site  https://git-scm.com/download/win 
2. Acesse a raiz \do servidor de páginas, conforme descrito anteriormente.
3. Clone o repositório com o comando
```bash
git clone https://github.com/dbeniciorj/CYBERSALA/
```
<br/>    
OBS: Mais instruções para operações com GIT em https://rogerdudler.github.io/git-guide/ 
<br/>
<br/>




///////////////////////////////	INST. REQS.
<br/>
S.O. UBUNTU 18.04 LTS
sudo apt-get install php7.2 apache2 php7.2-mysql mysql-server unzip bluez
<br/>
<br/>

///////////////////////////////	REDEF. MYSQL-SERVER PASS @ DEBIAN-LIKE
<br/>
sudo service mysql stop
<br/>
sudo mkdir /var/run/mysqld
<br/>
sudo chmod 777  /var/run/mysqld
<br/>
sudo /usr/bin/mysqld_safe --skip-grant-tables --daemonize --pid-file=/run/mysqld/mysqld.pid 2>/dev/null &  
<br/>
mysql -b mysql -u root -e "UPDATE user SET plugin='mysql_native_password' WHERE User='root'"
<br/>
mysql -b mysql -u root -e "update user set authentication_string=PASSWORD('XXXXXXXX') where User='root'"
<br/>
mysql -b mysql -u root -e "flush privileges"
<br/>
sudo pkill -9 mysqld
<br/>
sudo rm -r /var/run/mysqld
<br/>
sudo service mysql start
<br/>
<br/>
/////////////////////////////// INSTALL SQL ADMIN APP
<br/>
cd /var/www/
<br/>
sudo rm -r html/
<br/>
sudo git clone https://github.com/Frecuencio/sqlbuddy-php7.git
<br/>
sudo mv sqlbuddy-php7 html
<br/>
<br/>
/////////////////////////////// BASE
<br/>
mysql -u root -p -e "CREATE DATABASE iot"
<br/>
mysql -u root -p -e "CREATE USER 'iot'@'localhost' IDENTIFIED BY '3fedfwre@KD&'"
<br/>
mysql -u root -p -e "GRANT ALL PRIVILEGES ON iot.* TO 'iot'@'localhost'"
<br/>
mysql -u root -p -e "CREATE TABLE iot.presenca ( id int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,timeStamp TIMESTAMP NOT NULL , uid varchar (11) NOT NULL)"
<br/>
mysql -u root -p -e "CREATE TABLE iot.cartao ( uid varchar(11) NOT NULL PRIMARY KEY, nome varchar (45) NOT NULL)"
<br/>
<br/>
/////////////////////////////// SHELLSCRIPT\
<br/>
APÓS COPIAR SCRIPT E DAR PERMISSÃO DE EXECUÇÃO, AGENDAR EXECUÇÃO REGULAR DO MESMO. EXEMPLO:\
<br/>
chmod +x /usr/local/bin/sensor.sh
<br/>
echo "*/2 * * * *   root    /usr/local/bin/sensor.sh" >> /etc/crontab
<br/>
sudo service cron restart
<br/>
<br/>
/////////////////////////////// SENSOR
<br/>
### (FALTA DOCUMENTAR)
<br/>
<br/>
