#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

// Cross-platform getch implementation
char getChar() {
#ifdef _WIN32
    return _getch();
#else
    struct termios oldattr, newattr;
    char ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
#endif
}

// Write string to file
bool writeToFile(const string& filename, const string& content) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing!" << endl;
        return false;
    }
    file << content;
    file.close();
    return true;
}

// Read string from file
string readFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

// Display content with cursor
void displayWithCursor(const string& content, int cursorPos) {
    cout << "\n--- Content (Cursor at position " << cursorPos << ") ---" << endl;
    
    for (int i = 0; i < content.length(); i++) {
        if (i == cursorPos) {
            cout << "|"; // Cursor marker
        }
        cout << content[i];
    }
    
    if (cursorPos == content.length()) {
        cout << "|"; // Cursor at end
    }
    
    cout << endl;
    cout << "---------------------------------------------------" << endl;
}

// Cursor-based editor
void cursorEditor(const string& filename) {
    string content = readFromFile(filename);
    int cursorPos = content.length(); // Start at end
    
    cout << "\n========== CURSOR EDITOR MODE ==========" << endl;
    cout << "Commands:" << endl;
    cout << "  Left Arrow (a)  - Move cursor left" << endl;
    cout << "  Right Arrow (d) - Move cursor right" << endl;
    cout << "  Home (h)        - Move to start" << endl;
    cout << "  End (e)         - Move to end" << endl;
    cout << "  Insert (i)      - Insert text at cursor" << endl;
    cout << "  Delete (x)      - Delete character at cursor" << endl;
    cout << "  Backspace (b)   - Delete character before cursor" << endl;
    cout << "  Save (s)        - Save changes" << endl;
    cout << "  Quit (q)        - Exit without saving" << endl;
    cout << "=========================================" << endl;
    
    while (true) {
        displayWithCursor(content, cursorPos);
        cout << "\nEnter command: ";
        
        char cmd = getChar();
        cout << cmd << endl;
        
        switch (cmd) {
            case 'a': // Move left
                if (cursorPos > 0) {
                    cursorPos--;
                    cout << "Moved cursor left" << endl;
                } else {
                    cout << "Already at start!" << endl;
                }
                break;
                
            case 'd': // Move right
                if (cursorPos < content.length()) {
                    cursorPos++;
                    cout << "Moved cursor right" << endl;
                } else {
                    cout << "Already at end!" << endl;
                }
                break;
                
            case 'h': // Home
                cursorPos = 0;
                cout << "Moved to start" << endl;
                break;
                
            case 'e': // End
                cursorPos = content.length();
                cout << "Moved to end" << endl;
                break;
                
            case 'i': { // Insert
                cout << "Enter text to insert: ";
                string textToInsert;
                getline(cin, textToInsert);
                content.insert(cursorPos, textToInsert);
                cursorPos += textToInsert.length();
                cout << "Text inserted!" << endl;
                break;
            }
            
            case 'x': // Delete at cursor
                if (cursorPos < content.length()) {
                    content.erase(cursorPos, 1);
                    cout << "Character deleted!" << endl;
                } else {
                    cout << "Nothing to delete!" << endl;
                }
                break;
                
            case 'b': // Backspace
                if (cursorPos > 0) {
                    content.erase(cursorPos - 1, 1);
                    cursorPos--;
                    cout << "Character deleted!" << endl;
                } else {
                    cout << "Nothing to delete!" << endl;
                }
                break;
                
            case 's': // Save
                writeToFile(filename, content);
                cout << "Changes saved!" << endl;
                break;
                
            case 'q': // Quit
                cout << "Exiting cursor editor..." << endl;
                return;
                
            default:
                cout << "Invalid command!" << endl;
        }
    }
}

