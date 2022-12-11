// cathode_ray_tube.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <thread>
#include <vector>
#include "../../../day4/supply_stacks/supply_stacks/load_input.hpp"


constexpr auto TICK_TIMER = 1;

//main methods
void cycle_loop(vector<string> file);
void execute_loop(string line);
void check_cycles();

int ticks = 1;
int x = 1;
int current_line = 0;
int wait_for = 0;
int sum = 0;

int main()
{
    string line;
    vector<string> input;
    auto file = Input::LoadFile("input.txt");

    while (getline(file, line)) {
        cout << line << endl;
        input.push_back(line);
    }

    //the main thread for our system, it will be the tick we need
    std::thread([&] {
        while (ticks <= 221) {
            std::this_thread::sleep_for(std::chrono::milliseconds(TICK_TIMER));
            //call after the tick
            cycle_loop(input);
        }
    }).detach();

    while (true) {

    }
    std::cout << "Hello World!\n";
}

void cycle_loop(vector<string> file)
{
    ticks++;
    check_cycles();
    execute_loop(file[current_line]);
}

void execute_loop(string line)
{
    if(ticks == wait_for || wait_for == 0)
    if (line != "") {
        auto no = line.find("noop");
        auto add = line.find("addx");

        if (no != string::npos) {
            wait_for = ticks + 1;

            cout << "its a noop command! will just wait 1 cycle" << endl;
        }
        if (add != string::npos) {
            auto i = line.substr(5, line.length());
            wait_for = ticks + 2;
            x += stoi(i);

            cout << "it was an addx command with the value : " << i << " waiting 2 cycles, index now is : " << x << endl;
        }

        current_line++;
    }
}

void check_cycles()
{
    cout << "current cycle : " << ticks << endl;
    if (ticks == 20) {
        cout << "Its the 20th cycle! Register has X : " << x*20 << endl;
        sum += x * 20;
    }
    if (ticks == 60) {
        cout << "Its the 60th cycle! Register has X : " << x * 60 << endl;
        sum += x * 60;
    }
    if (ticks == 100) {
        cout << "Its the 100th cycle! Register has X : " << x * 100 << endl;
        sum += x * 100;
    }
    if (ticks == 140) {
        cout << "Its the 140th cycle! Register has X : " << x * 140 << endl;
        sum += x * 140;
    }
    if (ticks == 180) {
        cout << "Its the 180th cycle! Register has X : " << x * 180 << endl;
        sum += x * 180;
    }
    if (ticks == 220) {
        cout << "Its the 220th cycle! Register has X : " << x * 220 << endl;
        sum += x * 220;
    }

    if (ticks >= 220) {
        cout << "Final sum is : " << sum << endl;
    }
}
