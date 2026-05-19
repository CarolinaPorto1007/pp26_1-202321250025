#include "Logger.hpp"
#include <iostream>

void Logger::registrar(const std::string& acao) {
    if (acao.empty()) return;
    logs.push_back(acao);
    std::cout << "  [LOG] " << acao << std::endl;
}

void Logger::gerarRelatorio() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "              RELATORIO FINAL DO DEBATE           " << std::endl;
    std::cout << "==================================================" << std::endl;
    if (logs.empty()) {
        std::cout << "  Nenhuma acao registrada." << std::endl;
    } else {
        int i = 1;
        for (const auto& l : logs)
            std::cout << "  " << i++ << ". " << l << std::endl;
    }
    std::cout << "==================================================" << std::endl;
}