// Display menu
void displayMenu() {
    cout << "\n========== FILE STRING EDITOR ==========" << endl;
    cout << "1. View current content" << endl;
    cout << "2. Write/Overwrite entire content" << endl;
    cout << "3. Append text to end" << endl;
    cout << "4. Insert text at position" << endl;
    cout << "5. Replace text at position" << endl;
    cout << "6. Delete text from position" << endl;
    cout << "7. Replace substring" << endl;
    cout << "8. Delete all occurrences of substring" << endl;
    cout << "9. Clear entire file" << endl;
    cout << "10. CURSOR EDITOR MODE (Interactive)" << endl;
    cout << "0. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    string filename = "mytext.txt";
    string content;
    int choice;
    
    cout << "Welcome to File String Editor!" << endl;
    cout << "Working with file: " << filename << endl;
    
    // Check if file exists, if not create empty
    ifstream checkFile(filename);
    if (!checkFile.is_open()) {
        writeToFile(filename, "");
        cout << "Created new file: " << filename << endl;
    } else {
        checkFile.close();
    }
    
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1: {
                content = readFromFile(filename);
                cout << "\n--- Current Content ---" << endl;
                if (content.empty()) {
                    cout << "[File is empty]" << endl;
                } else {
                    cout << content << endl;
                    cout << "\nLength: " << content.length() << " characters" << endl;
                }
                break;
            }
            
            case 2: {
                cout << "\nEnter new content (press Enter to finish):" << endl;
                string newContent;
                getline(cin, newContent);
                writeToFile(filename, newContent);
                cout << "Content written successfully!" << endl;
                break;
            }
            
            case 3: {
                content = readFromFile(filename);
                cout << "\nEnter text to append:" << endl;
                string textToAppend;
                getline(cin, textToAppend);
                content += textToAppend;
                writeToFile(filename, content);
                cout << "Text appended successfully!" << endl;
                break;
            }
            
            case 4: {
                content = readFromFile(filename);
                cout << "\nCurrent content: " << content << endl;
                cout << "Enter position to insert (0 to " << content.length() << "): ";
                int pos;
                cin >> pos;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if (pos < 0 || pos > content.length()) {
                    cout << "Invalid position!" << endl;
                    break;
                }
                
                cout << "Enter text to insert: ";
                string textToInsert;
                getline(cin, textToInsert);
                
                content.insert(pos, textToInsert);
                writeToFile(filename, content);
                cout << "Text inserted successfully!" << endl;
                break;
            }
            
            case 5: {
                content = readFromFile(filename);
                cout << "\nCurrent content: " << content << endl;
                cout << "Enter position to start replacement: ";
                int pos;
                cin >> pos;
                
                cout << "Enter length of text to replace: ";
                int length;
                cin >> length;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                if (pos < 0 || pos >= content.length()) {
                    cout << "Invalid position!" << endl;
                    break;
                }
                
                cout << "Enter new text: ";
                string newText;
                getline(cin, newText);
                
                content.replace(pos, length, newText);
                writeToFile(filename, content);
                cout << "Text replaced successfully!" << endl;
                break;
            }
            
            case 6: {
                content = readFromFile(filename);
                cout << "\nCurrent content: " << content << endl;
                cout << "Enter position to start deletion: ";
                int pos;
                cin >> pos;
                
                cout << "Enter length of text to delete: ";
                int length;
                cin >> length;
                
                if (pos < 0 || pos >= content.length()) {
                    cout << "Invalid position!" << endl;
                    break;
                }
                
                content.erase(pos, length);
                writeToFile(filename, content);
                cout << "Text deleted successfully!" << endl;
                break;
            }
            
            case 7: {
                content = readFromFile(filename);
                cout << "\nCurrent content: " << content << endl;
                cout << "Enter text to find: ";
                string oldText;
                getline(cin, oldText);
                
                cout << "Enter replacement text: ";
                string newText;
                getline(cin, newText);
                
                size_t pos = content.find(oldText);
                if (pos != string::npos) {
                    content.replace(pos, oldText.length(), newText);
                    writeToFile(filename, content);
                    cout << "Text replaced successfully!" << endl;
                } else {
                    cout << "Text not found!" << endl;
                }
                break;
            }
            
            case 8: {
                content = readFromFile(filename);
                cout << "\nCurrent content: " << content << endl;
                cout << "Enter text to delete (all occurrences): ";
                string textToDelete;
                getline(cin, textToDelete);
                
                size_t pos = 0;
                int count = 0;
                while ((pos = content.find(textToDelete, pos)) != string::npos) {
                    content.erase(pos, textToDelete.length());
                    count++;
                }
                
                if (count > 0) {
                    writeToFile(filename, content);
                    cout << "Deleted " << count << " occurrence(s) successfully!" << endl;
                } else {
                    cout << "Text not found!" << endl;
                }
                break;
            }
            
            case 9: {
                cout << "\nAre you sure you want to clear the entire file? (y/n): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    writeToFile(filename, "");
                    cout << "File cleared successfully!" << endl;
                } else {
                    cout << "Operation cancelled." << endl;
                }
                break;
            }
            
            case 10: {
                cursorEditor(filename);
                break;
            }
            
            case 0: {
                cout << "\nExiting... Goodbye!" << endl;
                return 0;
            }
            
            default:
                cout << "\nInvalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}