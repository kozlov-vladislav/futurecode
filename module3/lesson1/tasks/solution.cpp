#include <string>
#include <unordered_map>
#include <unordered_set>

class AccessControl {
    std::unordered_set<std::string> KnownRoles; // Список ролей
    std::unordered_map<std::string, std::unordered_set<int>> GrantedRoles; // Роль -> список пользователей
    bool RoleExists(const std::string& roleName) const {
        return KnownRoles.count(roleName);
    }
public:
    bool HasRole(int id, const std::string& roleName) const {
        if (!RoleExists(roleName)) { // Такой роли нет
            return false;
        }
        auto& usersList = GrantedRoles.find(roleName)->second;
        return usersList.count(id) == 1;
    }

    bool GrantRole(int id, const std::string& roleName) { // bool - успешно ли
        if (!RoleExists(roleName)) { // Такой роли нет
            return false;
        }
        GrantedRoles[roleName].insert(id);
        return true;
    }
    bool RemoveRole(int id, const std::string& roleName) { // bool - успешно ли
        if (!RoleExists(roleName)) { // Такой роли нет
            return false;
        }
        auto& roleInfo = GrantedRoles[roleName];
        auto iter = roleInfo.find(id);
        if (iter == roleInfo.end()) { // У пользователя уже нет такой роли
            return false;
        }
        roleInfo.erase(iter);
        return true;
    }

    void RegisterRole(const std::string& roleName) {
        KnownRoles.insert(roleName);
        GrantedRoles.insert({roleName, {}});
    }
};

class Pausable {
    bool Paused = false;
public:
    bool IsPaused() const {
        return Paused;
    }
    void Pause() {
        Paused = true;
    }
    void UnPause() {
        Paused = false;
    }
};

struct ResposeData {
    bool Success;
    std::string Response;
};

ResposeData MakeSuccessResponse() {
    return {true, ""};
}

ResposeData MakeFailedResponse(const std::string& response) {
    return {false, response};
}


class SystemBase : public AccessControl, public Pausable {
    const std::string ADMIN_ROLE = "admin";
    const std::string USER_ROLE = "user";
    const std::string MODERATOR_ROLE = "moderator";
    const std::string BANNED_ROLE = "banned";
public:
    SystemBase(int admin) {
        RegisterRole(ADMIN_ROLE);
        RegisterRole(USER_ROLE);
        RegisterRole(MODERATOR_ROLE);
        RegisterRole(BANNED_ROLE);
        GrantRole(admin, ADMIN_ROLE);
    }

    ResposeData BanUser(int sender, int user)  {
        if (!HasRole(sender, MODERATOR_ROLE)) {
            return MakeFailedResponse("only moderator can ban");
        }
        if (HasRole(user, BANNED_ROLE)) {
            return MakeFailedResponse("already banned");
        }
        GrantRole(user, BANNED_ROLE);
        return MakeSuccessResponse();
    }
    ResposeData UnBanUser(int sender, int user)  {
        if (!HasRole(sender, MODERATOR_ROLE)) {
            return MakeFailedResponse("only moderator can unban");
        }
        if (!HasRole(user, BANNED_ROLE)) {
            return MakeFailedResponse("already unbanned");
        }
        RemoveRole(user, BANNED_ROLE);
        return MakeSuccessResponse();
    }
    ResposeData RegisterNewUser(int sender, int newUser) {
        if (!HasRole(sender, ADMIN_ROLE)) {
            return MakeFailedResponse("only admin can register");
        }
        if (HasRole(newUser, USER_ROLE)) { // Пользователь уже зареган
            return MakeFailedResponse("already registered");
        }
        GrantRole(newUser, USER_ROLE);
        return MakeSuccessResponse();
    }
    ResposeData GrantModeratorRole(int sender, int user) {
        if (!HasRole(sender, ADMIN_ROLE) && !HasRole(sender, MODERATOR_ROLE)) {
            return MakeFailedResponse("only admin or moderator can grant moderator role");
        }
        GrantRole(user, MODERATOR_ROLE);
        return MakeSuccessResponse();
    }
    ResposeData GrantAdminRole(int sender, int user) {
        if (!HasRole(sender, ADMIN_ROLE)) {
            return MakeFailedResponse("only admin can grant admin role");
        }
        GrantRole(user, ADMIN_ROLE);
        return MakeSuccessResponse();
    }

    ResposeData StopChat(int sender) {
        if (IsPaused()) {
            return MakeFailedResponse("already stopped");
        }
        if (!HasRole(sender, ADMIN_ROLE)) {
            return MakeFailedResponse("only admin can stop chat");
        }
        Pause();
        return MakeSuccessResponse();
    }
    ResposeData ResumeChat(int sender) {
        if (!IsPaused()) {
            return MakeFailedResponse("already unpaused");
        }
        if (!HasRole(sender, ADMIN_ROLE)) {
            return MakeFailedResponse("only admin");
        }
        UnPause();
        return MakeSuccessResponse();
    }
};