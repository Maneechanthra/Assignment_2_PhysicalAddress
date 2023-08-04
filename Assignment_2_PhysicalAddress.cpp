#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> lines;           //สร้างตัวแปร lines ประเภทข้อมูลแบบ string 
vector<string> PageTable1;      //สร้างตัวแปร Pagetable1 ประเภทข้อมูลแบบ string เพื่อเก็บข้อมูลของ Table_1
vector<string> PageTable2;      //สร้างตัวแปร Pagetable2 ประเภทข้อมูลแบบ string เพื่อเก็บข้อมูลของ Table_2

// ประกาศ Functions calculatePhysical และมีการรับค่า inputVirtaulAddress pagetable1 และ pagetable2 มาจาก function main
pair<string, string> calculatePhysical(string inputVirtaulAddress, vector<string>& PageTable1, vector<string>& PageTable2) { 

    string PT1, PT2, Offset; // ประกาศตัวแปร PT1 PT2 และ offset เพื่อเก็บค่าการแบ่งช้อมูลที่ได้รับมาจาก inputVirtaulAddress ที่กรอกมาจากแป้นพิพม์
    PT1 = inputVirtaulAddress.substr(0, 10); //PT1 เก็บข้อมูล bit 10 ตัวแรกมาจาก inputVirtaulAddress 
    PT2 = inputVirtaulAddress.substr(10, 10); //PT2 เก็บข้อมูล bit 10 ตัวถัดมาต่อจาก PT1  
    Offset = inputVirtaulAddress.substr(20, 12); //offset เก็บข้อมูล bit 12 ที่เหลือจาก inputVirtaulAddress

    //แสดงข้อมูล bit ทีได้รับการแบ่งไปยังตัวแปรต่างๆ ทางหน้าจอ
    cout << "Input 1 (10 bit) : " << PT1 << endl; 
    cout << "Input 2 (10 bit) : " << PT2 << endl;
    cout << "Offset  (12 bit) : " << Offset << endl;

    int index1 = stoi(PT1, nullptr, 2); //ประกาศตัวแปร index1 เพือ่ทำการเก็บค่าตำแหน่งเพื่อนำไปอ้างอิงตำแหน่งในข้อมูล โดยทำการแปลงข้อมูลจาก PT1 ฐาน 2 ให้เป็น ฐาน 10
    int index2 = stoi(PT2, nullptr, 2); //ประกาศตัวแปร index2 เพือ่ทำการเก็บค่าตำแหน่งเพื่อนำไปอ้างอิงตำแหน่งในข้อมูล โดยทำการแปลงข้อมูลจาก PT2 ฐาน 2 ให้เป็น ฐาน 10

    cout << "Index PageTable 1 : " << index1 << endl; //แสดงตำแหน่งอ้างอิงหลังจากได้ทำการแปลงจากฐาน 2 เป็น ฐาน 10 แล้ว ทางหน้าจอ
    cout << "Index PageTable 2 : " << index2 << endl; //แสดงตำแหน่งอ้างอิงหลังจากได้ทำการแปลงจากฐาน 2 เป็น ฐาน 10 แล้ว ทางหน้าจอ
    
    //กำหนดเงื่อนไข ถ้า index2 มีค่ามากกว่าหรือเท่ากับขนาดของ PageTable1 หรือ index2 มีค่ามากกว่าหรือเท่ากับขนาดของ PageTable1
    if (index1 >= PageTable1.size() || index2 >= PageTable2.size()) { 
        cout << "Error: Page table entry not found!" << endl; // หากเข้าเงื่อนไขข้างต้นจะแสดงข้อความ error ทางหน้าจอ
        return make_pair("", ""); // return ค่าว่างกลับไป เพราะมีการใช้ชนิดข้อมูลแบบ pair ในการ return ค่าหลายค่า จึงต้องทำให้มีการ Return ค่าว่างกลับไป 2 ค่า
    }

    //ประกาศตัวแปร PhysicalAddress_str ประเภท String เพื่อเก็บผลลัพธ์ของ PhysicallAddress ที่ได้อ้างอิงตำแหน่งใน Table แล้ว
    string PhysicalAddress_str = PageTable1[index1] + PageTable2[index2] + Offset; // กำหนดให้ PhysicalAddress_str มีค่าเท่ากับ Pagetable1 ตำแหน่ง index1 บวกด้วย Pagetable2 ตำแหน่งที่ index2 และบวกด้วย offset 12 bit ที่เก็บค่าไว้
    string PhysicalAdrress_log = PageTable1[index1] + " " + PageTable2[index2] + " " + Offset;
    return make_pair(PhysicalAddress_str, PhysicalAdrress_log); // Return ค่า PhysicalAddress_str PhysicalAdrress_log กลับไปยัง Function main ในรูปแบบของ String

}

