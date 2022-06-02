#include <iostream>
#include "mygraphics.h"
#include <string>
#include <ctime>
#include <conio.h>
#include <fstream>
using namespace std;

// **************************************** STRUCTURE OF BOOK ****************************************//

struct node
{
	string isbn;
	int quantity;
	int price;
	string title;
	string author;
	struct node* next;
};

struct node* head=NULL;	 // start pointer -----> point first node


void login_option();
  
  
//******************************* Print Select One Option ********************************************//


void print_select_one()
{
	cout<<"\n   ";
	for(int i=0;i<65;i++){ cout<<"\xB2";}
	cout<<"\n\n\t\t\t   Select Any One Option \n\n   ";
	for(int i=0;i<65;i++){ cout<<"\xB2";}
}


//************************************ Print Valid Option ********************************************//


void print_select_valid()
{
	cout<<"\n \t\t\t";
	for(int i=0;i<30;i++){ cout<<"\xB2";}
	cout<<"\n \t\t\t  Please Select Valid Option  \n\t\t\t";
	for(int i=0;i<30;i++){ cout<<"\xB2";}
	cout<<"\n";	
	system("pause");
}


//*******************************It Will Help To print Time********************************************//


void time()
{
	time_t t = time(NULL);
    tm* tPtr = localtime(&t);

    cout << "Date: " <<(tPtr->tm_mday)<<"/"<< (tPtr->tm_mon)+1 <<"/"<< (tPtr->tm_year)+1900;
    cout << "\t\t\t\t\t Time: " << (tPtr->tm_hour)<<":"<< (tPtr->tm_min)<<":"<< (tPtr->tm_sec) << endl; 
}


//************************************ Print Header on Screem ********************************************//


void header()
{
	for(int i=0;i<72;i++){ cout<<"\xB2";}
	cout<<"\n  ";
	time();
	for(int i=0;i<72;i++){ cout<<"\xB2";}	
}


//********************************** Add New Book in Stock *************************************************//


void add_book()
{
	system("cls");
	header();

	ofstream fout;
	ifstream fin;

	node* item;
	item = new node;
	string temp_isbn;
	bool x=true;
	cout<<"\n\n\t\t\t**** ADD NEW BOOK IN STOCK ****\n\n";

	cout << "\n\n\t\t\tEnter ISBN of Book      : ";
	cin.ignore();  
    getline(cin, item->isbn);
    temp_isbn=item->isbn;
	fin.open("Book.txt",ios::in);
    
	if(!fin)
	{
		fin.open("Book.txt",ios::in);
	}

	else
	{
		int quantity,price;
		string title, author,isbn;
			while(!fin.eof())
			{	
				fin>>isbn >> quantity >> title >> author >> price;
				if (temp_isbn==isbn)
				{
	 			cout<<"\n\n\t\t\t  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
				cout<<"\n \t\t\t    BOOK ALREADY EXIST  \n";
				cout<<"\t\t\t  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
				x=false;
				getch();
				break;
				}
			}
		}	
	
	
	if(x==true)
	{	
	cout << "\t\t\tEnter Quantity in Stock : ";
	cin >> item->quantity;
	
	cout << "\t\t\tEnter Title of Book     : ";
	cin.ignore();
	getline(cin, item->title);
	
	cout << "\t\t\tEnter Book Author's Name: ";
	getline(cin, item->author);
	
	cout << "\t\t\tEnter Price of Book     : ";
    cin >> item->price;
    
	item->next = NULL;
	
	fout.open("Book.txt",ios::app);
	fout<<item->isbn<<" "<<item->quantity<<" "<<item->title<<" "<<item->author<<" "<<item->price<<"\n";
	fout.close();
	
	
	if (head == NULL) 
	{
	head = item;
	}
	else
	{
	node *temp=head;
	while (temp->next != NULL)
	{
 	temp=temp->next;
	}
	temp->next = item;
	}
	
	cout<<"\n \t\t\t";
	for(int i=0;i<30;i++){ cout<<"\xB2";}
	cout<<"\n \t\t\t    Book Added Successfully  \n\t\t\t";
	for(int i=0;i<30;i++){ cout<<"\xB2";}	
	
	getch();
	}

}


//********************************** Print Details of Searched Book ********************************************//


