#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <vector>
#include <fstream>

class Logger {
private:
    std::vector<std::string> logs;
    std::string arquivoSaida;

public:
    Logger(const std::string& arquivo = "debate_log.txt");
    void registrar(const std::string& categoria, const std::string& acao);
    void gerarRelatorio();
    void salvarArquivo();
};

#endif