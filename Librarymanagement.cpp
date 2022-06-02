#include <iostream>
#include <string>
#include<conio.h>
#include<fstream>
using namespace std;

int count=0;	// for total no of book in stock
int indBook=0;

int count_m=0;
int final_count=0;

int quant_iss_Book=0;

void Login_form();			// initialized Login_form
int retTotBook();		   //  initialized retTotBook

// **************************************** STRUCTURE OF BOOK ****************************************

struct node
{
	int isbn;
	int quantity;
	string title;
	string author;
	struct node* next;
	struct node* prev;
};

struct node* start=NULL;	 // start pointer -----> point first node
struct node* tail=NULL;		//	tail pointer  -----> point last node


// **************************************** STRUCTURE OF MEMBER ****************************************

struct node_m
{
	int code;
	string name;
	
	int isbn_iss_book;
	int validity_iss_book;
	string title_iss_book;
	string author_iss_book;
	int book_iss_quant;
	
	struct node_m* next_m;
	struct node_m* prev_m;	
};

struct node_m* start_m=NULL;	 // start pointer for member -----> point first node
struct node_m* tail_m=NULL;		//  tail pointer for member -----> point last node



// **************************************** RETURN TOTAL BOOK ****************************************

int retTotBookForADD()
{
	int countBook;
	ifstream fin;
	fin.open("TotalBook.txt",ios::in);
	fin>>countBook;
	return countBook;
}

// **************************************** RETURN TOTAL MEMBER ****************************************

int retTotMemberForADD()
{
	int countMemb;
	ifstream fin;
	fin.open("TotalMember.txt",ios::in);
	fin>>countMemb;
	return countMemb;
}


// **************************************** ADD BOOK ****************************************

void AddBook(int isbn, int quantity,  string title, string author)
{
	int readtotbook;
	ofstream fout,fout1;
	ifstream fin;
	fout.open("Book.txt",ios::app);
	
	if(!fout)
	{
		cout<<"Error With Opening File ";
	}	
	else
	{
		int quant;
		if(start==NULL)
		{
			fin.open("TotalBook.txt",ios::in);
			fin>>readtotbook;
			fout1.open("TotalBook.txt",ios::out);
			struct node* temp=new node;
			temp->isbn=isbn;
			temp->quantity=quantity;
			temp->title=title;
			temp->author=author;
			temp->next=NULL;
			temp->prev=NULL;
			start=temp;
			tail=temp;
			
			quant=temp->quantity;
			readtotbook=readtotbook+quant;	
			
			fout<<temp->isbn<<" "<<temp->quantity<<" "<<temp->title<<" "<<temp->author<<"\n";
			fout.close();
			fout1<<readtotbook;
			fout1.close();
		}
		else
		{		
			int readtotbook=retTotBookForADD();
			fout1.open("TotalBook.txt",ios::out);
			struct node* ptr=start;
			while(ptr->next!=NULL)
			{
				ptr=ptr->next;			
			}
	
			struct node*temp=new node;
			temp->isbn=isbn;
			temp->quantity=quantity;
			temp->title=title;
			temp->author=author;
			ptr->next=temp;
			temp->prev=ptr;
			temp->next=NULL;
			tail=temp;
			quant=temp->quantity;
			readtotbook=readtotbook+quant;	
			fout1<<readtotbook;
			
			fout<<temp->isbn<<" "<<temp->quantity<<" "<<temp->title<<" "<<temp->author<<"\n";
			fout.close();
			
			fout1.close();
		}
	}
}

// **************************************** TOTAL NUMBER OF RECORD OF BOOK IN FILE ****************************************

int tot_rec_book()
{
	int isbn,quantity,counter=0;
	string title,author;
	
	ifstream fin;
	fin.open("Book.txt",ios::in);
	if(!fin)
	{
		cout<<"Error With Opening File ";
	}
	else
	{
		fin>>isbn>>quantity>>title>>author;
		while(!fin.eof())
		{
			counter++;
			fin>>isbn>>quantity>>title>>author;
		}
		return counter;
	}
}


// **************************************** SORT BOOK ****************************************

void sorting()
{
	int tot_rec=tot_rec_book();
	ifstream fin;
	struct node* array[tot_rec];
	
	int isbn,quantity,i=0;
	string title,author;
	
	int t_isbn,t_quantity;
	string t_title,t_author;

	fin.open("Book.txt",ios::in);
	if(!fin)
	{
		cout<<"Error With Opening File ";
	}
	else
	{
		fin>>isbn>>quantity>>title>>author;
		while(!fin.eof())
		{	
			struct node* temp=new node;
			temp->isbn=isbn;
			temp->quantity=quantity;
			temp->title=title;
			temp->author=author;
			
			array[i]=temp;
			i++;
			fin>>isbn>>quantity>>title>>author;
		}
		int store=i;
		
		for(int i=0;i<store;i++)
		{
			for(int j=i+1;j<store;j++)
			{
				if(array[i]->isbn > array[j]->isbn)
				{
					t_isbn=array[i]->isbn;
					t_quantity=array[i]->quantity;
					t_title=array[i]->title;
					t_author=array[i]->author;
					
					array[i]->isbn=array[j]->isbn;
					array[i]->quantity=array[j]->quantity;
					array[i]->title=array[j]->title;
					array[i]->author=array[j]->author;
					
					array[j]->isbn=t_isbn;
					array[j]->quantity=t_quantity;
					array[j]->title=t_title;
					array[j]->author=t_author;
					
				}
			}
		}
		
		int readTotBook=retTotBook();
		cout<<"\n TOTAL NUMBER OF BOOKS IN STOCK : "<<readTotBook<<endl<<endl;
		
		cout<<" ==============================================================================================================="<<endl;
		cout<<"      "<<"ISBN"<<"\t\t     ";cout<<"QUANTITY"<<"\t\t     ";cout<<"   TITLE"<<"\t\t   ";cout<<"    AUTHOR"<<endl;
		cout<<" ==============================================================================================================="<<endl;	
		for(int i=0;i<store;i++)
		{
			cout<<"      "<<array[i]->isbn<<"\t\t\t"<<array[i]->quantity<<"\t\t\t"<<array[i]->title<<"\t\t\t"<<array[i]->author<<endl;
		}
	
	}
}


