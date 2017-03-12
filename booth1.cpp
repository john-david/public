//John David
//UMSL CS 2700
//jdcvd@mail.umsl.edu
//
//Booth's Algorithm Project

#include <iostream>
#include <bitset>

using namespace std;

int main() {
	cout << "This program multiplies signed integers via a 16 bit Booth's Algorithm" << endl;

	//set variables for the multiplier and the multiplicand
	int multiplier = 0;
	int multiplicand = 0;

	//ask the user for the multipler
	//check the input against the scope of a signed 16 bit integar
	cout << "Please enter a signed integer (between -32,768 and 32767) for the multiplier:" << endl;
	cin >> multiplier;
	while(multiplier < -32768 || multiplier > 32767){
		cout << "Your number was either less than -32768 or greater than 32767.\n";
		cout << "please enter an integer between -32768 and 32767.\n";
	    cin >> multiplier;
	}

	cout << "you entered:  " << multiplier << endl;

	//ask the user for the multiplicand
	//check the input against the scope of a signed 16 bit integer
	cout << "\nPlease enter a signed integer (between -32,768 and 32767) for the multiplicand:" << endl;
	cin >> multiplicand;
	while(multiplicand < -32768 || multiplicand > 32767){
		cout << "Your number was either less than -32768 or greater than 32767.\n";
		cout << "please enter an integer between -32768 and 32767.\n";
	    cin >> multiplicand;
	}

	cout << "you entered:  " << multiplicand << endl;

	//calculate the product in decimal
	int product = multiplier * multiplicand;
	//convert the product into binary to check result against the algorithm's result
	bitset<32> p(product);

	//prepare the negative completment of the multiplier
	int negMultiplier = multiplier * -1;

	//prepare 16 bit binary sets of the multiplier, negMultiplier, multiplier
	bitset<16> a(multiplier);
	bitset<16> negA(negMultiplier);
	bitset<16> m(multiplicand);
	bitset<16> o(0);

	//variables used for check bit and bridging bits across 16 bit arrays on shifts
	int minus = 0;
	int step = 0;
	int msb = o[15];
	int lsb = m[0];
	int bridge = a[0];

	//inform the user of the binary number complements of the inputs chosen
	cout << "\nThe multiplier 'm' in binary is: " << a << endl;
	cout << "The binary 2's complement of the multiplier '-m' is:  " << negA << endl;
	cout << "The multiplicand in binary is:  " << m << endl;
	cout << "\nIn 32 bit 2's complement binary this product would be: " << endl;
	cout << "\n\t" << p << endl;

	cout << "\n\nnow...let's do this in binary using a 16 bit Booth's ALgorithm...\n\n" << endl;

	//prepare the table for the algorithm
	cout << "\nstep " << "\t Multiplier " << "\t" << "\t Multiplacand" << "\t\t m-1" << "\t" << endl;
	cout << "__________________________________________________________________________" << endl;
	cout << "  " << step << "\t"  << o << "\t" << m << "\t  " << minus << endl << endl;

	//16 bit booth's algorithm requires 16 steps.
	//this will be handled by a for loop
	//each iteration will check the least sig bit and most sig bit
	//and shift, add and shift, subtract and shift as appropriate.
	for(step = 1; step <= 16; step++){

		//msb 0, lsb 0, shift.
		if(lsb == 0 && minus == 0){
			//set bits pre-shift
			cout << "0 0 shift." << endl;
			minus = m[0];
			msb = o[15];
			bridge = o[0];
			//shift blocks
			o >>= 1;
			if(msb == 1)
				o[15] = 1;
			m >>= 1;
			m[15] = bridge;
			lsb = m[0];
		}
		//msb 1, lsb 1, shift
		else if(lsb == 1 && minus == 1){
			//set bits pre-shift
			cout << "1 1 shift." << endl;
			minus = m[0];
			msb = o[15];
			bridge = o[0];
			//shift blocks
			o >>= 1;
			if(msb == 1)
				o[15] = 1;
			m >>= 1;
			m[15] = bridge;
			lsb = m[0];
		}
		//msb 1, lsb 0, add multiplier and shift right
		else if(lsb == 1 && minus == 0){
			//subtract by negA addition
			cout << "1 0 add -m and shift." << endl;
			bitset<16> const aa(o);
			bitset<16> const bb(negA);
			bitset<16> const mm("1");
			bitset<16> result;
			for (int i = 0; i < result.size(); ++i) {
			    bitset<16> const diff(((aa >> i)&mm).to_ullong() + ((bb >> i)&mm).to_ullong() + (result >> i).to_ullong());
			    result ^= (diff ^ (result >> i)) << i;
			}
			o = result;
			//shift sequence
			//set bits pre-shift
			minus = m[0];
			msb = o[15];
			bridge = a[0];
			//shift blocks
			o >>= 1;
			if(msb == 1)
				o[15] = 1;
			m >>= 1;
			m[15] = bridge;
			lsb = m[0];
		}
		//msb 1, lsb 0, subtract multiplier and shift right
		else if(lsb == 0 && minus == 1){
			//add by M addition
			cout << "0 1 add m and shift." << endl;
			bitset<16> const aa(o);
			bitset<16> const bb(a);
			bitset<16> const mm("1");
			bitset<16> result;
			for (int i = 0; i < result.size(); ++i) {
			    bitset<16> const diff(((aa >> i)&mm).to_ullong() + ((bb >> i)&mm).to_ullong() + (result >> i).to_ullong());
			    result ^= (diff ^ (result >> i)) << i;
			}
			o = result;
			//shift sequence
			//set bits pre-shift
			minus = m[0];
			msb = o[15];
			bridge = o[0];
			//shift blocks
			o >>= 1;
			if(msb == 1)
				o[15] = 1;
			m >>= 1;
			m[15] = bridge;
			lsb = m[0];
		}

		cout << endl << "  " << step << "\t"  << o << "\t" << m << "\t  " << minus << endl << endl;

	}

	//show final results.
	cout << "Using Booth the product in 32 bit 2's complement binary is: " << endl << "\n\t" << o << m << endl;

	cout << "\nThe decimal product of these two numbers is: " << product << endl << endl;

	return 0;
}
