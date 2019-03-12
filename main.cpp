#include<iostream>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<Mysql.h>
#include<stdlib.h>
#include<sstream>
#include<MMSystem.h>
#include<string>
#include<cstdlib>
#include<wininet.h>
#include<ctime>
#pragma comment(lib, "Wininet")
using namespace std;

COORD coord;
MYSQL* con;
MYSQL_ROW row;
MYSQL_RES* res;
int cnt = 0;

float convertBalanceFlaot( char*);
string convertBalanceString(float);
bool sendSms(string, string, string);

class Account
{
    string actNo, actPin;
public:
    void mainMenu();
    void subMenu();
    void note();
    void otherServices();
    Account loginCheck();
    void help();
    bool checkAccount(Account);
    void cashDeposit(Account);
    void cashWithdraw(Account);
    void fundTransfer(Account);
    void pinChange(Account);
    void fastCash(Account);
    void balanceInquiry(Account);
    void miniStatement(Account);
    void instantAmount(Account);
    void askAgain(Account);
};

float convertBalanceFlaot(char* strBalance)
{
    float bal;
    bal = strtof(strBalance, NULL);
    return bal;
}
string convertBalanceString(float finalBal)
{
    string strFinalBal;
	std::stringstream ss;
	ss << finalBal;
	ss >> strFinalBal;
	return strFinalBal;
}
class date		//class current date and time of system
{
	public:
		int aday,amonth,ayear,ahour,amin,asec;
	void date_times()
	{
		SYSTEMTIME t;		//pre defined in time.h header
 		GetLocalTime(&t);
		aday=t.wDay,amonth=t.wMonth,ayear=t.wYear,ahour=t.wHour,amin=t.wMinute,asec=t.wSecond;

	}
};
char *date_time()
{
	time_t t;
	time(&t);
	char *loc=ctime(&t);
	return loc;	//returns local time and date
}
void gotoxy(int x, int y)	//defining/initializing to predefined objects
{

    coord.X = x;
    coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void frame()
{
	int i,j=99;
	for(i = 0;i<100,j>=0;i++,j--)
	{
		gotoxy(i,3);
		Sleep(10);
		cout<<"_";
		gotoxy(j,25);
		Sleep(10);
		cout<<"_";
	}
	gotoxy(76,2);
	char s[20];
	strcpy(s,date_time());
	cout<<s;		//every frame has date on the right top
}
void frameFix()
{
	int i,j=99;
	for(i = 0;i<100,j>=0;i++,j--)
	{
		gotoxy(i,3);
		//Sleep(10);
		cout<<"_";
		gotoxy(j,25);
		//Sleep(10);
		cout<<"_";
	}
	gotoxy(76,2);
	char s[20];
	strcpy(s,date_time());
	cout<<s;		//every frame has date on the right top
}
void play(int a)
{
	if(a==1)
	PlaySound(TEXT("pin.wav"),NULL,SND_SYNC);
	if(a==2)
    PlaySound(TEXT("welcome.wav"),NULL,SND_ASYNC);
    if(a==3)
    PlaySound(TEXT("thankyou.wav"),NULL,SND_SYNC);
    if(a==4)
    PlaySound(TEXT("validate.wav"),NULL,SND_SYNC);
	if(a==5)
    PlaySound(TEXT("transaction.wav"),NULL,SND_SYNC);
    if(a==6)
    PlaySound(TEXT("invalid.wav"),NULL,SND_SYNC);
    if(a==7)
    PlaySound(TEXT("collect.wav"),NULL,SND_ASYNC);
    if(a==8)
    PlaySound(TEXT("invalidpin.wav"),NULL,SND_SYNC);
    if(a==9)
    PlaySound(TEXT("actnotmatch.wav"),NULL,SND_SYNC);
    if(a==10)
    PlaySound(TEXT("changepin.wav"),NULL,SND_SYNC);

}

void wellComePage()
{
    system("color FC");
    gotoxy(35,14);cout<<"ATM SERVICES";
	gotoxy(46,14);cout<<" WELCOMES YOU ";
    play(2);
	for(int j=99,i=0;j>=0,i<=99;j--,i++)
	{
		gotoxy(j,25);cout<<"|";
		gotoxy(i,4);cout<<"|";
		Sleep(30);
    }
	gotoxy(83,27);cout<<"Margi 7874062672";
	gotoxy(83,28);cout<<"Mayur 8155881015";
	Sleep(1000);//
}
void flow(char *ch)	//flow of instructions
{
	char *str=ch;
	for(int i=0;i<strlen(str);i++)
	{
		Sleep(100);
		cout<<str[i];
	}
}

bool sendSms(string mobno,string  name, string otp) //send sms to register no. using HTTP
{
    //set Result to the content of the stream

        // Mayur's SMS Gateway's host and Port
        string host       = "192.168.43.1";
        int port          = 9800;
        // Username
        // and password.
        string username   = "";
        string password   = "G1htPWxc";
        // Message
        string message    = "Hello ";
        message += name;
        message += ". Your OTP is - ";
        message += otp;
        // Originator's phone number.
        string originator = "+91";
        // Recipient(s) phone number.
        //        If You want to send message to multiple recipients, separate them with coma.
        // (don't use space character!) Ex: "+002222222,+003333333,+004444444"
        string recipient  = "+91";
        recipient += mobno;
        string val="/sendsms?password=G1htPWxc&originator=+918155881015&recipient=" + recipient + "&messagedata=" + message;
        // Preparing the HTTPRequest url
        stringstream url;
                url <<val;
        // Create socket.
        HINTERNET inet = InternetOpen("Ozeki", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
        // Open connection and bind it to the socket.
        HINTERNET conn = InternetConnect(inet, host.c_str() , port, NULL, NULL,
        INTERNET_SERVICE_HTTP, 0, 0);
        // Open the HTTP request
        HINTERNET sess = HttpOpenRequest(conn, "GET", url.str().c_str(), "HTTP/1.1",
        NULL, NULL, INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 0);
        // Check errors
        int error = GetLastError();
        if(error == NO_ERROR)
        {
                // Send HTTP request.
                HttpSendRequest(sess, NULL, 0, NULL,0);
                // Receive HTTP response.
                int size = 1024;
                char *buffer = new char[size + 1];
                DWORD read;
                int rsize = InternetReadFile(sess, (void *)buffer, size, &read);
                string s = buffer;
                s = s.substr(0, read);
                // Check statuscode
                int pos = s.find("<statuscode>0</statuscode>");
                // If statuscode is 0, write "Message sent." to output else write "Error."
                if(pos > 0){
                   return true;
                }
                else
                {
                    return false;
                }
        }
}

void Account::note()	//final !!!
{
    system("cls");
	system("color F0");
	gotoxy(32,14);
	cout<<"THANK YOU FOR VISITING OUR ATM SYSTEM";
	play(3);
	for(int j=35;j<65;j++)
	{
		gotoxy(j, 15);
		cout<<"-";
		Sleep(30);
    }
    Sleep(10000);
	mainMenu();
}

void Account::otherServices() //instruction...
{
    system("cls");
	system("COLOR 70");
	for(int i=3;i<28;i++)
	{
		gotoxy(12,i);
		cout<<"|";
		gotoxy(87,i);
		cout<<"|";
	}

	gotoxy(43,1);
	cout<<"POINTS TO NOTE";
	gotoxy(13,4);
	flow("Ensure that you change the PIN number after first using your card also");
	gotoxy(13,5);
	flow("frequently change PIN number");
	gotoxy(13,7);
    flow("Ensure that nobody else can see you entering your PIN number at the ATM.");
	gotoxy(13,9);
	flow("Do not use the ATM machine when strangers are inside the ATM counter.");
	gotoxy(13,11);
	flow("Do not seek the assistance of strangers while operating the ATM machine.");
	gotoxy(13,13);
	flow("Should you notice anything strange or suspicious at the ATM counter please");
	gotoxy(13,14);
	flow("refrain from using the same.");
	gotoxy(13,16);
	flow("Ensure that you check your account statement from time to time.");
	gotoxy(13,18);
	flow("In case you lose your ATM card call 1800-425-3800 to block your card and ");
	gotoxy(13,19);
	flow("this avoid miss use of the card.");
	gotoxy(13,21);
	flow("Do not disclose your PIN number to others IBO/RBI or any other Government,");
	gotoxy(13,22);
	flow("Banking institutions will never require you to disclose your PIN number.");
	gotoxy(13,24);
	cout<<"--------------------------------------------------------------------------";
	gotoxy(43,24);
	flow(" THANK YOU ");
	Sleep(5000);
    mainMenu();
}
void Account::help()
{
	system("cls");
	system("COLOR 70");
    for(int i=3;i<28;i++)
	{
		gotoxy(12,i);
		cout<<"|";
		gotoxy(87,i);
		cout<<"|";
	}
	gotoxy(13,4);
	cout<<"Inorder to use our ATM services be sure that,";
	gotoxy(13,6);
	cout<<"you might have already opened an account previously. ";

	gotoxy(13,24);
	cout<<"For more information, contact:";
	gotoxy(13,25);
	cout<<"Call our 24x7 helpline through toll free 1800 100 2400.";
	gotoxy(13,26);
	cout<<"Contact at margimayur@gmail.com";

	gotoxy(13,8);
	flow("ATM Services");
	gotoxy(13,11);
	flow("Cash Withdrawal : Use this service to withdraw amount (15,000/-per day).");
	gotoxy(13,13);
	flow("Fast Cash : This enables to withdraw your preferred amounts with a touch.");
	gotoxy(13,15);
	flow("Pin Change : Use this service to change your ATM password.");
	gotoxy(13,17);
	flow("Balance Enquiry : To check the current balance in your account.");
	gotoxy(13,19);
	flow("Ministatement : Keep track of the transactions in your account.");
	gotoxy(13,21);
	flow("Fund Transfer : Transfers amount instantly to your loved ones.");
	getch();
	mainMenu();
}

void Account::mainMenu()	//main menu for all functions included
{
    //wellComePage();
    //Sleep(900);
	system("cls");
	system("COLOR 2F");
	frame();
	gotoxy(30,14);
	cout<<"IF YOU HAVE ACCOUNT PRESS P TO PROCEED ";
	gotoxy(94,24);
	cout<<"HELP";
	gotoxy(1,24);
	cout<<"INSTRUCTION";
	char op;
	gotoxy(1,26);
	cout<<" H : Help P : Proceed to account E : Exit I:Instruction";
	gotoxy(48,21);
	cin>>op;
	if(op=='h'||op=='H')
	{
		cout<<"h";
        help();
	}
	else if(op=='p'||op=='P')
	{
        subMenu();
	}
	else if(op=='i'||op=='I')
	{
		otherServices();
	}
	else if(op=='e'||op=='E')
	{
		system("cls");
		note();
	}
	else
	{
	    gotoxy(41,22);
		cout<<" \a\a\aINVALID OPTION ";
		Sleep(1000);
		mainMenu();
	}
}
void Account::subMenu()	//after user login the following functions are displayed
{
	system("cls");
    Account act;
    act = loginCheck();
	int cpin;

		while(1)
		{
			int i;
			system("cls");
			system("COLOR 1F");
			frame();
			gotoxy(1,8);
			cout<<"1.CASH WITHDRAWL";
			gotoxy(1,12);
			cout<<"3.FUND TRANSFER";
			gotoxy(1,16);
			cout<<"5.BALANCE ENQUIRY";
			gotoxy(1,20);
			cout<<"7.INSTANT CASH";

			gotoxy(82,8);
			cout<<"2.CASH DEPOSITE";
			gotoxy(82,12);
			cout<<"4.PIN CHANGE";
			gotoxy(82,16);
			cout<<"6.FAST CASH";
			gotoxy(82,20);
			cout<<"8.MINI STATEMENT";

			gotoxy(37,5);
			char *s ="Select your transaction";
			for(int i=0;i<24;i++)
			{
				cout<<s[i];
				Sleep(100);
			}

			int op;
			gotoxy(48,24);
			cout<<" ";
			cin>>op;
			switch(op)
			{
				case 1:
					{
						cashWithdraw(act);
						break;
					}
				case 2:
					{
					    cashDeposit(act);
						break;
					}
				case 3:
					{
						fundTransfer(act);
						break;
					}
				case 4:
					{
						pinChange(act);
						break;
					}
				case 5:
					{
                        balanceInquiry(act);
						break;
					}
				case 6:
					{
						fastCash(act);
						break;
					}
				case 7:
					{
						instantAmount(act);
						break;
					}
				case 8:
					{
						miniStatement(act);
						break;
					}
				default:
					{
						gotoxy(64,24);
						cout<<"Invalid Input ";
						play(6);
						cout<<"\a\a\a";		//terminating to mainmenu
						Sleep(1000);
						mainMenu();
					}
			}
		}
}
Account Account::loginCheck() //match account no and pin, return account object
{
    Account act;
    char x,y,ans,chPin;
    string aPin;
    system("cls");
	system("COLOR 1F");
	frame();
	gotoxy(3,6);
	cout<<"enter any number";
	gotoxy(3,8);
	cout<<"between 10 and 99";
	gotoxy(3,10);
	cout<<"for eg. 25 ";
	gotoxy(3,13);
	cout<<"Press y if the";
	gotoxy(3,15);
	cout<<"number is displayed";
	gotoxy(3,18);
	cout<<"Press n if the";
	gotoxy(3,20);
	cout<<"number is not displayed";
	gotoxy(45,23);
	x = getche();
	gotoxy(46,23);
	y = getche();
	gotoxy(49,23);
	ans = getche();
    if(ans=='y'||ans=='Y')
	{
        float factNo;
        string aNo;
        con=mysql_init(0);
        /*if(con)//if succeed
            cout<<"connection object ok"<<endl;
        else
            cout<<"conn object problem"<<mysql_error(con)<<endl;*/
        con=mysql_real_connect(con,"localhost","root","","atmdb",0,NULL,0);
        if(con)//if succeed
        {
            //cout<<"connection is Open!!"<<endl;
            system("cls");
            gotoxy(32,12);
            //frameFix();
            cout<<" PLEASE ENTER YOUR ACCOUNT NUMBER ";
            gotoxy(45,14);
            cin>>aNo;
            act.actNo=aNo;
            string query = "select * from user where act_no='" + act.actNo +"'";
            const char* sq=query.c_str();
            cnt=mysql_query(con,sq);
            if(!cnt) //id insert succeed
            {
                res=mysql_store_result(con);
                row=mysql_fetch_row(res);
                if(row!=NULL)
                {
                    system("cls");
                    frameFix();
                    gotoxy(1,2);
                    cout<<"CITY BANK OF KALUPUR";
                    gotoxy(35,5);
                    cout<<"PLEASE ENTER YOUR PIN";
                    gotoxy(2,13);
                    cout<<"HELLO - "<<row[2];
                    gotoxy(2,15);
                    cout<<"YOUR PIN IS CONFIDENTIAL";
                    gotoxy(2,17);
                    cout<<"NOBODY SHOULD SEE THE PIN";
                    gotoxy(2,19);
                    cout<<"WHILE YOU ARE ENTERING IT.";
                    gotoxy(2,21);
                    cout<<"MAKE YOUR PIN MORE SECURE BY";
                    gotoxy(2,23);
                    cout<<"CHANGING IT FREQUENTLY.";
                    gotoxy(44,7);
                    chPin = _getch();
                    for(int i=0; i<4; i++)
                    {
                        aPin.push_back(chPin);
                        cout<<"X";
                        play(1);
                        chPin = _getch();
                    }
                    //cout<<aPin;
                    act.actPin=aPin;
                    string query = "select pin_no from user where act_no='"+ act.actNo +"'";
                    const char* q=query.c_str();
                    cnt=mysql_query(con,q);
                    res=mysql_store_result(con);
                    row=mysql_fetch_row(res);
                    //cout<<actPin;
                    //Sleep(100);
                    if(row[0]==act.actPin)
                    {
                        return act;
                    }
                    else
                    {
                        system("cls");
                        gotoxy(42,13);
                        cout<<"INVALID PIN!!!";
                        play(8);
                        Sleep(1000);
                        mainMenu();
                    }
                }
                else
                {
                system("cls");
                gotoxy(36,13);
                cout<<"ACCOUNT NUMBER NOT MATCH!!!";
                play(9);
                Sleep(1000);
                mainMenu();
                }
            }
        }
	}
	else{
        mainMenu();
	}
}
bool Account::checkAccount(Account act) // check account type
{
    int acttype;
    string type;
    system("cls");
	frameFix();
	system("color 1F");
	gotoxy(35,6);
	flow("SELECT YOUR ACCOUNT TYPE ");
    gotoxy(38,10);
    cout<<"1.Current Account";
    gotoxy(38,13);
    cout<<"2.Savings Account";
    gotoxy(45,17);
	cin>>acttype;
    con=mysql_init(0);
    con=mysql_real_connect(con,"localhost","root","","atmdb",0,NULL,0);
    if(con)//if succeed
    {
        switch(acttype)
        {
        case 1:
                type="Current";
                break;
        case 2:
                type="Saving";
                break;
        }
        string query="select act_type from user where act_no='"+ act.actNo +"' and act_type='"+ type + "'";
        const char* q=query.c_str();
        cnt=mysql_query(con,q);
        if(!cnt) //id insert succeed
        {
            res=mysql_store_result(con);
            row=mysql_fetch_row(res);
            if(row != NULL)
            {
                cout<<"TRUE";
                return true;
            }
            else
            {
                cout<<"FALSE";
                return false;
            }
        }
    }
    else{
        cout<<"Not Connected!!";
    }
}
void Account::cashDeposit(Account act)	//argument object received from login_check function
{
    string type;
    bool chk = checkAccount(act);
    if(chk == true)
    {
        float cash;
        float finalBalance;
        float beforeBalance;
        con=mysql_init(0);
        /*if(con)//if succeed
            cout<<"connection object ok"<<endl;
        else
            cout<<"conn object problem"<<mysql_error(con)<<endl;*/
        con=mysql_real_connect(con,"localhost","root","","atmdb",0,NULL,0);
        if(con)//if succeed
        {
            //cout<<"connection is Open!!"<<endl;
            system("cls");
            int cash;
            frameFix();
            system("color 1F");
            gotoxy(35,6);
            cout<<"PLEASE ENTER AMOUNT : ";
            cin>>cash;
                if(cash%100 == 0)
                {
                string squery = "select * from user where act_no='"+ act.actNo +"'";
                const char *sq = squery.c_str();
                cnt=mysql_query(con,sq);
                if(!cnt)
                {
                    res=mysql_store_result(con);
                    row=mysql_fetch_row(res);
                    beforeBalance = convertBalanceFlaot( row[4]);
                    finalBalance = beforeBalance + cash;
                    string query="update user set balance='" + convertBalanceString(finalBalance) +"' where act_no='"+act.actNo+"'";
                    if(!cnt)
                    {
                        const char* q=query.c_str();
                        cnt=mysql_query(con,q);
                        string tquery = "insert into transection(act_no,trac_amt,final_balance,type) values('"+ act.actNo +"','"+ convertBalanceString(cash)+"','"+ convertBalanceString(finalBalance)+"','DEPOSITE')";
                        const char* tq=tquery.c_str();
                        mysql_query(con,tq);
                        string squery = "select * from user where act_no='"+ act.actNo +"'";
                        const char *sq = squery.c_str();
                        cnt=mysql_query(con,sq);
                        if(!cnt)
                        {
                            res=mysql_store_result(con);
                            system("cls");
                            frameFix();
                            gotoxy(25,12);
                            row=mysql_fetch_row(res);
                            cout<<"AMOUNT DEPOSITED  : "<<cash<<" FINAL BALANCE : "<<finalBalance;
                            Sleep(3000);
                        }
                        else
                        {
                            cout<<"no recored found";
                        }
                    }
                    else
                    {
                        cout<<"not saving";
                    }
                    system("cls");
                    gotoxy(35,13);
                    cout<<"PLEASE WAIT VALIDATING THE CASH";
                    play(4);
                    Sleep(1000);
                    system("cls");
                    gotoxy(33,13);
                    cout<<"TRANSACTION COMPLETED SUCCESSFULLY";
                    play(5);
                    Sleep(1000);
                    askAgain(act);
                }
            }
            else{
               system("cls");
                gotoxy(35,13);
                cout<<"PLEASE ENTER AMOUNT IN X100";
                Sleep(1000);
                subMenu();
            }
        }
    }
    else if(chk==false)
    {
        system("cls");
        gotoxy(36,13);
        cout<<"ACCOUNT TYPE NOT MATHCH!!";
        Sleep(1000);
        mainMenu();
    }
}
void Account::cashWithdraw(Account act)
{
    bool chk = checkAccount(act);
    if(chk == true)
    {
        int cash;
        float finalBalance;
        float beforeBalance;
        con=mysql_init(0);
        /*if(con)//if succeed
            cout<<"connection object ok"<<endl;
        else
            cout<<"conn object problem"<<mysql_error(con)<<endl;*/
        con=mysql_real_connect(con,"localhost","root","","atmdb",0,NULL,0);
        if(con)//if succeed
        {
            //cout<<"connection is Open!!"<<endl;
            system("cls");
            system("color 1F");
            int cash;
            frameFix();
            gotoxy(35,6);
            cout<<"PLEASE ENTER AMOUNT : ";
            cin>>cash;
            if(cash <= 15000){
                if(cash%100 == 0)
                {
                    string squery = "select * from user where act_no='"+ act.actNo +"'";
                    const char *sq = squery.c_str();
                    cnt=mysql_query(con,sq);
                    if(!cnt)
                    {
                        res=mysql_store_result(con);
                        row=mysql_fetch_row(res);
                        beforeBalance = convertBalanceFlaot( row[4]);
                        if(beforeBalance > cash)
                        {
                            finalBalance = beforeBalance - cash;
                            string query="update user set balance='" + convertBalanceString(finalBalance) +"'where act_no='"+ act.actNo +"'";
                            const char* q=query.c_str();
                            cnt=mysql_query(con,q);
                            if(!cnt)
                            {
                                string tquery = "insert into transection(act_no,trac_amt,final_balance,type) values('"+ act.actNo +"','"+ convertBalanceString(cash)+"','"+ convertBalanceString(finalBalance)+"','WITHDRAWAL')";
                                const char* tq=tquery.c_str();
                                mysql_query(con,tq);

                                string squery = "select * from user where act_no='"+ act.actNo +"'";
                                const char *sq = squery.c_str();
                                cnt=mysql_query(con,sq);
                                if(!cnt) //id insert succeed
                                {
                                    res=mysql_store_result(con);
                                    system("cls");
                                    frameFix();
                                    gotoxy(25,12);
                                    row=mysql_fetch_row(res);
                                    cout<<"AMOUNT WITHDRAWAL  : "<<cash<<" FINAL BALANCE : "<<finalBalance;
                                    Sleep(3000);
                                }
                                else
                                {
                                    cout<<"no recored found";
                                }
                            }
                            else
                            {
                                cout<<"not saving";
                            }
                        }
                        else{
                            system("cls");
                            gotoxy(40,13);
                            cout<<"INSUFFICIENT FUNDS";
                            Sleep(1000);
                            subMenu();
                        }
                        system("cls");
                        gotoxy(35,13);
                        cout<<"PLEASE WAIT VALIDATING THE CASH";
                        play(4);
                        Sleep(1000);
                        system("cls");
                        gotoxy(33,13);
                        cout<<"TRANSACTION COMPLETED SUCCESSFULLY";
                        play(5);
                        Sleep(500);
                        gotoxy(40,16);
                        cout<<"PLEASE COLLECT CASH";
                        play(7);
                        Sleep(1000);
                        askAgain(act);
                    }
                }
                else{
                    system("cls");
                    gotoxy(35,13);
                    cout<<"PLEASE ENTER AMOUNT IN X100";
                    Sleep(1000);
                    subMenu();
                }
            }
            else{
                system("cls");
                gotoxy(35,13);
                cout<<"Withdrawal limit is 15000";
                Sleep(1000);
                subMenu();
            }
        }
    }
    else{
        system("cls");
        gotoxy(36,13);
        cout<<"ACCOUNT TYPE NOT MATHCH!!";
        Sleep(1000);
        mainMenu();
    }
}
void Account::fundTransfer(Account act)
{
    string ractNo, ractNo1;
    int cash;
    float finalBalance,finalBalancer;
    float beforeBalance,beforeBalancer;
    con=mysql_init(0);
    con=mysql_real_connect(con,"localhost","root","","atmdb",0,NULL,0);
    if(con)//if succeed
    {
        cout<<"connection is Open!!"<<endl;
        system("cls");
        system("color 1F");
        frameFix();
        gotoxy(24,8);
        cout<<"ENTER RECEPIENT'S ACCOUNT NUMBER : ";
        cin>>ractNo;
        gotoxy(24,11);
        cout<<"CONFIRM ACCOUNT NUMBER           : ";
        cin>>ractNo1;
        gotoxy(24,14);
        if(ractNo == ractNo1)
        {
            cout<<"PLEASE ENTER AMOUNT              : ";
            cin>>cash;
            string squery = "select * from user where act_no='"+ractNo1+"'";
            const char *sq = squery.c_str();
            cnt=mysql_query(con,sq);
            if(!cnt)
            {
                res=mysql_store_result(con);
                row=mysql_fetch_row(res);
                if(row==NULL)
                {
                    system("cls");
                    system("color 1F");
                    gotoxy(35,8);
                    cout<<"ACCOUNT NUMBER NOT EXITS!!";
                    Sleep(1000);
                    subMenu();
                }
                else if(row[0] == ractNo1)
                {
                    beforeBalancer = convertBalanceFlaot(row[4]);
                    if(cash % 100 == 0)
                    {
                        string squery = "select * from user where act_no='"+ act.actNo +"'";
                        const char *sq = squery.c_str();
                        cnt=mysql_query(con,sq);
                        if(!cnt) //id insert succeed
                        {
                            res=mysql_store_result(con);
                            row=mysql_fetch_row(res);
                            beforeBalance = convertBalanceFlaot(row[4]);
                            if(beforeBalance > cash)
                            {
                                finalBalance = beforeBalance - cash;
                                string query="update user set balance='" + convertBalanceString(finalBalance) +"' where act_no='"+act.actNo+"'";
                                const char* q=query.c_str();
                                cnt=mysql_query(con,q);
                                if(!cnt)
                                {
                                    finalBalancer = beforeBalancer + cash;
                                    string rquery="update user set balance='" + convertBalanceString(finalBalancer) +"'where act_no='"+ ractNo1 +"'";
                                    const char* rq=rquery.c_str();
                                    cnt=mysql_query(con,rq);
                                    if(!cnt)
                                    {
                                        string tquery = "insert into transection(act_no,trac_amt,final_balance,type) values('"+ act.actNo +"','"+ convertBalanceString(cash)+"','"+ convertBalanceString(finalBalance)+"','TRANSFER')";
                                        const char* tq=tquery.c_str();
                                        mysql_query(con,tq);
                                        system("cls");
                                        frameFix();
                                        gotoxy(25,12);
                                        cout<<"AMOUNT TRANSFER  : "<<cash<<" FINAL BALANCE : "<<finalBalance;
                                        Sleep(3000);
                                        system("cls");
                                        gotoxy(35,13);
                                        cout<<"PLEASE WAIT VALIDATING THE CASH";
                                        play(4);
                                        Sleep(1000);
                                        system("cls");
                                        gotoxy(33,13);
                                        cout<<"TRANSACTION COMPLETED SUCCESSFULLY";
                                        play(5);
                                        Sleep(500);
                                        askAgain(act);
                                    }
                                }
                            }
                            else{
                                system("cls");
                                gotoxy(40,13);
                                cout<<"INSUFFICIENT FUNDS";
                                Sleep(1000);
                                subMenu();
                            }
                        }
                    }
                    else{
                        system("cls");
                        gotoxy(35,13);
                        cout<<"PLEASE ENTER AMOUNT IN X100";
                        Sleep(1000);
                        subMenu();
                    }
                }

            }
        }
        else{
            system("cls");
            system("color 1F");
            gotoxy(35,8);
            cout<<"ACCOUNT NUMBER NOT MATCH!!";
            Sleep(1000);
            subMenu();
        }
    }
}
void Account::pinChange(Account act)
{
    con=mysql_init(0);
    con=mysql_real_connect(con,"localhost","root","","atmdb",0,NULL,0);
    if(con)//if succeed
    {
        system("cls");
        frameFix();
        system("color 1F");
        float newPin1,newPin2;
        gotoxy(37,12);
        cout<<"PLEASE ENTER YOUR NEW PIN";
        //play(1);
        gotoxy(47,15);
        cin>>newPin1;
        system("cls");
        frameFix();
        system("color 1F");
        gotoxy(35,12);
        cout<<"PLEASE RE-ENTER YOUR NEW PIN";
        //play(1);
        gotoxy(45,15);
        cin>>newPin2;

        if(newPin1 == newPin2)
        {
            string query="update user set pin_no='"+ convertBalanceString(newPin1) + "' where act_no='"+ act.actNo +"'";
            const char* q=query.c_str();
            cnt=mysql_query(con,q);

            system("cls");
            gotoxy(28,13);
            cout<<"PLEASE WAIT YOUR TRANSACTION IS BEING PROCESSED";
            gotoxy(45,15);
            cout<<"PLEASE WAIT";
            Sleep(2000);
            system("cls");
            gotoxy(33,13);
            cout<<"YOUR PIN HAS BEING CHANGE SUCCESSFULLY";
            play(10);
            Sleep(1000);
            askAgain(act);
        }
        else
        {
            system("cls");
            gotoxy(35,13);
            cout<<"PIN DOES NOT MATCH!!";
            Sleep(1000);
        }
    }
}
void Account::fastCash(Account act)
{
    int choice;
    float amt=0;
    system("color 1F");
    system("cls");
	frameFix();
	gotoxy(34,5);
	flow("SELECT YOUR TRANSACTION AMOUNT");
	gotoxy(15,8);
	cout<<"1. 100";
	gotoxy(15,11);
	cout<<"3. 200";
	gotoxy(15,14);
	cout<<"5. 500";
	gotoxy(15,17);
	cout<<"7. 1000";
	gotoxy(77,8);
	cout<<"2. 2000";
	gotoxy(77,11);
	cout<<"4. 3000";
	gotoxy(77,14);
	cout<<"6. 5000 ";
	gotoxy(77,17);
	cout<<"8. 10000 ";
	gotoxy(50,22);
	cout<<"";
	cin>>choice;
    switch(choice)
    {
    case 1:
        amt = 100;
        break;
    case 2:
        amt = 2000;
        break;
    case 3:
        amt = 200;
        break;
    case 4:
        amt = 3000;
        break;
    case 5:
        amt = 500;
        break;
    case 6:
        amt = 5000;
        break;
    case 7:
        amt = 1000;
        break;
    case 8:
        amt = 10000;
        break;
    default:
        system("cls");
        gotoxy(40,13);
        cout<<"INVALID OPTION";
        Sleep(1000);
        subMenu();
    }
    if(amt != 0)
    {
    float finalBalance;
    float beforeBalance;
    con=mysql_init(0);
    /*if(con)//if succeed
        cout<<"connection object ok"<<endl;
    else
        cout<<"conn object problem"<<mysql_error(con)<<endl;*/
    con=mysql_real_connect(con,"localhost","root","","atmdb",0,NULL,0);
    if(con)//if succeed
    {
        //cout<<"connection is Open!!"<<endl;
        system("cls");
        system("color 1F");
        string squery = "select * from user where act_no='"+ act.actNo +"'";
        const char *sq = squery.c_str();
        cnt=mysql_query(con,sq);
        if(!cnt) //id insert succeed
        {
            res=mysql_store_result(con);
            row=mysql_fetch_row(res);
            beforeBalance = convertBalanceFlaot( row[4]);
            if(beforeBalance > amt && amt!=0)
            {
                finalBalance = beforeBalance - amt;
            }
            else{
                system("cls");
                gotoxy(40,13);
                cout<<"INSUFFICIENT FUNDS";
                Sleep(1000);
                subMenu();
            }
            string query="update user set balance='" + convertBalanceString(finalBalance) +"'where act_no='"+ act.actNo +"'";
            const char* q=query.c_str();
            cnt=mysql_query(con,q);
            if(!cnt) //if insert is succeed
            {
                string tquery = "insert into transection(act_no,trac_amt,final_balance,type) values('"+ act.actNo +"','"+ convertBalanceString(amt)+"','"+ convertBalanceString(finalBalance)+"','FAST CASH')";
                const char* tq=tquery.c_str();
                mysql_query(con,tq);

                string squery = "select * from user where act_no='"+ act.actNo +"'";
                const char *sq = squery.c_str();
                cnt=mysql_query(con,sq);
                if(!cnt) //id insert succeed
                {
                    res=mysql_store_result(con);
                    system("cls");
                    frameFix();
                    gotoxy(25,12);
                    row=mysql_fetch_row(res);
                    cout<<"AMOUNT WITHDRAWAL  : "<<amt<<" FINAL BALANCE : "<<finalBalance;
                    Sleep(3000);
                    system("cls");
                    gotoxy(35,13);
                    cout<<"PLEASE WAIT VALIDATING THE CASH";
                    play(4);
                    Sleep(1000);
                    system("cls");
                    gotoxy(33,13);
                    cout<<"TRANSACTION COMPLETED SUCCESSFULLY";
                    play(5);
                    Sleep(500);
                    gotoxy(40,16);
                    cout<<"PLEASE COLLECT CASH";
                    play(7);
                    Sleep(1000);
                    askAgain(act);
                }
                else
                {
                    cout<<"no recored found";
                }
            }
            else
            {
                cout<<"not saving";
            }
        }
    }}
}
void Account::balanceInquiry(Account act)
{
    string type;
    bool chk = checkAccount(act);
    if(chk == true)
    {
        con=mysql_init(0);
        /*if(con)//if succeed
            cout<<"connection object ok"<<endl;
        else
            cout<<"conn object problem"<<mysql_error(con)<<endl;*/
        con=mysql_real_connect(con,"localhost","root","","atmdb",0,NULL,0);
        if(con)//if succeed
        {
            string squery = "select * from user where act_no='"+ act.actNo +"'";
            const char *sq = squery.c_str();
            cnt=mysql_query(con,sq);
            if(!cnt)
            {
                res=mysql_store_result(con);
                row=mysql_fetch_row(res);
                system("cls");
                system("color 1F");
                frameFix();
                gotoxy(32,10);
                cout<<"ACCOUNT HOLDER NAME  : "<<row[2];
                gotoxy(32,13);
                cout<<"CURRENT BALANCE      : "<<row[4];
                Sleep(3000);
                system("cls");
                gotoxy(27,13);
                cout<<"YOUR TRANSACTION IS BEING PROCESSED PLEASE WAIT";
                Sleep(1000);
                system("cls");
                gotoxy(33,13);
                cout<<"TRANSACTION COMPLETED SUCCESSFULLY";
                play(5);
                Sleep(500);
                askAgain(act);
            }
        }
    }
    else if(chk==false)
    {
        system("cls");
        gotoxy(36,13);
        cout<<"ACCOUNT TYPE NOT MATHCH!!";
        Sleep(1000);
        mainMenu();
    }
}
void Account::miniStatement(Account act)
{
	string type;
    bool chk = checkAccount(act);
    if(chk == true)
    {
        system("cls");
        system("COLOR 1F");
        for(int i=2;i<28;i++)
        {
            gotoxy(12,i);
            cout<<"|";
            gotoxy(87,i);
            cout<<"|";
        }

        gotoxy(16,2);
        cout<<"DATE TIME";
        gotoxy(38,2);
        cout<<"TRANSACTION TYPE";
        gotoxy(60,2);
        cout<<"AMOUNT";
        gotoxy(70,2);
        cout<<"FINAL BALANCE";
        gotoxy(13,3);
        for(int i=13;i<86;i++)
        {
            cout<<"-";
            Sleep(20);
        }

        con=mysql_init(0);
        /*if(con)//if succeed
            cout<<"connection object ok"<<endl;
        else
            cout<<"conn object problem"<<mysql_error(con)<<endl;*/
        con=mysql_real_connect(con,"localhost","root","","atmdb",0,NULL,0);
            cout<<"-";
        if(con)//if succeed
        {
            //string squery="SELCT * from transection where act_no='"+ act.actNo + "'order by (datetime1) asc";
            string squery = "SELECT * FROM (SELECT * FROM transection where act_no='"+ act.actNo +"' ORDER BY datetime1 DESC  LIMIT 5)sub ORDER BY datetime1 desc";
            //string squery = "SELECT * FROM transection where act_no='"+ act.actNo +"'";
            //string squery = "select * from transection where act_no='"+ act.actNo +"' order by(datetime1) asc";
            const char *sq = squery.c_str();
            cnt=mysql_query(con,sq);
            if(!cnt)
            {
                res=mysql_store_result(con);
//                row=mysql_fetch_row(res);
                int i=5;
                if(row!=NULL)
                {
                    while((row=mysql_fetch_row(res))!=NULL)
                    {
                        gotoxy(16,i);
                        cout<<row[0];
                        gotoxy(42,i);
                        cout<<row[1];
                        gotoxy(61,i);
                        cout<<row[3];
                        gotoxy(75,i);
                        cout<<row[4];
                        i=i+2;
                   }
                }
                else{
                    gotoxy(40,5);
                    cout<<"...NO TRANSACTION...";
                }
            }
        }
        Sleep(15000);
        system("cls");
        gotoxy(27,13);
        cout<<"YOUR TRANSACTION IS BEING PROCESSED PLEASE WAIT";
        Sleep(1000);
        system("cls");
        gotoxy(33,13);
        cout<<"TRANSACTION COMPLETED SUCCESSFULLY";
        play(5);
        Sleep(500);
        askAgain(act);
    }
    else if(chk==false)
    {
        system("cls");
        gotoxy(36,13);
        cout<<"ACCOUNT TYPE NOT MATHCH!!";
        Sleep(1000);
        mainMenu();
    }
}
void Account::instantAmount(Account act)
{
    bool chk = checkAccount(act);
    if(chk == true)
    {
        int cash;
        int userOTP;
        float finalBalance;
        float beforeBalance;
        con=mysql_init(0);
        /*if(con)//if succeed
            cout<<"connection object ok"<<endl;
        else
            cout<<"conn object problem"<<mysql_error(con)<<endl;*/
        con=mysql_real_connect(con,"localhost","root","","atmdb",0,NULL,0);
        if(con)
        {
            system("cls");
            system("color 1F");
            int cash, otp;
            frameFix();
            gotoxy(35,6);
            cout<<"PLEASE ENTER AMOUNT : ";
            cin>>cash;
            if(cash <= 15000){
                if(cash%100 == 0)
                {
                    string squery = "select * from user where act_no='"+ act.actNo +"'";
                    const char *sq = squery.c_str();
                    cnt=mysql_query(con,sq);
                    if(!cnt)
                    {
                        res=mysql_store_result(con);
                        row=mysql_fetch_row(res);
                        beforeBalance = convertBalanceFlaot( row[4]);
                        if(beforeBalance > cash)
                        {
                            srand(time(NULL));
                            int otp = rand() % 9000 + 1000;
                            string Result;
                            stringstream convert;
                            convert << otp;
                            Result = convert.str();
                            bool i;
                            i = sendSms(row[3], row[2], Result);
                            if(i==true)
                            {
                                system("cls");
                                system("color 1F");
                                frameFix();
                                gotoxy(25,6);
                                cout<<"PLEASE ENTER OTP(One Time password) : ";
                                cin>>userOTP;
                                if(otp==userOTP)
                                {
                                    finalBalance = beforeBalance - cash;
                                    string query="update user set balance='" + convertBalanceString(finalBalance) +"'where act_no='"+ act.actNo +"'";
                                    const char* q=query.c_str();
                                    cnt=mysql_query(con,q);
                                    if(!cnt)
                                    {
                                        string tquery = "insert into transection(act_no,trac_amt,final_balance,type) values('"+ act.actNo +"','"+ convertBalanceString(cash)+"','"+ convertBalanceString(finalBalance)+"','INSTANT')";
                                        const char* tq=tquery.c_str();
                                        mysql_query(con,tq);

                                        string squery = "select * from user where act_no='"+ act.actNo +"'";
                                        const char *sq = squery.c_str();
                                        cnt=mysql_query(con,sq);
                                        if(!cnt)
                                        {
                                            res=mysql_store_result(con);
                                            system("cls");
                                            frameFix();
                                            gotoxy(25,12);
                                            row=mysql_fetch_row(res);
                                            cout<<"AMOUNT WITHDRAWAL  : "<<cash<<" FINAL BALANCE : "<<finalBalance;
                                            Sleep(3000);
                                        }
                                        else
                                        {
                                            cout<<"no recored found";
                                        }
                                    }
                                    else
                                    {
                                        cout<<"not saving";
                                    }
                                }
                                else{
                                    system("cls");
                                    gotoxy(40,13);
                                    cout<<"OTP NOT MATCH!!";
                                    Sleep(1000);
                                    subMenu();
                                }
                            }
                            else{
                                Sleep(1000);
                                system("cls");
                                gotoxy(32,13);
                                cout<<"SORRY, OTP WILL NOT BE SEND DUE TO SOME REASON.";
                            }
                        }
                        else{
                            system("cls");
                            gotoxy(40,13);
                            cout<<"INSUFFICIENT FUNDS";
                            Sleep(1000);
                            subMenu();
                        }
                        system("cls");
                        gotoxy(35,13);
                        cout<<"PLEASE WAIT VALIDATING THE CASH";
                        play(4);
                        Sleep(1000);
                        system("cls");
                        gotoxy(33,13);
                        cout<<"TRANSACTION COMPLETED SUCCESSFULLY";
                        play(5);
                        Sleep(500);
                        gotoxy(40,16);
                        cout<<"PLEASE COLLECT CASH";
                        play(7);
                        Sleep(1000);
                        askAgain(act);
                    }
                }
                else{
                    system("cls");
                    gotoxy(35,13);
                    cout<<"PLEASE ENTER AMOUNT IN X100";
                    Sleep(1000);
                    subMenu();
                }
            }
            else{
                system("cls");
                gotoxy(35,13);
                cout<<"Withdrawal limit is 15000";
                Sleep(1000);
                subMenu();
            }
        }
    }
    else{
        system("cls");
        gotoxy(36,13);
        cout<<"ACCOUNT TYPE NOT MATHCH!!";
        Sleep(1000);
        mainMenu();
    }
}
void Account::askAgain(Account act) //asked for more transaction
{
    system("cls");
    system("color 1F");
    char ans;
	frameFix();
	gotoxy(28,6);
	cout<<"YOU WANT TO DO MORE TRANSACTION?(Y/N)";
	gotoxy(43,8);
	cin>>ans;
	if(ans == 'y' || ans=='Y')
        subMenu();
    else
       note();
 }
int main()
{
    wellComePage();
    Account act;
    act.mainMenu();
    //frameFix();
    //wellComePage();
    //frame();
    //subMenu();
    //act.help();
    //note();
    //otherServices();
    //loginCheck();
    //cashDeposit();
    //checkAccount();
    //cashWithdraw();
    //fundTransfer();
    //pinChange();
    //fastCash();
    //balanceInquiry();
    //miniStatement();
    //instantAmount();
    //askAgain();
    return 0;
}