void print_searched(node *data)
{
	cout<<"\n********************************************************************************\n";
	cout <<"\t\t\t1 : ISBN of Book      = " <<data->isbn<<endl;
	cout <<"\t\t\t2 : Quantity in Stock = " <<data->quantity<<endl;
	cout <<"\t\t\t3 : Title of Book     = " <<data->title<<endl;
	cout <<"\t\t\t4 : Author of Book    = " <<data->author<<endl;
	cout <<"\t\t\t5 : Price of Book     = " <<data->price<<endl;
	cout<<"\n********************************************************************************\n";
	system("pause");
}


//********************************** Search any book from Stock ********************************************//


bool search_book() 
{
	system("cls");
	header();
	cout<<"\n\n\t\t   **** SEARCH BOOK FROM STOCK ****\n\n";
	int choice;

	cout << "\n\t\t\t****************************";
	cout << "\n\n\t\t\t1: SEARCH BY ISBN NO ";
	cout << "\n\t\t\t2: SEARCH BY Title ";
	cout << "\n\t\t\t3: SEARCH BY Author Name ";
	cout << "\n\t\t\t****************************";
	cout << "\n\n\t\t\tEnter Your Choice : ";
	cin >> choice ;
	
	node* data = new node;

	ifstream fin;
	fin.open("Book.txt",ios::in);
	if(!fin)
	{
		cout<<"\n \t\t\t";
		for(int i=0;i<30;i++){ cout<<"\xB2";}
		cout<<"\n \t\t\t    Error With Opening File  \n\t\t\t";
		for(int i=0;i<30;i++){ cout<<"\xB2";}
		getch();	
	}
	else
	{
		int quantity,price;
		string title,isbn, author;
		
	switch(choice)
	{
		case 1:
		{
			bool x=true;
			string searched_isbn;
			cout<<"\n\n\t\t\tEnter ISBN To Search : ";
			cin.ignore();
			getline(cin, searched_isbn);
			
			while(fin>>isbn >> quantity >> title >> author >> price)
			{		
			if (searched_isbn==isbn ) 
			{
				data->isbn=isbn;   data->quantity=quantity;  data->title=title;  data->author=author; data->price=price;
				print_searched(data);
				x=false;
				return true;
				break;
			}
			}
			if(x==true)
			{
			cout<<"\n \t\t\t";
			for(int i=0;i<30;i++){ cout<<"\xB2";}
			cout<<"\n \t\t\t     NO RECORD TO DISPLAY  \n\t\t\t";
			for(int i=0;i<30;i++){ cout<<"\xB2";}
			getch();	
			}
			break;	
		}
		
		case 2:
		{
			bool x=true;
			string searched_title;
			cout<<"\n\n\t\t\tEnter Title To Search : ";
			cin.ignore();
			getline(cin,searched_title);
			
			while(fin>>isbn >> quantity >> title >> author >> price)
			{		
			if (searched_title==title ) 
			{
				data->isbn=isbn;   data->quantity=quantity;  data->title=title;  data->author=author; data->price=price;
				print_searched(data);
				x=false;
				return true;
				break;
			}
			}
			if(x==true)
			{
			cout<<"\n \t\t\t";
			for(int i=0;i<30;i++){ cout<<"\xB2";}
			cout<<"\n \t\t\t     NO RECORD TO DISPLAY  \n\t\t\t";
			for(int i=0;i<30;i++){ cout<<"\xB2";}
			getch();
			}
			break;
		}
		
		case 3:
		{
			bool x=true;
			string searched_name;
			cout<<"\n\n\t\t\tEnter Author Name To Search : ";
			cin.ignore();
			getline(cin, searched_name);
			
			while(fin>>isbn >> quantity >> title >> author >> price)
			{		
			if (searched_name==author) 
			{
				data->isbn=isbn;   data->quantity=quantity;  data->title=title;  data->author=author; data->price=price;
				print_searched(data);
				x=false;
				return true;
				break;
			}
			}
			if(x==true)
			{
			cout<<"\n \t\t\t";
			for(int i=0;i<30;i++){ cout<<"\xB2";}
			cout<<"\n \t\t\t     NO RECORD TO DISPLAY  \n\t\t\t";
			for(int i=0;i<30;i++){ cout<<"\xB2";}
			getch();	
			}
			break;
		}
		
		default :
		{
			print_select_valid();
			search_book();			
		}
	}
	}
}

