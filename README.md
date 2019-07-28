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

### Permissions
+ Commercial use
+ Modification
+ Distribution
+ Private use
### Limitations
+ Liability
+ Warranty
<br/>
-------
<br/>
<br/>
Copyright (c) 2019 Daniel
<br/>
<br/>
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
<br/>
<br/>
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
<br/>
<br/>
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
<br/>
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
## Lista de componentes:
<br/>
= Microcontrolador ESP32
<br/>
= Protoboard
<br/>
= LEDs
<br/>
= 2x resistores de 330 ohms (lar/lar/mar/*)
<br/>
= Sensor RFID RC522
<br/>
= Cartes RFID para testar (riocardo, crachá de identificação, etc...)
<br/>
### (FALTA TERMINAR DE DOCUMENTAR)
<br/>
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
<br/>
```bash
sudo apt-get install mysql-server unzip bluez
```
<br/>
<br/>

///////////////////////////////	REDEF. MYSQL-SERVER PASS @ DEBIAN-LIKE
<br/>
```bash
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
```
<br/>
<br/>
/////////////////////////////// BASE
<br/>
```bash
mysql -u root -p -e \"CREATE DATABASE iot\"
mysql -u root -p -e \"CREATE USER \'iot\'@\'localhost\' IDENTIFIED BY \'3fedfwre@KD&\'"\
mysql -u root -p -e \"GRANT ALL PRIVILEGES ON iot.* TO \'iot\'@'localhost\'\"
mysql -u root -p -e \"CREATE TABLE iot.presenca ( id int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,timeStamp TIMESTAMP NOT NULL , uid varchar (11) NOT NULL)\"
mysql -u root -p -e \"CREATE TABLE iot.cartao ( uid varchar(11) NOT NULL PRIMARY KEY, nome varchar (45) NOT NULL)\"
```
<br/>
<br/>
/////////////////////////////// EXIBIR LISTA DE ACESSOS DIRETO DO TERMINAL (OPCIONAL)
<br/>
```bash
PASS="3fedfwre@KD&"
watch -n2 "/opt/lampp/bin/mysql -b iot -p$PASS -e \"select presenca.timestamp,presenca.uid,cartao.nome from presenca left join cartao on (presenca.uid=cartao.uid)\""
```
<br/>
/////////////////////////////// SHELLSCRIPT
<br/>
APÓS COPIAR SCRIPT E DAR PERMISSÃO DE EXECUÇÃO, AGENDAR EXECUÇÃO REGULAR DO MESMO. EXEMPLO:\
<br/>
```bash
chmod +x /usr/local/bin/sensor.sh
echo "*/2 * * * *   root    /usr/local/bin/sensor.sh" >> /etc/crontab
sudo service cron restart
```
<br/>
<br/>
/////////////////////////////// SENSOR
<br/>
Já com a Arduino IDE instalada, execute-a e clique em Arquivo->Preferências. Depois em "URLs adicionais para gerenciadores de placas" adcionar o endereço https://dl.espressif.com/dl/package_esp32_index.json .
<br/>
Durante o desenvolvimento utitlizar a placa "ESP32 Dev Module" como especificação da placa. E atentar para a seleçã da porta serial utilizada para subir o código abaixo para o microcontrolador.
<br/>
### (FALTA TERMINAR DE DOCUMENTAR)
<br/>
<br/>
