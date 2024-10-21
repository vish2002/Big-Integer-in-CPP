#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>
#include <string>

// Node structure for linked list
struct Node {
    int data;
    Node* next;
};

// BigInteger class
class BigInteger {
private:
    Node* head;

public:
    // Constructor
    BigInteger();

    // Destructor
    ~BigInteger();

    // Function to add a new node at the end of the linked list
    void addNode(int data);

    // Function to display the linked list
    void display();

    // Function to add two large numbers
    void add(BigInteger& num2);

    // Function to subtract two large numbers
    void subtract(BigInteger& num2);

    // Function to convert a string to a BigInteger
    void stringToBigInteger(const std::string& str);
};

#endif // BIGINTEGER_H