//****************************** Method to Print "Edited Successfully" *************************************//


void edited_successfully()
{
	cout<<"\n \t\t\t";
	for(int i=0;i<30;i++){ cout<<"\xB2";}
	cout<<"\n \t\t\t      Edited Successfully  \n\t\t\t";
	for(int i=0;i<30;i++){ cout<<"\xB2";}	
	cout<<"\n";
	system("pause");
}


//********************************** Update any book from Stock ********************************************//



void edit_book() 
{
	system("cls");
	header();
	cout<<"\n\n\t\t\t** EDIT BOOK DETAILS **\n\n";
	
	int quantity,price;
	string isbn,title, author;
	
	ofstream fout;
	ifstream fin;
	
	
	node* data=new node;
	bool x=0;	
	string user_isbn;
	
		x=search_book() ;
		if(x==1)
		{			
			
			cout<<"\n\n\t\t\tPlease Again Enter ISBN : ";
			cin.ignore();
			getline(cin, user_isbn);
			
			fin.open("Book.txt",ios::in);		
			fout.open("NewBook.txt",ios::out);
			
			if(!fin||!fout)
			{
				cout<<"\n \t\t\t";
				for(int i=0;i<30;i++){ cout<<"\xB2";}
				cout<<"\n \t\t\t    Error With Opening File  \n\t\t\t";
				for(int i=0;i<30;i++){ cout<<"\xB2";}
				getch();	
			}
			else
			{
			while(fin>>isbn >> quantity >> title >> author >> price)
			{
				fin>>isbn >> quantity >> title >> author >> price;		
			
				if(user_isbn!=isbn)
				{
					fout<<isbn<<" "<<quantity<<" "<<title<<" "<<author<<" "<<price<<"\n";
					fin>>isbn >> quantity >> title >> author >> price;
				}
				else if(user_isbn==isbn)
				{
					cout << "\t\t\tEnter Quantity in Stock : ";
					cin >> data->quantity;
	
					cout << "\t\t\tEnter Title of Book     : ";
					cin.ignore();
					getline(cin, data->title);
	
					cout << "\t\t\tEnter Book Author's Name: ";
					getline(cin, data->author);
	
					cout << "\t\t\tEnter Price of Book     : ";
   					cin >> data->price;	
					
					fout<<isbn<<" "<<data->quantity<<" "<<data->title<<" "<<data->author<<" "<<data->price<<"\n";		
				}
			}
		}
			fin.close();
			fout.close();
			remove("Book.txt");
			rename("NewBook.txt","Book.txt");
			edited_successfully();
		}
}


//********************************** Delete books from Stock ********************************************//


void delete_book()
{
	system("cls");
	header();
	
	ofstream fout;
	ifstream fin;
	fin.open("Book.txt",ios::in);
	    
	int quantity,price;
	string isbn,title, author;   
	
	bool x=0;
		
	if(!fin)
	{
		cout<<"\n \t\t\t";
		for(int i=0;i<30;i++){ cout<<"\xB2";}
		cout<<"\n \t\t\t    Error With Opening File  \n\t\t\t";
		for(int i=0;i<30;i++){ cout<<"\xB2";}
		getch();	
	}
	
	else 
	{
		x=search_book() ;
		if(x==1)
		{    
			string user_isbn;
			cout<<"\n\n\t\t\tPlease Again Enter ISBN : ";
			cin.ignore();
			getline(cin, user_isbn);
			
			fout.open("NewBook.txt",ios::out);
			fin>>isbn>>quantity>>title>>author>>price;	
			while(!fin.eof())
			{				
				if(user_isbn!=isbn)
				{
					fout<<isbn<<" "<<quantity<<" "<<title<<" "<<author<<" "<<"\n";	
				}
				fin>>isbn>>quantity>>title>>author>>price;
			}
			fin.close();
			fout.close();
			remove("Book.txt");
			rename("NewBook.txt","Book.txt");
	 	}
	cout<<"\n \t\t\t";
	for(int i=0;i<30;i++){ cout<<"\xB2";}
	cout<<"\n \t\t\t      Deleted Successfully  \n\t\t\t";
	for(int i=0;i<30;i++){ cout<<"\xB2";}	
	getch();

}
}


