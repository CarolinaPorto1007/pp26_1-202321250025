# Sistema de Debate Politico


## Padroes utilizados

| Padrao    | Classe            | Funcao                                               |
|-----------|-------------------|------------------------------------------------------|
| Facade    | Fachada           | Ponto unico de entrada — simplifica o uso do sistema |
| Mediator  | GerenciadorDebate | Coordena fases, microfones, sorteio e temporizador   |
| Singleton | Fachada           | Garante uma unica instancia do controlador           |
| Observer  | Observador/Eleitor| Notifica eleitores quando seu candidato fala         |

---

## Estrutura dos arquivos

```
debate_src/
├── main.cpp                   — Interface CLI e ponto de entrada
├── Fachada.hpp / .cpp         — Padrao Facade + Singleton
├── GerenciadorDebate.hpp/.cpp — Padrao Mediator
├── Candidato.hpp / .cpp       — Sujeito do Observer
├── Eleitor.hpp / .cpp         — ObservadorConcreto
├── Observador.hpp             — Interface Observer (atualizar)
├── Mediador.hpp               — Interface Mediator (proximaAcao)
├── Cronometro.hpp / .cpp      — Temporizador das fases
├── Colaborador.hpp / .cpp     — Base do Cronometro
├── Microfone.hpp / .cpp       — Controle de microfone por candidato
└── Logger.hpp / .cpp          — Registro de eventos com timestamp
```

---

## Como compilar e executar

```bash
g++ -std=c++11 -o debate *.cpp -lpthread
./debate
```

O programa roda diretamente no terminal atual.

---

## Fluxo do debate

```
1. Informe a quantidade de candidatos
2. Cadastre nome e partido de cada candidato
3. Cadastre os eleitores e seus candidatos preferidos
4. Configure os tempos de cada fase (PERGUNTA, RESPOSTA, REPLICA, TREPLICA)
5. O sistema sorteia automaticamente o inquiridor
6. Voce escolhe o inquirido via CLI
7. O debate roda fase por fase automaticamente
8. A cada fase o Observer notifica os eleitores do candidato que esta falando
9. Ao fim de cada rodada o proximo inquiridor e sorteado automaticamente
10. O ciclo repete ate todos os candidatos terem perguntado
11. Ao encerrar o relatorio e exibido e salvo em debate_log.txt
```

---

## Arquivo de log

Ao final o sistema salva `debate_log.txt` com o registro completo.

| Categoria    | O que registra                       |
|--------------|--------------------------------------|
| SISTEMA      | Inicio e fim do debate               |
| SORTEIO      | Inquiridor sorteado em cada rodada   |
| CONFIGURACAO | Inquirido definido pelo apresentador |
| FASE         | Fase iniciada com tempo e atores     |
| RODADA       | Fim de cada rodada                   |

---
