
#include <iostream>
#include <map>
#include "../../../day4/supply_stacks/supply_stacks/load_input.hpp"

using namespace std;

int main()
{
    //strings to get the lines and the lines that are food
    map<int, int> elves;
    string line;
    int amount = 0;
    int i = 0;
    auto file = Input::LoadFile("input.txt");

    while (getline(file, line)) {
        if (line == "") {
            elves.insert(pair<int, int>(i, amount));
            i++;
            amount = 0;
            continue;
        }
        amount += stoi(line);
    }

    //just to check the most calorie
    int highestCalorie = 0;
    int middleCalorie = 0;
    int lowestCalorie = 0;
    int elfCarryingHighest = 0;

    for (auto const& e : elves) {
        cout << "The " << e.first+1 << " Elf has : " << e.second << " Calories! " << endl;
        if (e.second > highestCalorie) {
            highestCalorie = e.second;
            elfCarryingHighest = e.first + 1;
        }
        if (e.second > middleCalorie && e.second < highestCalorie) {
            middleCalorie = e.second;
        }
        if (e.second > lowestCalorie && e.second < middleCalorie) {
            lowestCalorie = e.second;
        }
    }

    int sum = highestCalorie + middleCalorie + lowestCalorie;

    cout << "The elf that is carrying the most calories is : " << elfCarryingHighest << " With : " << highestCalorie << " Calories ! " << endl;
    cout << "The sum is : " << sum << endl;

    while (true) {

    }

    std::cout << "Hello World!\n";
}

