#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int x, y;
int table[100][100] = { 0 }; //table for [Xi,Yi]
vector<vector<int>> ans;
//check the set is covering or not
bool isCover(int level, bool isIn[100]) {
    bool in;
    for (int i = 1; i <= x; ++i) {
        in = false;
        for (int j = 1; j <= level; ++j) {
            if (isIn[j] == true && table[i][j] == 1) {
                in = true;
                break;
            }
        }
        if (!in) {
            return false;
        }
    }
    return true;
}
//generate cover
void generate(int level, bool isIn[100]) {
    if (isCover(level, isIn)) {
        vector<int> temp;
        for (int i = 1; i <= level; ++i) {
            if (isIn[i] == true) {
                temp.push_back(i);
                //cout << i << " ";
            }
        }
        //cout << "level: " << level << endl;
        ans.push_back(temp);
        return;
    }
    if (level <= y) {
        bool newA[100];
        for (int i = 0; i < 100; ++i) {
            newA[i] = isIn[i];
        }
        generate(level + 1, newA); //Yi ignore, go to right child tree
        newA[level] = true;
        generate(level + 1, newA); //Yi choose, go to left child tree
    }
}
//get weight
int getWeight(int label) {
    vector<int> temp = ans[label];
    int r = 0;
    for (int a : temp) {
        r += table[0][a];
    }
    return r;
}

int main(int argc, char* argv[]) {
    ifstream f;
    for (int f_i = 1; f_i < argc; ++f_i) {
        f.open(argv[f_i]);
        ans.clear();
        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 100; ++j)
                table[i][j] = { 0 };
        }
        int w, x_c, y_c;
        bool isIn[100]; //for Yi(Pi)
        for (int i = 0; i < 100; i++) {
            isIn[i] = false;
        }
        f >> x >> y;
        for (int i = 1; i <= y; ++i) {
            f >> w;
            table[0][i] = w;
        }
        while (f >> x_c >> y_c && x_c) {
            table[x_c][y_c] = 1;
        }
        generate(1, isIn);

        int r = 0, weight, weightT; //r is smallest size in ans, weight is smallest weight, weightT is temp to store current weight
        r = ans[0].size();
        weight = getWeight(0);
        ans[0].push_back(weight);
        for (int i = 1; i < ans.size(); ++i) {
            weightT = getWeight(i);
            if (r > ans[i].size()) {
                r = ans[i].size();
                if (weightT < weight) {
                    weight = weightT;
                }
            }
            ans[i].push_back(weightT);
        }
        ++r;
        for (int i = 0; i < ans.size(); ++i) {
            if (ans[i].size() == r && ans[i][ans[i].size() - 1] == weight) {
                for (int j = 0; j < ans[i].size() - 1; ++j) {
                    cout << ans[i][j] << "\t";
                }
                cout << endl << "(" << ans[i].size() - 1 << "," << ans[i][ans[i].size() - 1] << ")" << endl;
            }
        }
        f.close();
    }
}