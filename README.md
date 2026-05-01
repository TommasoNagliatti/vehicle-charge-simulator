# Simulador de Recarga Veicular - V1.0

Programa em C que simula uma sessao de recarga de um veiculo eletrico, calculando energia consumida, custo e nivel de bateria com base no tempo de carga informado pelo usuario.

---

## Veiculo de referencia

| Campo | Valor |
|---|---|
| Modelo | BYD Yangwang U7 |
| Capacidade da bateria | 154 kWh |
| Custo por kWh | R$ 0,71 |

---

## Como funciona

O programa exibe um menu inicial e pergunta se o usuario deseja iniciar a simulacao. Se sim, ele escolhe entre dois metodos de carregamento. Um contador e iniciado e fica rodando ate o usuario pressionar `q` ou o tempo limite ser atingido. Ao encerrar, o programa calcula e exibe o resumo da sessao.

---

## Metodos de carregamento

### Wallbox - GoodWe HCA G2
- Potencia: 11 kW
- Corrente: 16 A
- Tempo limite simulado: 14.00 'horas'

### Tomada residencial 220V
- Potencia: 2,2 kW
- Tempo limite simulado: 70.00 'horas'

---

## Logica do contador

O contador usa `clock()` da biblioteca `<time.h>` para medir o tempo real decorrido, sem depender de `Sleep()`. A cada tick de ~20ms, um contador de "minutos" e incrementado. Ao chegar em 60, vira um segundo (que representa 1 hora simulada no contexto do programa).

O valor retornado segue o formato `segundos + (minutos / 100.0)`, ou seja, 4 segundos e 35 ticks retorna `4.35` — o mesmo valor exibido na tela, facilitando a leitura do resultado.

---

## Calculos realizados

Com base no tempo retornado pelo contador:

```
energia       = potencia_carregador * tempo
custo         = energia * preco_kwh
bateria (%)   = (energia / capacidade_bateria) * 100
tempo_total   = capacidade_bateria / potencia_carregador
tempo_restante = tempo_total - tempo
```

---

## Estrutura do codigo

```
main()
├── menu()               — apresentacao do programa
└── escolha_caso()
    ├── menu_escolha()   — selecao do metodo de carga
    ├── wallbox()
    │   ├── contador_wallbox()   — contador com clock()
    │   └── exibe resumo da sessao
    └── tomada_comum()
        ├── contador_tomada()    — contador com clock()
        └── exibe resumo da sessao
```

---

## Dependencias

| Biblioteca | Uso |
|---|---|
| `<stdio.h>` | `printf`, `scanf` |
| `<conio.h>` | `kbhit()`, `getch()` |
| `<ctype.h>` | `tolower()` |
| `<time.h>` | `clock()` |

> O programa usa `<conio.h>` para captura de teclas em tempo real, o que o torna **exclusivo para Windows**.
