#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <map>

using namespace std;
//we need this class to control duplicates on the item.
class Item {
public:
    string idx;
    char item{};
};

int getPriority(char letter);
void calculate(map<string, Item> input);
void getBadge(map<int, vector<string>> groupsMap);

int main()
{
    int choice;

    //variables to get the groups for the badge
    int currentIdx = 0;
    int groups = 0;
    {
        //opening the input with an txt
        //i could have created a method for this
        ifstream file;file.open("input.txt");
        if (!file.is_open()) {
            cout << "unable to open the file" << endl;
            return 0;
        }

        string line;
        //items map
        map<string, Item> items;
        //groups map
        map<int, vector<string>> groupsMap;
        string currentGroupMap[3];
        while (getline(file, line)) {
            //creation of the groups
            currentGroupMap[currentIdx] = line;
            vector<string> stringMap;

            currentIdx++;
            //main loop for the group, we keep tracking the number of the lines in the .txt
            //if its bigger than 3 we add it to the maps and increase the number of groups
            if (currentIdx >= 3) {
                for (size_t i = 0; i < 3; i++)
                {
                    stringMap.push_back(currentGroupMap[i]);
                }
                groupsMap.insert(pair<int, vector<string>>(groups, stringMap));

                groups++;
                currentIdx = 0;
                stringMap.clear();
            }
            //since all the compartments are divided equally we just get the size/2 
            //and use it with a substr to get the two halfs.
            int size = (line.size() / 2);
            string firstHalf = line.substr(0, size);
            string secondHalf = line.substr(size, line.size());

            //with this loop we can loop through all the letters in both halfs
            for (auto const& item : firstHalf) {
                for (size_t i = 0; i < size; i++)
                {
                    //if we find the item we create a new itemobj for it
                    if (item == secondHalf[i]) {
                        Item itemObj;
                        itemObj.idx = secondHalf;
                        itemObj.item = item;

                        //that is why we needed the map:
                        //we can check if we already have it on the compartment.
                        map<string, Item>::iterator it;
                        it = items.find(secondHalf);
                        if (it != items.end()) {

                        }
                        else {
                            items.insert(pair<string,Item>(secondHalf, itemObj));
                        }                       
                    }
                }
            }
        }
        cout << "Number of groups : " << groups << endl;
        calculate(items);

        //groups logic
        getBadge(groupsMap);
        //just for debug purpouses, i didnt want to keep hitting f5 all the time.
        scanf_s("%d", &choice);
    }
}

//function that will be used to return the priority
int getPriority(char letter)
{
    //instead of creating a complex map for the values, we'll just create a string with the values needed for the math 
    string values = "abcdefghijklmnopqrstuvwyxzABCDEFGHIJKLMNOPQRSTUVWYXZ";
    int idx = 1;
    for (char c : values) {
        //if we find the item we just increase the sum with the idx
        //otherwise we increase the idx
        if (letter == c)break;
        idx++;
    }
    return idx;
}

//our main method, here we'll get the map of the items from the .txt and calculate it acording to the exercise.
void calculate(map<string, Item> input) {
    //instead of creating a complex map for the values, we'll just create a string with the values needed for the math 
    string values = "abcdefghijklmnopqrstuvwyxzABCDEFGHIJKLMNOPQRSTUVWYXZ";
    int sum = 0;

    for (auto const& item : input) {
        //started on 1 because of the priority starting at 1
        int idx = 1;

        for (char c : values) {
            //if we find the item we just increase the sum with the idx
            //otherwise we increase the idx
            if (item.second.item == c) {
                sum += idx;
            }
            idx++;
        }
    } 
    cout << "Sum of the items : " << sum << endl;
}

//function that is used to obtain the badge for each group
void getBadge(map<int, vector<string>> groupsMap)
{
    int sum = 0;
    for (auto const& group : groupsMap) {
        cout << "Group : " << group.first << endl;
        cout << "_________" << endl;

        char badge = 0;
        int idx = 0;

        //loop to get the badge, we loop through each char of each string (3)
        //if we get the same letter on all the 3 of them we break the loop and use it as badge.
        for (char c : group.second[0]) {
            idx = 0;
            for (char ch : group.second[1]) {
                if (c == ch) {
                    idx++;
                    break;
                }
            }
            for (char cha : group.second[2]) {
                if (c == cha) {
                    idx++;
                    break;
                }
            }

            if (idx >= 2) {
                badge = c;
                break;
            }
        }
        int priority = getPriority(badge);
        sum += priority;
        cout << "Found the badge : " << badge << endl;
        cout << "Badge priority : " << priority << endl;
    }
    cout << "Sum of all the badges : " << sum;
}