// **************************************** IS BOOK FOUND FOR EDIT ****************************************

bool IsBookFoundForEdit(int user_isbn)
{
	int isbn,quantity;
	string title,author;
	string user_title;	
	
	ifstream fin;
	fin.open("Book.txt",ios::in);
	if(!fin)
	{
		return false;
	}
	else
	{	
		while(!fin.eof())
		{
			fin>>isbn>>quantity>>title>>author;	
				
			if(user_isbn==isbn)
			{
				return true;
			}
		}
		fin.close();
		return false;
	}
}



// **************************************** IS BOOK FOUND FOR TOTAL BOOK ****************************************

struct node* IsBookFoundForEditTotalBook(int user_isbn)
{
	int isbn,quantity;
	string title,author;
	string user_title;	
	struct node* NotFound=NULL;
	
	ifstream fin;
	fin.open("Book.txt",ios::in);
	if(!fin)
	{
		return NotFound;
	}
	else
	{	
		while(!fin.eof())
		{
			fin>>isbn>>quantity>>title>>author;	
				
			if(user_isbn==isbn)
			{
				struct node* temp=new node;
				temp->isbn=isbn;
				temp->quantity=quantity;
				temp->title=title;
				temp->author=author;
				return temp;
			}
		}
		fin.close();
		return NotFound;
	}
}

int retTotBook()
{
	int countBook;
	ifstream fin;
	fin.open("TotalBook.txt",ios::in);
	fin>>countBook;
	return countBook;
}


// **************************************** EDIT BOOK ****************************************

void EditBook()
{
	int isbn,quantity,user_isbn,countBook,final_count,quant,temp_count;
	string title,author;
	int u_isbn,u_quantity;
	string u_title, u_author;
	
	ifstream fin;
	ofstream fout,fout1;
	fin.open("Book.txt",ios::in);
	if(!fin)
	{
		cout<<"Error With Opening File ";
		return ;
	}
	else
	{	
		cout<<"Enter Isbn Of Book To Edit : ";
		cin>>user_isbn;
		bool Isfound=IsBookFoundForEdit(user_isbn);
		struct node* check=IsBookFoundForEditTotalBook(user_isbn);
		
		if(Isfound==false)
		{
			cout<<"Book Not Found ";
			return ;
		}
		else
		{
			fout.open("NewBook.txt",ios::out);
			fin>>isbn>>quantity>>title>>author;	
			
			while(!fin.eof())
			{		
				if(user_isbn!=isbn)
				{
					fout<<isbn<<" "<<quantity<<" "<<title<<" "<<author<<"\n";
					fin>>isbn>>quantity>>title>>author;	
				}
				else
				{
					quant=check->quantity;
					temp_count=retTotBook();
					cout<<"\nEnter Isbn of Book : ";
					cin>>u_isbn;
					cout<<"Enter Quantity of Book : ";
					cin>>u_quantity;
					cout<<"Enter Title of Book : ";
					cin>>u_title;
					cout<<"Enter Author of Book : ";
					cin>>u_author;
					fout<<u_isbn<<" "<<u_quantity<<" "<<u_title<<" "<<u_author<<"\n";
					fout1.open("TotalBook.txt",ios::out);
					final_count=temp_count+(u_quantity-quant);
					fout1<<final_count;
					cout<<"\nRecord Is Updated Successfully";	
					fin>>isbn>>quantity>>title>>author;	
				}
			}			
			fin.close();
			fout.close();
			remove("Book.txt");
			rename("NewBook.txt","Book.txt");
			fout1.close();
		}
	}	
}



// **************************************** IS BOOK FOUND FOR DELETE BOOK AND TOTAL BOOK ****************************************

struct node* IsBookFoundForDeleteTotalBook(int user_isbn)
{
	int isbn,quantity;
	string title,author;
	string user_title;	
	struct node* NotFound=NULL;
	
	ifstream fin;
	fin.open("Book.txt",ios::in);
	if(!fin)
	{
		return NotFound;
	}
	else
	{	
		while(!fin.eof())
		{
			fin>>isbn>>quantity>>title>>author;	
				
			if(user_isbn==isbn)
			{
				struct node* temp=new node;
				temp->isbn=isbn;
				temp->quantity=quantity;
				temp->title=title;
				temp->author=author;
				return temp;
			}
		}
		fin.close();
		return NotFound;
	}
}

// **************************************** DELETE BOOK ****************************************

