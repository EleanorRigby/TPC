//============================================================================
// Name        : TPCPROBLEM003.cpp
// Author      : Tushar
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include<cstdlib>
#include<ctime>
#include<stdio.h>
#include<string.h>
#include<iomanip>
using namespace std;



/*
 * Given N men and N women, where each person has ranked all members of the opposite sex in order of preference, marry the men and women together such that there are no two people of opposite sex who would both rather have each other than their current partners. If there are no such people, all the marriages are “stable”.

Consider the following example.

Let there be two men m1 and m2 and two women w1 and w2.
Let m1‘s list of preferences be {w1, w2}
Let m2‘s list of preferences be {w1, w2}
Let w1‘s list of preferences be {m1, m2}
Let w2‘s list of preferences be {m1, m2}

The matching { {m1, w2}, {w1, m2} } is not stable because m1 and w1 would prefer each other over their assigned partners. The matching {m1, w1} and {m2, w2} is stable because there are no two people of opposite sex that would prefer each other over their assigned partners.

Input & Output: Input is a 2D matrix of size (2*N)*N where N is number of women or men. Rows from 0 to N-1 represent preference lists of men and rows from N to 2*N – 1 represent preference lists of women. So men are numbered from 0 to N-1 and women are numbered from N to 2*N – 1. The output is list of married pairs.

// Number of Men or Women
#define N  4
// Driver program to test your function
int main()
{
    int prefer[2*N][N] = { {7, 5, 6, 4},
        {5, 4, 6, 7},
        {4, 5, 6, 7},
        {4, 5, 6, 7},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
    };
    stableMarriage(prefer);

    return 0;
}
Output:

Girl   Boy
4       2
5       1
6       3
7       0
 *
 *
 * */


#define TESTCASE_COUNT	1
#define MIN_COUPLE		2
#define MAX_COUPLE		3
#define	NUM_COUPLE		4

//void	TestGenAndSolve	(int numberofpairs);
void	Solver_Men		(int [][NUM_COUPLE], int * pGreedyMen, int number);
void	Solver_Women	(int [][NUM_COUPLE], int * pGreedyWomen, int number);
void	Print			(int * a, bool b, int c);
int 	LookUpPreference(int * a, int b, int c);

//Driver Program
int main() {

	int array [8][4] = { 	{7, 5, 6, 4},
	        				{5, 4, 6, 7},
	        				{4, 5, 6, 7},
	        				{4, 5, 6, 7},
	        				{0, 1, 2, 3},
	        				{0, 1, 2, 3},
	        				{0, 1, 2, 3},
	        				{0, 1, 2, 3},
	    };

	int * pMen	=	new int[4];
	int * pWomen=	new int[4];

	for (unsigned h = 0; h < NUM_COUPLE; ++h) {
		pMen[h]		=	NUM_COUPLE + 1;
		pWomen[h] 	=	2*NUM_COUPLE + 1;
	}

	//Solve if men are choosers
	//Solver_Men   (array, pMen, 4);
	//Solve if women are choosers
	Solver_Women (array, pWomen, 4);

	//Print Results
	Print(pMen, false, 4);
	cout<<endl<<endl;
	Print(pWomen, true, 4);

	int a;
	cin>>a;

	return 0;
}


//Solving considering men will choose among all women
void Solver_Men (int pref [][4], int * pGreedyMen, int numberofpairs)
{
		bool women_avail [NUM_COUPLE]	=	{true, true, true, true};

	//all woen ask men for marriage
	for (unsigned girl = 0; girl < numberofpairs; girl = 0) {

		//only women who are not matched will ask
		while (women_avail[girl] == false) {
			++girl;
			//case: all girls matched , return
			if (girl > NUM_COUPLE)
				return;
		}


		//boys choose the best girl  for them and keep updating their selection.
		for (unsigned boy = 0; boy < numberofpairs; ++boy) {
			//get woman's first pref
			int men = pref[girl + NUM_COUPLE][boy];

			//check preference of girl that boy selected. and reject or accept offer
			if (LookUpPreference(pref[men], girl + NUM_COUPLE, numberofpairs) < LookUpPreference(pref[men], pGreedyMen[men], numberofpairs)) {

						//extract the old preference
						int temp = pGreedyMen[men];

						//set new pref women to not available
						women_avail[girl] = false;

						//set old pref to avaialble if applicable
						if (temp < 2*NUM_COUPLE)
							women_avail[temp] = true;

						//set new pref
						pGreedyMen[men]	=	girl + NUM_COUPLE;


						break;

					}
			}




	}



}

