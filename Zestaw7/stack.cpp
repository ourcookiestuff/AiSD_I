/*Jakub Dziurka, 28.11.2023 jakub.dziurka@student.uj.edu.pl

 --> Instrukcja kompilacji:
    make run
*/
#include <iostream>
#include <vector>
#include <cassert>

bool isnumber(const std::string& input) {
    bool hasMinus = false;
    bool hasDigit = false;
    bool hasDecimal = false;

    for (size_t i = 0; i < input.size(); ++i) {
        char t = input[i];

        if (t == '-') {
            // Minus jest dozwolony tylko na początku i jeśli jeszcze nie wystąpił.
            if (i != 0 || hasMinus) {
                return false;
            }
            hasMinus = true;
        }
        else if (t == 46) {
            // Kropka dziesiętna jest dozwolona tylko po znaku minus i jeśli jeszcze nie wystąpiła.
            if (hasDecimal || (!hasMinus && i == 0) || !hasDigit) {
                return false;
            }
            hasDecimal = true;
        }
        else if (t >= 48 && t <= 57) {
            hasDigit = true;
        }
        else {
            return false;
        }
    }

    return hasDigit;
}

bool czy_oper(const std::string& input)
{
    return input == "+" || input == "-" || input == "*" || input == "/";
}

void push(double stack[],int &count,double &x)
{
    stack[count] = x;
    count++;
}

double pop(double stack[],int &count)
{
    double x = stack[count-1];
    count--;
    stack[count] = 0;
    return x;
}

int onp(std::vector<std::string> input)
{
    double array[50];
    double a, b, c;
    int count = 0;
    for(unsigned int i = 0 ; i < input.size() ; i++)
    {
        if(isnumber(input[i])) {
            a = stod(input[i]);
            push(array,count,a);
        }
        else if (czy_oper(input[i])) {
            if(input[i]=="+")
            {
                a = pop(array,count);
                b = pop(array,count);
                c = a + b;
                push(array,count,c);
            }
            else if(input[i]=="-")
            {
                a = pop(array,count);
                b = pop(array,count);
                c = b - a;
                push(array,count,c);
            }
            else if(input[i]=="*")
            {
                a = pop(array,count);
                b = pop(array,count);
                c = a * b;
                push(array,count,c);
            }
            else if(input[i]=="/")
            {
                a = pop(array,count);
                b = pop(array,count);
                assert(a != 0);
                c = b / a;
                push(array,count,c);
            }
        }
    }
    return array[count - 1];
}

int main()
{
    std::vector<std::string> input { "-6", "2", "/" };
    int result = onp(input);
    assert( result == -3 );
    std::cout << "Wynik: " << result << std::endl;

    return 0;
}