void del_indvBook_by_Isbn()
{
	int isbn,quantity,user_isbn,temp_count;
	string title,author;
	int flag=0;
	int count_;
	
	ifstream fin;
	ofstream fout,fout1;
	fin.open("Book.txt",ios::in);
	fout.open("NewBook.txt",ios::out);
	if(!fin)
	{
		cout<<"Error With Opening File ";
	}
	else
	{
		cout<<"Enter Isbn Of Book To Delete : ";
		cin>>user_isbn;
		struct node* temporary=IsBookFoundForDeleteTotalBook(user_isbn);
		if(temporary==NULL)
		{
			cout<<"Not Found ";
			return;
		}
		else
		{
			count_=temporary->quantity;
			temp_count=retTotBook();
			temp_count=temp_count-count_;
			fout1.open("TotalBook.txt",ios::out);
			fout1<<temp_count;
			fout1.close();
			
			fin>>isbn>>quantity>>title>>author;	
			while(!fin.eof())
			{				
				if(user_isbn!=isbn)
				{
					fout<<isbn<<" "<<quantity<<" "<<title<<" "<<author<<"\n";	
				}
				fin>>isbn>>quantity>>title>>author;
			}
			fin.close();
			fout.close();
			remove("Book.txt");
			rename("NewBook.txt","Book.txt");
			cout<<"RECORD DELETED\n";
		}
	}	
}

// **************************************** SEARCH BOOK BY ISBN ****************************************

void search()
{
	
	int readTotBook=retTotBook();
	cout<<"\n TOTAL NUMBER OF BOOKS IN STOCK : "<<readTotBook<<endl<<endl;
		
	int user_isbn;
	int isbn,quantity;
	string title,author;
		
	ifstream fin;
	fin.open("Book.txt",ios::in );
	if(!fin)
	{
		cout<<"Error With Opening File";
	}
	else
	{
		cout<<"Enter Isbn Of Book To Search : ";
		cin>>user_isbn;
		
		while(!fin.eof())
		{
			fin>>isbn>>quantity>>title>>author;	
				
			if(user_isbn==isbn)
			{
				cout<<" ==============================================================================================================="<<endl;
				cout<<"      "<<"ISBN"<<"\t\t     ";cout<<"QUANTITY"<<"\t\t     ";cout<<"   TITLE"<<"\t\t   ";cout<<"    AUTHOR"<<endl;
				cout<<" ==============================================================================================================="<<endl;	
					
				cout<<"      "<<isbn<<"\t\t\t"<<quantity<<"\t\t\t"<<title<<"\t\t\t"<<author<<endl;		
				return ;
			}
		}
		cout<<"Book Not Found !";
		fin.close();
	}
}

// **************************************** DISPLAY BOOK BY ISBN BEFORE SORTING ****************************************

void display_by_isbn()
{
	int isb,quan;
	string tit,aut;
	int readTotBook=retTotBook();
	cout<<"\n TOTAL NUMBER OF BOOKS IN STOCK : "<<readTotBook<<endl<<endl;	ifstream fin;
	fin.open("Book.txt",ios::in);
	
	if(!fin)
	{
		cout<<"Error With Opening File ";
	}
	else
	{
		fin>>isb>>quan>>tit>>aut;
		while(!fin.eof())
		{	
			cout<<"ISBN : "<<isb<<endl;
			cout<<"QUANTITY : "<<quan<<endl;
			cout<<"TITLE : "<<tit<<endl;
			cout<<"AUTHOR : "<<aut<<endl<<endl;
			
			fin>>isb>>quan>>tit>>aut;
		}
		fin.close();
	}	
}


// **************************************** SEARCH BOOK BY NAME ****************************************

void search_book_by_name()
{
	int readTotBook=retTotBook();
	cout<<"\n TOTAL NUMBER OF BOOKS IN STOCK : "<<readTotBook<<endl<<endl;
	
	int isbn,quantity;
	string title,author;
	string user_title;	
	ifstream fin;
	fin.open("Book.txt",ios::in);
	if(!fin)
	{
		cout<<"Error With Opening File";
	}
	else
	{
		cout<<"Enter Name Of Book To Search : ";
		cin>>user_title;
		
		while(!fin.eof())
		{
			fin>>isbn>>quantity>>title>>author;	
				
			if(user_title==title)
			{
				
				cout<<" ==============================================================================================================="<<endl;
				cout<<"      "<<"ISBN"<<"\t\t     ";cout<<"QUANTITY"<<"\t\t     ";cout<<"   TITLE"<<"\t\t   ";cout<<"    AUTHOR"<<endl;
				cout<<" ==============================================================================================================="<<endl;	
					
				cout<<"      "<<isbn<<"\t\t\t"<<quantity<<"\t\t\t"<<title<<"\t\t\t"<<author<<endl;	
				return ;
			}
		}
		cout<<"Book Not Found ";
		fin.close();
	}
}


// **************************************** ADD MEMBER ****************************************

void AddMember(int code, string name)
{
	int readtotmember;
	ofstream fout,fout1;
	ifstream fin;
	fout.open("Member.txt",ios::app);
	
	if(!fout)
	{
		cout<<"Error With Opening File ";
	}	
	else
	{
		int memquant;
		if(start==NULL)
		{
			fin.open("TotalMember.txt",ios::in);
			fin>>readtotmember;
			fout1.open("TotalMember.txt",ios::out);
			struct node_m* temp_m=new node_m;
			temp_m->code=code;
			temp_m->name=name;
			temp_m->next_m=NULL;
			temp_m->prev_m=NULL;
			start_m=temp_m;
			tail_m=temp_m;
			
			memquant++;
			readtotmember=readtotmember+memquant;	
			
			fout<<temp_m->code<<" "<<temp_m->name<<" "<<"\n";
			fout.close();
			fout1<<readtotmember;
			fout1.close();
		}
		else
		{		
			int readtotmember=retTotMemberForADD();
			fout1.open("TotalMember.txt",ios::out);
			struct node_m* ptr_m=start_m;
			while(ptr_m->next_m!=NULL)
			{
				ptr_m=ptr_m->next_m;			
			}
	
			struct node_m* temp_m=new node_m;
			temp_m->code=code;
			temp_m->name=name;
			temp_m->next_m=NULL;
			temp_m->prev_m=NULL;
			start_m=temp_m;
			tail_m=temp_m;
			
			memquant++;
			readtotmember=readtotmember+memquant;	
			
			fout<<temp_m->code<<" "<<temp_m->name<<" "<<"\n";
			fout.close();
			fout1<<readtotmember;
			fout1.close();

		}
	}
}

