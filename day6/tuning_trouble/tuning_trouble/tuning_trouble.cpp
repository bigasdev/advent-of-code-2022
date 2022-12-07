

#include <iostream>
#include <string>
#include <set>
#include "load_input.hpp"

//method to detect the duplicates inside a "marker"
bool isDuplicate(string line);

int duplicateIdx = 0;
int find_last_four_non_repeating(const std::string& s);

int main()
{
    auto file = Input::LoadFile("input.txt");
    
    string line;
    //string that will be constantly storing our marker
    string marker;
    bool canAdd = true;
    int index = 0;int currentMarker = 0;int helpIdx = 0;
    //while loop for the line, we'll count the letters with an index
    while (getline(file, line)) {
        int test = find_last_four_non_repeating(line);
        cout << test << endl;

        for (size_t i = 0; i < line.length(); i++)
        {
            if (canAdd)marker += line[i];
            canAdd = true;
            currentMarker++;
            cout << "The current marker is : " << marker << endl;
            if (isDuplicate(marker)) {
                cout << "the marker finished at : " << line[i] << endl;
                marker = line[duplicateIdx];
                i = duplicateIdx + 1;
                continue;
                /*currentMarker--;
                int pos = index - currentMarker;
                cout << pos << endl;
                if(pos >= 0)
                    marker = line.substr(pos, index);
                /*if (helpIdx >= 4) {
                    if (line.length() <= index + 1) {
                        marker = line[index + 1];
                        canAdd = false;
                        helpIdx = 0;
                    }
                }*/
                cout << "marker after duplicate : " << marker << endl;
                currentMarker = 0;
            }
            helpIdx++;
            cout << "trying with  : " << marker << endl;
            if (marker.length() >= 4)break;
        }
        /*for (char c : line) {
            index++;
            if(canAdd)marker += c;
            canAdd = true;
            currentMarker++;
            cout << "The current marker is : " << marker << endl;
            if (isDuplicate(marker)) {
                cout << "the marker finished at : " << c << endl;
                marker = line[duplicateIdx];
                /*currentMarker--;
                int pos = index - currentMarker;
                cout << pos << endl;
                if(pos >= 0)
                    marker = line.substr(pos, index);
                /*if (helpIdx >= 4) {
                    if (line.length() <= index + 1) {
                        marker = line[index + 1];
                        canAdd = false;
                        helpIdx = 0;
                    }
                }
                cout << "marker after duplicate : " << marker << endl;
                currentMarker = 0;
            }
            helpIdx++;
            cout << "trying with  : " << marker << endl;
            if (marker.length() >= 4)break;
        }*/
    }

    cout << marker << endl;
    cout << "The output is : " << index << endl;

    while (true) {

    }
}

bool isDuplicate(string line)
{
    int size = line.length();
    if (size < 2) {
        cout << "not enough size" << endl;
        return false;
    }
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (line[i] == line[j] && line[i] != ' ') {
                //its duplicate
                duplicateIdx = i;
                cout << "found the duplicate : " << "at : " << i << line[i] << endl;
                return true;
            }
        }
    }
    return false;
}
int find_last_four_non_repeating(const std::string& s) {
    std::set<char> last_four;
    for (int i = s.length() - 1; i >= 0; i--) {
        if (last_four.count(s[i]) == 0) {
            last_four.insert(s[i]);
        }
        else {
            last_four.erase(s[i]);
        }
        if (last_four.size() == 4) {
            break;
        }
    }
    return s.length() - last_four.size();
}

