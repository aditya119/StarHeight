#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;

//my own stack
struct stack
{
	char data;
	stack *top, *next, *prev;
	void setNull();
	void push(char x);
	char pop();
	char topData();
	bool isEmpty();
};

void stack :: setNull()
{
	top = NULL;
}

void stack :: push(char x)
{
	stack *naya;
	naya = (stack*)malloc(sizeof(stack));
	if(!naya)
	{
		cout << "memory error\n";
		return;
	}
	naya->data = x;
	naya->next = NULL;
	if(top == NULL)
	{
		naya->prev = NULL;
	}
	else
	{
		naya->prev = top;
		top->next = naya;
	}
	top = naya;
}

char stack :: pop()
{
	if(top == NULL)
	{
		cout << "stack empty\n";
		return NULL;
	}
	stack *temp;
	temp = top;
	char t = top->data;
	if(top->prev == NULL)
	{
		top = NULL;
	}
	else
	{
		top = temp->prev;
		top->prev = temp->prev->prev;
		top->next = NULL;	
	}
	free(temp);
	return t;
}

char stack :: topData()
{
	if(top == NULL)
	{
		cout << "stack empty\n";
		return NULL;
	}
	return top->data;
}

bool stack :: isEmpty()
{
	if(top == NULL)
	{
		cout << "stack empty\n";
		return true;
	}
	return false;
}

bool checkRegEx(char* regex)
{//* - kleen's closure, + - union
	if(regex[0] == '*' || regex[0] == '+')
	{
		cout << "invalid regular expression";
		return false;
	}
	if(regex[strlen(regex)-1] == '+')
	{
		cout << "invalid regular expression";
		return false;
	}
	stack a;
	a.setNull();
	for(int i = 0; i < strlen(regex); i++)
	{
		if(regex[i] == '*')
		{
			if(regex[i+1] == '*')
			{
				cout << "invalid regular expression";
				return false;
			}
		}
		else if(regex[i] == '(')
		{
			if(regex[i+1] == '+' || regex[i+1] == '*')
			{
				cout << "invalid regular expression";
				return false;
			}
			a.push(regex[i]);
		}
		else if(regex[i] == ')')
		{
			if(regex[i-1] == '+')
			{
				cout << "invalid regular expression";
				return false;
			}
			if(a.isEmpty())
			{
				cout << "invalid regular expression";
				return false;
			}
			a.pop();
		}
	}
	if(!a.isEmpty())
	{
		cout << "invalid regular expression";
		return false;
	}
	cout << "valid regular expression\n";
	return true;
}

int getBrackets(char *regex)
{
	int noOfBrackets = 0;
	for(int i = 0; i < strlen(regex); i++)
	{
		if(regex[i] == '(')
		{
			noOfBrackets++;
		}
	}
	return noOfBrackets;
}

int getStarHeight(char *regex)
{
	int sh1 = 0, sh2 = 0, flag = 0;
	stack s;
	s.setNull();
	for(int i = 0; i < strlen(regex); i++)
	{
		if(regex[i] == '(')
		{
			s.push(regex[i]);
		}
		else if(regex[i] == '*' && flag == 0)
		{
			sh1++;
			flag = 1;
		}
		else if(regex[i] == ')')
		{
			flag = 0;
			s.pop();
		}
	}
	flag = 0;
	for(int i = strlen(regex) - 1; i >= 0; i--)
	{
		if(regex[i] == ')')
		{
			s.push(regex[i]);
		}
		else if(regex[i] == '*' && flag == 0)
		{
			sh2++;
			flag = 1;
		}
		else if(regex[i] == '(')
		{
			flag = 0;
			s.pop();
		}
	}
	int sh = 0;
	if(sh1 > sh2)
	{
		sh = sh1;
	}
	else
	{
		sh = sh2;
	}
	return sh;
}

int main()
{
	char regex[100];
	cout << "enter regular expression:\n";
	cin >> regex;
	if(checkRegEx(regex))
	{
		cout << "start height: " << getStarHeight(regex);
	}
	return 0;
}
