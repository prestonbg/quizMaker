#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
using namespace std;

struct Question {
    string text;
    vector<string> options;
    int correctAnswer;
};

struct Test {
    string name;
    vector<Question> questions;
};

Test createTest() {
    Test test;
    cout << "Enter the name of the test: ";
    cin.ignore();
    getline(cin, test.name);
    int questionCount;
    cout << "How many questions will be on the test? ";
    cin >> questionCount;

    for (int i = 0; i < questionCount; i++) {
        Question q;
        while (true) {
            cout << "Enter the text of the question " << i + 1 << ": ";
            cin.ignore();
            getline(cin, q.text);
            if (q.text == test.name) {
                cout << "The text of the question cannot be the same as the test name. Try again.\n";
            }
            else {
                break;
            }
        }

        int optionCount;
        cout << "How many answer choices are there? ";
        cin >> optionCount;
        q.options.resize(optionCount);

        for (int j = 0; j < optionCount; j++) {
            cout << "Enter an answer choice " << j + 1 << ": ";
            cin.ignore();
            getline(cin, q.options[j]);
        }

        cout << "Enter the number of the correct answer: ";
        cin >> q.correctAnswer;
        q.correctAnswer--;

        test.questions.push_back(q);
    }
    return test;
}

void takeTest(const Test& test) {
    cout << "Passing the test: " << test.name << endl;
    int score = 0;

    for (size_t i = 0; i < test.questions.size(); i++) {
        cout << "Question " << i + 1 << ": " << test.questions[i].text << endl;
        for (size_t j = 0; j < test.questions[i].options.size(); j++) {
            cout << j + 1 << ". " << test.questions[i].options[j] << endl;
        }
        int answer;
        cout << "Your answer: ";
        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (answer - 1 == test.questions[i].correctAnswer) {
            score++;
        }
    }
    cout << "Your result: " << score << " from " << test.questions.size() << endl;
}

void saveTestsToFile(const vector<Test>& tests, const string& filename) {
    ofstream file(filename, ios::out);
    if (!file) {
        cerr << "Error saving tests to file." << endl;
        return;
    }

    file << tests.size() << endl;
    for (const auto& test : tests) {
        file << test.name << endl;
        file << test.questions.size() << endl;
        for (const auto& question : test.questions) {
            file << question.text << endl;
            file << question.options.size() << endl;
            for (const auto& option : question.options) {
                file << option << endl;
            }
            file << question.correctAnswer << endl;
        }
    }
}

vector<Test> loadTestsFromFile(const string& filename) {
    vector<Test> tests;
    ifstream file(filename, ios::in);
    if (!file) {
        return tests; // Return empty list if file does not exist
    }

    size_t testCount;
    file >> testCount;
    file.ignore();

    for (size_t i = 0; i < testCount; i++) {
        Test test;
        getline(file, test.name);

        size_t questionCount;
        file >> questionCount;
        file.ignore();

        for (size_t j = 0; j < questionCount; j++) {
            Question question;
            getline(file, question.text);

            size_t optionCount;
            file >> optionCount;
            file.ignore();

            question.options.resize(optionCount);
            for (size_t k = 0; k < optionCount; k++) {
                getline(file, question.options[k]);
            }

            file >> question.correctAnswer;
            file.ignore();

            test.questions.push_back(question);
        }

        tests.push_back(test);
    }
    return tests;
}

void deleteTest(vector<Test>& tests) {
    if (tests.empty()) {
        cout << "There are no tests to delete." << endl;
        return;
    }

    cout << "Available tests:" << endl;
    for (size_t i = 0; i < tests.size(); i++) {
        cout << i + 1 << ". " << tests[i].name << endl;
    }

    int choice;
    cout << "Enter the number of the test to delete: ";
    cin >> choice;

    if (choice >= 1 && choice <= tests.size()) {
        tests.erase(tests.begin() + choice - 1);
        cout << "Test deleted." << endl;
    }
    else {
        cout << "Invalid choice." << endl;
    }
}

int main() {
    vector<Test> tests = loadTestsFromFile("tests.txt");
    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Create a test\n";
        cout << "2. Take a test\n";
        cout << "3. Delete a test\n";
        cout << "4. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice == 1) {
            tests.push_back(createTest());
        }
        else if (choice == 2) {
            if (tests.empty()) {
                cout << "There are no available tests to take." << endl;
            }
            else {
                cout << "Available tests:" << endl;
                for (size_t i = 0; i < tests.size(); i++) {
                    cout << i + 1 << ". " << tests[i].name << endl;
                }
                int testChoice;
                cout << "Select a test: ";
                cin >> testChoice;
                if (testChoice >= 1 && testChoice <= tests.size()) {
                    takeTest(tests[testChoice - 1]);
                }
                else {
                    cout << "Invalid choice." << endl;
                }
            }
        }
        else if (choice == 3) {
            deleteTest(tests);
        }
        else if (choice == 4) {
            saveTestsToFile(tests, "tests.txt");
            break;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    }
    return 0;
}