// **************************************** IS MEMBER FOUND FOR EDIT ****************************************

bool IsMemberFoundForEdit(int user_code)
{
	int code;
	string name;
		
	ifstream fin;
	fin.open("Member.txt",ios::in);
	if(!fin)
	{
		return false;
	}
	else
	{	
		while(!fin.eof())
		{
			fin>>code>>name;	
				
			if(user_code==code)
			{
				return true;
			}
		}
		fin.close();
		return false;
	}
}


// **************************************** EDIT MEMBER ****************************************

void edit_member()
{
	int u_code,code,user_code;
	string name,u_name;
	
	ifstream fin;
	ofstream fout;
	fin.open("Member.txt",ios::in);
	if(!fin)
	{
		cout<<"Error With Opening File ";
		return ;
	}
	else
	{	
		cout<<"Enter Code Of Member To Edit : ";
		cin>>user_code;
		bool Isfound=IsMemberFoundForEdit(user_code);
		if(Isfound==false)
		{
			cout<<"Member Not Found ";
			return ;
		}
		else
		{
			fout.open("NewMember.txt",ios::out);
			fin>>code>>name;	
			
			while(!fin.eof())
			{		
				if(user_code!=code)
				{
					fout<<code<<" "<<name<<"\n";
					fin>>code>>name;	
				}
				else
				{
					cout<<"\nEnter Code of Member : ";
					cin>>u_code;
					cout<<"Enter Name of Member : ";
					cin>>u_name;
					fout<<u_code<<" "<<u_name<<"\n";
					cout<<"\nRecord Is Updated Successfully";	
					fin>>code>>name;	
				}
			}			
			fin.close();
			fout.close();
			remove("Member.txt");
			rename("NewMember.txt","Member.txt");
		}
	}	
}

// **************************************** SEARCH MEMBER ****************************************

void search_member()
{
	int code;
	string name;
	int user_code;
	ifstream fin;
	fin.open("Member.txt",ios::in);
	if(!fin)
	{
		cout<<"Error With Opening File";
	}
	else
	{
		cout<<"Enter Code Of Member To Search : ";
		cin>>user_code;
		
		while(!fin.eof())
		{
			fin>>code>>name;	
							
			if(user_code==code)
			{
				cout<<" ================================="<<endl;
				cout<<"     "<<"CODE"<<"\t\t";cout<<"NAME "<<endl;
				cout<<" ================================="<<endl;
				cout<<"      "<<code<<"\t\t\t"<<name<<endl;
				return ;
			}
		}
		cout<<"Member Not Found";
		fin.close();
	}
}


// **************************************** DISPLAY ALL MEMBER ****************************************

void display_member()
{	
	int cod;
	string nam;

	ifstream fin;
	fin.open("Member.txt",ios::in);
	if(!fin)
	{
		cout<<"Error Wwith Opening File";
	}
	else
	{
		int readtotmember=retTotMemberForADD();
		cout<<"TOTAL NUMBER OF MEMBER : "<<readtotmember<<"\n\n";
		cout<<" ================================="<<endl;
		cout<<"     "<<"CODE"<<"\t\t";cout<<"NAME "<<endl;
		cout<<" ================================="<<endl;
		fin>>cod>>nam;		
		while(!fin.eof())
		{	
			cout<<"      "<<cod<<"\t\t\t"<<nam<<endl;
			fin>>cod>>nam;		
		}
		fin.close();
	}	
}


// **************************************** IS MEMBER FOUND OR NOT ****************************************

struct node_m* IsMemberFound(int user_code)
{
	struct node_m* temp;
	struct node_m* NoFound=NULL;
	int code;
	string name;
	ifstream fin;
	fin.open("Member.txt",ios::in );
	if(!fin)
	{
		return NoFound;
	}
	else
	{	
		fin>>code>>name;		
		while(!fin.eof())
		{				
			if(user_code==code)
			{
				cout<<"Member Found !\n\n";
				cout<<"CODE : "<<code<<endl;
				cout<<"NAME : "<<name<<endl<<endl;
				
				temp=new node_m;
				temp->code=code;
				temp->name=name;
				return temp;
			}
			fin>>code>>name;
		}
		fin.close();
		return NoFound;
	}
}


// **************************************** IS MEMBER FOUND FOR DELETE AND TOTAL MEMBER ****************************************

struct node_m* IsMemberFoundForDeleteTotalMem(int user_code)
{
	int code;
	string name;
	struct node_m* NotFound=NULL;
	
	ifstream fin;
	fin.open("Member.txt",ios::in);
	if(!fin)
	{
		return NotFound;
	}
	else
	{	
		while(!fin.eof())
		{
			fin>>code>>name;	
				
			if(user_code==code)
			{
				struct node_m* temp=new node_m;
				temp->code=code;
				temp->name=name;
				return temp;
			}
		}
		fin.close();
		return NotFound;
	}
}




