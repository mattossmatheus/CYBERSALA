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
= Sensor Mifare MFRC522 (NXP RC522), a.k.a. RFID-RC522
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
RFID.ino      - programação do microcrontrolador ESP32.
<br/>
<br/>


## Requisitos:
<br/>
1. S.O. UBUNTU 18.04 LTS (pode usar a IDE, cujo uso é pontual, em qualquer plataforma; aqui sistema definido para persistência de dados)
2. Arduino IDE.
3. Libs BLE, RC522 e ESP32 ( https://dl.espressif.com/dl/package_esp32_index.json ) a IDE.
<br/>
<br/>

**OBS:** Para instalação básica: 
1 - instalar os requisitos acima e disponibilizar o código no servidor. 
2 - subir o código RFID.ino para o microcontrolador ESP32.


## DEV ROADMAP:
Para sincronizar o fonte, efetuar os passos abaixo (ou preferencialmente utilizar uma ferramenta gráfica para operação do GIT. Ex.: Git GUI - vem junto com o pacote GIT BASH, ou GIT-DESKTOP): 

1. Clone o repositório com o comando
```bash
git clone https://github.com/dbeniciorj/CYBERSALA/
```
<br/>
2. Dar permissão ao script sensor.sh
3. Ajustar Mac Address Bluetooth do ESP32 na linha no. 2 do script
4. Subir BD
5. 


<br/>
<br/>




///////////////////////////////	INST. REQS.
Após baixar o código no servidor e executar os procedimentos básicos de instalação, proceder como abaixo:
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
mysql -u root -p -e \"CREATE TABLE iot.presenca ( id int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,timeStamp TIMESTAMP NOT NULL , uid varchar (11) NOT NULL, site enum('2035') default '2035')\"
mysql -u root -p -e \"CREATE TABLE iot.cartao ( uid varchar(11) NOT NULL PRIMARY KEY, nome varchar (45) NOT NULL,perf enum('professor','aluno') default 'professor')\"
```
<br/>
<br/>
///////////////////////////////  (OPCIONAL)
### Consultar sensor pela serial BLE
<br/>
No Android, usar app. Serial Bluetooth Terminal!

<br/>
<br/>

### EXIBIR LISTA DE ACESSOS DIRETO DO TERMINAL
<br/>


```bash
PASS="1234"
watch -n2 "/opt/lampp/bin/mysql -b iot -e \"select presenca.timestamp,presenca.uid,cartao.nome,cartao.perf,presenca.site from presenca left join cartao on (presenca.uid=cartao.uid)\""
```
<br/>
/////////////////////////////// SHELLSCRIPT
<br/>
APÓS COPIAR SCRIPT E DAR PERMISSÃO DE EXECUÇÃO, AGENDAR EXECUÇÃO REGULAR DO MESMO. EXEMPLO:
<br/>


```bash
chmod +x /usr/local/bin/sensor.sh
echo "*/2 * * * *   root    /usr/local/bin/sensor.sh" >> /etc/crontab
sudo service cron restart
```
<br/>
<br/>

## PROBLEMAS ENCONTRADOS:
06/08 - Criado arquivo INO. Antes não foi encontrado código contemplando comunicação com sensor via WPAN LE.
<br/>
<br/>

## Próximos passos
= Conversão serial BLE  > TEXT PLAN (ESTUDAR DOCUMENTAÇÃO DOS FABRICANTES)
<br/>

= Automação relé conforme perfis presentes no local - cód pronto!
<br/>

= Salva e apresentação dos dados na Nuvem.
<br/>
<br/>


