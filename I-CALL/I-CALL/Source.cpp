#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct complaint
{
	string ID;
	string name;
	string address;
	string complains;
	string contact;
	string date;

	struct complaint* nextPtr;
};

struct status
{
	string ID;
	string name;
	string reason;
	string status;
	string action;

	struct status* nextPtr;
};

typedef struct complaint Complaint;
typedef Complaint* ComplaintsPtr;

Complaint deleted;

typedef struct status Status;
typedef Status* StatusPtr;

//Function Prototypes
void insert(ComplaintsPtr* sPtr, string ID);
bool deleteitem(ComplaintsPtr* sPtr, string ID, ComplaintsPtr* delPtr);
int isEmpty(ComplaintsPtr sPtr);
void printList(ComplaintsPtr sPtr);
void menu(void);
void update(ComplaintsPtr* sPtr, string id);
void viewsingle(ComplaintsPtr* sPtr, string id);
bool search(ComplaintsPtr* sPtr, string id);
int statusEmpty(StatusPtr headPtr);
void status(StatusPtr* headPtr, StatusPtr *tailPtr, string id);
void alldelete(ComplaintsPtr delPtr);
void allclosed(StatusPtr headPtr);

int main()
{
	ComplaintsPtr startPtr = NULL;
	ComplaintsPtr deletedPtr = NULL;
	StatusPtr headPtr = NULL;
	StatusPtr tailPtr = NULL;

	char input, cont;
	string ID;
	string name;
	string address;
	string complains;
	string contact;
	string date;
	string id;

	do
	{
		menu();
		cout << "Which option would you like to choose (1-8): " << endl;
		cin >> input;

		switch (input)
		{
		case '1':
			system("cls");
			cout << "\t---------------------------------------------" << endl;
			cout << "\t             Add Complaints" << endl;
			cout << "\t---------------------------------------------" << endl;
			if (isEmpty(startPtr))
			{
				cout << "Enter complaint ID                ";
				cin >> id;
				insert(&startPtr, id);
			}
			else
			{
				do
				{
					cout << "Enter new complaint ID            ";
					cin >> id;
					if (search(&startPtr, id))
					{
						cout << "ID already in use!, please enter a valid ID\n" << endl;
					}
				} while (search(&startPtr, id));

				if (!search(&startPtr, id))
				{
					insert(&startPtr, id);
				}	
			}
			break;
		case '2':
			system("cls");
			cout << "\t---------------------------------------------" << endl;
			cout << "\t              Remove Complaints" << endl;
			cout << "\t---------------------------------------------" << endl;
			if (!isEmpty(startPtr))
			{
				cout << "Enter ID to be Deleted" << endl;
				cin >> ID;

				if (deleteitem(&startPtr, ID, &deletedPtr))
				{	
					cout << "Complaint Successfully Deleted" << endl;
					cout << "\n" << endl;
				}
				else
				{
					cout << "\tID Not Found!" << endl;
					cout << "\n" << endl;
				}
			}
			else
			{
				cout << "\tList Is Empty!" << endl;
			}
			break;
		case '3':
			system("cls");
			cout << "\t---------------------------------------------" << endl;
			cout << "\t                Update Complaint" << endl;
			cout << "\t---------------------------------------------" << endl;
			if (!isEmpty(startPtr))
			{
				cout << "Enter ID to be updated" << endl;
				cin >> id;
				if (search(&startPtr, id))
				{
					update(&startPtr, id);
				}
				else
				{
					cout<<"ID not Found!"<<endl;
				}
			}
			else
			{
				cout << "List is Empty!" << endl;
			}
			break;
		case '4':
			system("cls");
			cout << "\t---------------------------------------------" << endl;
			cout << "\t               View Single Complaint" << endl;
			cout << "\t---------------------------------------------" << endl;
			if (!isEmpty(startPtr))
			{
				cout << "Enter ID to be viewed" << endl;
				cin >> id;
				if (search(&startPtr, id))
				{
					viewsingle(&startPtr, id);
				}
				else
				{
					cout << "ID not found!" << endl;
				}
			}
			else
			{
				cout << "List is Empty!" << endl;
			}

			break;
		case '5':
			printList(startPtr);;
			break;
		case '6':
			system("cls");
			cout << "\t-----------------------------------------------------" << endl;
			cout << "\t              Update Status to complaints" << endl;
			cout << "\t-----------------------------------------------------" << endl;
			if (!isEmpty(startPtr))
			{
				cout << "Enter Complaint ID to update Status" << endl;
				cin >> id;
				if (!search(&startPtr, id))
				{
					cout << "ID not Found!" << endl;
				}
				else
				{
					status(&headPtr, &tailPtr, id);
				}
			}
			else
			{
				cout << "List is Empty!\n" << endl;
			}
			break;
		case '7':
			allclosed(headPtr);
			break;
		case '8':
			alldelete(deletedPtr);
			break;
		default:
			cout << "Invalid Input" << endl;
			break;
		}
		cout << "\tEnter 'y' to Continue" << endl;
		cin >> cont;
	} while (cont == 'y');

	return 0;
}
void menu(void)
{

	cout << "\t=====================================================" << endl;
	cout << "\t  WELCOME TO I-CALL COMPLAINT MANAGEMENT SYSTEM" << endl;
	cout << "\t=====================================================" << endl;
	cout << "\t-----------------------------------------------------" << endl;
	cout << "\t                MENU             " << endl;
	cout << "\t-----------------------------------------------------" << endl;
	cout << "\t     1. Add complaints" << endl;
	cout << "\t-----------------------------------------------------" << endl;
	cout << "\t     2. Remove complaints" << endl;
	cout << "\t-----------------------------------------------------" << endl;
	cout << "\t     3. Update complaint" << endl;
	cout << "\t-----------------------------------------------------" << endl;
	cout << "\t     4. View Details of a single Complaint" << endl;
	cout << "\t-----------------------------------------------------" << endl;
	cout << "\t     5. View Details of all Complaints" << endl;
	cout << "\t-----------------------------------------------------" << endl;
	cout << "\t     6. Store Status of the Complaints" << endl;
	cout << "\t-----------------------------------------------------" << endl;
	cout << "\t     7. View All closed complaints in the queue" << endl;
	cout << "\t-----------------------------------------------------" << endl;
	cout << "\t     8. View Removed Complaint Data" << endl;
	cout << "\t-----------------------------------------------------" << endl;

}
void insert(ComplaintsPtr* sPtr, string ID)
{
	string name;
	string address;
	string complains;
	string contact;
	string date;
	ComplaintsPtr startPtr = NULL;

	cout << "Enter customer name:              ";
	cin.ignore();
	getline(cin, name);
	cout << "Enter address of customer:        ";
	getline(cin, address);
	cout << "Enter the complaint:              ";
	getline(cin, complains);;
	cout << "Enter contact number of customer: ";
	getline(cin, contact);
	cout << "Enter today's date:               ";
	getline(cin, date);
	cout << "\n" << endl;
	cout << "\tComplaint Added Successfully!" << endl;
	cout << "\n" << endl;
	ComplaintsPtr newPtr = NULL;
	ComplaintsPtr previousPtr = NULL;
	ComplaintsPtr currentPtr = NULL;

	newPtr = new Complaint;

	//Checking if space is available.
	if (newPtr != NULL)
	{
		//placing the individual elements in the node.
		newPtr->ID = ID;
		newPtr->name = name;
		newPtr->address = address;
		newPtr->complains = complains;
		newPtr->contact = contact;
		newPtr->date = date;
		newPtr->nextPtr = NULL;

		previousPtr = NULL;
		currentPtr = *sPtr;

		//sorting
		while (currentPtr != NULL && ID > currentPtr->ID)
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}

		if (previousPtr == NULL)
		{
			newPtr->nextPtr = *sPtr;
			*sPtr = newPtr;
		}
		else
		{
			previousPtr->nextPtr = newPtr;
			newPtr->nextPtr = currentPtr;
		}

	}
	else
	{
		cout << "\tNot inserted, No memory available!" << endl;
	}
}	
int isEmpty(ComplaintsPtr sPtr)
{
	return sPtr == NULL;
}
bool deleteitem(ComplaintsPtr* sPtr, string ID, ComplaintsPtr* delPtr)
{
	bool f=false;
	ComplaintsPtr previousPtr = NULL;
	ComplaintsPtr currentPtr = NULL;
	ComplaintsPtr tempPtr = NULL;
	string id;
	string name;
	string address;
	string complains;
	string contact;
	string date;
	ComplaintsPtr delpreviousPtr = NULL;
	ComplaintsPtr delcurrentPtr = NULL;
	ComplaintsPtr newPtr = NULL;
	newPtr = new complaint;

	if (ID == (*sPtr)->ID)
	{
		tempPtr = *sPtr;

		//Data taken into individual elements.
		id = tempPtr->ID;
		name = tempPtr->name;
		address = tempPtr->address;
		complains = tempPtr->complains;
		contact = tempPtr->contact;
		date = tempPtr->date;

		//Data being tranfered over to the secondary data structure.
		newPtr->ID = id;
		newPtr->name = name;
		newPtr->address = address;
		newPtr->complains = complains;
		newPtr->contact = contact;
		newPtr->date = date;
		newPtr->nextPtr = NULL;//This node does not link to another node (End).
		delpreviousPtr = NULL;
		delcurrentPtr = *delPtr;

		while (delcurrentPtr != NULL && id > delcurrentPtr->ID)
		{
			delpreviousPtr = delcurrentPtr;
			delcurrentPtr = delcurrentPtr->nextPtr;
		}
		if (delpreviousPtr == NULL)//It is used to enter a new node at the beginning of the list.
		{
			newPtr->nextPtr = *delPtr;
			*delPtr = newPtr;
		}
		else//else used to enter node between delprevious and delcurrent.
		{
			delpreviousPtr->nextPtr = newPtr;
			newPtr->nextPtr = delcurrentPtr;
		}
		*sPtr = (*sPtr)->nextPtr;
		delete(tempPtr);
		f = true;
	}
	else
	{
		previousPtr = *sPtr;
		currentPtr = (*sPtr)->nextPtr;

		while (currentPtr != NULL && currentPtr->ID != ID)
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}

		if (currentPtr != NULL)
		{
			tempPtr = currentPtr;
			previousPtr->nextPtr = currentPtr->nextPtr;

			//Data taken into individual elements.
			id = tempPtr->ID;
			name = tempPtr->name;
			address = tempPtr->address;
			complains = tempPtr->complains;
			contact = tempPtr->contact;
			date = tempPtr->date;

			//Data being tranfered over to the secondary data structure.
			newPtr->ID = ID;
			newPtr->name = name;
			newPtr->address = address;
			newPtr->complains = complains;
			newPtr->contact = contact;
			newPtr->date = date;
			newPtr->nextPtr = NULL;
			delpreviousPtr = NULL;
			delcurrentPtr = *delPtr;

			while (delcurrentPtr != NULL && id > delcurrentPtr->ID)
			{
				delpreviousPtr = delcurrentPtr;
				delcurrentPtr = delcurrentPtr->nextPtr;
			}
			if (delpreviousPtr == NULL)
			{
				newPtr->nextPtr = *delPtr;
				*delPtr = newPtr;
			}
			else
			{
				delpreviousPtr->nextPtr = newPtr;
				newPtr->nextPtr = delcurrentPtr;
			}

			delete(tempPtr);
			f = true;
		}
	}
	return f;
}
void printList(ComplaintsPtr sPtr)
{ 
	system("cls");
	cout << "\t-----------------------------------------------------" << endl;
	cout << "\t                 View all Complaints" << endl;
	cout << "\t-----------------------------------------------------" << endl;
	if (sPtr == NULL)
	{
		cout << "List is empty!" << endl;
	} 
	else
	{
		cout << "All the complaints are: " << endl;

		while (sPtr != NULL)
		{
			cout << "----------------------------------------------" << endl;
			cout <<"Complaint ID:                 "<< sPtr->ID << endl;
			cout <<"Customer Name:                "<< sPtr->name << endl;
			cout <<"Customer Address:             "<< sPtr->address << endl;
			cout <<"Customer complaint:           "<< sPtr->complains << endl;
			cout <<"Customer Contact:             "<< sPtr->contact << endl;
			cout <<"Date of complaint registered: "<< sPtr->date << endl;
			cout << "----------------------------------------------" << endl;
			sPtr = sPtr->nextPtr;

		}
		cout << "End of list" << endl;
	}
}
void update(ComplaintsPtr* sPtr, string id)
{
	ComplaintsPtr previousPtr = NULL;
	ComplaintsPtr currentPtr = NULL;

	if (id == (*sPtr)->ID)
	{
		cout << "Enter updated Address" << endl;
		cin.ignore();
		getline(cin, (*sPtr)->address);
		cout << "Enter updated contact number" << endl;
		getline(cin, (*sPtr)->contact);
		cout << "\n" << endl;
		cout << "Complaint Updated Successfully" << endl;
	}
	else
	{
		previousPtr = *sPtr;
		currentPtr = (*sPtr)->nextPtr;

		while (currentPtr->ID != id)
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}
		cout << "Enter updated address" << endl;
		cin.ignore();
		getline(cin, (currentPtr)->address);
		cout << "Enter updated contact number" << endl;
		getline(cin, (currentPtr)->contact);
		cout << "\n"<<endl;
		cout << "Complaint Updated Successfully" << endl;
	}
}
void viewsingle(ComplaintsPtr* sPtr, string id)
{
	ComplaintsPtr previousPtr = NULL;
	ComplaintsPtr currentPtr = NULL;

	if (id == (*sPtr)->ID)
	{
		cout <<"Complaint ID                      "<< (*sPtr)->ID << endl;
		cout <<"Customer Name                     "<< (*sPtr)->name << endl;
		cout <<"Customer Address                  "<< (*sPtr)->address << endl;
		cout <<"Complaint                         "<< (*sPtr)->complains << endl;
		cout <<"Customer Contact                  "<< (*sPtr)->contact << endl;
		cout <<"Date of complaint registered      "<< (*sPtr)->date << endl;

	}
	else
	{
		previousPtr = *sPtr;
		currentPtr = (*sPtr)->nextPtr;

		while (currentPtr->ID != id)
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}
		cout << "Complaint ID                      " << (currentPtr)->ID << endl;
		cout << "Customer Name                     " << (currentPtr)->name << endl;
		cout << "Customer Address                  " << (currentPtr)->address << endl;
		cout << "Complaint                         " << (currentPtr)->complains << endl;
		cout << "Customer Contact                  " << (currentPtr)->contact << endl;
		cout << "Date of complaint registered      " << (currentPtr)->date << endl;
	}

}
bool search(ComplaintsPtr *sPtr, string id)
{
	bool found = false;
	ComplaintsPtr previousPtr = NULL;
	ComplaintsPtr currentPtr = NULL;

	if ((*sPtr)->ID==id)
	{
		found = true;
	}
	else
	{
		previousPtr = *sPtr;
		currentPtr = (*sPtr)->nextPtr;

		//Loop to find the correct location.
		while (currentPtr != NULL && currentPtr->ID != id)
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPtr;
		}
		if (currentPtr != NULL)
		{
			found = true;
		}

	}
	return found;
}
void alldelete(ComplaintsPtr delPtr)
{
	system("cls");
	cout << "\t-----------------------------------------------------" << endl;
	cout << "\t              View all Deleted Complaints" << endl;
	cout << "\t-----------------------------------------------------" << endl;
	if (delPtr == NULL)
	{
		cout << "List is empty!" << endl;
	}
	else
	{
		cout << "All the deleted complaints are: " << endl;

		while (delPtr != NULL)
		{
			cout << "----------------------------------------------" << endl;
			cout << "Complaint ID:                 " << delPtr->ID << endl;
			cout << "Customer Name:                " << delPtr->name << endl;
			cout << "Customer Address:             " << delPtr->address << endl;
			cout << "Customer complaint:           " << delPtr->complains << endl;
			cout << "Customer Contact:             " << delPtr->contact << endl;
			cout << "Date of complaint registered: " << delPtr->date << endl;
			cout << "----------------------------------------------" << endl;
			delPtr = delPtr->nextPtr;

		}
		cout << "End of list" << endl;
	}
}
int statusEmpty(StatusPtr headPtr)
{
	return headPtr == NULL;
}
void status(StatusPtr* headPtr, StatusPtr* tailPtr, string id)
{
	StatusPtr newPtr;
	newPtr = new Status;
	char choice;

	if (newPtr != NULL)
	{
		newPtr->ID = id;
		cout << "Enter name of Customer:" << endl;
		cin.ignore();
		getline(cin, newPtr->name);
		cout << "Enter the reason:" << endl;
		getline(cin, newPtr->reason);
		cout << "Enter the Action taken:" << endl;
		getline(cin, newPtr->action);
		cout << "\tSelect the Status Below:" << endl;
		cout << "\t1.Closed" << endl;
		cout << "\t2.Open" << endl;
		cout << "\t3.Cannot Address" << endl;
		cin >> choice;

		switch (choice)
		{
		case '1':
			newPtr->status = "Closed";
			cout << "Complaint status updated" << endl;
			break;
		case '2':
			newPtr->status = "Open";
			cout << "Complaint status updated" << endl;
			break;
		case '3':
			newPtr->status = "Cannot Address";
			cout << "Complaint status updated" << endl;
			break;
		default:
			cout << "Invalid input!" << endl;
			break;
		}
		newPtr->nextPtr = NULL;
		if (statusEmpty(*headPtr))
		{
			*headPtr = newPtr;
		}
		else
		{
			(*tailPtr)->nextPtr = newPtr;
		}
		*tailPtr = newPtr;
	}

}
void allclosed(StatusPtr headPtr)
{
	system("cls");
	cout << "\t-----------------------------------------------------" << endl;
	cout << "\t              View all closed complaints" << endl;
	cout << "\t-----------------------------------------------------" << endl;
	if (headPtr == NULL)
	{
		cout << "queue is Empty!\n" << endl;
	}
	else
	{
		cout << "All closed complaints are" << endl;

		while (headPtr != NULL)
		{
			cout << "Complaint ID:       " << headPtr->ID << endl;
			cout << "Reason:             " << headPtr->reason << endl;
			cout << "Action Taken:       " << headPtr->action << endl;
			cout << "Status:             " << headPtr->status << endl;
			cout << "-----------------------------------------------------\n" << endl;
			headPtr = headPtr->nextPtr;
		}
		cout << "End of List\n" << endl;
	}
}