// **************************************** DELETE SPECIFIC MEMBER ****************************************

void del_member()
{
	int code,user_code;
	string name;
	
	ifstream fin;
	ofstream fout,fout1;
	fin.open("Member.txt",ios::in);
	fout.open("NewMember.txt",ios::out);
	if(!fin)
	{
		cout<<"Error With Opening File ";
	}
	else
	{
		cout<<"Enter Code Of Member To Delete : ";
		cin>>user_code;
		struct node_m* ismemberfound=IsMemberFoundForDeleteTotalMem(user_code);
		if(ismemberfound==NULL)
		{
			cout<<"Not Found";
			return;
		}
		else
		{
			fin>>code>>name;	
			while(!fin.eof())
			{				
				if(user_code!=code)
				{
					fout<<code<<" "<<name<<"\n";	
				}
				fin>>code>>name;
			}
			fin.close();
			fout.close();
			remove("Member.txt");
			rename("NewMember.txt","Member.txt");
			int readtotmember=retTotMemberForADD();
			readtotmember=readtotmember-1;
			fout1.open("TotalMember.txt",ios::out);
			fout1<<readtotmember;
			fout1.close();
			cout<<"Record Deleted \n";
		}
	}	
}


// **************************************** IS BOOK FOUND OR NOT ****************************************

struct node* IsBookFound(int user_isbn)
{
	struct node* temp;
	struct node* NoFound=NULL;
	int isbn,quantity;
	string title,author;
	string user_title;	
	
	fstream fin;
	fin.open("Book.txt",ios::in);
	if(!fin)
	{
		return NoFound;
	}
	else
	{	
		while(!fin.eof())
		{
			fin>>isbn>>quantity>>title>>author;	
				
			if(user_isbn==isbn)
			{
				cout<<"Book Found !\n\n";
				cout<<"ISBN : "<<isbn<<endl;
				cout<<"QUANTITY : "<<quantity<<endl;
				cout<<"TITLE : "<<title<<endl;
				cout<<"AUTHOR : "<<author<<endl<<endl;
				
				temp=new node;
				temp->isbn=isbn;
				temp->quantity=quantity;
				temp->title=title;
				temp->author=author;
				return temp;
			}
		}
		fin.close();
		return NoFound;
	}
}


// **************************************** IS MEMBER FOUND OR NOT FOR SUBMITTED BOOK ****************************************

bool Is_Member_Found_Submitted_Book(int user_code)
{
	int code,isbn,validity;
	string name,title,author;
	ifstream fin;
	fin.open("IssueBook.txt",ios::in );
	if(!fin)
	{
		return false;
	}
	else
	{			
		while(!fin.eof())
		{		
			fin>>code>>name>>isbn>>author>>title>>validity;		
			if(user_code==code)
			{
				return true;
			}
		}
		fin.close();
		return false;
	}	
}


// **************************************** IS MEMBER ALREADY ISSUED BOOK ****************************************

struct node_m* Is_Already_Issued(int u_code)
{
	struct node_m* NotFound=NULL;
	struct node_m* temp;
	
	ifstream fin;
	int code,isbn,validity;
	string name,author,title;
	
	fin.open("IssueBook.txt",ios::in);
	if(!fin)
	{
		return NotFound;
	}
	else
	{	
		while(!fin.eof())
		{
			fin>>code>>name>>isbn>>author>>title>>validity;
				
			if(u_code==code)
			{
				temp=new node_m;
				temp->code=code;
				temp->name=name;
				temp->isbn_iss_book=isbn;
				temp->author_iss_book=author;
				temp->title_iss_book=title;
				temp->validity_iss_book=validity;
				return temp;
			}
		}
		fin.close();
		return NotFound;
	}
}


// **************************************** ISSUE BOOK ****************************************

