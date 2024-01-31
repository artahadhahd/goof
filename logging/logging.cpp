#include "logging.hpp"

void Logger::log_err(std::string msg) {
    errs += 1;
    // std::cerr << "\033[3;12m" << msg << "\033[0m";
    std::cerr << BRED << "Error: " << msg << WHT << std::endl;
}

void Logger::log_warning(std::string msg) {
    warns += 1;
    std::cerr << BMAG << "Warning: " << msg << WHT << std::endl;
}

#if 0
int main() {
    Logger logger;
    logger.log_err("fuck you");
    logger.log_warning("you are shit");
}
#endif