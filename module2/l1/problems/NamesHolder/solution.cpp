#include <string>
#include <vector>

struct NamesHolder {
    std::vector<std::string> names;
    void AddName(const std::string&);
    bool HasName(const std::string&);
    unsigned long long Size();
};

void NamesHolder::AddName(const std::string& name) {
    names.push_back(name);
}

bool NamesHolder::HasName(const std::string& name) {
    bool result = false;
    for (int i = 0, n = names.size(); i < n; ++i) {
        if (names[i] == name) {
            result = true;
            break;
        }
    }
    return result;
}

unsigned long long NamesHolder::Size() {
    return names.size();
}