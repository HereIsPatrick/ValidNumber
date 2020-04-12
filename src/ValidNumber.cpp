//============================================================================
// Name        : ValidNumber.cpp
// Author      : PatrickChiu
//============================================================================

#include <iostream>
#include <cassert>
#include <cctype>
using namespace std;

#define S0 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define S7 7
#define S8 8
#define S9 9

class Solution {
private:
	int _currentState;

    bool isOtherASCII(char c)
    {
    	if(c>='a' && c<='z')
    	{
    		if(c!='e')
    			return true; // other ascii
    		else
    			return false;
    	}

    	if(c=='+')
    		return true; // other ascii
    	else
    		return false;
    }

    bool isDecimalNumber(char c)
    {
    	if(c>='0' && c<='9')
    		return true;
    	else
    		return false;
    }

    bool isNegative( char c)
    {
    	if(c=='-')
    		return true;
    	else
    		return false;
    }

    bool isPositive( char c)
    {
    	if(c=='+')
    		return true;
    	else
    		return false;
    }

    bool isDecimalPoint(char c)
    {
    	if(c=='.')
    		return true;
    	else
    		return false;
    }

    bool isExponent(char c)
    {
    	if(c=='e')
    		return true;
    	else
    		return false;
    }

public:
    Solution(){
    	_currentState=S0;
    }
    bool isNumber(string s) {

    	// Step. remove space
    	s.erase(remove(s.begin(),s.end(),' '),s.end());


    	// Step. convert to char*
    	char str[64];
    	strcpy(str, s.c_str());

    	for(int i=0; i<strlen(str); i++)
    	{
    		stateMachine(str[i]);
    	}
		cout << "_currentState : " << _currentState << endl;
    	if( _currentState == S3 || _currentState == S6 || _currentState == S9)
    	{
    		// Step. reset state machine.
    		_currentState = S0;
    		return true;
    	}
    	else
    	{
    		// Step. reset state machine.
    		_currentState = S0;
    		return false;
    	}

    }

    void stateMachine(char c)
    {
    	if( _currentState == S0 )
    	{
    		if(isDecimalNumber(c))
    		{
    			_currentState=S3;
    		}
    		else if( isNegative(c) )
    		{
    			_currentState=S1;
    		}
    		else if( isOtherASCII(c) || isExponent(c) )
    		{
    			_currentState=S2;
    		}
    	}
    	else if( _currentState == S1 )
    	{
    		if( isPositive(c) || isNegative(c) )
    		{
    			_currentState=S2;
    		}
    		else if(isDecimalNumber(c) )
    		{
    			_currentState=S3;
    		}
    	}
    	else if( _currentState == S3 )
    	{
    		if( isExponent(c))
    		{
    			_currentState=S4;
    		}
    		else if(isDecimalNumber(c) )
    		{
    			_currentState=S3;
    		}
    		else if(isDecimalPoint(c) )
    		{
    			_currentState=S8;
    		}
    		else if(isOtherASCII(c) )
    		{
    			_currentState=S2;
    		}
    	}
    	else if( _currentState == S4 )
    	{
    		if( isNegative(c))
    		{
    			_currentState=S5;
    		}
    		else if(isDecimalNumber(c) )
    		{
    			_currentState=S6;
    		}
    	}
    	else if( _currentState == S5 )
    	{
    		if(isDecimalNumber(c) )
    		{
    			_currentState=S6;
    		}
    	}
    	else if( _currentState == S6 )
    	{
    		if( isDecimalPoint(c))
    		{
    			_currentState=S7;
    		}
    		else if(isDecimalNumber(c) )
    		{
    			_currentState=S6;
    		}
    	}
    	else if( _currentState == S8 )
    	{
    		if(isDecimalNumber(c) )
    		{
    			_currentState=S9;
    		}
    	}
    	else if( _currentState == S9 )
    	{
    		if(isDecimalNumber(c) )
    		{
    			_currentState=S9;
    		}
    	}
    }
};

int main() {

	Solution s;
	assert(s.isNumber(string("0"))==true);
	assert(s.isNumber(string(" 0.1 "))==true);
	assert(s.isNumber(string("abc"))==false);
	assert(s.isNumber(string("1 a"))==false);
	assert(s.isNumber(string("2e10"))==true);
	assert(s.isNumber(string(" -90e3   "))==true);
	assert(s.isNumber(string(" 1e"))==false);
	assert(s.isNumber(string("e3"))==false);
	assert(s.isNumber(string(" 6e-1"))==true);
	assert(s.isNumber(string(" 99e2.5 "))==false);
	assert(s.isNumber(string("53.5e93"))==true);
	assert(s.isNumber(string(" --6 "))==false);
	assert(s.isNumber(string("-+3"))==false);
	assert(s.isNumber(string("95a54e53"))==false);
	return 0;
}
