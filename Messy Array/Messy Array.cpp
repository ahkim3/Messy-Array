/*
Name: Andrew Kim
Date: January 27, 2021
Program: Messy Array

I hereby certify that this program represents my
work and that the design and logic was completed
without outside assistance.

Signature: Andrew Kim
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int SIZE = 20;

void generateNumbers(int[]);
void askKey(int, int[]);
int linearSearch(int[], int, int&, int&, int&);
void bubbleSort(int[], int&, int&, int&);
int binarySearch(int[], int, int&, int&, int&, int, int);
void printResults(int, int, int, int, int);


int main()
{
    char repeat = 'y', newArray;
    int numbers[SIZE], menuSelection;

    // Sets the seed to be used by rand() later to generate random numbers
    srand(time(NULL));

    do
    {
        generateNumbers(numbers);

        do
        {
            newArray = 'n';

            // Prompts user with menu to identify intended search algorithm
            system("cls");
            cout << "Algorithm Options:" << endl;
            cout << "(1) Basic search" << endl;
            cout << "(2) Bubble sort" << endl;
            cout << "(3) Binary search" << endl;
            cout << "(4) Exit" << endl << endl;
            cout << "Please enter the corresponding number to your desired "
                << "algorithm: ";
            cin >> menuSelection;
            cout << endl;

            // Performs corresponding algorithm to user's selection
            switch (menuSelection)
            {
            case 1: // Basic search
            case 2: // Bubble sort
            case 3: // Binary search
                askKey(menuSelection, numbers);
                break;
            case 4: // Exit
                repeat = 'n';
                newArray = 'y'; // Prevents prompting for new array
                break;
            default:
                cout << "That was not a valid option. Please try again." 
                    << endl << endl;
                newArray = 'd'; // Prevents prompting for new array
                system("pause");
            }

            /* Asks user if they would like to generate a new array before 
            prompting menu again */
            if ((newArray != 'y') && (newArray != 'd'))
            {
                cout << endl 
                    << "Would you like to generate a new array? (y/n): ";
                cin >> newArray;
                cin.get();
                repeat = tolower(repeat);
                system("cls");
            }
        } while ((newArray != 'y') && (newArray != 'd'));

        // Cleanup
        cout << endl;
        system("cls");
    } while (repeat != 'n');
}

/* Generates an array with SIZE elements containing unique random numbers that
conform to [1-60] */
void generateNumbers(int numbers[])
{
    fstream outputFile;
    int potentialNum;
    bool assigned;

    // Assigns SIZE random numbers that conform to [1-60]
    for (int i = 0; i < SIZE; i++)
    {
        assigned = false;
        while (!assigned)
        {
            assigned = true;
            // Generates new random number
            potentialNum = (rand() % 60) + 1;

            // Checks to see if number is unique before assigning to array
            for (int j = 0; j < i; j++)
            {
                if (numbers[j] == potentialNum)
                    assigned = false;
            }
        }
        numbers[i] = potentialNum;
    }

    // Outputs array to file
    outputFile.open("generated numbers.txt", ios::out);
    if (!outputFile)
        cout << "Something went wrong. File was not created." << endl;
    else
    {
        for (int i = 0; i < SIZE; i++)
            outputFile << numbers[i] << endl;
        outputFile.close();
    }

    return;
}

/* Asks user to enter a key value to search for, calls for the previously
requested search function, and calls print function. */
void askKey(int searchType, int numbers[])
{
    int key, index = -1, assignments = 0, additions = 0, comparisons = 0, 
        min = 0, max = 19;

    // Asks user to input number to search for
    cout << "Please enter a number to search for: ";
    cin >> key;
    cout << endl;

    switch (searchType)
    {
    case 1: // Basic search
        index = linearSearch(numbers, key, assignments, additions,
            comparisons);
        break;
    case 2: // Bubble sort
        bubbleSort(numbers, assignments, additions, comparisons);
        index = linearSearch(numbers, key, assignments, additions,
            comparisons);
        break;
    case 3: // Binary search
        bubbleSort(numbers, assignments, additions, comparisons);
        index = binarySearch(numbers, key, assignments, additions, 
            comparisons, min, max);
        break;
    default: // searchType is an invalid value
        cout << "Something went wrong. searchType is an invalid value." 
            << endl;
    }

    printResults(searchType, index, assignments, additions, comparisons);
    
    return;
}

// Performs linear (basic) search. Returns index of key value.
int linearSearch(int numbers[], int key, int& assignments, int& additions, 
    int& comparisons)
{
    bool found = false, end = false;
    int index = -1; // Index is set to -1 when not found

    // Tracks work done
    assignments += 3;

    // Searches for number incrementally
    while (!found && !end)
    {
        if (numbers[index] == key) // Found number
        {
            found = true;

            // Tracks work done
            assignments++;
            comparisons++;
        }
        else if (index >= SIZE) // Could not find number in array, terminate
        {
            end = true;
            index = -1; // Sets index back to -1 if not found

            // Tracks work done
            assignments += 2;
            comparisons += 2; // Adds two to account for if else chain
        }
        else // Could not find number at index, keep searching
        {
            index++;

            // Tracks work done
            assignments++;
            additions++;
            comparisons += 2; // Adds two to account for if else chain
        }
    }

    return index;
}

/* Performs a bubble sort algorithm, swapping values left to right in
ascending order. */
void bubbleSort(int numbers[], int& assignments, int& additions,
    int& comparisons)
{
    int temp;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE - i - 1; j++)
        {
            /* Swaps adjacent elements if left side is incorrectly greater than
            right side */
            if (numbers[j] > numbers[j + 1])
            {
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
                
                comparisons++; // Tracks work done
            }
            
            // Tracks work done
            assignments++;
            additions++;
            comparisons++;
        }

        // Tracks work done
        assignments++;
        additions++;
        comparisons++;
    }

    assignments += 2; // Tracks work done
    
    return;
}

// Performs a binary search on sorted array. Returns index of key value.
int binarySearch(int numbers[], int key, int& assignments, 
    int& additions, int& comparisons, int min, int max)
{   
    comparisons++; // Tracks work done

    if (min <= max)
    {
        // Finds midpoint of indices
        int mid = (min + max) / 2;
        
        // Tracks work done
        assignments++; 
        additions++;

        if (numbers[mid] == key) // Number found
        {
            comparisons++; // Tracks work done
            return mid;
        }
        else if (numbers[mid] < key) // Midpoint is too low
        {
            min = mid + 1;

            // Tracks work done
            assignments++;
            additions++;
            comparisons += 2;

            return binarySearch(numbers, key, assignments, additions, 
                comparisons, min, max);
        }
        else if (numbers[mid] > key) // Midpoint is too high
        {
            max = mid - 1;

            // Tracks work done
            assignments++;
            comparisons += 3;

            return binarySearch(numbers, key, assignments, additions, 
                comparisons, min, max);
        }
    }

    // Number was not found
    return -1;
}

// Prints results to user, including index (if applicable) and work performed
void printResults(int searchType, int index, int assignments, int additions, 
    int comparisons)
{
    // Displays if number was found to user, and if so, at what index
    if (index == -1)
        cout << "Your number could not be found.";
    else
        cout << "Your number was found at index " << index << ".";
    
    // Displays work performed to user
    cout << endl << endl;
    cout << "Assignments performed: " << assignments << endl;
    cout << "Additions performed: " << additions << endl;
    cout << "Comparisons performed: " << comparisons << endl;

    return;
}
