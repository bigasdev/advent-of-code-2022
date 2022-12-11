// treetop_tree_house.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <vector>
#include <array>
#include "../../../day4/supply_stacks/supply_stacks/load_input.hpp"

//for this one we'll need to store the strings to map it later
void generateMap(string map[], int count);

//our tree class
struct Tree {
public:
    int middle;
    int up;
    int down;
    int right;
    int left;
};

//list of trees
vector<Tree> trees;
int count = 0;

std::string line;
std::array<std::array<int, 99>, 99> grid_2d;

int main()
{
    auto file = Input::LoadFile("input.txt");
    string line;

    //map stuff
    string map[100];
    int count = 0;

    /*for (int i = 0; i < 99; i++)
    {
        std::getline(file, line);
        for (int j = 0; j < 99; j++)
        {
            grid_2d[i][j] = (line[j] - '0');
            cout << grid_2d[i][j] << endl;
        }
    }

    int score = 197;
    int tree_height = 0;

    for (int i = 1; i <= 98; ++i)
    {
        for (int j = 1; j <= 98; ++j)
        {
            tree_height = grid_2d[i][j];

            for (int x = i - 1; x >= 0; --x)
            {
                if (tree_height <= grid_2d[x][j]) { goto check2; }
            }
            score++; continue;

        check2:;
            for (int x = i + 1; x < 99; ++x)
            {
                if (tree_height <= grid_2d[x][j]) { goto check3; }
            }
            score++; continue;

        check3:;
            for (int y = j - 1; y >= 0; --y)
            {
                if (tree_height <= grid_2d[i][y]) { goto check4; }
            }
            score++; continue;

        check4:;
            for (int y = j + 1; y < 99; ++y)
            {
                if (tree_height <= grid_2d[i][y]) { goto turbo_break; }
            }
            score++; continue;

        turbo_break:;
        }
    }

    cout << score << endl;*/

    while (getline(file, line)) {
        //we count the lines and add it to the array of strings
        map[count] = line;
        count++;
    }
    //generating the map
    generateMap(map, count);
    //to not exit the program
    while (true) {

    }
    std::cout << "Hello World!\n";
}

void generateMap(string map[], int count)
{
    int treeAmount = 0;

    for (size_t i = 0; i < count; i++)
    {
        //loop to check the trees from outside and whatnot
        cout << map[i] << endl;
        {
            if (i == 0) {
                cout << " Top of the grid ! " << endl;
                for (size_t i = 0; i < map[i].length(); i++)
                {
                    treeAmount++;
                }
            }else if (i == count-1) {
                cout << " Bottom of the grid ! " << endl;
                for (size_t i = 0; i < map[i].length(); i++)
                {
                    treeAmount++;
                }
            }
            //normal loop, this is where we'll check the normal trees
            else {
                //reeAmount += 2;
                for (size_t j = 0; j < map[i].length(); j++)
                {
                    //creating the tree struct
                    Tree tree{};
                    //we are not using the first and last elements because they are on the edge
                    if (j != 0 && j != map[i].length() - 1) {
                        tree.middle = map[i][j] - '0';
                        cout << "Element : " << tree.middle << endl;

                        //here we have the base of the element, we need to check if there are trees in the side
                        int right = j + 1;
                        int left = j - 1;
                        int up = i - 1;
                        int down = i + 1;

                        //checks to make sure they can execute
                        if (right <= map[i].length() - 1) {
                            tree.right = (int)map[i][right] - '0';
                        }
                        if (left >= 0) {
                            tree.left = (int)map[i][left] - '0';
                        }
                        if (up >= 0) {
                            tree.up = (int)map[up][j] - '0';
                        }
                        if (down <= count-1) {
                            tree.down = (int)map[down][j] - '0';
                        }
                        trees.push_back(tree);
                    }
                }
            }
        }
    }
    for (auto const& t : trees) {
        cout << "We have this Tree : " << endl;
        cout << " " << t.up << " " << endl;
        cout << t.left << " " << t.middle << " " << t.right << endl;
        cout << " " << t.down << " " << endl;

        if (t.middle > t.up) {
            if (t.middle > t.right && t.middle > t.left && t.middle > t.down) {
                cout << " its visible on up ! " << endl;
                treeAmount++;
                cout << treeAmount << endl;
                continue;
            }
        }
    }
    cout << "Amount of trees : " << treeAmount << endl;
}
