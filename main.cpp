#include <iostream>

using namespace std;

int RSAencryption(int);
int gcd(int, int);

int main(){
    int pin = 10000;

    //Check that the user is entering a 4-digit pin
    while(pin < 1000 || pin > 9999)
    {
        //Get user pin
        cout << "Enter your 4-digit pin between 1000-9999: ";
        cin >> pin;
    }

    cout << "You entered " << pin << endl;

    //Encrypt the pin using a non-quantum-safe method
    int RSApin = RSAencryption(pin);

}

int RSAencryption(int pNum){
    //Declaration of variables needed for RSA algorithm
    int p = 13;
    int q = 11;
    int n = p * q;
    int tempGCD;
    int phi = (p - 1) * (q - 1);

    //Get public key


    //Get private key


    //Encrypt pin number
    int pin = 0;

    //Return results
    return pin;
}

int gcd(int a, int b){
    int temp = 1;

    //Loop until remainder of the division is 0
    while(temp != 0){
        temp = a % b;
        if(temp == 0) break;

        //Update values to test
        a = b;
        b = temp;
    }

    return b;
}