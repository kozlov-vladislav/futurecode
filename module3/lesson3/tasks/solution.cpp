#include <vector>

class ModuleBase {
public:
    virtual void OnTick(double price) = 0;
    virtual void CloseAll() = 0;
};


class ModulesRouter {
    std::vector<ModuleBase*> modules;
public:
    void OnTick(double price) {
        for (auto modulePtr : modules) {
            modulePtr->OnTick(price);
        }
    }
    void AddModule(ModuleBase* ptr) {
        modules.push_back(ptr);
    }
    void CloseAll() {
        for (auto modulePtr : modules) {
            modulePtr->CloseAll();
        }
    }
};



class ModuleBorders : public ModuleBase {
    AccountInterface* ptr;
    std::vector<int> posIds;
public:
    ModuleBorders(AccountInterface* account) : ptr(account) {};

    void OnTick(double price) override {
        if (price <= 4) {
            auto balance = ptr->GetAvailBalance();
            auto posSize = balance / price / price * 0.99;
            auto posIndex = ptr->OpenPosition(posSize);
            posIds.push_back(posIndex);
        } else if (price >= 6) {
            CloseAll();
        }
    }
    void CloseAll() override {
        for (auto index : posIds) {
            ptr->ClosePosition(index);
        }
        posIds = std::vector<int>();
    };
};