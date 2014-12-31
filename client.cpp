#include <iostream>
#include <cstdio>
#define MAXLENGTH 100

#define FTP_OK 0
#define SYNTAX_ERROR -500
#define SYNTAX_ERROR_P -501
using namespace std;


void printError(int error)
{
	char* errordoc;
	int err = -error;
	if(error == SYNTAX_ERROR)
		errordoc = "Syntax error, command unrecognized.";
	else if(error == SYNTAX_ERROR_P)
		errordoc = "Syntax error in parameters or arguments.";
	cout<<"Error "<<err<<": "<<errordoc<<endl;
}

int parser(char* str, int& command, char*& targetname)
{
	if(strlen(str) > MAXLENGTH)
		return SYNTAX_ERROR;
	int paracnt = 0;
	int pos = strlen(str);
	for(int i = 0;i<strlen(str);i++)
		if(str[i] == ' ')
		{
			paracnt += 1;
			pos = i;
		}
	if(paracnt != 0 && paracnt != 1)
		return SYNTAX_ERROR_P;
	char* substr = new char[10];
	memset(substr, 0, 10);
	memcpy(substr, str, pos);
	if(strcmp(substr, "get") == 0)
	{
		if(paracnt != 1)
			return SYNTAX_ERROR_P;
		command = 1;
		targetname = str + (pos + 1);
	}
	else if(strcmp(substr, "put") == 0)
	{
		if(paracnt != 1)
			return SYNTAX_ERROR_P;
		command = 2;
		targetname = str + (pos + 1);
	}
	else if(strcmp(substr, "pwd") == 0)
	{
		if(paracnt != 0)
			return SYNTAX_ERROR_P;
		command = 3;
		targetname = NULL;
	}
	else if(strcmp(substr, "dir") == 0)
	{
		if(paracnt != 0)
			return SYNTAX_ERROR_P;
		command = 4;
		targetname = NULL;
	}
	else if(strcmp(substr, "cd") == 0)
	{
		if(paracnt != 1)
			return SYNTAX_ERROR_P;
		command = 5;
		targetname = str + (pos + 1);
	}
	else if(strcmp(substr, "help") == 0)
	{
		if(paracnt != 0)
			return SYNTAX_ERROR_P;
		command = 6;
		targetname = NULL;
	}
	else if(strcmp(substr, "quit") == 0)
	{
		if(paracnt != 0)
			return SYNTAX_ERROR_P;
		command = 7;
		targetname = NULL;
	}
	else
		return SYNTAX_ERROR;
	return FTP_OK;
}

int main()
{
	char* str = new char[100];
	memset(str, 0, 100);
	while(gets(str))
	{
		int cmd;
		char* targetname = new char[100];
		memset(targetname, 0, 100);
		int err = parser(str, cmd, targetname);
		if(err != FTP_OK)
		{
			printError(err);
			continue;
		}
		cout<<cmd<<" "<<targetname<<endl;
		memset(str, 0, 100);
	}
	return 0;
}