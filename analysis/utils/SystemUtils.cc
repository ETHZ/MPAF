#include "analysis/utils/SystemUtils.hh"

std::string 
SystemUtils::exec(const std::string& cmd) {
    char buffer[128];
    std::string result = "";
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
    return result;
}
