#include <iostream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

class BigInteger {
private:
    Node* head;
    int length;

public:
    BigInteger() : head(nullptr), length(0) {}

    BigInteger(const string& number) {
        head = nullptr;
        length = 0;
        for (int i = number.length() - 1; i >= 0; --i) {
            int digit = number[i] - '0';
            insertAtEnd(digit);
        }
    }

    ~BigInteger() {
        Node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertAtEnd(int digit) {
        Node* newNode = new Node(digit);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        length++;
    }

    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data;
            temp = temp->next;
        }
        cout << endl;
    }

    BigInteger add(BigInteger& other) {
        BigInteger result;
        Node* temp1 = head;
        Node* temp2 = other.head;
        int carry = 0;
        
        while (temp1 != nullptr || temp2 != nullptr || carry != 0) {
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
            sum %= 10;
            result.insertAtEnd(sum);
        }
        
        return result;
    }

    BigInteger subtract(BigInteger& other) {
        // To be implemented based on requirements
    }

    BigInteger multiply(BigInteger& other) {
        BigInteger result;
        Node* temp1 = head;
        
        while (temp1 != nullptr) {
            Node* temp2 = other.head;
            BigInteger intermediateResult;
            int carry = 0;
            
            while (temp2 != nullptr || carry != 0) {
                int product = carry;
                if (temp2 != nullptr) {
                    product += temp1->data * temp2->data;
                    temp2 = temp2->next;
                }
                carry = product / 10;
                product %= 10;
                intermediateResult.insertAtEnd(product);
            }
            
            for (int i = 0; i < result.length; ++i) {
                intermediateResult.insertAtEnd(0);
            }
            result = result.add(intermediateResult);
            temp1 = temp1->next;
        }
        
        return result;
    }

    BigInteger divide(BigInteger& other) {
        BigInteger quotient;
        BigInteger dividend = *this;
        BigInteger divisor = other;
        
        while (dividend.compare(divisor) >= 0) {
            BigInteger temp = divisor;
            BigInteger count("1");
            
            while (temp.multiply(BigInteger("2")).compare(dividend) <= 0) {
                temp = temp.multiply(BigInteger("2"));
                count = count.multiply(BigInteger("2"));
            }
            
            dividend = dividend.subtract(temp);
            quotient = quotient.add(count);
        }
        
        return quotient;
    }

    int compare(BigInteger& other) {
        if (length > other.length) return 1;
        if (length < other.length) return -1;
        
        Node* temp1 = head;
        Node* temp2 = other.head;
        
        while (temp1 != nullptr && temp2 != nullptr) {
            if (temp1->data > temp2->data) return 1;
            if (temp1->data < temp2->data) return -1;
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        
        return 0;
    }
};

int main() {
    BigInteger num1("12345678901234567890");
    BigInteger num2("98765432109876543210");

    BigInteger product = num1.multiply(num2);
    cout << "Product: ";
    product.display();

    BigInteger quotient = num2.divide(num1);
    cout << "Quotient: ";
    quotient.display();

    return 0;
}
