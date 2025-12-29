#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    ifstream infile("input.txt");
    string line;
    long long grandTotal = 0;

    while (getline(infile, line)) {
        if (line.empty()) continue;
        
        size_t startBracket = line.find('[');
        size_t endBracket = line.find(']');
        string lightPattern = line.substr(startBracket + 1, endBracket - startBracket - 1);
        
        int numLights = lightPattern.length();
        vector<int> target(numLights);
        for(int i = 0; i < numLights; i++) {
            target[i] = (lightPattern[i] == '#' ? 1 : 0);
        }

        vector<vector<int>> buttons;
        size_t pos = line.find('(');
        while (pos != string::npos) {
            size_t end = line.find(')', pos);
            string buttonContent = line.substr(pos + 1, end - pos - 1);
            
            vector<int> currentButton;
            stringstream ss(buttonContent);
            string lightNum;
            while (getline(ss, lightNum, ',')) {
                currentButton.push_back(stoi(lightNum));
            }
            buttons.push_back(currentButton);
            pos = line.find('(', end);
        }

        int numButtons = buttons.size();
        vector<vector<int>> table(numLights, vector<int>(numButtons + 1, 0));

        for (int b = 0; b < numButtons; b++) {
            for (int lightIndex : buttons[b]) {
                table[lightIndex][b] = 1;
            }
        }
        for (int l = 0; l < numLights; l++) {
            table[l][numButtons] = target[l];
        }

        
        int pivotRow = 0;
        vector<int> pivotCol(numLights, -1);
        
        for (int col = 0; col < numButtons && pivotRow < numLights; col++) {
            int sel = pivotRow;
            while (sel < numLights && table[sel][col] == 0) sel++;
            
            if (sel == numLights) continue;

            swap(table[sel], table[pivotRow]);
            pivotCol[pivotRow] = col;

            for (int i = 0; i < numLights; i++) {
                if (i != pivotRow && table[i][col] == 1) {
                    for (int j = col; j <= numButtons; j++) {
                        table[i][j] = table[i][j] ^ table[pivotRow][j];
                    }
                }
            }
            pivotRow++;
        }

        vector<int> freeVars;
        vector<bool> isPivot(numButtons, false);
        for (int i = 0; i < pivotRow; i++) {
            if (pivotCol[i] != -1) {
                isPivot[pivotCol[i]] = true;
            }
        }
        for (int b = 0; b < numButtons; b++) {
            if (!isPivot[b]) {
                freeVars.push_back(b);
            }
        }

        int minPresses = numButtons + 1;
        int numFree = freeVars.size();
        
        for (int mask = 0; mask < (1 << numFree); mask++) {
            vector<int> solution(numButtons, 0);
            
            for (int f = 0; f < numFree; f++) {
                if (mask & (1 << f)) {
                    solution[freeVars[f]] = 1;
                }
            }
            
            for (int i = pivotRow - 1; i >= 0; i--) {
                if (pivotCol[i] != -1) {
                    solution[pivotCol[i]] = table[i][numButtons];
                    for (int j = pivotCol[i] + 1; j < numButtons; j++) {
                        solution[pivotCol[i]] ^= (table[i][j] & solution[j]);
                    }
                }
            }
            
            int count = 0;
            for (int b = 0; b < numButtons; b++) {
                if (solution[b] == 1) count++;
            }
            minPresses = min(minPresses, count);
        }
        
        grandTotal += minPresses;
    }

    cout << grandTotal << endl;
    return 0;
}