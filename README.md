# 🚗 Projeto IoT - Garagem Mottu

Este projeto foi desenvolvido com foco em **IoT e prototipagem**. O objetivo é demonstrar uma solução que integra **Arduino**, **Node-RED** e **Tinkercad**, com protótipo real e dashboard para monitoramento em tempo real.

---

## 💻 Tecnologias Utilizadas
- **Arduino (C++)** → código principal para controle do protótipo.
- **Tinkercad** → simulação do circuito eletrônico.
- **Node-RED** → dashboard para monitoramento em tempo real.

---

## 📂 Estrutura do Projeto
- `GaragemMottu/GaragemMottu.ino` → código-fonte do Arduino.
- `Dashboard.json` → fluxo e dashboard do **Node-RED**.
- `image/Thinkercad Arduino.png` → esquema do circuito no Tinkercad.

---

## 🚀 Como Executar

### 1. Arduino
- Abra o arquivo `GaragemMottu.ino` no **Arduino IDE**.
- Faça upload para uma placa **Arduino Uno** ou simule no **Tinkercad**.

### 2. Circuito
- Utilize a imagem abaixo como referência para a montagem.
- O circuito simula o sensor ultrassônico para medir distância e um potenciômetro para simular o GPS (localização).

![Esquema do Circuito no Tinkercad: Arduino, Sensor Ultrassônico e LEDs](Image/Arduino.png)
 
### 3. Node-RED (Dashboard)
- Abra o **Node-RED** no navegador.
- Vá em **Menu → Import → Clipboard**.
- Instale os plugin: node-red-node-serialport, node-red-dashboard
- Copie e cole o conteúdo de `Dashboard.json`.
- O fluxo/dash será criado automaticamente, incluindo a configuração de entrada serial (Certifique-se de configurar a porta `COM` correta).

### Parte 4: Simulação IoT (Arduino + Node-RED)

1.  **Carregar o Código no Arduino**
    * Abra a **IDE do Arduino**.
    * O código (`Protótipo_IoT.ino`) está na pasta `Arduino/` do repositório.
    * Cole o código-fonte na IDE e faça o upload para a sua placa Arduino.

2.  **Configurar o Node-RED**
    * Abra o **Node-RED** no seu navegador (geralmente `http://localhost:1880`).
    * O fluxo está no arquivo `flows.json` na raiz do repositório. Importe este arquivo para o seu editor.

3.  **Vincular o Hardware ao Banco de Dados (Passo Essencial)**
    O Arduino envia dados genéricos. Precisamos "dizer" ao Node-RED qual moto e qual pátio do banco de dados esse Arduino representa.

    * **a. Obtenha os UUIDs:** Com o projeto Java (`Parte 1`) rodando, acesse seu banco de dados (DBeaver, pgAdmin, etc.) para encontrar os IDs que você irá simular.

        ```sql
        -- 1. Encontre o ID da moto que você quer simular
        SELECT id_moto, nm_modelo, nr_placa FROM t_mtu_moto;
        -- (Copie o id_moto desejado, por exemplo: "afd8d463-c4c1-44a6-be25-a7419ebfffba")

    * **c. Configure o "Tradutor" no Node-RED:** No fluxo do Node-RED, encontre o nó "Change" (ou "Função") que é usado para "traduzir" a mensagem. Dê um duplo clique para editar.

    * **d. Insira os UUIDs:** Dentro deste nó, você encontrará a lógica para anexar os IDs. Procure pela variável que define o ID da moto, como `var idRealDaMoto = "...";`. **É aqui que você deve colar o `id_moto`** que copiou do banco de dados:

        ```javascript
        // Exemplo dentro do nó "Função" do Node-RED
        var idRealDaMoto = "COLE_O_UUID_AQUI"; // <-- COLE O UUID DA SUA MOTO AQUI
        ```
    
    * As imagens (também presentes no repositório) mostram como a configuração do `payload` é feita nesse nó.
    
    * Este passo é crucial: ele transforma dados genéricos do sensor em uma atualização específica para a "Moto X" no "Pátio Y". Isso permite ao Java processar a entidade correta e evitar spam de logs.

5.  **Configurar Conexões e Fazer o Deploy**
    * **a. Conexão Serial:** Dê um duplo clique no nó de entrada (roxo) `serial in`. Selecione a porta USB correta onde seu Arduino foi detectado (ex: `COM3`, `COM4`, etc.).
    * **b. Conexão MQTT:** Confirme que os nós de saída (verdes) `mqtt out` estão configurados para o broker `broker.hivemq.com`.
    * **c. Deploy:** Clique no botão **Deploy** no canto superior direito do Node-RED.

### 4. Execução
- Execute o Node-RED.
- Visualize os dados de status, distância (Ultrassônico) e GPS (Potenciômetro) do Arduino no dashboard em tempo real.
- Neste ponto, os dados do seu Arduino físico estão sendo lidos, enriquecidos com os UUIDs do banco de dados e publicados no MQTT.

---

## 📊 Detalhes Técnicos do Dashboard (Node-RED)

O dashboard é configurado para visualizar os seguintes dados:

| Componente | Dados Exibidos | Descrição |
| :--- | :--- | :--- |
| **Indicador de Status** | Texto e Cor | Exibe a mensagem de status da moto (`local correto` em verde, `em movimento` em amarelo ou `alerta` em vermelho). |
| **Distância da Moto** | Gauge (Medidor) | Mostra a distância lida pelo sensor ultrassônico em **cm**. |
| **Gráfico GPS** | Gráfico de Linha | Monitora a variação do valor do potenciômetro (simulação do GPS) ao longo do tempo (valor de 0 a 1023). |

---

## 📊 Resultados Parciais
- Protótipo funcional no **Tinkercad**.
- Protótipo **real construído com Arduino** .
- Código testado e validado no Arduino Uno.
- Dashboard do **Node-RED** configurado para exibir dados de telemetria.

---

## 👨‍💻 Integrantes do Grupo
- Thiago Henry Dias - Rm 5545222
- Nicolas Dobbeck Mendes - Rm 557605
- José Bezerra Bastos Net - Rm 557605
