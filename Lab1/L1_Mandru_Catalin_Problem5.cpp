#include <iostream>

using namespace std;

float power(float number, int exponent) {
    if (exponent == 0) return 1;

    if (exponent == 1) return number;

    float temp = power(number, exponent / 2);
    if (exponent % 2 == 0)
        return temp * temp;

    return number * temp * temp;
}


// x und n lesen und x^n drucken
void subpunktA() {
    float x;
    int n;

    cout << "=============Subpunkt a.================" << endl;
    cout << "x = ";
    cin >> x;
    cout << "n = ";
    cin >> n;

    if (x == 0 && n == 0) {
        cout << "0^0 funktioniert nicht! :(\n";
        return;
    }

    float resultat = power(x, n);

    cout << "x^n = " << resultat << endl;
}

// Bestimmt der Startindex des langster Sub-array, wo jede 2-te Komponente ein vershiedener Vorzeichen hat.
// Input: *numbers = pointer fur einen Array
//        &numbers = Lange des Arrays
// Output: starting_index der Sub-array
//         &numbers = wird mit die Lange der Sub-array ersetzt
int start_longest_seq(int* numbers, int &nr_numbers){
    int max_length = 1;
    int current_length = 1;
    int starting_index = 0;

    for (int index = 0; index < nr_numbers - 1; index++) {
        // pruft ob die benachbarte Zahlen verschiedene Vorzeichen haben
        if (numbers[index] * numbers[index + 1] < 0)
            current_length++;
        else
            current_length = 1;

        // speichert die neue Daten wenn man eine neues Sub-array findet
        if (current_length > max_length) {
            max_length = current_length;
            starting_index = index + 2 - max_length;
        }
    }

    nr_numbers = max_length;
    return starting_index;
}


// Langste Sub-Array wo die Komponente verschiedener Vorzeichen haben
void subpunktB() {
    int nr_numbers;
    cout << "=============Subpunkt b.================" << endl;
    cout << "Number of numbers in array = ";
    cin >> nr_numbers;

    // falls es kein Anfangsarray gibt
    if (nr_numbers <= 0) {
        cout << "Kein Sub-array";
        return;
    }

    // Lesen der Zahlen in array
    int numbers[nr_numbers];
    for (int index = 0; index < nr_numbers; index++) {
        cout << "Zahl " << index + 1 << " = ";
        cin >> numbers[index];
    }

    // bestimmen der starting_index und max_length
    int starting_index = start_longest_seq(numbers, nr_numbers);

    // druckt das Sub-array
    for (int index = starting_index; index < starting_index + nr_numbers; index++)
        cout << numbers[index] << ' ';
}


int main() {
    subpunktA();
    subpunktB();
}
