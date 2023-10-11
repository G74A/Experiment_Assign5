// CISC230 - Task List 230 - Experiment Assign5
// Gail Anderson 

// Standard libraries
#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

// *** Add any additional #include's you need here

using namespace std;


// Prototypes for support functions
int get_int(const string& prompt);
void load_tasks(list<string>& tasks);
void save_tasks(list<string>& tasks);

// Prototypes for task management functions
void add_task(list<string>& tasks);
void delete_task(list<string>& tasks);
void insert_task(list<string>& tasks);
void move_task(list<string>& tasks);
void print_tasks(const list<string>& tasks);

// main - Creates a list of strings for storing tasks. Loads saved tasks
// from file tasklist.txt. Presents a menu for managing the task list,
// calling the corresponding functions. Prior to exit, saves all tasks to
// file tasklist.txt.


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

// get_int - Prompts for and inputs and integer. Ensures that an integer is
// entered and handles invalid integer input.
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

// load_tasks - Loads the task list saved in file tasklist.txt. Assumes the
// parameter given is an empty list.
void load_tasks(list<string>& tasks) {
    ifstream f("tasklist.txt");
    string task;
    while (getline(f, task))
        tasks.push_back(task);
}

// write_task - Function object to facilitate saving tasks to file
// tasklist.txt. Used by function save_tasks.
class write_task {
public:
    ofstream& f;
    write_task(ofstream& file) : f(file) {}
    void operator() (const string& task) { f << task << endl; }
};

// save_tasks - Writes tasks to file tasklist.txt. Iterates through
// the task list using the for_each algorithm, and uses the write_task
// function object to write each task.
void save_tasks(list<string>& tasks) {
    ofstream f("tasklist.txt");
    for_each(tasks.begin(), tasks.end(), write_task(f));
}

// add_task - Adds a task to the task list. Prompts for and inputs
// a task (string) and adds the task to the end of the task list.
void add_task(list<string>& tasks) {
    string task;
    cout << "Enter task: ";
    getline(cin, task);
    tasks.push_back(task);
}

// *** Add your code below this line


// Template class for managing task lists
template <typename T>
class TaskList {
public:
    TaskList(const std::string& filename) : filename_(filename) {
        load_tasks(const T&);
    }

    void print() {
        printTasks(0);
    }

    void insert(const T& task) {
        task_.push_back(task);
        saveTasks();
    }

    void move(int fromIndex, int toIndex) {
        if (fromIndex >= 0 && fromIndex < taskList_.size() &&
            toIndex >= 0 && toIndex < tasks_.size()) {
            T task = tasks_[fromIndex];
            tasks_.erase(tasks_.begin() + fromIndex);
            tasks_.insert(tasks_.begin() + toIndex, task);
            saveTasks();
        }
    }

    void delete(int index) {
        if (index >= 0 && index < tasks_.size()) {
            tasks_.erase(tasks_.begin() + index);
            saveTasks();
        }
    }

private:
    std::string filename_;
    std::vector<T> tasks_;

    // void loadTasks() {
    //     std::ifstream file(filename_);
    //     if (file.is_open()) {
    //         T task;
    //         while (file >> task) {
    //             tasks_.push_back(task);
    //         }
    //         file.close();
    //     }
    // }

    void printTasks(int index) {
        if (index < tasks_.size()) {
            std::cout << tasks_[index] << std::endl;
            printTasks(index + 1);
        }
    }

//     void saveTasks() {
//         std::ofstream file(filename_);
//         if (file.is_open()) {
//             for (const T& task : tasks_) {
//                 file << task << "\n";
//             }
//             file.close();
//         }
//     }
// };


    TaskList<std::string> taskList("tasklist.txt");

    int choice;
    while (true) {
        std::cout << "1. Print Tasks\n2. Insert Task\n3. Move Task\n4. Delete Task\n5. Exit\n";
        std::cin >> choice;

        if (choice == 1) {
            taskList.print();
        } else if (choice == 2) {
            std::string task;
            std::cout << "Enter task: ";
            std::cin >> task;
            taskList.insert(task);
        } else if (choice == 3) {
            int from, to;
            std::cout << "Enter index to move from: ";
            std::cin >> from;
            std::cout << "Enter index to move to: ";
            std::cin >> to;
            taskList.move(from, to);
        } else if (choice == 4) {
            int index;
            std::cout << "Enter index to delete: ";
            std::cin >> index;
            taskList.delete(index);
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid choice. Try again." << std::endl;
        }
    }

    return 0;



// 
// 
//void delete_task(list<string>& tasks) {
    // Prompt for a task number
    // If task number is valid:
    //  delete task from the list
    // Else:
    //  issue an error message
//}

//void insert_task(list<string>& tasks) {
    // Prompt for a task number
    // If task number is valid:
    //  prompt for and input task
    //  insert task at the requested position
    // Else:
    //  issue an error message
//}

//void move_task(list<string>& tasks) {
    // Prompt for a task number
    // If task number is valid:
    //  Prompt for new position for task
    //  If new position is valid:
    //   move task to new position
    //  Else: 
    //   issue an error message
    // Else:
    //  issue an error message
//}

// void print_tasks(const list<T>& tasks) {
//     // Print all tasks with position number, for example:
//     //  1. Pick up milk
//     //  2. Cut the grass
//     int count = 1;
//     for (const T& task : tasks) {
//         cout << count++ << " ." << task << endl;
//     }   
// }

// void print_tasks(const list<T>& tasks) {   
//     int count = 1; 
//     ofstream f("tasklist.txt");
//     for_each(tasks.begin(), tasks.end(), print_tasks(f));
};