void issueBook()
{
	int code,u_code,u_isbn,u_validity,isbn,quant,final_quant,isb,tot_count_book,quantity;
	string title,name,author,validity,tit,aut;
	bool ans;
	struct node* IsBookfound;
	struct node_m* IsMemberfound;
	
	ifstream fin1;
	ofstream fout1,fout2,fout3;
	
	cout<<"Enter Code of Member : ";
	cin>>u_code;
	cout<<"Enter Isbn of Book : ";
	cin>>u_isbn;
	cout<<"Enter Validity : ";
	cin>>u_validity;
	
	IsMemberfound=IsMemberFound(u_code);
	IsBookfound=IsBookFound(u_isbn);
	struct node_m* IsAlreadyIssued=Is_Already_Issued(u_code);
	
	if(IsMemberfound==NULL && IsBookfound==NULL)
	{
	   	cout<<"\nBOOK AND MEMBER BOTH ARE NOT FOUND!";
	  	return;
	}
	if(IsAlreadyIssued!=NULL)
	{
		cout<<"Member Already Issued a Book ";
		return ;
	}
	else
	{		
		if(IsMemberfound!=NULL)
		{
			if(IsBookfound!=NULL)
			{
				cout<<" ======================================================================================================================"<<endl;
				cout<<"      "<<"MEMBER CODE "<<"\t\t     ";cout<<"MEMBER NAME"<<"\t\t     ";cout<<"BOOK ISBN"<<"\t\t     ";cout<<"BOOK TITLE"<<endl;
				cout<<" ======================================================================================================================"<<endl;
				cout<<"\t  "<<IsMemberfound->code<<"\t\t\t       "<<IsMemberfound->name<<"\t\t\t       "<<IsBookfound->isbn<<"\t\t       "<<IsBookfound->title<<endl;
				
				fout1.open("NewBook.txt",ios::out);
				fin1.open("Book.txt",ios::in);
				fin1>>isbn>>quantity>>title>>author;	
				
				while(!fin1.eof())
				{		
					if(IsBookfound->isbn!=isbn)
					{
						fout1<<isbn<<" "<<quantity<<" "<<title<<" "<<author<<"\n";
						fin1>>isbn>>quantity>>title>>author;	
					}
					else
					{
						
						isb=IsBookfound->isbn;
						quant=IsBookfound->quantity;
						final_quant=quant=quant-1;
						
						tit=IsBookfound->title;
						aut=IsBookfound->author;
						
						IsMemberfound->isbn_iss_book=isb;
						IsMemberfound->author_iss_book=aut;
						IsMemberfound->title_iss_book=tit;
						IsMemberfound->validity_iss_book=u_validity;
						
						
						fout1<<isb<<" "<<quant<<" "<<tit<<" "<<aut<<"\n";
						fin1>>isbn>>quantity>>title>>author;	
						
						fout2.open("IssueBook.txt",ios::app);
						fout2<<IsMemberfound->code<<" "<<IsMemberfound->name<<" "<<	IsMemberfound->isbn_iss_book<<" "<<IsMemberfound->author_iss_book<<" "<<IsMemberfound->title_iss_book<<" "<<IsMemberfound->validity_iss_book<<endl;
						fout2.close();
						tot_count_book=retTotBook();
						tot_count_book=tot_count_book-1;
						fout3.open("TotalBook.txt",ios::out);
						fout3<<tot_count_book;
						fout3.close();
						cout<<"\n\nBook is issued successfully \n";
					}	
				}
				fin1.close();
				fout1.close();
				remove("Book.txt");
				rename("NewBook.txt","Book.txt");
			}
			else
			{
				cout<<"Book Not Found";
				return;
			}
		}
		else
		{
			cout<<"Member Not Found";
			return;
		}
	}	
}



// **************************************** IS MEMBER FOUND FOR SUBMITTED BOOK AND TOTAL BOOK ****************************************

struct node_m* IsMemberFoundForSubmitTotalBook(int user_code)
{
	int code,isbn,validity;
	string name,title,author;
	struct node_m* Notfound=NULL;
	
	ifstream fin;
	fin.open("IssueBook.txt",ios::in );
	if(!fin)
	{
		return Notfound;
	}
	else
	{		
		while(!fin.eof())
		{				
			fin>>code>>name>>isbn>>author>>title>>validity;	
			if(user_code==code)
			{
				struct node_m* temp=new node_m;
				temp->code=code;
				temp->name=name;
				temp->isbn_iss_book=isbn;
				temp->author_iss_book=author;
				temp->title_iss_book=title;
				temp->validity_iss_book=validity;
				return temp;
			}
		}
		fin.close();
		return Notfound;
	}	
}


// **************************************** CHECK WHICH BOOK MEMBER IS SUBMITTED ****************************************

struct node* CheckSubmitBookForQuantity(int user_isbn)
{
	int isbn,quantity;
	string title,author;
	struct node* Notfound=NULL;
	
	ifstream fin;
	fin.open("Book.txt",ios::in );
	if(!fin)
	{
		return Notfound;
	}
	else
	{		
		fin>>isbn>>quantity>>title>>author;
		while(!fin.eof())
		{					
			if(user_isbn==isbn)
			{
				struct node* temp=new node;
				temp->isbn=isbn;
				temp->quantity=quantity;
				temp->title=title;
				temp->author=author;
				return temp;
			}
			fin>>isbn>>quantity>>title>>author;
		}
		fin.close();
		return Notfound;
	}	
	
}
// **************************************** SUBMITTED BOOK ****************************************

void depositBook()
{
	struct node* ptr=start;
	struct node_m* ptr_m=start_m;
	
	int u_code,quant,t_book_file;
	int code,isbn,validity;
	string name,title,author;
	
	ofstream fout,fout1,fout2;
	ifstream fin;
	fin.open("IssueBook.txt",ios::in);
	
	if(!fin)
	{
		cout<<"Error with opening file ";
		return;
	}
	else
	{
		fout.open("temp.txt",ios::out);
		cout<<"Enter code of member to deposit a book : ";
		cin>>u_code;
		struct node_m* check=IsMemberFoundForSubmitTotalBook(u_code);
		
		struct node_m* tempor=IsMemberFoundForSubmitTotalBook(u_code);
		if(tempor==NULL)
		{
			cout<<"Member Not Found";
			return;
		}
		else
		{
			quant=tempor->book_iss_quant;
			int tot_quant=quant+1;
			fin>>code>>name>>isbn>>author>>title>>validity;
			while(!fin.eof())
			{
				if(u_code!=code)
				{
					fout<<code<<" "<<name<<" "<<isbn<<" "<<author<<" "<<title<<" "<<validity<<"\n";
					fin>>code>>name>>isbn>>author>>title>>validity;
					
				}
				fin>>code>>name>>isbn>>author>>title>>validity;
			}
			fin.close();
			fout.close();
			remove("IssueBook.txt");
			rename("temp.txt","IssueBook.txt");
			cout<<"Book Submitted";
			
			int totBook=retTotBook();
			totBook=totBook+1;
			fout2.open("TotalBook.txt",ios::out);
			fout2<<totBook;
			fout2.close();
			
			struct node* ChSubBookFQuant=CheckSubmitBookForQuantity(check->isbn_iss_book);
			if(ChSubBookFQuant!=NULL)
			{
				ofstream fout1;
				ifstream fin1;
				int isbn,quantity,quant;
				string title,author,tit,aut; 
				
				fout1.open("NewBook.txt",ios::out);
				fin1.open("Book.txt",ios::in);
				fin1>>isbn>>quantity>>title>>author;	
				
				while(!fin1.eof())
				{		
					if(ChSubBookFQuant->isbn!=isbn)
					{
						fout1<<isbn<<" "<<quantity<<" "<<title<<" "<<author<<"\n";
						fin1>>isbn>>quantity>>title>>author;	
					}
					else
					{
						int isb,quant,final_quant;
						
						isb=ChSubBookFQuant->isbn;
						quant=ChSubBookFQuant->quantity;
						final_quant=quant=quant+1;
						
						tit=ChSubBookFQuant->title;
						aut=ChSubBookFQuant->author;
						
						fout1<<isb<<" "<<quant<<" "<<tit<<" "<<aut<<"\n";
						fin1>>isbn>>quantity>>title>>author;
					}
				}
				fin1.close();
				fout1.close();
				remove("Book.txt");
				rename("NewBook.txt","Book.txt");
			}
		}
	}
}