int main()
{

    ifstream virtual_addr("virtual_addr.txt"); //เปิดและเชื่อมต่อไฟล์ที่ชื่อว่า "virtual_addr.txt" โดยตัวแปร virtual_addr จะเป็นอ็อบเจกต์ที่ใช้ในการเข้าถึงข้อมูลในไฟล์
    string line; //สร้างตัวแปร line เป็นชนิดข้อมูล String 
    while (getline(virtual_addr, line)) { //ใช้ while loop เพื่อทำอ่านข้อมูลจาก object virtual_addr โดยใช้ function getline เพื่ออ่านข้อมูลแต่ละบรรทัดในไฟล์ "virtual_addr.txt" แล้วนำไปเก็บไว้ในตัวแปร line เก็บข้อมูลจากแต่ละบรรทัดของไฟล์
        lines.push_back(line); //เมื่อทำการเก็บข้อมูลไว้ใน line แล้ว จากนั้นจะนำข้อมูลไปเก็บไว้ใน vector lines เพือ่จัดเก้บข้อมูลทั้งหมดที่ได้จากการอ่าน file
    }

    bool ReadingTable1 = false; //ประกาศตัวแปร ReadingTable 1 เป็นชนิดข้อมูลแบบ boolean โดยกำหนดค่าเริ่มต้นให้เป็น false 

    for (const auto& line : lines) { //เรียกใช้ for loop เพื่อคำการอ่านค่าตามจำนวนข้อมูลที่อยู่ใน vector lines แล้วทำการเก็บไว้ในตัวแปร line ในแต่ละรอบของการวนลูป
        if (line.find("Table_1") != string::npos) { // กำหนดเงื่อนไข if เพื่อตรวจสอบว่าตัวแปร line มีคำว่า Table_1 หรือไม่ กรณีถ้าไม่พบคำว่า Table_1 จะคืนค่า string::npos ซึ่งมีค่าเท่ากับ -1
            ReadingTable1 = true; //หากเงื่อนไข if เป็นจริง พบคำว่า Table1 จะกำหนดค่า ReadingTable1 ให้มีค่าเท่ากับ true 
        }
        else if (line.find("Table_2") != string::npos) { // กำหนดเงื่อนไข if เพื่อตรวจสอบว่าตัวแปร line มีคำว่า Table_2 หรือไม่ กรณีถ้าไม่พบคำว่า Table_2 จะคืนค่า string::npos ซึ่งมีค่าเท่ากับ -1
            ReadingTable1 = false; //หากเงื่อนไข if เป็นจริง พบคำว่า Table_2 จะกำหนดค่า ReadingTable1 ให้มีค่าเท่ากับ false 
        }
        else { // หากไม่เข้าเงื่อนไข if จะเรียกมีการเรียกใช้ เงื่อนไข else 
            if (ReadingTable1) { //ถ้าค่าของตัวแปร ReadingTable1 = true หรือเป้นจริง
                PageTable1.push_back(line); //เพิ่มข้อมูล line ลงใน vector PageTable1
            }
            else { //หาก if ไม่เป็นจริง
                PageTable2.push_back(line); //เพิ่มข้อมูล line ลงใน vector PageTable 2 
            }
        }
    }

    string inputVirtaulAddress; // ประกาศตัวแปร inputVirtaulAddress มีประเภทเป็น string 
    cout << "input VirtaulAddress (32 bit) : "; //แสดงข้อความ  input VirtaulAddress (32 bit) :  ทางหน้าจอ
    cin >> inputVirtaulAddress; //รับข้อมูลที่ผู้ใช้ป้อนเข้ามา (input) โดยค่าที่ผู้ใช้ป้อนเข้ามาจะถูกเก็บในตัวแปร inputVirtaulAddress
     
    //เรียกใช้ฟังก์ชัน calculatePhysical() โดยมีการส่ง paramiter คือ  inputVirtaulAddress PageTable1 PageTable2 ไปยัง function calculatePhysical
    pair<string, string> result = calculatePhysical(inputVirtaulAddress, PageTable1, PageTable2); //ประกาศตัวแปร result ที่มีประเภทเป็นคู่ของสตริง แต่ละสตริงเก็บค่าที่คำนวณและได้รับคืนมาจากฟังก์ชัน calculatePhysical()

    if (!result.first.empty()) { //ตรวจสอบว่ามีค่า result.first เป็นค่าว่างหรือไม่ หากไม่เป็นค่าว่าง จะแสดงผลลัพธ์ทางหน้าจอ
        cout << "\nPhysical Address : " << result.first << endl; //แสดง  Physical Address ทางหน้าจอ
        cout << "Physicall Address Log : " << result.second << endl; //แสดง  Physical Address Log ทางหน้าจอ
    }

    return 0;

}

