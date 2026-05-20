#include "Logger.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

static std::string timestamp() {
    std::time_t t = std::time(nullptr);
    std::tm* tm   = std::localtime(&t);
    std::ostringstream ss;
    ss << std::setfill('0')
       << std::setw(2) << tm->tm_hour << ":"
       << std::setw(2) << tm->tm_min  << ":"
       << std::setw(2) << tm->tm_sec;
    return ss.str();
}

Logger::Logger(const std::string& arquivo) : arquivoSaida(arquivo) {}

void Logger::registrar(const std::string& categoria, const std::string& acao) {
    if (acao.empty()) return;
    std::string entrada = "[" + timestamp() + "] [" + categoria + "] " + acao;
    logs.push_back(entrada);
}

void Logger::gerarRelatorio() {
    std::cout << "\n╔══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           RELATÓRIO FINAL DO DEBATE              ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════╣" << std::endl;
    if (logs.empty()) {
        std::cout << "║  Nenhuma ação registrada.                        ║" << std::endl;
    } else {
        int i = 1;
        for (const auto& l : logs)
            std::cout << "  " << std::setw(2) << i++ << ". " << l << std::endl;
    }
    std::cout << "╚══════════════════════════════════════════════════╝" << std::endl;
    salvarArquivo();
}

void Logger::salvarArquivo() {
    std::ofstream f(arquivoSaida);
    if (!f.is_open()) {
        std::cerr << "[ERRO] Nao foi possivel salvar o arquivo de log." << std::endl;
        return;
    }
    f << "============================================\n";
    f << "       REGISTRO COMPLETO DO DEBATE\n";
    f << "============================================\n\n";
    int i = 1;
    for (const auto& l : logs)
        f << std::setw(2) << i++ << ". " << l << "\n";
    f << "\n============================================\n";
    f.close();
    std::cout << "\n  [LOG] Arquivo salvo em: " << arquivoSaida << std::endl;
}