//********************************** View all books from Stock ********************************************//


void view_stock() 
{
	system("cls");
	header();
	cout<<"\n\n\t\t\t**** ALL BOOKs DETAIL ****\n\n";
	
	int quantity,price;
	string title, author ,isbn;
	
	ifstream fin;
	fin.open("Book.txt");
		if(!fin)
		{
		cout<<"\n \t\t\t";
		for(int i=0;i<30;i++){ cout<<"\xB2";}
		cout<<"\n \t\t\t    Error With Opening File  \n\t\t\t";
		for(int i=0;i<30;i++){ cout<<"\xB2";}
		getch();	
		}
		else
		{
		while (fin >> isbn >> quantity >> title >> author >> price)
		{
		cout<<"\n********************************************************************************\n";
		cout <<"\t\t\tISBN of Book :      " <<isbn<<endl;
		cout <<"\t\t\tQuantity in Stock : " <<quantity<<endl;	
		cout <<"\t\t\tTitle of Book :     " <<title<<endl;
		cout <<"\t\t\tAuthor of Book :    " <<author<<endl;
		cout <<"\t\t\tPrice of Book :     " <<price<<endl;
		}
		system("pause");
		}
		fin.close();
}


//************************************ Add Staff Details **************************************************//

string Staff_name, Staff_CNIC , Staff_DOB;
int Staff_age;

void Add_Staff_Details()
{
	system("cls");
	header();
	cout<<"\n\n\t\t\t**** ADD STAFF DETAILS ****\n\n";
	cout <<"\n\t\t\tEnter Name : ";
	cin.ignore();
	getline(cin, Staff_name);
	
	cout << "\t\t\tEnter CNIC : ";
	getline(cin,Staff_CNIC );
	
	cout << "\t\t\tEnter Age : ";
	cin >> Staff_age;
	
	cout << "\t\t\tEnter Date Of Birth : ";
    cin.ignore();
	getline(cin,Staff_DOB);
	
	ofstream fout;
	fout.open("Staff_Details.txt");
	fout<<Staff_name<<" "<<Staff_CNIC<<" "<<Staff_age<<" "<<Staff_DOB<<"\n";
	fout.close();
	
	cout<<"\n \t\t\t";
	for(int i=0;i<40;i++){ cout<<"\xB2";}
	cout<<"\n \t\t\t    Staff Details Added Successfully  \n\t\t\t";
	for(int i=0;i<40;i++){ cout<<"\xB2";}
	getch();	
}


//************************************ Print Staff Details **************************************************//


void view_Staff_Details()
{
	
	system("cls");
	header();
	cout<<"\n\n\t\t\t**** STAFF DETAIL ****\n\n";
	
	ifstream fin;
	fin.open("Staff_Details.txt");
		if(!fin)
		{
		cout<<"\n \t\t\t";
		for(int i=0;i<30;i++){ cout<<"\xB2";}
		cout<<"\n \t\t\t    Error With Opening File  \n\t\t\t";
		for(int i=0;i<30;i++){ cout<<"\xB2";}
		getch();	
		}
		else
		{
		while (fin >> Staff_name >> Staff_CNIC >> Staff_DOB >> Staff_age)
		{	
		cout<<"\n********************************************************************************\n";
		cout <<"\t\t\t1. Name  : " <<Staff_name<<endl;
		cout <<"\t\t\t2. CNIC : " <<Staff_CNIC<<endl;	
		cout <<"\t\t\t3. Date Of Birth : " <<Staff_DOB<<endl;
		cout <<"\t\t\t4. Age : " <<Staff_age<<endl;
		cout<<"\n********************************************************************************\n";
		}
}
		fin.close();
		system("pause");
}


//************************************ Generate Bill **************************************************//


