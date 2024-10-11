#include "BigInteger.h"

// Constructor
BigInteger::BigInteger() {
    head = nullptr;
}

// Destructor
BigInteger::~BigInteger() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
}

// Function to add a new node at the end of the linked list
void BigInteger::addNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to display the linked list
void BigInteger::display() {
    Node* temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

// Function to calculate the factorial of a large number
void BigInteger::factorial(int n) {
    BigInteger result;
    result.addNode(1);

    for (int i = 1; i <= n; i++) {
        BigInteger temp;
        temp.stringToBigInteger(std::to_string(i));
        result.multiply(temp);
    }

    result.display();
}

// Function to add two large numbers
void BigInteger::add(BigInteger& num2) {
    Node* temp1 = head;
    Node* temp2 = num2.head;
    int carry = 0;
    BigInteger result;

    while (temp1 != nullptr || temp2 != nullptr) {
        int sum = carry;
        if (temp1 != nullptr) {
            sum += temp1->data;
            temp1 = temp1->next;
        }
        if (temp2 != nullptr) {
            sum += temp2->data;
            temp2 = temp2->next;
        }

        carry = sum / 10;
        result.addNode(sum % 10);
    }

    if (carry > 0) {
        result.addNode(carry);
    }

    result.display();
}

// Function to subtract two large numbers
void BigInteger::subtract(BigInteger& num2) {
    Node* temp1 = head;
    Node* temp2 = num2.head;
    int borrow = 0;
    BigInteger result;

    while (temp1 != nullptr || temp2 != nullptr) {
        int diff = borrow;
        if (temp1 != nullptr) {
            diff += temp1->data;
            temp1 = temp1->next;
        }
        if (temp2 != nullptr) {
            diff -= temp2->data;
            temp2 = temp2->next;
        }

        if (diff < 0) {
            borrow = -1;
            diff += 10;
        } else {
            borrow = 0;
        }

        result.addNode(diff);
    }

    result.display();
}

// Function to convert a string to a BigInteger
void BigInteger::stringToBigInteger(const std::string& str) {
    for (int i = str.length() - 1; i >= 0; i--) {
        addNode(str[i] - '0');
    }
}

// Function to multiply two large numbers
void BigInteger::multiply(BigInteger& num2) {
    BigInteger result;
    Node* temp1 = head;

    while (temp1 != nullptr) {
        int carry = 0;
        Node* temp2 = num2.head;
        BigInteger tempResult;

        while (temp2 != nullptr) {
            int product = carry + temp1->data * temp2->data;
            carry = product / 10;
            tempResult.addNode(product % 10);
            temp2 = temp2->next;
        }

 if (carry > 0) {
            tempResult.addNode(carry);
        }

        result.add(tempResult);
        temp1 = temp1->next;
    }

    result.display();
}

int main() {
    BigInteger num1, num2;
    num1.stringToBigInteger("12345678901234567890");
    num2.stringToBigInteger("98765432109876543210");

    std::cout << "Number 1: ";
    num1.display();
    std::cout << "Number 2: ";
    num2.display();

    std::cout << "Addition: ";
    num1.add(num2);

    std::cout << "Subtraction: ";
    num1.subtract(num2);

    std::cout << "Factorial of 5: ";
    num1.factorial(5);

    return 0;
}