//Solving considering women will choose among all men
void Solver_Women (int pref [][NUM_COUPLE], int * pGreedyWomen, int numberofpairs)
{
	//array to mainatain availability of men not married
	bool men_avail[NUM_COUPLE] = {true, true, true, true};

	//boy asks every girl  for marriage
	for (unsigned boy = 0; boy < numberofpairs; boy = 0) {

		//only boys who are not matched will ask
		while (men_avail[boy] == false) {
			++boy;
			//case: all boys matched , return
			if (boy > NUM_COUPLE)
				return;
		}

		//girls choose the best boy for them and keep updating their selection.
		for (unsigned girl = 0; girl < numberofpairs; ++girl) {
				//get boy's first pref
				int women 		= pref[boy][girl];
				int womenlookup = women % NUM_COUPLE;

			//check preference of girl that boy selected. and reject or accept offer
			if (LookUpPreference(pref[women], boy, numberofpairs) < LookUpPreference(pref[women], pGreedyWomen[womenlookup], numberofpairs)) {

				//extract the old preference
				int temp = pGreedyWomen[womenlookup];

				//set new pref boy to not available
				men_avail[boy] = false;

				//set old pref to avaialble if applicable
				if (temp < NUM_COUPLE)
					men_avail[temp] = true;

				//set new pref
				pGreedyWomen[womenlookup]	=	boy;


				break;

			}
		}


	}

}



void Print (int * arr, bool pIsWomenGreedy, int len)
{
	if (pIsWomenGreedy)
		cout<<"Greedy approach for girls"<<endl;
	else
		cout<<"Greedy approach for boys"<<endl;

	cout<<setw(5)<<"Girl"<<setw(5)<<"Boy";
	cout<<endl;

	for (int iter = 0; iter < len; ++iter)
		cout<<setw(5)<<(pIsWomenGreedy ? iter + 4 : iter)<<setw(5)<<arr[iter]<<endl;
}


int LookUpPreference (int * arr, int searchentry, int length)
{
	int iter;

	for (iter = 0; iter < length; ++iter)
		if (arr[iter] == searchentry)
			break;

	return iter+1;


}



void TestGenAndSolve (int numberofpairs)
{

		int ** 	input_array	=	NULL;
		int *	greedy_men	=	NULL;
		int	*	greedy_women=	NULL;

		cout<<"Test Case #"<<1;

	//Allocate array
	input_array	=	new int * [numberofpairs * 2];

	cout<<"Test Case #"<<3;

	for(int gen= 0; gen < numberofpairs; ++gen)
	{
		input_array[gen]= new int[numberofpairs];
	}

	//Allocate out put arrays
	greedy_men		=	new int[numberofpairs];
	greedy_women	=	new int[numberofpairs];

	//Fill the array, to generate test case
	for (int gen = 0; gen < 2 * numberofpairs ; ++gen) {
		for (int geny = 0; geny < numberofpairs; ++geny) {
			srand(time(NULL));
			if (gen < numberofpairs)
				input_array[gen][geny]	=	rand() % numberofpairs;
			else
				input_array[gen][geny]	=	rand() % (2*numberofpairs) + numberofpairs;

		}

	}


	//Solver_Men (input_array, greedy_men, numberofpairs);
	//Solver_Women (input_array, greedy_women, numberofpairs);

	Print(greedy_women, true, numberofpairs);
	Print(greedy_men, false, numberofpairs);
}









