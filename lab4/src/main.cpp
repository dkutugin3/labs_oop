#include "../include/array.hpp"
#include "../include/childs.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <string>


void printMenu() {
    std::cout << "\nFigure Management CLI\n";
    std::cout << "1. Add Pentagon\n";
    std::cout << "2. Add Hexagon\n";
    std::cout << "3. Add Octagon\n";
    std::cout << "4. Print All Figures\n";
    std::cout << "5. Remove Figure by Index\n";
    std::cout << "6. Compute Total Area\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
}

template <typename T>
void addFigure(std::vector<std::shared_ptr<Figure<T>>>& figures) {
    std::cout << "Enter the center coordinates (x y): ";
    T x, y;
    std::cin >> x >> y;

    std::cout << "Enter the radius: ";
    T radius;
    std::cin >> radius;

    std::cout << "Select Figure Type:\n";
    std::cout << "1. Pentagon\n";
    std::cout << "2. Hexagon\n";
    std::cout << "3. Octagon\n";
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        figures.push_back(std::make_shared<Pentagon<T>>(Point<T>{x, y}, radius));
        std::cout << "Pentagon added successfully.\n";
        break;
    case 2:
        figures.push_back(std::make_shared<Hexagon<T>>(Point<T>{x, y}, radius));
        std::cout << "Hexagon added successfully.\n";
        break;
    case 3:
        figures.push_back(std::make_shared<Octagon<T>>(Point<T>{x, y}, radius));
        std::cout << "Octagon added successfully.\n";
        break;
    default:
        std::cout << "Invalid choice. No figure added.\n";
        break;
    }
}

template <typename T>
void printAllFigures(const std::vector<std::shared_ptr<Figure<T>>>& figures) {
    if (figures.empty()) {
        std::cout << "No figures available.\n";
        return;
    }

    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Figure " << i + 1 << ":\n";
        figures[i]->print(std::cout);
        std::cout << "\n";
    }
}

template <typename T>
void removeFigure(std::vector<std::shared_ptr<Figure<T>>>& figures) {
    std::cout << "Enter the index of the figure to remove (1-based): ";
    size_t index;
    std::cin >> index;

    if (index == 0 || index > figures.size()) {
        std::cout << "Invalid index. No figure removed.\n";
        return;
    }

    figures.erase(figures.begin() + (index - 1));
    std::cout << "Figure removed successfully.\n";
}

template <typename T>
void computeTotalArea(const std::vector<std::shared_ptr<Figure<T>>>& figures) {
    if (figures.empty()) {
        std::cout << "No figures available. Total area is 0.\n";
        return;
    }

    T totalArea = 0;
    for (const auto& figure : figures) {
        totalArea += figure->area();
    }

    std::cout << "Total area of all figures: " << totalArea << "\n";
}

int main() {
    std::vector<std::shared_ptr<Figure<double>>> figures;
    bool running = true;

    while (running) {
        printMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
        case 2:
        case 3:
            addFigure(figures);
            break;
        case 4:
            printAllFigures(figures);
            break;
        case 5:
            removeFigure(figures);
            break;
        case 6:
            computeTotalArea(figures);
            break;
        case 7:
            running = false;
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
            break;
        }
    }

    return 0;
}