void generate_bill() 
{	
	system("cls");
	header();
	cout<<"\n\n\t\t\t** GENERATE BILL **\n\n";

	int c;
	ifstream fin,fin_p,fin_ed;
	ofstream fout,fout1,fout_up;
	fout.open("print.txt",ios::app);
	fout1.open("All_Bill.txt",ios::app);
	
	time_t t = time(NULL);
    tm* tPtr = localtime(&t);

   int day=(tPtr->tm_mday),month= (tPtr->tm_mon)+1 , year=(tPtr->tm_year)+1900;
   int hour=(tPtr->tm_hour), minute=(tPtr->tm_min) , sec= (tPtr->tm_sec); 

	
	
	if (!fout||!fout1)
	{
			cout << "\n \t\t\t";
			for (int i = 0; i < 30; i++) { cout << "\xB2"; }
			cout << "\n \t\t\t    Error With Opening File  \n\t\t\t";
			for (int i = 0; i < 30; i++) { cout << "\xB2"; }
			getch();
	}
	
	do {
		int cust_quantity;
		string cust_isbn;
		cout<<"\n\t\t\tEnter ISBN : ";
		cin >> cust_isbn;
		cout<<"\n\t\t\tEnter Quantity : ";
		cin >> cust_quantity;
	
		fin.open("Book.txt", ios::in);
		if (!fin)
		{
			cout << "\n \t\t\t";
			for (int i = 0; i < 30; i++) { cout << "\xB2"; }
			cout << "\n \t\t\t    Error With Opening File  \n\t\t\t";
			for (int i = 0; i < 30; i++) { cout << "\xB2"; }
			getch();
		}
		else
		{
			int  quantity, price;
			string title, author,isbn;
			while (fin >> isbn >> quantity >> title >> author >> price)
			{
			//	fin >> isbn >> quantity >> title >> author >> price;
				if (cust_isbn == isbn)
				{
					fout <<"\n\tBook Shop Management System"<<"\nBook ISBN : "<< cust_isbn << "\nBook Title: " << title << "\nAuthor: " << author << "\nBook Quantity: "<< cust_quantity<< "\nBook Price: "
						 << price * cust_quantity <<"\n****************";

					
					fout1 << "\nBook ISBN : "<< cust_isbn << "\nBook Title" << title << "\nAuthor" << author << "\nBook Quantity"<< cust_quantity<< "\nBook Price : "
						 << price * cust_quantity <<"\n****************";

					break;
				}
			}				
		}
		
			fout_up.open("NewBook.txt",ios::out);
			
			int  quantity, price;
			string title, author,isbn;
			fin>>isbn>>quantity>>title>>author>>price;	
			while(!fin.eof())
			{				
				if(cust_isbn!=isbn)
				{
					fout<<isbn<<" "<<quantity<<" "<<title<<" "<<author<<" "<<"\n";	
				}
				else{
					fin>>isbn>>quantity>>title>>author>>price;
					int temp = quantity;
					quantity=quantity-cust_quantity;
					if(quantity<0)
					{
						cout<<"\n\t\tWe Don't Have Enough Quantity\n";
						cout<<"\t\tNumber of Book in Stock : "<<temp;
					}
					fout<<isbn<<" "<<quantity<<" "<<title<<" "<<author<<" "<<price<<"\n";
					}
			}
		
		
			fout_up.close();
			remove("Book.txt");
			rename("NewBook.txt","Book.txt");				
		
again:
		cout << "\n";
		cout << "\n\t1 : Do you wish for another product ";
		cout << "\n\t2 : Exit ";
		cout << "\n*****************************************";
		cout << "\n\t Enter Your Choice : ";
		cin >> c;
		cout << "*****************************************";
		if(c>2)
		{
			print_select_valid();
			goto again;
		}
	} while (c==1);	
			
		fout << "\nDate : "<< day << "/" << month << "/" << year << "\nTime : " << hour << ":" << minute << ":" << sec << "\n" ;
		fout1 << "\nDate : "<< day << "/" << month << "/" << year << "\nTime : " << hour << ":" << minute << ":" << sec << "\n" ;
		fin.close();
		fout.close();
		fout1.close();
		
		fin_p.open("print.txt");	
		int p_quantity,p_price,p_day, p_month, p_year,  p_hour , p_minute,p_sec;
		string p_title, p_author, p_isbn;
		
		while (fin >> p_isbn >>  p_title >> p_author >> p_quantity >> p_price >> p_day >>  p_month >> p_year >>  p_hour >> p_minute >> p_sec)
		{
		cout<<"\n****************************\n";
		cout <<"\t\t\tISBN of Book :      " <<p_isbn<<endl;
		cout <<"\t\t\tQuantity Buyed : " <<p_quantity<<endl;	
		cout <<"\t\t\tTitle of Book :     " <<p_title<<endl;
		cout <<"\t\t\tAuthor of Book :    " <<p_author<<endl;
		cout <<"\t\t\tTotal Price of Bill :     " <<p_price<<endl;
		cout <<"\t\t\tTime :    " << p_hour <<":"<<p_minute << ":" << p_sec <<endl;
		cout <<"\t\t\tDate :    " << p_day << "/" <<p_month << "/" << p_year <<endl;
		}
		system("pause");
		
	system("notepad /p print.txt");
	cout<<"\n\t\t\tPrinting Slip....";
	if (remove("print.txt") != 0)
		perror("File deletion failed");
	else
		cout << "File deleted successfully";
}



