#include <iostream>
#include <string>

class warehous {
private:
    std::string type;
public:
    warehous(std::string type): type(type) {}
    std::string getType() { return type; }
};

class truck {
private:
    std::string type;
public:
    truck(std::string type) : type(type) {}
    std::string getType() { return type; }
};

class unloadingStrategy {
public:
    virtual ~unloadingStrategy() = default;
    virtual void unload() = 0;
};

class automatedUnloading: public unloadingStrategy {
public:
    void unload() override {
        std::cout << "drones instantly unloaded everything\n";
    }
};

class highPriorityUnloading : public unloadingStrategy {
public:
    void unload() override {
        std::cout << "unloading took about half an hour\n";
    }
};

class lowPriorityUnloading : public unloadingStrategy {
public:
    void unload() override {
        std::cout << "unloading took about three houres\n";
    }
};

class unloadingHandler {
private:
    unloadingStrategy* strategy = nullptr;
public:
    void unload() {
        if (strategy) strategy->unload();
    }
    void setStrategyContext(warehous& warehous, truck& truck) {
        if (warehous.getType() == "automatic") {
            strategy = new automatedUnloading();
        }
        else if (warehous.getType() == "big" || truck.getType() == "big") {
            strategy = new highPriorityUnloading();
        }
        else {
            strategy = new lowPriorityUnloading();
        }
    }
};

int main()
{
    warehous warehous1 { "small" };
    warehous warehous2 { "big" };
    warehous warehous3 { "automatic" };

    truck truck1 { "small" };
    truck truck2 { "big" };

    unloadingHandler uh;

    uh.setStrategyContext(warehous1, truck1);
    uh.unload();

    uh.setStrategyContext(warehous1, truck2);
    uh.unload();

    uh.setStrategyContext(warehous2, truck1);
    uh.unload();

    uh.setStrategyContext(warehous3, truck2);
    uh.unload();
}
