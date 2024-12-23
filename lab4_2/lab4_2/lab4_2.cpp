﻿#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
template<typename T1, typename T2>
class Pair {
	T1 first;
	T2 second;
};
class MenuItem {
protected:
	string name;
	double price;
	string type;
public:
	MenuItem(string name, double price, string type) :name(name), price(price), type(type) {}
	virtual void displayInfo() {
		cout << "Name: " << name << endl;
		cout << "Price: " << price << endl;
		cout << "Type: " << type << endl;
	}
	string getName() {
		return name;
	}
	double getPrice() {
		return price;
	}
	virtual string getType() {
		return "MenuItem";
	}
	virtual string getSpecial() = 0;
};



class Appetizer: public MenuItem {
private:
	string HotorCold;
public:
	Appetizer(string name, double price, string HotorCold) :MenuItem(name, price, "Appetizer"), HotorCold(HotorCold) {}
	void displayInfo() override{
		MenuItem::displayInfo();
		cout << "Appetizer is " << HotorCold<<endl<<endl;
	}
	string getType() override{
		return "Appetizer";
	}
	string getSpecial() override {
		return HotorCold;
	}
};
class MainCourse: public MenuItem {
private:
	string TypeofMain;
public:
	MainCourse(string name, double price, string TypeofMain) :MenuItem(name, price, "MainCourse"), TypeofMain(TypeofMain) {}
	void displayInfo() override {
		MenuItem::displayInfo();
		cout << "Main course is " << TypeofMain<<endl<<endl;
	}
	string getType() override {
		return "MainCourse";
	}
	string getSpecial() override {
		return TypeofMain;
	}

};
class Dessert: public MenuItem {
private:
	int difficulty;
public:
	Dessert(string name, double price, int difficulty) :MenuItem(name, price, "Dessert"), difficulty(difficulty) {}
	void displayInfo() override {
		MenuItem::displayInfo();
		cout << "The difficulty of this dessert: " << difficulty<<endl<<endl;
	}
	string getType() override {
		return "Dessert";
	}
	string getSpecial() override {
		return to_string(difficulty);
	}
};
class Menu {
private:
	vector<MenuItem*> menu;
public:
	void addMenuItem(MenuItem* menuitem) {
		menu.push_back(menuitem);
	}

	void searchMenuItem(string name) {
		for (auto it : menu) {
			if(it->getName()==name){
				it->displayInfo();
			}
		}
	}

	void sortMenuByPrice() {
		sort(menu.begin(), menu.end(), [](MenuItem* a,MenuItem* b) { return a->getPrice() < b->getPrice(); });
	}
	void displayInfo() {
		for (auto it : menu) {
			it->displayInfo();
		}
	}
	void saveToFile(string filename) {
		fstream f;
		f.open(filename,ios::out);
		f << menu.size() << endl;
		for (auto it : menu) {
			f << it->getName() << endl;
			f << it->getPrice() << endl;
			f << it->getType() << endl;
			f << it->getSpecial() << endl;
		}
	}

};
Menu RecoverMenu(string filename) {
	ifstream f;
	f.open(filename);
	Menu menu;
	string name;
	string type;
	string price;
	string size;
	string special;
	MenuItem* newitem;
	getline(f, size);
	for (int i = 0;i < stoi(size);i++) {
		getline(f, name);
		getline(f, price);
		getline(f, type);
		getline(f, special);

		if (type == "Appetizer") {
			newitem = new Appetizer(name, stod(price), special);
		}
		else if (type == "MainCourse") {
			newitem = new MainCourse(name, stod(price), special);
		}
		else {
			newitem = new Dessert(name, stod(price), stoi(special));
		}
		menu.addMenuItem(newitem);
	}
	return menu;
}

int main() {
	fstream out;
	out.open("output.txt", ios::app);
	Menu menu;
	ifstream f;
	f.open("menu.txt");
	if (f) {
		f.close();
		menu = RecoverMenu("menu.txt");
	}
	else {
		f.close();
		menu.addMenuItem(new Appetizer("Vegetables", 5, "Cold"));
		menu.addMenuItem(new Appetizer("Croutons", 8, "Hot"));
		menu.addMenuItem(new MainCourse("Borsch", 12, "Soap"));
		menu.addMenuItem(new MainCourse("Pasta carbonara", 14, "Hot dish"));
		menu.addMenuItem(new Dessert("Apple", 2, 3));
		menu.addMenuItem(new Dessert("Pen", 4, 5));
		menu.addMenuItem(new Dessert("ApplePen", 6, 8));
	}
	
	int action = 0;
	menu.displayInfo();
	cout << "Menu: " << endl;
	cout << "1. Add menu item " << endl;
	cout << "2. Search the menu item" << endl;
	cout << "3. Sort menu items by price" << endl;
	cout << "4. Save data" << endl;
	cout << "5. Exit" << endl;
	while (action != 5) {
		string name;
		string type;
		double price;
		cin >> action;
		MenuItem* newitem;
		switch (action) {
		case 1:
			out << "Adding"<<endl;
			cout << "Enter the name: ";
			cin >> name;
			cout << "Enter the price: ";
			cin >> price;
			cout << "Enter the type(Appetizer, MainCourse, Desert): ";
			cin >> type;
			
			if (type == "Appetizer") {
				cout << "Is appetizer hot or cold: ";
				string HotorCold;
				cin >> HotorCold;
				newitem = new Appetizer(name, price, HotorCold);
			}
			else if (type == "MainCourse") {
				cout << "Is maincourse a soap or a hot dish: ";
				string typeofmain;
				cin >> typeofmain;
				newitem = new MainCourse(name, price, typeofmain);
			}
			else {
				cout << "What is the difficulty of this dessert(1 to 10): ";
				int difficulty;
				cin >> difficulty;
				newitem = new Dessert(name, price, difficulty);
			}
			menu.addMenuItem(newitem);
			break;
		case 2:
			out << "Searching" << endl;
			cout << "Enter the name: ";
			cin >> name;
			menu.searchMenuItem(name);
			break;
		case 3:
			out << "Sorting" << endl;
			menu.sortMenuByPrice();
			break;
		case 4:
			out << "Saving" << endl;
			menu.saveToFile("menu.txt");
			break;
		case 5:
			out << "Exit" << endl;
			menu.displayInfo();
			break;
		default:
			cout << "wrong action, try again" << endl;
			break;
		}
		
	}
}
