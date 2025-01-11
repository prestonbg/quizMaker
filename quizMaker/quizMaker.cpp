#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

void createTest() {
    string testName;
    cout << "Enter the test name: ";
    cin.ignore();
    getline(cin, testName);

    ofstream outFile(testName + ".txt");
    if (!outFile) {
        cerr << "Failed to create the test file!" << endl;
        return;
    }

    int questionCount;
    cout << "Enter the number of questions: ";
    cin >> questionCount;
    cin.ignore();

    for (int i = 1; i <= questionCount; ++i) {
        string question;
        string correctAnswer;
        cout << "Enter question " << i << ": ";
        getline(cin, question);
        cout << "Enter the correct answer for question " << i << ": ";
        getline(cin, correctAnswer);

        outFile << question << "\n" << correctAnswer << "\n";
    }

    outFile.close();
    cout << "Test \"" << testName << "\" created successfully!" << endl;
}

void takeTest() {
    string testName;
    cout << "Enter the test name to take: ";
    cin.ignore();
    getline(cin, testName);

    ifstream inFile(testName + ".txt");
    if (!inFile) {
        cerr << "Failed to open the test file!" << endl;
        return;
    }

    vector<pair<string, string>> questions;
    string question, correctAnswer;
    while (getline(inFile, question) && getline(inFile, correctAnswer)) {
        questions.emplace_back(question, correctAnswer);
    }
    inFile.close();

    int score = 0;
    for (const auto& q : questions) {
        string userAnswer;
        cout << q.first << endl;
        cout << "Your answer: ";
        getline(cin, userAnswer);

        if (userAnswer == q.second) {
            cout << "Correct!" << endl;
            ++score;
        }
        else {
            cout << "Wrong. Correct answer: " << q.second << endl;
        }
    }

    cout << "Your score: " << score << " out of " << questions.size() << endl;
}

void deleteTest() {
    string testName;
    cout << "Enter the test name to delete: ";
    cin.ignore();
    getline(cin, testName);

    if (remove((testName + ".txt").c_str()) == 0) {
        cout << "Test \"" << testName << "\" deleted successfully!" << endl;
    }
    else {
        cerr << "Failed to delete test \"" << testName << "\"!" << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Create a test\n";
        cout << "2. Take a test\n";
        cout << "3. Delete a test\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createTest();
            break;
        case 2:
            takeTest();
            break;
        case 3:
            deleteTest();
            break;
        case 4:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);

    return 0;
}