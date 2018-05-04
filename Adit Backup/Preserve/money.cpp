/* CSCI261 Lab 10A: Money Class
*
* Description: Implementation file for Money Class
*
* Author:
*
*/
#include "money.h"
Money::Money(){
	dollars = 0, cents = 0;
	}
Money::Money(int dols, int cens){
	dollars = dols, cents = cens;
}
int Money::GetDollars(){
	return dollars;
}
int Money::GetCents(){
	return cents;
}
void Money::SetDollars(int dols){
	dollars = dols;
}
void Money::SetCents(int cens){
	cents = cens;
}