// **************************************** DISPLAY ALL MEMBERS ISSUED BOOK ****************************************

void display_info_of_mem_issueBook()
{
	int code,isbn,validity;
	string name,author,title;

	ifstream fin;
	fin.open("IssueBook.txt",ios::in);
	if(!fin)
	{
		cout<<"Error With Opening File";
	}
	else
	{
		cout<<" ==================================================================================================================="<<endl;
		cout<<"   "<<"MEMBER CODE"<<"\t\t";cout<<"MEMBER NAME"<<"\t\t";cout<<"BOOK ISBN"<<"\t\t";cout<<"TITLE"<<"\t\t";cout<<"AUTHOR "<<"\t\t";cout<<"VALIDITY"<<endl;
		cout<<" ==================================================================================================================="<<endl;
		while(!fin.eof())
		{
			fin>>code>>name>>isbn>>author>>title>>validity;	
					
			cout<<"       "<<code<<"\t\t   "<<name<<"\t\t   "<<isbn<<"\t\t\t"<<title<<"\t\t "<<author<<"\t\t "<<validity<<endl;
				
			fin>>code>>name>>isbn>>author>>title>>validity;
		}
		fin.close();
	}	
}

// **************************************** SEARCH MEMBER ISSUED BOOK ****************************************

void search_info_of_mem_issueBook()
{
	int user_code;
	int isbn,code,validity;
	string name,title,author;
		
	ifstream fin;
	fin.open("IssueBook.txt",ios::in );
	if(!fin)
	{
		cout<<"Error With Opening File";
	}
	else
	{
		cout<<"Enter Code Of Member To Search : ";
		cin>>user_code;
		
		while(!fin.eof())
		{
			fin>>code>>name>>isbn>>author>>title>>validity;
				
			if(user_code==code)
			{
				cout<<" ==================================================================================================================="<<endl;
				cout<<"   "<<"MEMBER CODE"<<"\t\t";cout<<"MEMBER NAME"<<"\t\t";cout<<"BOOK ISBN"<<"\t\t";cout<<"TITLE"<<"\t\t";cout<<"AUTHOR "<<"\t\t";cout<<"VALIDITY"<<endl;
				cout<<" ==================================================================================================================="<<endl;	
				
				cout<<"       "<<code<<"\t\t   "<<name<<"\t\t   "<<isbn<<"\t\t\t"<<title<<"\t\t "<<author<<"\t\t "<<validity<<endl;
			
				fin>>code>>name>>isbn>>author>>title>>validity;
				return ;
			}
		}
		cout<<"Not Found !";
		fin.close();
	}
}




