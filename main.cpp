// CISC230 - Task List 230 - Experiment Assign5
// Gail Anderson 

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

using namespace std;

// Function object to facilitate saving tasks to file
class SaveTasks {
public:
    ofstream& file;
    SaveTasks(ofstream& f) : file(f) {}
    void operator() (const string& task) { file << task << endl; }
};

// Template class for managing task lists
template <typename T>
class TaskList {
public:
    TaskList(const std::string& file) : filename_(file) {
        load_tasks();
    }

    void print_tasks() {
        print_task_list();
    }

    void insert_task(const T& task) {
        tasks_.push_back(task);
        save_tasks();
    }

    void move_task(int fromIndex, int toIndex) {
        if (fromIndex >= 0 && fromIndex < tasks_.size() &&
            toIndex >= 0 && toIndex < tasks_.size()) {
            auto task = tasks_.begin();
            advance(task, fromIndex);
            T task_to_move = *task;
            tasks_.erase(task);
            task = tasks_.begin();
            advance(task, toIndex);
            tasks_.insert(task, task_to_move);
            save_tasks();
        } else {
            cout << "Invalid indices. Move operation failed." << endl;
        }
    }

    void delete_task(int index) {
        if (index >= 0 && index < tasks_.size()) {
            auto task = tasks_.begin();
            advance(task, index);
            tasks_.erase(task);
            save_tasks();
        } else {
            cout << "Invalid index. Delete operation failed." << endl;
        }
    }

private:
    std::string filename_;
    list<T> tasks_;

    void load_tasks() {
        std::ifstream file(filename_);
        if (file.is_open()) {
            T task;
            while (getline(file, task)) {
                tasks_.push_back(task);
            }
            file.close();
        }
    }

    void print_task_list() {
        int index = 1;
        for (const T& task : tasks_) {
            cout << index << ". " << task << endl;
            index++;
        }
    }

    void save_tasks() {
        ofstream file(filename_);
        if (file.is_open()) {
            for (const T& task : tasks_) {
                file << task << endl;
            }
            file.close();
        }
    }
};

int main() {
    TaskList<string> task_list("tasklist.txt");

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
            case 1: task_list.print_tasks(); break;
            case 2: add_task(task_list); break;
            case 3: insert_task(task_list); break;
            case 4: move_task(task_list); break;
            case 5: delete_task(task_list); break;
            case 9: done = true;
        }
    } while (!done);

    return 0;
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