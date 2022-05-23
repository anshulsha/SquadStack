#include<bits/stdc++.h>
using namespace std;

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;

class userObject {
    public:
        string vehicleNumber = "";
        int age = 0;
        int slotNumber;
    
    userObject(string vehicleNumber, int age, int slotNumber){
        this->vehicleNumber = vehicleNumber;
        this->age = age;
        this->slotNumber = slotNumber;
    }
};
    static int slot_size = 0;
    unordered_map<int, std::vector<int>> age_slot;
    unordered_map<int, vector<string>> age_vehicle_number;
    unordered_map<string, int> vehicle_slot;
    unordered_map<int, bool> slot;
    unordered_map<int, userObject*> parking_DB;

void leave(int slot_num){
    int age = parking_DB[slot_num]->age;
    string vehicleNumber = parking_DB[slot_num]->vehicleNumber;
    age_slot.erase(age);
    vector<string> vec = age_vehicle_number[age];
    vector<string> new_vec;
    for (int i = 0; i < vec.size(); i++){
        if (vec[i] == vehicleNumber){
            continue;
        }
        else {
            new_vec.push_back(vec[i]);
        }
    }
    age_vehicle_number[age] = new_vec;
    vehicle_slot.erase(vehicleNumber);
    slot.erase(slot_num);
    delete parking_DB[slot_num];
    parking_DB.erase(slot_num);
    cout<<"Slot number "<<slot_num<<" vacated, the car with vehicle registration number \""<<vehicleNumber<<"\" left the space, the driver of the car was of age "<<age<<endl;
}

void vehicle_slot_fun(string vehicleNumber){
    cout<<"Car with vehicle registration number "<<vehicleNumber<<" has been parked at slot number "<<vehicleNumber<<endl;
}

void slot_numbers(int age){
    vector<int> vec = age_slot[age];
    for (int i = 0;i < vec.size();i++){
        cout<<vec[i];
        i == vec.size()-1 ? cout<<"" : cout<<",";
    }
    cout<<endl;
}

void slot_number_with_vehicle_number(string vehicleNumber){
    cout<<vehicle_slot[vehicleNumber]<<endl;
}

void vehicle_registration_number_for_driver_of_age(int age) {
    vector<string> vec = age_vehicle_number[age];
    for (int i = 0;i < vec.size();i++){
        cout<<vec[i];
        i == vec.size()-1 ? cout<<"" : cout<<",";
    }
}
void replace_first(
    std::string& s,
    std::string const& toReplace,
    std::string const& replaceWith
) {
    std::size_t pos = s.find(toReplace);
    if (pos == std::string::npos) return;
    s.replace(pos, toReplace.length(), replaceWith);
}

void solve(string input_string){
  int c = 1;
        
        string str = input_string;
        if (str.find("Create_parking_lot") != std::string::npos) {
            replace_first(str, "Create_parking_lot ", "");
            stringstream toNum(str);
            int t_slot;
            toNum >> t_slot;
            slot_size = t_slot;
            cout<<"Created parking of "<<t_slot<<" slots"<<endl;
        }
        else if (str.find("Slot_numbers_for_driver_of_age") != std::string::npos) {
            replace_first(str, "Slot_numbers_for_driver_of_age ", "");
            stringstream toNum(str);
            int t_age;
            toNum >> t_age;
            slot_numbers(t_age);
        }
        else if (str.find("Slot_number_for_car_with_number") != std::string::npos) {
            replace_first(str, "Slot_number_for_car_with_number ", "");
            slot_number_with_vehicle_number(str);
        }
        else if (str.find("Leave") != std::string::npos) {
            replace_first(str, "Leave ", "");
            stringstream toNum(str);
            int t_slot;
            toNum >> t_slot;
            leave(t_slot);
        }
        else if (str.find("Vehicle_registration_number_for_driver_of_age") != std::string::npos) {
            replace_first(str, "Vehicle_registration_number_for_driver_of_age ", "");
            stringstream toNum(str);
            int t_age;
            toNum >> t_age;
            vehicle_registration_number_for_driver_of_age(t_age);
        }
        else {
        stringstream iss(str);
        string vehicleNumber;
        int age;
        int slot_val=0;
        
        string word;
        int temp_slot = 1;
                    while (temp_slot <= slot_size){
                        if (slot[temp_slot])
                            temp_slot++;
                        else
                            break;
                    }
                    slot[temp_slot] = true;
                    age = 0;
                    vehicleNumber = "";
        while (iss >> word) {
            if (word == "Park" || word == "driver_age") {
                continue;
            }
            else {
                if (word.find_first_not_of("0123456789") == string::npos) {
                    stringstream toNum(word);
                    toNum >> age;
                    
                    age_slot[age].push_back(temp_slot);
                }
                else {
                    vehicleNumber = word;
                    vehicle_slot[vehicleNumber] = temp_slot;

                }
            }
                if (age > 0 && vehicleNumber.size() > 0) {
                    age_vehicle_number[age].push_back(vehicleNumber);
                }
        }
            userObject* obj = new userObject(vehicleNumber, age, temp_slot);
            parking_DB[temp_slot] = obj;
            cout<<"Car with vehicle registration number \""<<vehicleNumber<<"\" has been parked at slot number "<<temp_slot<<endl;
        }
}

void readInput() {
   string filename("input.txt");
    vector<string> lines;
    string line;

    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    while (getline(input_file, line)){
        lines.push_back(line);
    }

  
    for (const auto &i : lines){
      solve(i);
    }

    input_file.close();
}

int main () {
  for (int i = 1;i <= slot_size;i++){
            slot[i] = false;
        }
    std::ofstream ofs{"output.txt"}; 
    auto cout_buff = std::cout.rdbuf(); 
    std::cout.rdbuf(ofs.rdbuf()); 
    readInput();
    std::cout.rdbuf(cout_buff);
    return 0;
}
