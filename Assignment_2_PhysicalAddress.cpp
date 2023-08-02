#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> lines;
vector<string> PageTable1;
vector<string> PageTable2;

pair<string, string> calculatePhysicall(string inputVirtaulAddress, vector<string>& PageTable1, vector<string>& PageTable2) {

    string PT1, PT2, Offset;
    PT1 = inputVirtaulAddress.substr(0, 10);
    PT2 = inputVirtaulAddress.substr(10, 10);
    Offset = inputVirtaulAddress.substr(20, 12);

    cout << "Input 1 (10 bit) : " << PT1 << endl;
    cout << "Input 2 (10 bit) : " << PT2 << endl;
    cout << "Offset  (12 bit) : " << Offset << endl;

    int index1 = stoi(PT1, nullptr, 2);
    int index2 = stoi(PT2, nullptr, 2);

    cout << "Index PageTable 1 : " << index1 << endl;
    cout << "Index PageTable 2 : " << index2 << endl;
    

    if (index1 >= PageTable1.size() || index2 >= PageTable2.size()) {
        cout << "Error: Page table entry not found!" << endl;
        return make_pair("", "");
    }

    string PhysicalAddress_str = PageTable1[index1] + PageTable2[index2] + Offset;
    string PhysicalAdrress_log = PageTable1[index1] + " " + PageTable2[index2] + " " + Offset;
    //int PhysicalAddress = stoi(PhysicalAddress_str, nullptr, 2);
    return make_pair(PhysicalAddress_str, PhysicalAdrress_log);

}

int main()
{
    ifstream virtaul_addr("virtual_addr.txt");
    string line;
    while (getline(virtaul_addr, line)) {
        lines.push_back(line);
    }

    bool ReadingTable1 = false;

    for (const auto& line : lines) {
        if (line.find("Table_1") != string::npos) {
            ReadingTable1 = true;
        }
        else if (line.find("Table_2") != string::npos) {
            ReadingTable1 = false;
        }
        else {
            if (ReadingTable1) {
                PageTable1.push_back(line);
            }
            else {
                PageTable2.push_back(line);
            }
        }
    }

    string inputVirtaulAddress;
    cout << "input VirtaulAddress (32 bit) : ";
    cin >> inputVirtaulAddress;

    pair<string, string> result = calculatePhysicall(inputVirtaulAddress, PageTable1, PageTable2);

    if (!result.first.empty()) {
        cout << "\nPhysical Address : " << result.first << endl;
        cout << "Physicall Address Log : " << result.second << endl;
    }

    return 0;

}

