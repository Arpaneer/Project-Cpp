#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
using namespace std;

class Medicine{
private:
    int id, quantity;
    string name;
    float price;

public:

    void add(){
        cout<<"Enter Medicine ID: ";
        cin>>id;

        cout<<"Enter Medicine Name: ";
        cin>>name;

        cout<<"Enter Price: ";
        cin>>price;

        cout<<"Enter Quantity: ";
        cin>>quantity;
    }

    void display(){
        cout<<"\nID: "<<id
            <<"\nName: "<<name
            <<"\nPrice: "<<price
            <<"\nQuantity: "<<quantity<<endl;
    }

    int getID(){ return id; }
    string getName(){ return name; }
    float getPrice(){ return price; }
    int getQuantity(){ return quantity; }

    void reduceQuantity(int q){
        quantity -= q;
    }
};

// Search function
int findMedicine(vector<Medicine>& store,int id){
    for(int i=0;i<store.size();i++){
        if(store[i].getID()==id)
            return i;
    }
    return -1;
}

int main(){

    vector<Medicine> store;
    int choice;

    do{
        cout<<"\n\n===== Medical Store Management =====";
        cout<<"\n1. Add Medicine";
        cout<<"\n2. Display Medicines";
        cout<<"\n3. Search Medicine";
        cout<<"\n4. Buy Medicine";
        cout<<"\n5. Exit";
        cout<<"\nEnter choice: ";
        cin>>choice;

        system("cls");

        // ADD MEDICINE
        if(choice==1){
            Medicine m;
            m.add();
            store.push_back(m);
        }

        // DISPLAY MEDICINES
        else if(choice==2){
            if(store.empty())
                cout<<"No medicines available\n";

            for(int i=0;i<store.size();i++)
                store[i].display();
        }

        // SEARCH MEDICINE
        else if(choice==3){
            int id;
            cout<<"Enter Medicine ID: ";
            cin>>id;

            int index=findMedicine(store,id);

            if(index!=-1)
                store[index].display();
            else
                cout<<"Medicine not found\n";
        }

        // BUY MEDICINE (MULTIPLE + BILL IN NEW WINDOW)
        else if(choice==4){

            string cname,contact;
            cout<<"Enter Customer Name: ";
            cin>>cname;

            cout<<"Enter Contact Number: ";
            cin>>contact;

            char more='y';
            float grandTotal = 0;

            ofstream file("bill.txt");

            file<<"========== MEDICAL STORE BILL ==========\n\n";
            file<<"Customer Name : "<<cname<<endl;
            file<<"Contact       : "<<contact<<endl;

            file<<"\nMedicine Purchased\n";
            file<<"----------------------------------------\n";

            while(more=='y' || more=='Y'){

                int id, qty;
                cout<<"\nEnter Medicine ID: ";
                cin>>id;

                int index = findMedicine(store,id);

                if(index!=-1){

                    cout<<"Enter Quantity: ";
                    cin>>qty;

                    if(qty <= store[index].getQuantity()){

                        float price = store[index].getPrice();
                        float total = price * qty;

                        store[index].reduceQuantity(qty);

                        // Write to file instead of screen
                        file<<"Name       : "<<store[index].getName()<<endl;
                        file<<"Price      : "<<price<<endl;
                        file<<"Quantity   : "<<qty<<endl;
                        file<<"----------------------------------------\n";

                        grandTotal += total;
                    }
                    else{
                        cout<<"Not enough stock\n";
                    }
                }
                else{
                    cout<<"Medicine not found\n";
                }

                cout<<"Add more medicines? (y/n): ";
                cin>>more;
            }

            file<<"Total Bill : "<<grandTotal<<endl;
            file<<"========================================\n";
            file.close();

            // Open bill in new window
            system("start cmd /k type bill.txt");
        }

        if(choice!=5){
            cout<<"\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
        }

    }while(choice!=5);

    return 0;
}