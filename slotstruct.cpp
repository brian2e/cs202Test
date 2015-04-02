/*
Program: project 1b (slotMachine.cpp)
Author: Brian Eddleman
Date: 2/4/2015
Revisions:
Purpose:The purpose of this program is to present the user with a menu system to select 
        between a series of options. These options will allow the user to create a three
        reel slot machine with a possible of six symbols contained in 30 stops. Also the 
        user will be able to save the slot machine, open a previous slot machine and print
        the machine to the screen. The user will also be able to selection a location on the 
        machine to print to screen. They can also play some slots and see their score.
*/
# include<iostream>
# include<fstream>
# include<stdlib.h>// it shows a compile error without the .h
# include<ctime>

using namespace std;

struct symbol
{
char name[10];
int bonus;
bool flag;
};


int randomReturn(int);// not going to change

void populateStop(symbol[][10]);

bool strComp(char [],char []);

void printToScreen(symbol pay[][10]);

void saveMachine(symbol pay[][10]);

void openMachine(symbol pay[][10]);

void gotoStop(symbol pay[][10]);

void Play(symbol pay[][10]);
/*-----------------------------------------------------------------------
   MAIN
-------------------------------------------------------------------------*/

int main()
{
// three dimensional array
symbol machine[3][10];
//used for switch
char input;
//used to tell the user to enter 1-7
char pause;

// index variables
int i, j, k, l;


//int null=0; i tried null but it said invalid conversion from int to time_t*

//seed random number
srand(time(0));
	

do
{
//Menu
cout<<"     +++++++++++++++++++++++++++++++++++++++"<<endl;
cout<<"     Welcome to the High Roller Slot Machine"<<endl;
cout<<"     +++++++++++++++++++++++++++++++++++++++"<<endl<<endl;
cout<<"         Please select an option below by"<<endl;
cout<<"         pressing the number assosiated"<<endl;
cout<<"         with the option. Option 1 or 2 to start."<<endl<<endl;
cout<<"         Option 1: Randomly generate a run."<<endl;
cout<<"         Option 2: Open a saved run."<<endl;
cout<<"         Option 3: Print the run to screen."<<endl;
cout<<"         Option 4: Save the run."<<endl;
cout<<"         Option 5: Enter stop address to view content."<<endl;
cout<<"         Option 6: Play."<<endl;
cout<<"         Option 7: Quit."<<endl<<endl;
cout<<"         ";cin>>input;cout<<endl;

switch(input)
	{
	case '1':
		// create a function that uses populateStop in a loop to fill the 30 stops.
		populateStop(machine);//confirmed to work
		cout<<"         You have successfully created a new run"<<endl<<endl;
		break;
	case '2':
		// ask the user for the name of a file to open.(function)
		openMachine(machine);// confirmed to work
	break;
	case '3':
		// print to screen. can print symbols only or symbols and bonus see funtion comments
		printToScreen(machine);// confirmed to work
		break;
	case '4':
		// function that asks the user for name of file to save.
		saveMachine(machine);//confirmed to work
		break;
	case '5':
		// goto the address of the slot machine and print symbol and bonus
		gotoStop(machine);//confirmed to work
		break;
	case '6':
		// print three stops on the same reel. As well as show score
		Play(machine);//confirmed to work
		break;
	case '7':
		// quit
		break;
	default:
		cout<<"Please enter a number between 1-7"<<endl;
		cout<<"Press any button to continue."<<endl;
		cin>>pause;
	break;
	}

}
while(input!='7');




return 0;
}
/*-----------------------------------------------------------------------
  END MAIN
-------------------------------------------------------------------------*/
//generate random number
int randomReturn(int n)
{
 int random;
 random=rand()%n+1;
 return random;
}



void populateStop(symbol pay[][10])
{//function START
ifstream fin;
int i, j,k;

int random;

for (k=0;k<3;k++)
  {
//*****1 REEL
	for( j=0;j<10;j++)
   	 {	
		random=randomReturn(6);
//******STOP istead of doing it this way easy makes sense
// istead use load into another array and then copy to the main array
		fin.open("symbols");
		 for( i=0;i<random;i++)
			{
	 	         fin>>pay[k][j].name;
		         fin>>pay[k][j].bonus;
		         if(pay[k][j].bonus==0)
		             {
		     	      pay[k][j].flag=false;
	 	    	     }
		         else
	 	             {
	  		   	pay[k][j].flag=true;
	  		     }
			}
			fin.close();
	 }
  }

}//function END



