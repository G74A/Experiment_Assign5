//Assignment 5
//Gail Anderson

#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

using namespace std;

// Prototypes for support functions
int get_int(const string& prompt);
void load_tasks(list<string>& tasks);
void save_tasks(const list<string>& tasks);

// Prototypes for task management functions
void add_task(list<string>& tasks);
void delete_task(list<string>& tasks);
void insert_task(list<string>& tasks);
void move_task(list<string>& tasks);
void print_tasks(const list<string>& tasks);

int main () {
    list<string> tasks;
    load_tasks(tasks);

    cout << "Task List 230\n";

    bool done = false;
    do {
        cout << endl;
        cout << "1. Print Task List\n";
        cout << "2. Add a Task (at end)\n";
        cout << "3. Insert Task (at position)\n";
        cout << "4. Move a Task\n";
        cout << "5. Delete a Task\n";
        cout << "9. Exit\n\n";

        switch (get_int("Enter option: ")) {
            case 1: print_tasks(tasks); break;
            case 2: add_task(tasks); break;
            case 3: insert_task(tasks); break;
            case 4: move_task(tasks); break;
            case 5: delete_task(tasks); break;
            case 9: done = true;
        }
    } while (!done);

    save_tasks(tasks);
}

int get_int(const string& prompt) {
    cout << prompt;
    int input;
    while (!(cin >> input)) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "An integer is expected: ";
    }
    cin.ignore(INT_MAX, '\n');
    return input;
}

void load_tasks(list<string>& tasks) {
    ifstream file("tasklist.txt");
    string task;
    while (getline(file, task))
        tasks.push_back(task);
}

void save_tasks(const list<string>& tasks) {
    ofstream file("tasklist.txt");
    for (const string& task : tasks) {
        file << task << endl;
    }
}

void add_task(list<string>& tasks) {
    string task;
    cout << "Enter task: ";
    getline(cin, task);
    tasks.push_back(task);
}

void delete_task(list<string>& tasks) {
    int position = get_int("Enter the task number to delete: ");
    if (position >= 1 && position <= tasks.size()) {
        auto it = tasks.begin();
        advance(it, position - 1);
        tasks.erase(it);
    } else {
        cout << "Invalid task number. Task not deleted." << endl;
    }
}

void insert_task(list<string>& tasks) {
    int position = get_int("Enter the position to insert the task: ");
    if (position < 1 || position > tasks.size() + 1) {
        cout << "Invalid position. Task not inserted." << endl;
        return;
    }

    string task;
    cout << "Enter task: ";
    getline(cin, task);

    auto it = tasks.begin();
    advance(it, position - 1);
    tasks.insert(it, task);
}

void move_task(list<string>& tasks) {
    int fromPosition = get_int("Enter the position of the task to move: ");
    int toPosition = get_int("Enter the new position for the task: ");

    if (fromPosition < 1 || toPosition < 1 || fromPosition > tasks.size() || toPosition > tasks.size()) {
        cout << "Invalid positions. Task not moved." << endl;
        return;
    }

    auto fromIt = tasks.begin();
    advance(fromIt, fromPosition - 1);

    auto toIt = tasks.begin();
    advance(toIt, toPosition - 1);

    tasks.insert(toIt, *fromIt);
    tasks.erase(fromIt);
}

void print_tasks(const list<string>& tasks) {
    int count = 1;
    for (const string& task : tasks) {
        cout << count << ". " << task << endl;
        count++;
    }
}