//****************************** Show All Bills ****************************************//
void All_bill() 
{
	ifstream fin;	
	fin.open("All_Bill.txt", ios::in);
	if (!fin)
		{
			cout << "\n \t\t\t";
			for (int i = 0; i < 30; i++) { cout << "\xB2"; }
			cout << "\n \t\t\t    Error With Opening File  \n\t\t\t";
			for (int i = 0; i < 30; i++) { cout << "\xB2"; }
			getch();
		}
		else
		{
		int isbn,quantity,price,day, month, year,  hour , minute,sec;
		string title, author;
		while (fin >> isbn >>  title >> author >> quantity >> price >> day >>  month >> year >>  hour >>  minute >> sec )
		{
		cout<<"\n********************************************************************************\n";
		cout <<"\t\t\tISBN of Book :      " <<isbn<<endl;
		cout <<"\t\t\tQuantity Buyed : " <<quantity<<endl;	
		cout <<"\t\t\tTitle of Book :     " <<title<<endl;
		cout <<"\t\t\tAuthor of Book :    " <<author<<endl;
		cout <<"\t\t\tTotal Price of Bill :     " <<price<<endl;
		cout <<"\t\t\tTime :    " << hour <<":"<< minute << ":" << sec <<endl;
		cout <<"\t\t\tDate :    " << day << "/" << month << "/" << year <<endl;
		}
		system("pause");
	}
	fin.close();
}

//****************************** Costumer Activity Controller Method ****************************************//


void costumer()
{
	system("cls");
	print_select_one();
	cout<<"\n\n\t1  : SEARCH BOOK "<<endl;
	cout<<"\t2  : VIEW ALL BOOK "<<endl;
	cout<<"\t3  : MAIN MENU "<<endl;	

	int choice;
	cout<<"\tEnter your choice : ";
	cin>>choice;
	
	switch(choice)
	{
		case 1:
		{	
			search_book();
			costumer();
		}
		case 2:
		{
			view_stock();
			costumer();
		}
		case 3:
		{			
			login_option();
		}
		default:
		{
			print_select_valid();
			costumer();
		}
	}

}


//********************************* Staff Activity Controller Method **************************************//


void staff()
{
	system("cls");
	print_select_one();
	cout<<"\n\n\t1  : ADD NEW BOOK \n";
	cout<<"\t2  : EDIT BOOK \n";
	cout<<"\t3  : DELETE BOOK \n";
	cout<<"\t4  : VIEW STOCK \n";
	cout<<"\t5  : SEARCH BOOK \n";
	cout<<"\t6  : GENERATE BILL \n";
	cout<<"\t7  : LOG OUT \n";
	cout<<"\t8  : SHUT DOWN \n\n";
	
	int choice;
	cout<<"\tEnter your choice : ";
	cin>>choice;
	
	switch(choice)
	{
		case 1:
		{	
			add_book();
			staff();
		}
		case 2:
		{
			edit_book();
			staff();
		}
		case 3:
		{
			delete_book();
			staff();
		}
		case 4:
		{			
			view_stock();
			staff();
		}
		case 5:
		{
			search_book();
			staff();					
		}			
		case 6:
		{
			generate_bill();
			staff();				
		}
		case 7:
		{
			login_option();		
		}
		case 8:
		{
			system("cls");
			break;						
		}
		default:
		{
			print_select_valid();
			staff();
		}
	}
}


//********************************* Admin Activity Controller Method *************************************//


