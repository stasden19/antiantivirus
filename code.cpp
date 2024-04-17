#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char* argv[]) {
    std::fstream file(argv[1], std::ios::in | std::ios::out | std::ios::binary);

    if (!file) {
        std::cerr << "Ошибка открытия файла!";
        return 1;
    }
    unsigned int startPosition = std::strtoul(argv[2], nullptr, 10);
    unsigned int replaceSize = std::strtoul(argv[3], nullptr, 10);
    // int startPosition = (int)*argv[2];
    // int replaceSize = (int)*argv[3];

    std::cout << startPosition << " " << replaceSize << std::endl;
    unsigned char xorBytes[] = {0xFA, 0xA8, 0x52, 0x01, 0xBB};

    file.seekg(startPosition);

    std::vector<unsigned char> bytesToModify(replaceSize);
    file.read(reinterpret_cast<char*>(bytesToModify.data()), replaceSize);

    if (!file.good()) {
        std::cerr << "Ошибка чтения из файла!";
        return 1;
    }

    for (int i = 0; i < replaceSize; ++i) {
        bytesToModify[i] ^= xorBytes[i % sizeof(xorBytes)];
    }
    file.seekp(startPosition);
    file.write(reinterpret_cast<char*>(bytesToModify.data()), replaceSize);
    if (!file.good()) {
        std::cerr << "Ошибка записи в файл!";
        return 1;
    }
    file.close();

    std::cout << "Операция успешно выполнена!\n";

    return 0;
}
