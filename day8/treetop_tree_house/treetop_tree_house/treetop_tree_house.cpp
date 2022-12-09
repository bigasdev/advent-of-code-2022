// treetop_tree_house.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <vector>
#include "../../../day4/supply_stacks/supply_stacks/load_input.hpp"

//for this one we'll need to store the strings to map it later
void generateMap(string map[]);

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

int main()
{
    auto file = Input::LoadFile("input.txt");
    string line;

    //map stuff
    string map[100];
    int count = 0;

    while (getline(file, line)) {
        //we count the lines and add it to the array of strings
        map[count] = line;
        count++;
    }
    //generating the map
    generateMap(map);
    //to not exit the program
    while (true) {

    }
    std::cout << "Hello World!\n";
}

void generateMap(string map[])
{
    int treeAmount = 0;

    for (size_t i = 0; i < map->length(); i++)
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
            }else if (i == map->length()-1) {
                cout << " Bottom of the grid ! " << endl;
                for (size_t i = 0; i < map[i].length(); i++)
                {
                    treeAmount++;
                }
            }
            //normal loop, this is where we'll check the normal trees
            else {
                treeAmount += 2;
                for (size_t j = 0; j < map[i].length(); j++)
                {
                    //creating the tree struct
                    Tree tree{};
                    //we are not using the first and last elements because they are on the edge
                    if (j != 0 && j != map[i].length() - 1) {
                        tree.middle = map[i][j] - 48;
                        cout << "Element : " << tree.middle << endl;

                        //here we have the base of the element, we need to check if there are trees in the side
                        int right = j + 1;
                        int left = j - 1;
                        int up = i - 1;
                        int down = i + 1;

                        //checks to make sure they can execute
                        if (right <= map[i].length() - 1) {
                            tree.right = (int)map[i][right] - 48;
                        }
                        if (left >= 0) {
                            tree.left = (int)map[i][left] - 48;
                        }
                        if (up >= 0) {
                            tree.up = (int)map[up][j] - 48;
                        }
                        if (down <= map->length()) {
                            tree.down = (int)map[down][j] - 48;
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

        if (t.middle > t.up && (t.middle > t.right || t.middle > t.left)) {
            treeAmount++;
            continue;
        }
        if (t.middle > t.down && (t.middle > t.right || t.middle > t.left)) {
            treeAmount++;
            continue;
        }
    }
    cout << "Amount of trees : " << treeAmount << endl;
}