void option()
{
	int choose;
	bool b;
	system("color 0b");     //  for console color
	cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n";
	cout<<"<<<<<<<<<<<<<<<<<<<<<<<<   LIBRARY  >>>>>>>>>>>>>>>>>>>>>>\n";              //  \xB2  is for styling
	cout<<"<<<<<<<<<<<<<<<<<<<<<<<<   MANAGEMENT    >>>>>>>>>>>>>>>>>>>>>>\n";
	cout<<"<<<<<<<<<<<<<<<<<<<<<<<<   SYSTEM        >>>>>>>>>>>>>>>>>>>>>>\n\n \t\t\t\t\t\t\n";  // message
    cout<<"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n\n";
	cout<<"=============================== "<<endl;
	cout<<" CASE # 1   : ADD NEW BOOK "<<endl;
	cout<<" CASE # 2   : EDIT BOOK "<<endl;
	cout<<" CASE # 3   : DELETE BOOK "<<endl;
	cout<<" CASE # 4   : VIEW STOCK "<<endl;
	cout<<" CASE # 5   : SEARCH BOOK "<<endl;
	cout<<" CASE # 6   : ADD NEW MEMBER "<<endl;
	cout<<" CASE # 7   : EDIT MEMBER "<<endl;
	cout<<" CASE # 8   : VIEW ALL MEMBER "<<endl;
	cout<<" CASE # 9   : SEARCH MEMBER "<<endl;
	cout<<" CASE # 10  : DELETE MEMBER "<<endl;
	cout<<" CASE # 11  : DISPALY MEMBER ISSUED BOOK "<<endl;
	cout<<" CASE # 12  : SEARCH MEMBER ISSUED BOOK "<<endl;
	cout<<" CASE # 13  : LOG OUT "<<endl;
	cout<<" CASE # 14  : SHUT DOWN"<<endl<<endl;
	
	cout<<" Enter your choise : ";
	cin>>choose;
	if(choose>14)
	{
		cout<<endl;
		cout<<" ============================= "<<endl; 
		cout<<" WRONG INPUT. PLEASE TRY AGAIN "<<endl;
		cout<<" ============================="<<endl<<endl;
		getch();
		system("cls");
		option();
	}
	else
	{
		int isbn,quantity,code,validity;
		string title,author,name;
		
		switch(choose)
		{
			case 1:
			
			system("cls");
			
			cout<<"Enter isbn of book : ";
			cin>>isbn;
	
			cout<<"Enter quantity of book : ";
			cin>>quantity;
			cin.ignore();
	
			
			cout<<"Enter title of book (lower case) : ";
			cin>>title;
	
			cout<<"Enter name of author : ";
			cin>>author;

			AddBook(isbn, quantity, title, author);
			cout<<"\nBOOK IS ADDED SUCCESSFULLY ! "<<endl;
			
			getch();
			system("cls");
			option();
			break;
			
			case 2:
			system("cls");
			EditBook();
			getch();
			system("cls");
			option();
			break;
			
			case 3:
			system("cls");
			del_indvBook_by_Isbn();
			getch();
			system("cls");
			option();
			break;
				
			case 4:
			system("cls");
			sorting();
			getch();
			system("cls");
			option();
			break;
				
			case 5:
			int ch;
			system("cls");
			cout<<" CASE # 1   : Search By Isbn "<<endl;
			cout<<" CASE # 2   : Search By Name "<<endl<<endl;
			
			cout<<"Enter your choise : ";
			cin>>ch;
			
			switch(ch)
			{
				case 1:
				system("cls");
				search();
				getch();
				system("cls");
				option();
				break;	
				
				case 2:
				system("cls");
				search_book_by_name();
				getch();
				system("cls");
				option();
				break;	
					
			}
			
			case 6:
			system("cls");
			
			cout<<"Enter code of member : ";
			cin>>code;
			cin.ignore();
	
			cout<<"Enter name of member : ";
			cin>>name;

			AddMember(code, name);
			cout<<"\nMEMBER IS ADDED SUCCESSFULLY ! "<<endl;
			getch();
			system("cls");
			option();
			break;	
				
			case 7:
			system("cls");
			edit_member();
			getch();
			system("cls");
			option();
			
			case 8:
			system("cls");
			display_member();
			getch();
			system("cls");
			option();
			break;
			
			case 9:
			system("cls");
			search_member();
			getch();
			system("cls");
			option();
			break;
			
			case 10:
			system("cls");
			del_member();
			getch();
			system("cls");
			option();
			break;	
			
			case 11:
			system("cls");
			display_info_of_mem_issueBook();
			getch();
			system("cls");
			option();
			break;
			
			case 12:
			system("cls");
			search_info_of_mem_issueBook();
			getch();
			system("cls");
			option();
			break;
				
			case 13:
			system("cls");
			Login_form();
			break;
			
			case 14:
			system("cls");
			cout<<"PROJECT BY A.A.R.W SOLUTION : \n";
			cout<<"\nAzhan Awais\nRayyan Bin Riaz\nMuhammad Wasif\n";
			exit(1);
			break;
			
		}
	}
}

void memberForm()
{
	int c;
	cout<<" CASE # 1   : ISSUE A BOOK "<<endl;
	cout<<" CASE # 2   : DEPOSIT A BOOK "<<endl;\
	cout<<" CASE # 3   : QUIT "<<endl;
	
	cout<<"\nEnter Your Choice : ";
	cin>>c;
	
	if(c==1)
	{
		system("cls");
		issueBook();
		getch();
		system("cls");
		Login_form();
	}
	else if(c==2)
	{
		system("cls");
		depositBook();
		getch();
		system("cls");
		Login_form();
	}	
	else if(c==3)
	{
		system("cls");
		Login_form();
	}	
	else
	{
		cout<<"Invalid Input";
	}
}

void Login_form()
{
	int choose;
	system("color 1F");  
	cout<<endl;
	cout.width(75);
  	cout<<"  =========================================="<<endl;
  	cout.width(76);
	cout<< " ***Please select any 1 option from list*** "<<endl;
	cout.width(75);
  	cout<<"  =========================================="<<endl;

	cout<<endl<<endl;
	cout<< " 1) ADMINISTRATION : "<<endl;
	cout<< " 2) CUSTOMER       : "<<endl;
	cout<<endl;
	
	cout<<" Select An Option 1,2 : ";
	cin>>choose;
	
	if(choose>2)
	{
		cout<<endl;
		cout<<" ============================= "<<endl; 
		cout<<" WRONG INPUT. PLEASE TRY AGAIN "<<endl;
		cout<<" ============================="<<endl<<endl;
		getch();
		system("cls");
		Login_form();
	}
	else if(choose==1)
	{
		string pass="bahria";
		string password="";
		char ch;
	
		cout<<" \n\n Enter Password : ";
		ch=getch();
		while(ch!=13)	// ASCII OF 'ENTER' KEY
		{
			cout<<'*';
			password+=ch;
			ch=getch();
		}
		if(password==pass)
		{
			cout<<"\n Access Approved";
			getch();
			system("cls");
			option();
		}
		else
		{
			cout<<"\n Access Denied";
			getch();
		}
	}
	else if(choose==2)
	{
		system("cls");
		memberForm();
	}
}


int main()
{		
	Login_form();
	//option();
}
