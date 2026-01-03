#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Shape {
    int id;
    vector<string> display;
    int area;
};

struct Region {
    int dim1;
    int dim2;
    vector<int> count;
};

int main(int argc, char* argv[])
{
    string input = "input.txt";
    if (argc > 1) {
        input = argv[1];
    }

    ifstream file(input);
    string line;

    vector<Shape> shapes;
    vector<Region> regions;
    int shape = -1;
    while(getline(file, line)) {
        if (line.back() == ':') {
            shapes.emplace_back();
            shapes.back().id = stoi(line.substr(0, line.size() - 1));
        } else if (line[0] == '.' || line[0] == '#') {
            shapes.back().display.push_back(line);
        } else if (line.find('x') != string::npos) {
            auto x_idx = line.find('x');
            auto colon_idx = line.find(':', x_idx + 1);
            regions.emplace_back();
            regions.back().dim1 = stoi(line.substr(0, x_idx));
            regions.back().dim2 = stoi(line.substr(x_idx+1, colon_idx - x_idx - 1));
            
            string nums = line.substr(colon_idx+2);
            istringstream iss(nums);
            int value;
            while (iss >> value) {
                regions.back().count.push_back(value);
            }
        }
    }
    for (auto& s : shapes) {
        s.area = 0;
        for (const auto& row : s.display) {
            for (const auto ele : row) {
                if (ele == '#') s.area++;
            }
        }
    }
    int n_regions_fit_presents = 0;
    for (const auto& r : regions) {
        int total_used_area = 0;
        for (size_t idx = 0; idx < r.count.size(); idx++) {
            total_used_area += (shapes[idx].area * r.count[idx]);
        }
        if ((r.dim1 * r.dim2) - total_used_area >= 0) {
            n_regions_fit_presents++;
        }
    }
    cout << n_regions_fit_presents << endl;
    return 0;
}