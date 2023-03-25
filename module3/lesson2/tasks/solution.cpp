class Solver : public SecretClass {
public:
    bool Get(const std::string& message) const {
        return CheckMessage(message);
    }
};


int main() {
    std::string message;
    std::cin >> message;
    std::cout << Solver().Get(message);
}
