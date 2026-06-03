# Sistema de Debate Politico — GDP v2.0

Implementacao de um sistema de debate politico utilizando os padroes de projeto
Facade, Mediator, Singleton, Observer, Builder e Prototype em C++.

---

## Padroes utilizados

| Padrao    | Classe                                      | Funcao                                               |
|-----------|---------------------------------------------|------------------------------------------------------|
| Facade    | Fachada                                     | Ponto unico de entrada — simplifica o uso do sistema |
| Mediator  | GerenciadorDebate                           | Coordena fases, microfones, sorteio e temporizador   |
| Singleton | Fachada                                     | Garante uma unica instancia do controlador           |
| Observer  | Observavel / Observador / Eleitor           | Notifica eleitores quando seu candidato fala         |
| Builder   | CandidatoBuilder / EleitorBuilder / OperadorBuilder | Constroi entidades com validacao             |
| Prototype | CandidatoConcreto / Eleitor / Operador      | Permite clonar entidades ja configuradas             |

---

## Estrutura dos arquivos

```
debate_src/
├── main.cpp                      — Interface CLI e ponto de entrada
├── Fachada.hpp / .cpp            — Padrao Facade + Singleton
├── GerenciadorDebate.hpp / .cpp  — Padrao Mediator
├── Candidato.hpp / .cpp          — Classe abstrata base + Observavel
├── CandidatoConcreto.hpp / .cpp  — Implementa Candidato + Prototype
├── CandidatoBuilder.hpp / .cpp   — Padrao Builder para Candidato
├── Eleitor.hpp / .cpp            — ObservadorConcreto + Prototype
├── EleitorBuilder.hpp / .cpp     — Padrao Builder para Eleitor
├── Operador.hpp / .cpp           — Entidade operador do GDP + Prototype
├── OperadorBuilder.hpp / .cpp    — Padrao Builder para Operador
├── Observador.hpp                — Interface Observer (atualizar)
├── Prototype.hpp                 — Interface Prototype (clonar)
├── Mediador.hpp                  — Interface Mediator (proximaAcao)
├── Cronometro.hpp / .cpp         — Temporizador das fases
├── Colaborador.hpp / .cpp        — Base do Cronometro
├── Microfone.hpp / .cpp          — Controle de microfone por candidato
└── Logger.hpp / .cpp             — Registro de eventos com timestamp
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
1.  Informe o nome do operador (apresentador do debate)
2.  Informe a quantidade de candidatos
3.  Cadastre nome e partido de cada candidato (via CandidatoBuilder)
4.  O sistema demonstra o Prototype clonando o primeiro candidato
5.  Cadastre os eleitores e seus candidatos preferidos (via EleitorBuilder)
6.  Configure os tempos de cada fase (PERGUNTA, RESPOSTA, REPLICA, TREPLICA)
7.  O sistema sorteia automaticamente o inquiridor
8.  Voce escolhe o inquirido via CLI
9.  O debate roda fase por fase automaticamente
10. A cada fase o Observer notifica os eleitores do candidato que esta falando
11. Ao fim de cada rodada o proximo inquiridor e sorteado automaticamente
12. O ciclo repete ate todos os candidatos terem perguntado
13. Ao encerrar o relatorio e exibido e salvo em debate_log.txt
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

## O que mudou da v1.0 para a v2.0

- Adicionado padrao **Builder** para construcao de `Candidato`, `Eleitor` e `Operador` com validacao
- Adicionado padrao **Prototype** com metodo `clonar()` em `CandidatoConcreto`, `Eleitor` e `Operador`
- Adicionada classe **Operador** representando quem opera o GDP
- `Candidato` virou classe abstrata com `CandidatoConcreto` como implementacao concreta
- `Observavel` substituiu `Sujeito` como classe abstrata base do Observer

---
