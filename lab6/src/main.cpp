#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <set>
#include <vector>
class BattleVisitor;
class Observer {
   public:
    virtual void notify(const std::string& event) = 0;
};

class FileLogger : public Observer {
    std::ofstream logFile;

   public:
    FileLogger() { logFile.open("log.txt", std::ios::app); }

    ~FileLogger() {
        if (logFile.is_open())
            logFile.close();
    }

    void notify(const std::string& event) override {
        if (logFile.is_open()) {
            logFile << event << std::endl;
        }
    }
};

class ConsoleLogger : public Observer {
   public:
    void notify(const std::string& event) override {
        std::cout << event << std::endl;
    }
};

enum class NPCType { Knight, Squirrel, Pegasus };

struct Dot {
    int x, y;

    Dot(int x, int y) : x(x), y(y) {}
};

class NPC {
   protected:
    std::string name;
    Dot position;

   public:
    NPC(const std::string& name, int x, int y) : name(name), position(x, y) {}
    virtual ~NPC() = default;
    std::string const getName() { return name; }
    virtual NPCType getType() const = 0;
    virtual bool canKill(const NPC& other) const = 0;

    const std::string& getName() const { return name; }
    int getX() const { return position.x; }
    int getY() const { return position.y; }
};


class Knight : public NPC {
   public:
    Knight(const std::string& name, int x, int y) : NPC(name, x, y) {}

    NPCType getType() const override { return NPCType::Knight; }
    bool canKill(const NPC& other) const override {
        return other.getType() == NPCType::Squirrel;
    }
};

class Squirrel : public NPC {
   public:
    Squirrel(const std::string& name, int x, int y) : NPC(name, x, y) {}

    NPCType getType() const override { return NPCType::Squirrel; }
    bool canKill(const NPC& other) const override {
        return other.getType() == NPCType::Pegasus;
    }
};

class Pegasus : public NPC {
   public:
    Pegasus(const std::string& name, int x, int y) : NPC(name, x, y) {}

    NPCType getType() const override { return NPCType::Pegasus; }
    bool canKill(const NPC& other) const override { return false; }
};

class NPCFactory {
   public:
    static std::shared_ptr<NPC> createNPC(NPCType type,
                                          const std::string& name,
                                          int x,
                                          int y) {
        switch (type) {
            case NPCType::Knight:
                return std::make_shared<Knight>(name, x, y);
            case NPCType::Squirrel:
                return std::make_shared<Squirrel>(name, x, y);
            case NPCType::Pegasus:
                return std::make_shared<Pegasus>(name, x, y);
            default:
                throw std::invalid_argument("Unknown NPC type");
        }
    }
};

class BattleVisitor {
    std::set<std::shared_ptr<NPC>>& npcs;
    std::set<std::shared_ptr<NPC>> beKilled;
    std::vector<std::shared_ptr<Observer>> observers;
    double range;

    void notifyObservers(const std::string& event) {
        for (const auto& observer : observers) {
            observer->notify(event);
        }
    }

    bool isWithinRange(const NPC& a, const NPC& b) const {
        return std::sqrt(std::pow(a.getX() - b.getX(), 2) +
                         std::pow(a.getY() - b.getY(), 2)) <= range;
    }

   public:
    BattleVisitor(std::set<std::shared_ptr<NPC>>& npcs, double range)
        : npcs(npcs), range(range) {}

    void addObserver(const std::shared_ptr<Observer>& observer) {
        observers.push_back(observer);
    }

    void visit() {
        for (auto unit : npcs) {
            for (auto target : npcs) {
                if (unit == target)
                    continue;
                if (unit->canKill(*target) && isWithinRange(*unit, *target)) {
                    if (beKilled.find(target) == beKilled.end()) {
                        notifyObservers(unit->getName() + " kill " +
                                        target->getName());
                        beKilled.emplace(target);
                    }
                }
            }
        }
        for (auto unit : beKilled)
            npcs.erase(unit);
    }
};

class ManagerNpc {
   public:
    bool mayAdded(const std::string& name,
                  int x,
                  int y,
                  std::set<std::shared_ptr<NPC>>& npcs) {
        return validPos(x, y) && validName(name, npcs);
    }

    bool validPos(int x, int y) {
        if (x < 0 || x > 500 || y < 0 || y > 500) {
            return false;
        }
        return true;
    }

