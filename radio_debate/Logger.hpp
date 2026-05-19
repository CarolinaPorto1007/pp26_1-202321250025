#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <vector>

class Logger {
private:
    std::vector<std::string> logs;

public:
    void registrar(const std::string& acao);
    void gerarRelatorio();
};

#endif
