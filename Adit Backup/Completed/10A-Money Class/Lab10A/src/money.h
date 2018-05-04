/* CSCI261 Lab 10A: Money Class
*
* Descriptiona: Header file for Money Class
*
* Author: Michael Bartlett
*
*/
#pragma once
class Money {
public:
	Money();
	Money(int dols, int cens);
	int GetDollars();
	int GetCents();
	void SetDollars(int dols);
	void SetCents(int cens);
private:
	int dollars, cents;
};
