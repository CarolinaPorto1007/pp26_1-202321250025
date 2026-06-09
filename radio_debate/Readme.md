# Sistema de Debate Politico — GDP v3.0

Implementacao de um sistema de debate politico utilizando os padroes de projeto
Facade, Mediator, Singleton, Observer, Builder, Prototype e State em C++.

---

## Padroes utilizados

| Padrao    | Classe                                              | Funcao                                               |
|-----------|-----------------------------------------------------|------------------------------------------------------|
| Facade    | Fachada                                             | Ponto unico de entrada — simplifica o uso do sistema |
| Mediator  | GerenciadorDebate                                   | Coordena fases, microfones, sorteio e temporizador   |
| Singleton | Fachada                                             | Garante uma unica instancia do controlador           |
| Observer  | Observavel / Observador / Eleitor                   | Notifica eleitores quando seu candidato fala ou exerce DR |
| Builder   | CandidatoBuilder / EleitorBuilder / OperadorBuilder | Constroi entidades com validacao                     |
| Prototype | CandidatoConcreto / Eleitor / Operador              | Permite clonar entidades ja configuradas             |
| State     | EstadoDebate / EstadoNormal / EstadoAguardandoDR / EstadoDireitoResposta | Gerencia o Direito de Resposta |

---

## Estrutura dos arquivos

```
debate_src/
├── main.cpp                         — Interface CLI e ponto de entrada
├── Fachada.hpp / .cpp               — Padrao Facade + Singleton
├── GerenciadorDebate.hpp / .cpp     — Padrao Mediator + controle de estado
├── EstadoDebate.hpp                 — Interface do padrao State
├── EstadoNormal.hpp / .cpp          — Estado normal do debate
├── EstadoAguardandoDR.hpp / .cpp    — Estado aguardando decisao do operador
├── EstadoDireitoResposta.hpp / .cpp — Estado de execucao do DR
├── Candidato.hpp / .cpp             — Classe abstrata base + Observavel
├── CandidatoConcreto.hpp / .cpp     — Implementa Candidato + Prototype
├── CandidatoBuilder.hpp / .cpp      — Padrao Builder para Candidato
├── Eleitor.hpp / .cpp               — ObservadorConcreto + Prototype
├── EleitorBuilder.hpp / .cpp        — Padrao Builder para Eleitor
├── Operador.hpp / .cpp              — Entidade operador do GDP + Prototype
├── OperadorBuilder.hpp / .cpp       — Padrao Builder para Operador
├── Observador.hpp                   — Interface Observer (atualizar + atualizarDR)
├── Prototype.hpp                    — Interface Prototype (clonar)
├── Mediador.hpp                     — Interface Mediator (proximaAcao)
├── Cronometro.hpp / .cpp            — Temporizador das fases
├── Colaborador.hpp / .cpp           — Base do Cronometro
├── Microfone.hpp / .cpp             — Controle de microfone + botao DR
└── Logger.hpp / .cpp                — Registro de eventos com timestamp
```

---

## Como compilar e executar

```bash
g++ -std=c++11 -o debate *.cpp -lpthread
./debate
```

---

## Fluxo do debate

```
1.  Informe o nome do operador
2.  Informe a quantidade de candidatos
3.  Cadastre nome e partido de cada candidato (via CandidatoBuilder)
4.  O sistema demonstra o Prototype clonando o primeiro candidato
5.  Cadastre os eleitores e seus candidatos preferidos (via EleitorBuilder)
6.  Configure os tempos de cada fase
7.  O sistema sorteia automaticamente o inquiridor
8.  Voce escolhe o inquirido via CLI
9.  O debate roda as 4 fases automaticamente: PERGUNTA, RESPOSTA, REPLICA, TREPLICA
10. A cada fase o Observer notifica os eleitores do candidato que esta falando
11. Ao fim da TREPLICA o sistema pergunta se algum candidato deseja solicitar DR
12. Podem ser solicitados multiplos DRs em ordem
13. O operador decide conceder ou negar os DRs
14. Se concedido cada solicitante fala em ordem — eleitores sao notificados via Observer
15. Durante o DR nenhum novo DR pode ser solicitado
16. Ao fim dos DRs o debate retorna ao fluxo normal
17. O ciclo repete ate todos os candidatos terem perguntado
18. Ao encerrar o relatorio e exibido e salvo em debate_log.txt
```

---

## Direito de Resposta — fluxo detalhado

```
Fim da TREPLICA
      ↓
Sistema pergunta se algum candidato quer solicitar DR
      ↓
Podem solicitar multiplos candidatos em ordem
      ↓
Estado muda para EstadoAguardandoDR
      ↓
Operador decide: conceder (1) ou negar (0)
      ↓
Se concedido → EstadoDireitoResposta
  - Microfone de cada solicitante aberto em ordem
  - Eleitores notificados com mensagem especifica de DR
  - Novos DRs bloqueados durante as defesas
      ↓
Retorna para EstadoNormal e continua o debate
```

---

## Arquivo de log

Ao final o sistema salva `debate_log.txt` com o registro completo.

| Categoria    | O que registra                            |
|--------------|-------------------------------------------|
| SISTEMA      | Inicio e fim do debate                    |
| SORTEIO      | Inquiridor sorteado em cada rodada        |
| CONFIGURACAO | Inquirido definido pelo apresentador      |
| FASE         | Fase iniciada com tempo e atores          |
| RODADA       | Fim de cada rodada                        |
| DR           | Solicitacoes, concessao e defesas de DR   |
| STATE        | Mudancas de estado do debate              |

---

## O que mudou da v2.0 para a v3.0

- Adicionado padrao **State** com 3 estados: EstadoNormal, EstadoAguardandoDR, EstadoDireitoResposta
- Adicionada funcionalidade de **Direito de Resposta** solicitavel ao fim de cada ciclo completo
- `Microfone` ganhou botao DR: `acionarDR()`, `isDrSolicitado()`, `resetarDR()`
- `GerenciadorDebate` ganhou fila de DR, controle de estado e metodos `solicitarDR()`, `executarDireitos()`, `mudarEstado()`
- `Observador` ganhou `atualizarDR()` para notificacao especifica de DR
- `Candidato` ganhou `notificarDR()` que dispara `atualizarDR()` nos eleitores
- `Eleitor` implementa `atualizarDR()` com mensagem diferenciada

---
