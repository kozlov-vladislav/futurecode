#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec;
    int q;
    std::cin >> q;
    while (q--) {
        char opcode;
        std::cin >> opcode;
        if (opcode == 'i') {
            int index;
            std::cin >> index;
            int x;
            std::cin >> x;
            vec.insert(vec.begin() + index, x);
        }
        else if (opcode == 'p') {
            int x;
            std::cin >> x;
            vec.push_back(x);
        }
        else {
            int index;
            std::cin >> index;
            std::cout << vec[index] << "\n";
        }
    }
}
