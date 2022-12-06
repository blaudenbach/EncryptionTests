/**
 * @file RSAcracked.cpp
 * 
 * @author Brandon Laudenbach
 * 
 * @brief This program gets a 4-digit pin from the user, encrypts it using the RSA system, and cracks the code to decrypt it.
 * 
 * @version 1.0
 * 
 * @date 2022-12-06
 * 
 */

//Include necessary files for program operation
#include <iostream>
#include <math.h>

using namespace std;

//Declaration of the functions.
double* RSAencryption(int, double*);
int gcd(int, int);
double findRSAkey(double, double);

/**
 * Main program.
 * 
 * @brief This program gets user input for a 4-digit pin, encrypts it with the RSA system, cracks the code and decrypts it.
 * 
 * @pre Program is run
 * @post Program is completed
 * 
 * @return int : main program return value
 */
int main(){
    //Initialize value of pin to enter while loop
    int pin = 10000;

    //Whitespace for readability
    cout << endl;

    //Check that the user is entering a 4-digit pin
    while(pin < 1000 || pin > 9999)
    {
        //Get user pin
        cout << "Enter your 4-digit pin between 1000-9999: ";
        cin >> pin;

        //Display message if user entered an invalid pin
        if(pin < 1000 || pin > 9999){
            cout << "Invalid pin. Please re-enter.\n" << endl;
        }
    }

    //Display the pin back to the uesr
    cout << "You entered " << pin << endl;

    //Create an array to pass to the encryption function. It will be filled with the return values
    double RSAarray[3];

    //Encrypt the pin using the RSA encryption systsem
    RSAencryption(pin, RSAarray);

    //Display the encrypted pin to the user
    cout << "Encrypted pin: " << RSAarray[0] << endl << endl;

    //Display public key to user. The public key is available to all
    cout << "The public key is (n, e): " << "(" << RSAarray[1] << ", " << RSAarray[2] << ")" << endl;

    //Notify user that the code is being cracked
    cout << "Cracking the code..." << endl;

    //Find the key used to decrypt the information
    double decryptionKey = findRSAkey(RSAarray[1], RSAarray[2]);

    //Display the decryption key to the user
    cout << "Decryption key: " << decryptionKey << endl;

    //Decode pin using the found decryption key
    double decodedPIN = pow(RSAarray[0], fmod(decryptionKey, RSAarray[1]));

    //Display the decoded pin to the user
    cout << "The decoded pin is: " << decodedPIN << endl;
    cout << endl;
}

/**
 * @brief This function takes an integer (the user's pin) and encrypts it with the RSA system.
 * It fills the given empty array with the encrypted pin and the public key used for encryption.
 * 
 * @pre main program calls passes user pin into function.
 * @post array is filled with desired values
 * 
 * @param data  The data to be encrypted. In this case, it will be the user's 4-digit pin.
 * @param returnArray   An empty array to be filled with the encrypted message and public key information.
 * 
 * @return double*  The now-filled array containing the encrypted pin and public key
 */
double* RSAencryption(int data, double* returnArray){
    //Declaration of variables needed for RSA algorithm
    //Public key = (n, e)

    //Selected "relatively small" prime numbers
    double  p = 373837;
    double q = 867617;
    //Display secret prime numbers to user
    cout << "Inside encryption function. The secret prime numbers are: " << p << " and " << q << endl;

    //Compute n of the key
    double n = p * q;

    //Other values needed to compute key
    double phi = (p - 1) * (q - 1);
    double tempGCD;
    

    //Get e of public key
    //Find a value of e relatively prime to phi
    double e = 2;
    while(e < phi){
        //Check if e and phi are relatively prime
        tempGCD = gcd(e, phi);
        //If yes, exit loop
        if(tempGCD == 1)
            break;
        //Otherwise increment e and check again
        else
            e++;
    }

    //Encrypt pin number using RSA method
    //c = data ^ (e mod n)
    double c = pow(data, fmod(e, n));

    //Fill return array
    returnArray[0] = c;
    returnArray[1] = n;
    returnArray[2] = e;

    //Return the array
    return returnArray;
}

/**
 * @brief This function takes two integers, computes their greatest common divisor, and returns it.
 * 
 * @pre Function is called and passed two integers
 * @pre The greatest common divisor is returned
 * 
 * @param a     The first integer whose greatest common divisor is desired
 * @param b     The second integer whose greatest common divisor is desired
 * 
 * @return int  The greatest common divisor of the two input integers
 */
int gcd(int a, int b){
    //Initialize value to enter the while loop
    int temp = 1;

    //Loop until remainder of the division is 0
    while(temp != 0){
        //Find remainder
        temp = a % b;

        //If remainder is 0, we are done
        if(temp == 0) break;

        //Otherwise update values to test again
        a = b;
        b = temp;
    }

    //Return the value of the greatest common divisor
    return b;
}

/**
 * @brief This function takes the two parts of the public key then finds the decryption key and returns it.
 * 
 * @pre Main program passes the public key as parameters
 * @post Decryption key is returned
 * 
 * @param n     The n value of the public key
 * @param e     The e value of the public key
 * 
 * @return double   The value used to decrypt messages which have been encrypted
 */
double findRSAkey(double n, double e){
    //Variable to store decrpytion key
    double d;

    //Find prime factors of n, p and q
    //First, find p
    double p = 2;
    //Find prime divisor of n
    while((fmod(n, p)) != 0){
        p++;
    }
    
    //Find q, since n = p * q
    double q = n / p;

    //Display the found prime numbers to the user
    cout << "Inside code-cracking function. The found prime numbers are: " << p << " and " << q << endl;

    //Find decrpytion key
    //d = e^-1 mod phi
    double phi = (p-1) * (q-1);
    d = fmod(pow(e, -1), phi);

    //Return decryption key
    return d;
}