    bool validName(const std::string& name,
                   std::set<std::shared_ptr<NPC>>& npcs) {
        for (auto npc : npcs) {
            if (!name.compare(npc->getName())) {
                return false;
            }
        }
        return true;
    }
};
class DungeonEditor {
   private:
    std::set<std::shared_ptr<NPC>> npcs;

   public:
    void addNPC(NPCType type, const std::string& name, int x, int y) {
        if (ManagerNpc().mayAdded(name, x, y, npcs)) {
            npcs.emplace(NPCFactory::createNPC(type, name, x, y));
        }
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        for (const auto& npc : npcs) {
            file << static_cast<int>(npc->getType()) << " " << npc->getName()
                 << " " << npc->getX() << " " << npc->getY() << std::endl;
        }
    }

    int loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: файл \"" << filename << "\" не найден!\n";
            return -1;
        }
        int typeInt;
        std::string name;
        int x, y;
        npcs.clear();
        while (file >> typeInt >> name >> x >> y) {
            addNPC(static_cast<NPCType>(typeInt), name, x, y);
        }
        return 0;
    }

    void printNPCs() const {
        for (const auto& npc : npcs) {
            std::string typeName;
            switch (npc->getType()) {
                case NPCType::Knight:
                    typeName = "Knight";
                    break;
                case NPCType::Squirrel:
                    typeName = "Squirrel";
                    break;
                case NPCType::Pegasus:
                    typeName = "Pegasus";
                    break;
            }
            std::cout << typeName << " " << npc->getName() << " ("
                      << npc->getX() << ", " << npc->getY() << ")" << std::endl;
        }
    }

    void runBattle(double range) {
        BattleVisitor visitor(npcs, range);
        auto consoleLogger = std::make_shared<ConsoleLogger>();
        auto fileLogger = std::make_shared<FileLogger>();
        visitor.addObserver(consoleLogger);
        visitor.addObserver(fileLogger);
        visitor.visit();
    }
};

int main() {
    DungeonEditor editor;
    char command;

    std::cout << "Добро пожаловать в Dungeon Editor!\n";
    do {
        std::cout << "\nВыберите действие:\n"
                  << "[A] Добавить юнита\n"
                  << "[P] Показать всех юнитов\n"
                  << "[S] Сохранить в файл\n"
                  << "[L] Загрузить из файла\n"
                  << "[B] Запустить бой\n"
                  << "[Q] Выйти\n"
                  << "Ваш выбор: ";
        std::cin >> command;
        command = std::toupper(command);

        switch (command) {
            case 'A': {
                std::string name;
                int x, y, typeInt;
                std::cout << "Введите имя юнита: ";
                std::cin >> name;
                std::cout << "Введите координаты (x y): ";
                std::cin >> x >> y;
                std::cout << "Выберите тип юнита (0 - Knight, 1 - Squirrel, 2 "
                             "- Pegasus): ";
                std::cin >> typeInt;

                if (typeInt < 0 || typeInt > 2) {
                    std::cout << "Неверный тип юнита!\n";
                    break;
                }

                try {
                    editor.addNPC(static_cast<NPCType>(typeInt), name, x, y);
                    std::cout << "Юнит успешно добавлен!\n";
                } catch (const std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << "\n";
                }
                break;
            }
            case 'P': {
                std::cout << "Список всех юнитов:\n";
                editor.printNPCs();
                break;
            }
            case 'S': {
                std::string filename;
                std::cout << "Введите имя файла для сохранения: ";
                std::cin >> filename;
                editor.saveToFile(filename);
                std::cout << "Юниты сохранены в файл \"" << filename << "\"!\n";
                break;
            }
            case 'L': {
                std::string filename;
                std::cout << "Введите имя файла для загрузки: ";
                std::cin >> filename;
                if (editor.loadFromFile(filename) == 0) {
                    std::cout << "Юниты загружены из файла \"" << filename
                              << "\"!\n";
                }
                break;
            }
            case 'B': {
                double range;
                std::cout << "Введите радиус действия боя: ";
                std::cin >> range;
                std::cout << "Начало боя:\n";
                editor.runBattle(range);
                std::cout << "Бой завершён!\n";
                break;
            }
            case 'Q': {
                std::cout << "Выход из программы...\n";
                break;
            }
            default:
                std::cout << "Неизвестная команда! Попробуйте ещё раз.\n";
        }
    } while (command != 'Q');
    return 0;
}
