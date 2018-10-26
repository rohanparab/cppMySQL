#include <iostream>
#include<windows.h>
#include<mysql.h>
#include <sstream>
#include<stdio.h>

using namespace std;

bool dbconn();
void addrec();
void editrec();
void findmed();
void view();

int main()
{
    int runforever = 1;
    int ans;

    while(runforever == 1){

        cout << endl << endl << "---------------" << endl << endl << "1. Add Medicine Record" << endl << "2. Edit Medicine Record" << endl << "3. Find / Sell Medicine" << endl << "4. View inventory" << endl << "5. End" << endl << endl << endl << "---------------" << endl;

        cout << endl << "Your Answer : ";

        cin >> ans;

        switch(ans){
        case 1:
            addrec();
            break;
        case 2:
            editrec();
            break;
        case 3:
            findmed();
            break;
        case 4:
            view();
            break;
        case 5:
            runforever = 0;
            break;
        }
    }

    return 0;
}



void addrec(){
    string dummy;
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.0.111", "df4u_rohan", "rohan459", "meds", 0, NULL, 0);
    if(conn){
        int qstate = 0, quantity;
        string name, location;

        cout << "Enter name : ";
        cin >> name;

        cout << "Enter location : ";
        cin >> location;

        cout << "Enter quantity : ";
        cin >> quantity;

        stringstream ss;
        ss << "INSERT INTO inventory(name, location, quantity) VALUES('" << name << "','" << location << "'," << quantity <<")";

        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record Inserted..." << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
        cin >> dummy;
    }

    system("pause");
    system("cls");

}

void editrec(){
    string dummy;
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.0.111", "df4u_rohan", "rohan459", "meds", 0, NULL, 0);
    if(conn){
        int qstate = 0;
        string name;
        int quantity;
        cout << "Enter Name : ";
        cin >> name;
        cout << "Enter Quantity : ";
        cin >> quantity;

        stringstream ss;
        ss << "UPDATE inventory SET quantity = quantity + " << quantity << " WHERE name = '" << name << "'";

        string query = ss.str();

        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record Updated..." << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
            cin >> dummy;
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
        cin >> dummy;
    }

    system("pause");
    system("cls");

}

void findmed(){
    string dummy;
    MYSQL* conn;
    MYSQL* conn2;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.0.111", "df4u_rohan", "rohan459", "meds", 0, NULL, 0);

    conn2 = mysql_init(0);
    conn2 = mysql_real_connect(conn, "192.168.0.111", "df4u_rohan", "rohan459", "meds", 0, NULL, 0);

    if(conn){

        string name;
        int quantity;
        cout << "Enter Name : ";
        cin >> name;
        cout << "Enter Quantity : ";
        cin >> quantity;


        int qstate1 = 0;

        stringstream ss1;
        ss1 << "UPDATE inventory SET quantity = quantity - " << quantity << " WHERE name = '" << name << "'";

        string query1 = ss1.str();

        const char* q1 = query1.c_str();
        qstate1 = mysql_query(conn2, q1);
        if(qstate1 == 0){
            cout << "Record Updated..." << endl;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
        }

    }

    cout << "Press B to go back";
    cin >> dummy;

    system("pause");
    system("cls");
}

void view(){
    string dummy;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "192.168.0.111", "df4u_rohan", "rohan459", "meds", 0, NULL, 0);
    if(conn){
        int qstate = mysql_query(conn, "SELECT id, name, location, quantity FROM inventory");

        if(!qstate){
            res = mysql_store_result(conn);

            while(row = mysql_fetch_row(res)){
                cout << row[0] <<"\t | \t" << row[1] <<"\t | \t" << row[2] <<"\t | \t" << row[3] << endl << endl;
             }
        }
    }

    cout << "Press B to go back";
    cin >> dummy;

    system("pause");
    system("cls");
}
