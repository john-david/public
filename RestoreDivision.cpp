//John David
//
//Restoring Division Algorithm with bitset STL

#include <iostream>
#include <bitset>

using namespace std;

int main() {
	cout << "This program divides numbers via a 16 bit Restoring Algorithm" << endl;

	//variables for the divisor and dividend
	int divisor = 0;
	int dividend = 0;

	//ask user for an unsigned integer for divisor
	cout << "Please enter an unsigned integer divisor (between 1 and 65536) for the divisor:" << endl;
	cin >> divisor;
	//while loop to check user's input for scope
	while(divisor < 1 || divisor > 65536){
		cout << "Your number was either less than or equal to 0 or greater than 65536.\n";
		cout << "please enter an integer between 1 and 65536.\n";
	    cin >> divisor;
	}

	cout << "you entered:  " << divisor << endl;

	//ask user for an unsigned integer for dividend
	cout << "Please enter an unsigned integer dividend (between 0 and 65536) for the dividend:" << endl;
	cin >> dividend;
	//while loop to check user's input for scope
	while(dividend < 0 || dividend > 65536){
		cout << "Your number was either less than 0 or greater than 65536.\n";
		cout << "please enter an integer between 0 and 65536.\n";
	    cin >> dividend;
	}

	cout << "you entered:  " << dividend << endl;

	//calculate quotient via decimal
	int quotient = dividend / divisor;
	//insert the quotient into a 16 bit array.
	//the bitset library automatically translates the number from decimal to the 16 bit binary complement
	bitset<16> quot(quotient);

	//calculate remainder via decimal
	int remainder = dividend % divisor;
	//insert the quotient into a 16 bit array
	//bitset library translates from decimal to binary complement
	bitset<16> rem(remainder);

	//inform the user of what the remainder and quotient of the division calculation
	//was from the decimal numbers.
	//print the anticipated result in binary.
	cout << "\n\nThe decimal quotient of these two numbers is: " << quotient << endl;
	cout << "\nThe decimdal remainder of these two numbers is: " << remainder << endl;
	cout << "\nIn 32 bit 2's complement binary this quotient and remainder would be: " << endl;
	cout << "(printing in remainder / quotient 16 bit by 2 binary format)" << endl;
	cout << "\t" << rem << "  " << quot << endl;

	//set the divisor to it's negative equivalent for subtraction in binary
	int negDivisor = divisor * -1;

	//prepare 3 16 bit bitsets for the restoring division algorithm
	bitset<16> negD(negDivisor);
	bitset<16> q(dividend);
	bitset<16> a(0);

	//prepare for the restoring division loop steps.
	//variable to count steps in the algorithm
	//variable to check/compare the most significant bit
	//variable to bridge the two bitsets when shifting left.
	int step = 0;
	int msb = a[15];
	int bridge = q[15];

	cout << "\n\nnow...let's do this in binary using a 16 bit by 2 Restoring Division Algorithm...\n\n" << endl;

	//prepare the table for output
	cout << "step " << " " << "\t Remainder " << "\t" << "\t Dividend" << "\t" << endl;
	cout << "__________________________________________________________________________" << endl;
	cout << "  " << step << "\t" << a << "\t" << q << "\t  " << endl << endl;

	//since this is a 16 bit restoring division algorithm,
	//16 steps are needed.
	//a for loop will loop 16 times checking the appropriate bits and performing the
	//subtraction, restore and shift steps accordingly
	for(step = 1; step <= 16; step++){

			//set bits pre-shift
			cout << "shift." << endl;
			bridge = q[15];
			//shift blocks
			a<<= 1;
			if(bridge == 1)
				a[0] = 1;
			q <<= 1;

			//subtract by negA addition
			cout << "add -m and check bits";
			bitset<16> const aa(a);
			bitset<16> const bb(negD);
			bitset<16> const mm("1");
			bitset<16> result;
			for (int i = 0; i < result.size(); ++i) {
			    bitset<16> const diff(((aa >> i)&mm).to_ullong() + ((bb >> i)&mm).to_ullong() + (result >> i).to_ullong());
			    result ^= (diff ^ (result >> i)) << i;
			}
			//compare result of subtraction after shift
			a = result;
			msb = a[15];
			//check msb
			if(msb == 1){
				cout << "\nmsb = 1, restore, set q0 to 0" << endl;
				q[0] = 0;

				bitset<16> const aa(a);
				bitset<16> const bb(divisor);
				bitset<16> const mm("1");
				bitset<16> result;
				for (int i = 0; i < result.size(); ++i) {
				    bitset<16> const diff(((aa >> i)&mm).to_ullong() + ((bb >> i)&mm).to_ullong() + (result >> i).to_ullong());
				    result ^= (diff ^ (result >> i)) << i;
				}
				a = result;

			}
			else{
				cout << ", set q0 to 1" << endl;
				q[0] = 1;
			}

		cout << "  " << step << "\t" << a << "\t" << q << "\t  " << endl << endl;

	}

	//summarize results
	cout << "Using Restoring Division the quotient and remainder in 32 bit dbinary form is: " << endl;
	cout << "(printing in remainder / quotient 16 bit by 2 binary format)" << endl;
	cout << "\n\t" << a << "  " << q << endl;

	return 0;
}
