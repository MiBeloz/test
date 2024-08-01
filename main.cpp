#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

std::vector<std::string> findFiles(std::string& folder);
std::string readFile(const std::string& file);
void writeFile(const std::string& file, const std::string& data);

int main(int argc, char* argv[]) {
    if (argc != 4) {
        return 1;
    }

    std::string arg[3];
    for (int i = 1; i < argc; ++i) {
        arg[i - 1] = argv[i];
    }

    std::vector<std::string> foundFiles = findFiles(arg[0]);

    for (auto& file : foundFiles) {
        std::string data = readFile(file);
        auto pos = data.find(arg[1]);
        if (pos != std::string::npos) {
            data.replace(pos, arg[2].size(), arg[2]);
            writeFile(file, data);
        }
    }
}

std::vector<std::string> findFiles(std::string& folder) {
    std::vector<std::string> foundFiles;
    for (auto& p : fs::directory_iterator{folder}) {
        if (p.is_regular_file()) {
            foundFiles.push_back(p.path().generic_string());
        }
    }
    return foundFiles;
}

std::string readFile(const std::string& file) {
    std::ifstream f;
    std::string data;
    f.open(file, std::ios::in);
    if (f.is_open()) {
        std::string line;
        while (std::getline(f, line)) {
            data += line + '\n';
        }
    }
    f.close();
    return data;
}

void writeFile(const std::string& file, const std::string& data) {
    std::ofstream f;
    f.open(file, std::ios::out);
    if (f.is_open()) {
        f << data;
    }
    f.close();
}
