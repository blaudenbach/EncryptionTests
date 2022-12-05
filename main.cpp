#include <iostream>
#include <math.h>

using namespace std;

double* RSAencryption(int, double*);
int gcd(int, int);
double findRSAkey(double, double);

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
    double RSAarray[3];
    RSAencryption(pin, RSAarray);

    cout << "Encrypted pin: " << RSAarray[0] << endl;

    //Display public key to user
    cout << "The public key is (n, e): " << "(" << RSAarray[1] << ", " << RSAarray[2] << ")" << endl;

    //Crack the RSA code
    double decryptionKey = findRSAkey(RSAarray[1], RSAarray[2]);
    cout << "Cracking the code. Encryption key: " << decryptionKey << endl;

    //Decode pin
    double decodedPIN = pow(RSAarray[0], fmod(decryptionKey, RSAarray[1]));
    cout << "The decoded pin is: " << decodedPIN << endl;

}

double* RSAencryption(int pNum, double* returnArray){
    //Declaration of variables needed for RSA algorithm
    double  p = 3;
    double q = 5;
    double n = p * q;
    double tempGCD;
    double phi = (p - 1) * (q - 1);

    //Get public key
    double e = 2;
    while(e < phi){
        tempGCD = gcd(e, phi);
        if(tempGCD == 1)
            break;
        else
            e++;
    }

    //Encrypt pin number
    double c = pow(pNum, fmod(e, n));

    //Fill return array
    returnArray[0] = c;
    returnArray[1] = n;
    returnArray[2] = e;

    return returnArray;
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

double findRSAkey(double n, double e){
    double d;

    //Find prime factors of n
    //Find p
    double p = 2;
    while((fmod(n, p)) != 0){
        p++;
    }
    
    //Find q
    double q = n / p;

    //Find decrpytion key
    double phi = (p-1) * (q-1);
    d = fmod(pow(e, -1), phi);

    return d;
}