// save machine to a file
void saveMachine(symbol pay[][10])
{// change this to save only symbols
 ofstream fout;
 // index
 int i, j;
 
 char fileName[20];
  //menu
 cout<<"         Please enter the name of the file you would like to save to."<<endl; 
 cout<<"         20 characters or less: ";cin>>fileName;cout<<endl;
 
 fout.open(fileName);
 

 for(i=0;i<3;i++)
 	{
 	for(j=0;j<10;j++)
 		{
 		fout<<pay[i][j].name<<' ';
 		fout<<pay[i][j].bonus<<endl;
 		}
 	}
 
 fout.close();
}



// prints symbols or symbols and bonus values to screen
void printToScreen(symbol pay[][10])
{
// index 
 int i, j;
 
 for(j=0;j<10;j++)
 	{
 	for(i=0;i<3;i++)
 		{
 		cout<<pay[i][j].name<<' ';
 //		cout<<pay[i][j].bonus<<"   ";
 		}
 	cout<<endl;
 	}

}


// loads a previous run into the main array
void openMachine(symbol pay[][10])
{
 ifstream fin;

 int i, j, k;

 char fileName[20];

 bool marker;
 // menu and test to see if file is there
 k=0;
do
{  
 cout<<"         Please enter the name of the file you would like to open."<<endl; 
 cout<<"         20 characters or less: ";cin>>fileName;cout<<endl;
 
 fin.open(fileName);

marker=true;
if(fin.fail())
 {
  cout<<"         The file was not successfully opened"<<endl;
  cout<<"         please make the sure the file exists."<<endl<<endl;
  marker=false;
  k++;
 }
if(k==2)
	{
	cout<<"         Please make sure you know the name of the file you would"<<endl;
	cout<<"         like to open and try again."<<endl<<endl;          
	}
}
while(marker==false && k<2);

for(i=0;i<3;i++)
	{
	for(j=0;j<10;j++)
		{
		fin>>pay[i][j].name;
		fin>>pay[i][j].bonus;
		}
	}
if(marker==true)
	{
	cout<<"         The file was successfully opened."<<endl<<endl;
	}

 	
fin.close();
}


//asks to user to select reel and stop to print to screen
void gotoStop(symbol pay[][10])
{
// address on array
int reel, stop;

//index
int k, l;

bool flag=false;

//menu goes to the location the user sends it also test and makes sure the input
// is valid
 do
  {
	 cout<<"         Please enter the reel address(1-3)."<<endl;
	 cout<<"         :";cin>>reel;cout<<endl;
	 cout<<"         Please enter the stop address(1-10)."<<endl; 
	 cout<<"         :";cin>>stop;cout<<endl;
	 cout<<"         ";
	 
	 if((reel<=3 && reel>=1)&&(stop<=10 && stop>=1))
	 	{
	 	reel=reel-1;
        stop=stop-1;
        
        cout<<pay[reel][stop].name<<" ";

        if(pay[reel][stop].flag ==false)
           {
	    cout<<"there is no bonus for this symbol"<<endl<<endl;
	   }
        else
           {
            cout<<pay[reel][stop].bonus<<endl<<endl;
           }
		 	
		flag=true;
		}
		else
		{
	    cout<<"         Please enter a value (1-3) for reels and (1-10) for stops. ";		 
		}
	 cout<<endl<<endl;
  }
  while(flag==false);
}




void Play(symbol pay[][10])
{
 // index
 int i,k;
 int random;
 char score[3];
 int scoreOut;
 int scoreToPlayer=0;
 
 cout<<"         ";
 for(i=0;i<3;i++)
 {
   random=rand()%10;
   
   cout<<pay[i][random].name<<' ';
   if(pay[i][random].bonus>0)
   	{
   	scoreOut=pay[i][random].bonus;
   	scoreToPlayer=scoreToPlayer+scoreOut;
   	}
  

 }
 cout<<"         Your Score is "<<scoreToPlayer<<" thank you for playing."<<endl<<endl;
 
 if(scoreToPlayer==30)
 	{
 	cout<<"         JACK POT"<<endl;
 	cout<<"         Your Awesome...... or just lucky"<<endl<<endl;
 	
 	}
}


bool strComp(char arrayD[],char arrayS[])
{
bool marker;



return marker;
}

