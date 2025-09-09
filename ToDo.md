# ToDo

### Planejamento
- [ ] Definir a operação extra e sua inversão.
- [ ] Especificar o protocolo de comunicação (formato das mensagens).

### Servidor (Python, PC)
- [ ] Criar aplicação Python com dois threads:
    - [ ] Thread para servidor UDP.
    - [ ] Thread para servidor TCP.
- [ ] Implementar lógica da calculadora para todas as operações e suas inversões.
- [ ] Tratar erros (operações inválidas, divisão por zero, etc).
- [ ] Enviar resposta (float ou mensagem de erro) ao cliente.

### Cliente (ESP32, PlatformIO)
- [x] Criar projeto PlatformIO para ESP32.
- [ ] Implementar leitura de dois operandos e uma operação.
- [ ] Criar duas tasks:
    - [ ] Task UDP: envia operandos e operação ao servidor UDP.
    - [ ] Task TCP: envia operandos invertidos e operação invertida ao servidor TCP.
- [ ] Receber e exibir resultados no terminal serial, indicando o protocolo usado.

### Testes
- [ ] Testar todas as operações e inversões.
- [ ] Testar tratamento de erros.
- [ ] Validar comunicação UDP e TCP.

### Documentação
- [ ] Adicionar instruções de uso e execução para ambos os lados (ESP32 e PC).