void admin()
{
	system("cls");
	print_select_one();
	cout<<"\n\n\t1  : ADD NEW BOOK \n";
	cout<<"\t2  : EDIT BOOK \n";
	cout<<"\t3  : DELETE BOOK \n";
	cout<<"\t4  : VIEW STOCK \n";
	cout<<"\t5  : SEARCH BOOK \n";
	cout<<"\t6  : ADD STAFF DETAILS \n";
	cout<<"\t7  : VIEW STAFF DETAILS \n";
	cout<<"\t8  : GENERATE BILL \n";
	cout<<"\t9  : VIEW ALL BILLS \n";
	cout<<"\t10 : LOG OUT \n";
	cout<<"\t11 : SHUT DOWN \n\n";
	
	int choice;
	cout<<"\tEnter your choice : ";
	cin>>choice;
	
	switch(choice)
	{
		case 1:
		{	
			add_book();
			admin();
		}
		case 2:
		{
			edit_book();
			admin();
		}
		case 3:
		{
			delete_book();
			admin();
		}
		case 4:
		{			
			view_stock();
			admin();
		}
		case 5:
		{
			search_book();
			admin();				
		}			
		case 6:
		{	
			Add_Staff_Details();
			admin();
		}
		case 7:
		{
			view_Staff_Details();
			admin();					
		}
		case 8:
		{
			generate_bill();
			admin();					
		}
		case 9:
		{
			All_bill() ;
			admin();					
		}
		case 10:
		{
			login_option();	
			break;					
		}
		case 11:
		{
			system("cls");
			break;					
		}

		default:
		{
			print_select_valid();
			admin();		
		}
		}
}


//************************************ Admin Login  *******************************************//


void admin_staff_login()
{
	system("cls");
	header();
	cout<<"\n\n\t\t\t**** LOGIN SCREEN ****\n\n";
		
		string password="";
		string username="";
		char un,ps;
			
		cout<<" \n\t\t\tEnter Username : ";
		un=getch();
		while(un!=13)	// ASCII OF 'ENTER' KEY
		{
			cout<<un;
			username+=un;
			un=getch();
		}
			
		cout<<" \n\n\t\t\tEnter Password : ";
		ps=getch();
		while(ps!=13)	// ASCII OF 'ENTER' KEY
		{
			cout<<'*';
			password+=ps;
			ps=getch();
		}
		
		if(username=="admin"&&password=="admin"||username=="staff"&&password=="staff")
		{
			cout<<"\n\n\t\t\t   \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n";
			cout<<"\t\t\t    Access Approved  \n";
			cout<<"\t\t\t   \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n";
			Sleep(1000);
			getch();
			system("cls");
			
			if(username=="admin")
			{
				admin();
			}
			else if(username=="staff")
			{
				staff();
			}
		}
		else
		{
			gotoxy(10,10);
			cout<<"\n\n\t\t\t    \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n";
			cout<<"\t\t\t      Access Denied  \n";
			cout<<"\t\t\t    \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n";
			Sleep(1000);
			getch();
			login_option();		
		}
	
}


//*********************************** Login Option *******************************************//


void login_option()
{
	system("cls");
	print_select_one();
	cout<<"\n\n\t1: Administrator\n";
	cout<<"\n\n\t2: Staff \n\n";	
	cout<<"\n\n\t3: Customer \n\n";	
	int choice;
	cout<<"\n\tEnter Your Choice : ";
	cin>>choice;
	
	switch(choice)
	{
		case 1:
		{
			admin_staff_login();
			break;		
		}
		
		case 2:
		{
			admin_staff_login();
			break;
		}
		
		case 3:
		{
			costumer();
			break;
		}
		default:
		{
			print_select_valid();
			login_option();
		}
	}
}


//************ Manage font and Prints Details *************//

HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
void fontsize(int a, int b) {
    PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
    lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
    lpConsoleCurrentFontEx->dwFontSize.X = a;
    lpConsoleCurrentFontEx->dwFontSize.Y = b;
    SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
}


//***************Main Method*****************//


int main()
{
system("color 0b"); //text color	f //Front Method Print Details of Developers	
fontsize(25,25);
header();
    cout << "\n\t\n\t  BOOK SHOP MANAGEMENT SYSTEM ";

    cout << "\n\n\t\t  GROUP                 MEMBERS ";

    cout << "\n\n\t\t  Ali Fawad           02-134191-094";

    cout << "\n\n\t\t  Basil Aslam         02-134191-002\n\n\n\n\n\n\n";
    system ("pause");
    login_option();
}

