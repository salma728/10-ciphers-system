#include <bits/stdc++.h>
using namespace std;

//This function is to represent the menu to let the user choose what he wants to do
void menu1()
{
    cout <<"\nWelcome to the encryption and decryption program!\n"
           "Choose what you want to do\n"
           "1 - Encrypt a message\n"
           "2 - Decrypt a message\n"
           "3 - Exit the program\n"
           "Enter your Choice: ";
}

//This function is to represent the menu to let the user choose what he wants to do
void menu2() {
    cout << "Choose the cipher that you want\n"
            "1- Affine Cipher\n"
            "2- Route Cipher\n"
            "3- Atbash Cipher\n"
            "4- Vignere Cipher\n"
            "5- Baconian Cipher\n"
            "6- Simple Substitution Cipher\n"
            "7- Polybius Cipher\n"
            "8- Morse Cipher\n"
            "9- Xor Cipher\n"
            "10- Rail fence Cipher\n"
            "Enter your choice: ";
}

// Function to get user choice with validation
int get_User_Choice(int min, int max) {

    // Variable to store user input as a string
    string user_choice;
    // Variable to store converted integer choice
    int choice;

    // Loop until a valid choice is entered
    while (true) {
        // Read user input as a string
        cin >> user_choice;
        try {
            // Attempt to convert the string input to an integer
            choice = stoi(user_choice);
            // Check if the converted integer is within the valid range
            if (choice < min || choice > max) {
                cout << "Error, please choose a valid choice" <<endl;
            } else {
                break; // Break out of the loop if the choice is valid
            }
        }
            // Handle invalid input not an integer
        catch (const invalid_argument &e) {
            cout << "Error, please choose a valid choice"<<endl;
        }
            // Handle input out of range
        catch (const out_of_range &e) {
            cout << "Error, please choose a valid choice" <<endl;
        }
    }
    // Return the valid choice
    return choice;
}
//***************************************AFFINE CIPHER FUNCTIONS******************************************************//
//This function making Affine cipher
void Affine_Cipher(){
    int a, b, c;
    cout << "Welcome to Affine cipher Program" << endl;
    cout << "Input three parameters a, b, and c: ";
    cin >> a >> b >> c;

    while ((a * c) % 26 != 1) {
        cout << "Please input parameters that satisfy the condition (a * c) mod 26 = 1\n";
        cout << "Input three parameters a, b, and c: ";
        cin >> a >> b >> c;
    }
    cout << "Enter the message you want to cipher: ";
    cin.ignore();
    string message;
    getline(cin, message);

    string encrypted_message = " ";
    for (char &ch : message) {
        if (isalpha(ch)) { // Check if character is alphabetic
            if (islower(ch)) {
                int x = ch - 'a';
                ch = ((a * x + b) % 26) + 'a'; // Convert back to character
            } else if (isupper(ch)) {
                int x = ch - 'A';
                ch = ((a * x + b) % 26) + 'A'; // Convert back to character
            }
        }
        encrypted_message += ch;
    }
    cout << "Encrypted message: " << encrypted_message << endl;
}
//This function making Affine decipher
void Affine_deCipher() {
    int a, b, c;
    cout << "Welcome to Affine cipher Program" << endl;
    cout << "Input three parameters a, b, and c: ";
    cin >> a >> b >> c;


    // Validate parameters
    while ((a * c) % 26 != 1) {
        cout << "Please input parameters that satisfy the condition (a * c) mod 26 = 1\n";
        cout << "Input three parameters a, b, and c: ";
        cin >> a >> b >> c;
    }

    cout << "Enter the message you want to decipher: ";
    cin.ignore();
    string message;
    getline(cin, message);
    string decrypted_message = " ";
    for (char &ch : message) {
        if (isalpha(ch)) { // Check if character is alphabetic
            int y = ch - ((islower(ch)) ? 'a' : 'A');
            int inv_a = 1;
            while ((a * inv_a) % 26 != 1) {
                inv_a++;
            }
            int decrypted_char = inv_a * (y - b);
            decrypted_char = (decrypted_char % 26 + 26) % 26; // Handle negative result
            decrypted_message += decrypted_char + ((islower(ch)) ? 'a' : 'A');
        } else {
            decrypted_message += ch;
        }
    }

    cout << "Decrypted message: ";
    for (char &ch : decrypted_message) {
        cout << (char)tolower(ch);
    }
    cout << endl;

}

//***************************************ROUTE CIPHER FUNCTIONS******************************************************//


//This function making Route cipher
void Route_cipher(){

    // To store the message entered by the user
    string message;
    // To store the number of columns entered by the user
    int cols;

    // Get input from the user for the message and number of columns
    cout << "Enter the message you want to cipher: " << endl;
    getline(cin, message);

    //to get length of the message without spaces and special characters
    int len = 0, position = 0;
    while (position < message.size()) {
        if (!isalpha(message[position]))
            position++;
        else {
            len += 1;
            position++;
        }
    }

    cout << "Enter secret_key: ";
    cin >> cols;
    cout << endl;
    //get key validation
    while (cols<1 || cols >(len/2)){
        cout<<"Error,please choose a secret key greater than 1 and less than length/2"<<endl;
        cin>>cols;
    }

    // Calculate the number of rows based on the message length and the number of columns
    int rows = ceil(len / (float)(cols));


    // Create matrix to store the message
    string matrix[rows][cols];

    // store the message in the matrix
    int index = 0; // Initialize index to iterate over the message characters

    // Fill the matrix with characters from the message
    for (int i = 0; i < rows; ++i) // loop for rows
    {
        for (int j = 0; j < cols; ++j) //loop for columns
        {
            // Skip special characters and spaces in the message
            while (index < message.length() && !isalpha(message[index])) {
                index++;
            }
            //turns all characters to upper case
            if (index < message.length()) {
                matrix[i][j] = toupper(message[index++]); // Convert characters to uppercase and assign to the matrix

            } else {
                // If the message length is less than matrix size, fill remaining cells with 'X'
                matrix[i][j] = 'X';
            }
        }
    }

    // Print the cipher message by looping over the matrix in a clockwise direction
    cout << "The cipher message is: "<<endl;

    int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
    int direction = 0;

    // Loop through the matrix in a clockwise direction until all elements are visited
    while (top <= bottom && left <= right) {
        if (direction == 0) // Move from top right to bottom right
        {
            for (int i = top; i <= bottom; ++i) {
                cout << matrix[i][right];
            }
            right--; // move to the previous column
        }
        else if (direction == 1) // Move from bottom right to bottom left
        {
            for (int i = right; i >= left; --i) {
                cout << matrix[bottom][i];
            }
            bottom--; // move to the previous row
        }
        else if (direction == 2) // Move from bottom left to top left
        {
            for (int i = bottom; i >= top; --i) {
                cout << matrix[i][left];
            }
            left++; // move to next column
        }
        else if (direction == 3) // Move from top left to top right
        {
            for (int i = left; i <= right; ++i) {
                cout << matrix[top][i];
            }
            top++; // move to next row
        }
        direction = (direction + 1) % 4; // Change direction after each loop
    }
    cout << endl;

}

//This function making Route decipher
void Route_decipher(){
    string message; // To store the message entered by the user in route cipher
    int cols; // To store the number of columns entered by the user in route cipher

    // Get input from the user for the message and number of columns
    cout << "Enter the message you want to decipher: " << endl;
    getline(cin, message);

    // get length of the message without spaces and special characters
    int len = 0, position = 0;
    while (position < message.size()) {
        if (!isalpha(message[position]))
            position++;
        else {
            len += 1;
            position++;
        }
    }

    cout << "Enter secret_key: ";
    cin >> cols;
    cout << endl;
    //get key validation
    while (cols<1 || cols >(len/2)){
        cout<<"Error,please choose a secret key greater than 1 and less than length/2"<<endl;
        cin>>cols;
    }

    // Calculate the number of rows based on the message length and the number of columns
    int rows = ceil(len / (float)(cols));


    // Create matrix to store the message
    string matrix[rows][cols];

    int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
    int direction = 0;
    int index = 0;
    while (top <= bottom && left <= right) {
        if (direction == 0) // Move from top right to bottom right
        {
            for (int i = top; i <= bottom; ++i) {
                matrix[i][right] = message[index++];
            }
            right--; // move to the previous column
        }
        else if (direction == 1) // Move from bottom right to bottom left
        {
            for (int i = right; i >= left; --i) {
                matrix[bottom][i] = message[index++];
            }
            bottom--; // move to the previous row
        }
        else if (direction == 2) // Move from bottom left to top left
        {
            for (int i = bottom; i >= top; --i) {
                matrix[i][left] = message[index++];
            }
            left++; // move to next column
        }
        else if (direction == 3) // Move from top left to top right
        {
            for (int i = left; i <= right; ++i) {
                matrix[top][i] = message[index++];
            }
            top++; // move to next row
        }
        direction = (direction + 1) % 4; // Change direction after each loop
    }

    // Print the deciphered message
    cout << "The deciphered message is: ";
    // Print the deciphered message index by index
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j];
        }
    }
    cout << endl;

}
//***************************************Atbash CIPHER FUNCTIONS***************************************************//
// this function make atbash cipher and decipher
void Atbash_Cipher()
{
    int choice;
    cout<<"welcome to Atbash Cipher program\n"
          "choose which version do you want\n"
          "version 1\n"
          "version 2\n";
    choice = get_User_Choice(1,2);
    switch(choice){
        case 1:
        {
            string message;
            cout << "Enter the message to decrypt: ";
            cin.ignore();
            getline(cin, message);

            // Remove spaces and special characters
            string processed_message;
            for (char c : message) {
                if (isalpha(c)) {
                    processed_message += c;
                }
            }

            // Decrypt the message using Atbash cipher
            for (char& c : processed_message) {
                if (isupper(c)) {
                    c = 'Z' - (c - 'A');
                } else {
                    c = 'z' - (c - 'a');
                }
            }

            // Output the decrypted message
            cout << "Decrypted message: " << processed_message << endl;

            break;
        }
        case 2:
        {
            string message;
            cout << "Enter the message to encrypt: ";
            cin.ignore();
            getline(cin, message);

            // Remove spaces and special characters
            string processed_message;
            for (char c : message) {
                if (isalpha(c)) {
                    processed_message += c;
                }
            }

            // Encrypt the message using Atbash cipher
            string encrypted_message = "";
            for (char c : processed_message) {
                if (isupper(c)) {
                    if (c >= 'A' && c <= 'M') {
                        encrypted_message += 'M' - (c - 'A');
                    } else {
                        encrypted_message += 'Z' - (c - 'N');
                    }
                } else {
                    if (c >= 'a' && c <= 'm') {
                        encrypted_message += 'm' - (c - 'a');
                    } else {
                        encrypted_message += 'z' - (c - 'n');
                    }
                }
            }

            // Output the encrypted message
            cout << "Encrypted message: " << encrypted_message << endl;

            break;
        }
    }
}
//***************************************Vignere CIPHER FUNCTIONS***************************************************//

void vignere_Cipher() {
    string message, key_word;

    // Input message
    cout << "Enter your message: ";
    getline(cin, message);

    // Input keyword
    cout << "Enter keyword: ";
    getline(cin, key_word);

    // Convert message and keyword to uppercase
    for (char& c : message)
        c = toupper(c);

    string adjusted_key_word = "";
    for (char c : key_word) {
        if (isalpha(c))
            adjusted_key_word += toupper(c);
    }

    string encrypted_message = "";

    int keyIndex = 0;
    for (char C : message) {
        if (isalpha(C)) { // Process only alphabetic characters
            char shift = adjusted_key_word[keyIndex] - 'A';
            C = ((C - 'A' + shift) % 26) + 'A';
            keyIndex = (keyIndex + 1) % adjusted_key_word.length(); // Move to the next character in the key word
        }
        encrypted_message += C; // Append the character to the encrypted message
        if (!isalpha(C)) // Preserve spaces and non-alphabetic characters
            ++keyIndex;
    }

    cout << "Encrypted message: " << encrypted_message << endl;
}

void Vigenere_Decipher() {
    string encrypted_message, key_word;

    // Input encrypted message
    cout << "Enter the message you want to decrypt: ";
    getline(cin, encrypted_message);

    // Input keyword
    cout << "Enter keyword: ";
    getline(cin, key_word);

    // Convert encrypted message and keyword to uppercase
    for (char& c : encrypted_message)
        c = toupper(c);

    string adjusted_key_word = "";
    for (char c : key_word) {
        if (isalpha(c))
            adjusted_key_word += toupper(c);
    }

    string decrypted_message = "";

    int keyIndex = 0;
    for (char C : encrypted_message) {
        if (isalpha(C)) { // Process only alphabetic characters
            char shift = adjusted_key_word[keyIndex] - 'A';
            C = ((C - 'A' - shift + 26) % 26) + 'A'; // Decryption formula
            keyIndex = (keyIndex + 1) % adjusted_key_word.length(); // Move to the next character in the key word
        }
        decrypted_message += C; // Append the character to the decrypted message
        if (!isalpha(C)) // Preserve spaces and non-alphabetic characters
            ++keyIndex;
    }

    cout << "Decrypted message: " << decrypted_message << endl;
}

//***************************************BACONIAN CIPHER FUNCTIONS***************************************************//
map<char, string> baconianDict = {
        {'a', "aaaaa"}, {'b', "aaaab"}, {'c', "aaaba"}, {'d', "aaabb"}, {'e', "aabaa"},
        {'f', "aabab"}, {'g', "aabba"}, {'h', "aabbb"}, {'i', "abaaa"}, {'j', "abaab"},
        {'k', "ababa"}, {'l', "ababb"}, {'m', "abbaa"}, {'n', "abbab"}, {'o', "abbba"},
        {'p', "abbbb"}, {'q', "baaaa"}, {'r', "baaab"}, {'s', "baaba"}, {'t', "baabb"},
        {'u', "babaa"}, {'v', "babab"}, {'w', "babba"}, {'x', "babbb"}, {'y', "bbaaa"},
        {'z', "bbaab"}
};

void baconian_cipher() {
    string inputText;
    cout << "Enter the text to encode: ";
    getline(cin, inputText);

    string bacoText;
    for (char c : inputText) {
        if (c == ' ') {
            bacoText += "  "; // Three spaces for word separation
        } else {
            bacoText += baconianDict.at(tolower(c)) + " "; // One space for letter separation
        }
    }
    cout << "Baconian Code: " << bacoText << endl;
}

void baconian_decipher() {
    string inputText;
    cout << "Enter the Baconian code to decode: ";
    getline(cin, inputText);

    string orgText;
    string deciphered;
    bool firstLetterIgnored = false;

    for (char n : inputText) {
        if (n == ' ') {
            if (orgText == "   ") {
                deciphered += " "; // Add space for word separation
            } else if (!orgText.empty()) {
                // Check morse dictionary in reverse
                for (auto pair : baconianDict) {
                    if (pair.second == orgText) {
                        deciphered += pair.first;
                        if (!firstLetterIgnored) {
                            // Set the flag to true after decoding the first letter
                            firstLetterIgnored = true;
                        }
                        break;
                    }
                }
                orgText.clear();
            }
        } else {
            orgText += n;
        }
    }

    // Appending last character if any
    if (!orgText.empty()) {
        for (auto pair : baconianDict) {
            if (pair.second == orgText) {
                deciphered += pair.first;
                break;
            }
        }
    }
    cout << "Decoded Text: " << deciphered << endl;
}
//********************************SIMPLE SUBSTITUTION CIPHER FUNCTIONS***********************************************//
string buildCipherAlphabet(const string& key) {
    // Initialize the cipher alphabet with the key
    string cipherAlphabet = key;

    // Build a set to store unique characters in the key
    unordered_set<char> keySet;
    for (char c : key) {
        keySet.insert(tolower(c));
    }

    // Add remaining letters to the cipher alphabet
    for (char c = 'a'; c <= 'z'; ++c) {
        if (keySet.find(c) == keySet.end()) {
            cipherAlphabet += c;
        }
    }

    return cipherAlphabet;
}

void simple_substitution_cipher() {
    string key;
    cout << "Enter the key (5 unique letters): ";
    getline(cin, key);

    // Validate key
    if (key.size() != 5 || key.find_first_not_of("abcdefghijklmnopqrstuvwxyz") != string::npos) {
        cout << "Invalid key. Please enter 5 unique letters." << endl;
        return;
    }

    // Build the cipher alphabet
    string cipherAlphabet = buildCipherAlphabet(key);

    string message;
    cout << "Enter the message to encrypt: ";
    getline(cin, message);

    string encryptedMessage;
    for (char c : message) {
        if (isalpha(c)) {
            char encryptedChar = cipherAlphabet[tolower(c) - 'a'];
            encryptedMessage += isupper(c) ? toupper(encryptedChar) : encryptedChar;
        } else {
            encryptedMessage += c; // Keep non-alphabetic characters unchanged
        }
    }

    cout << "Encrypted Message: " << encryptedMessage << endl;
}

void simple_substitution_decipher() {
    string key;
    cout << "Enter the key (5 unique letters): ";
    getline(cin, key);

    // Validate key
    if (key.size() != 5 || key.find_first_not_of("abcdefghijklmnopqrstuvwxyz") != string::npos) {
        cout << "Invalid key. Please enter 5 unique letters." << endl;
        return;
    }

    // Build the cipher alphabet
    string cipherAlphabet = buildCipherAlphabet(key);

    string message;
    cout << "Enter the message to decrypt: ";
    getline(cin, message);

    string decryptedMessage;
    for (char c : message) {
        if (isalpha(c)) {
            size_t index = cipherAlphabet.find(tolower(c));
            char decryptedChar = 'a' + index;
            decryptedMessage += isupper(c) ? toupper(decryptedChar) : decryptedChar;
        } else {
            decryptedMessage += c; // Keep non-alphabetic characters unchanged
        }
    }

    cout << "Decrypted Message: " << decryptedMessage << endl;
}
//***************************************POLYBIUS CIPHER FUNCTIONS***************************************************//

void polybius_cipher() {
    char alphabet[5][5] = { // hard coding the matrix of the alphabets
            {'A','B','C','D','E'},
            {'F','G','H','I','K'},
            {'L','M','N','O','P'},
            {'Q','R','S','T','U'},
            {'V','W','X','Y','Z'}
    };
    int a, b, c, d, e;
    // key validation
    while (true) {
        string input;
        cout << "Enter your encryption key separated by spaces: ";

        if (getline(cin, input)) {
            istringstream stream(input);
            if (stream >> a >> b >> c >> d >> e && stream.eof()) { //validate that the input is only 5 integers
                // validate input is from 1 to 5
                if (a >= 1 && a <= 5 && b >= 1 && b <= 5 && c >= 1 && c <= 5 &&
                    d >= 1 && d <= 5 && e >= 1 && e <= 5) {
                    break;
                } else {
                    cout << "The key must be in the range of 1 to 5." << endl;
                    continue;
                }
            }
        }
        cout << "The key must be only five integers separated by spaces" << endl;
    }

    // mapping the indices to the key of the cipher
    map< int, int > index_map ={
            {0, a},
            {1, b},
            {2, c},
            {3, d},
            {4, e}
    };

    string original_text;
    cout << "Enter your text: ";
    getline(cin, original_text); // getting the message the user want to encrypt


    cout << "The ciphered message is: \n";
    for (int ch = 0; ch < original_text.length(); ch++){
        char letter = toupper(original_text[ch]);
        if (toupper(letter) == 'J'){ // making the I's and the j's have the same cipher as required
            letter = 'I';
        }
        if (isspace(letter)){  // reserving spaces
            cout << " ";
        }
        if (ispunct(letter)){  // ignoring any special character
            continue;
        }
        // ciphering the letters with the mapped indices
        for (int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                if (alphabet[i][j] == letter){
                    cout << index_map[i] << index_map[j];
                }
            }
        }
    }
}

void polybius_decipher() {
    char alphabet[5][5] = { // hard coding the matrix of the alphabets
            {'A','B','C','D','E'},
            {'F','G','H','I','K'},
            {'L','M','N','O','P'},
            {'Q','R','S','T','U'},
            {'V','W','X','Y','Z'}
    };
    char a, b, c, d, e;

    while (true) {  // validating the key input
        cout << "Enter your encryption key separated by spaces: ";
        // making sure the user insert only five digits and four spaces
        if (cin.get(a) && cin.get() == ' ' &&
            cin.get(b) && cin.get() == ' ' &&
            cin.get(c) && cin.get() == ' ' &&
            cin.get(d) && cin.get() == ' ' &&
            cin.get(e) && cin.peek() == '\n') {

            // validate input is from 1 to 5
            if (a >= '1' && a <= '5' && b >= '1' && b <= '5' &&
                c >= '1' && c <= '5' && d >= '1' && d <= '5' &&
                e >= '1' && e <= '5') {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                break;
            } else {
                cout << "The key must be in the range of 1 to 5" << endl;
            }
        } else {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            cout << "The key must be only five characters from 1 to 5 separated by spaces" << endl;
        }
    }
    // mapping the key to the indices of the matrix
    map< char, int > index_map = {
            {a, 0},
            {b, 1},
            {c, 2},
            {d, 3},
            {e, 4}
    };

    string ciphered_text, modified_text;
    cout << "Enter the ciphered message: ";
    getline(cin, ciphered_text); // getting the ciphered message

    cout << "The plain text is: ";
    for (int i = 0; i < ciphered_text.length(); i++){
        char letter = ciphered_text[i];
        if (isspace(letter)){ // ignoring spaces
            continue;
        }
        if (ispunct(letter)){ // ignoring special characters
            continue;
        }
        if (letter > '5' || letter < '1'){  // ignoring numbers out of range from 1 to 5
            continue;
        }
        else {
            modified_text += letter;
        }
    }
    if (modified_text.length() % 2 != 0){  // ignoring single numbers (e.g. taking only paired numbers)
        modified_text.pop_back();
    }
    // deciphering the modified input after ignoring additional content
    for (int ch = 0; ch < modified_text.length(); ch+=2){
        char row = modified_text[ch];
        char col = modified_text[ch+1];
        cout << alphabet[index_map[row]][index_map[col]];
    }
}

//***************************************MORSE CIPHER FUNCTIONS******************************************************//
// Morse code dictionary
map<char, string> morseDict = {
        {'a', ".-"}, {'b', "-..."}, {'c', "-.-."}, {'d', "-.."}, {'e', "."},
        {'f', "..-."}, {'g', "--."}, {'h', "...."}, {'i', ".."}, {'j', ".---"},
        {'k', "-.-"}, {'l', ".-.."}, {'m', "--"},{'n', "-."}, {'o', "---"},
        {'p', ".--."}, {'q', "--.-"}, {'r', ".-."}, {'s', "..."}, {'t', "-"},
        {'u', "..-"}, {'v', "...-"}, {'w', ".--"}, {'x', "-..-"}, {'y', "-.--"},
        {'z', "--.."},
        {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
        {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."},
        {'.', ".-.-.-"},{'?', "..--.."}, {'!', "-.-.--"}, {',', "--..--"}, {'"', ".-..-."},
        {'(', "-.--."}, {')', "-.--.-"}, {'&', ".-..."}, {':', "---..."}, {';', "-.-.-."},
        {'/', "-..-."}, {'_', "..--.-"},{'=', "-...-"}, {'+', ".-.-."}, {'-', "-....-"},
        {'$', "...-..-"}, {'@', ".--.-."}
};

void Morse_cipher() {
    cout << "Enter the text to encode: ";
    string input_text;
    getline(cin, input_text);
    string morseText;
    for (char c : input_text) {
        if (c == ' ') {
            morseText += "   "; // Three spaces for word separation
        } else {
            morseText += morseDict.at(tolower(c)) + " "; // One space for letter separation
        }
    }
    cout << "Morse text: " << morseText;
}

void Morse_decipher() {
    string morse_input;
    string orgText;
    string deciphered;
    bool firstLetterIgnored = false;

    cout << "Enter the Morse code to decode: ";
    getline(cin, morse_input);

    for (char n : morse_input) {
        if (n == ' ') {
            if (orgText == "   ") {
                deciphered += " "; // Add space for word separation
            } else if (!orgText.empty()) {
                // Check morse dictionary in reverse
                for (auto pair : morseDict) {
                    if (pair.second == orgText) {
                        deciphered += pair.first;
                        if (!firstLetterIgnored) {
                            // Set the flag to true after decoding the first letter
                            firstLetterIgnored = true;
                        }
                        break;
                    }
                }
                orgText.clear();
            }
        } else {
            orgText += n;
        }
    }

    // Appending last character if any
    if (!orgText.empty()) {
        for (auto pair : morseDict) {
            if (pair.second == orgText) {
                deciphered += pair.first;
                break;
            }
        }
    }

    cout << "Plain text: " << deciphered;
}

//*****************************************XOR CIPHER FUNCTIONS******************************************************//
void xor_cipher() {
    string xor_key, ciphered;
    cout << "Enter your key: ";
    cin >> xor_key;
    cin.ignore();

    string plain_text,filtered_text;
    cout << "Enter your message: ";
    getline(cin, plain_text);

    // Encrypt the message using XOR operation
    for (int i = 0; i < plain_text.length(); i++) {
        plain_text[i] = plain_text[i] ^ xor_key[i % xor_key.length()];
    }
    // filter non-printable characters
    for (char c : plain_text) {
        if (isprint(c)) {
            filtered_text += c;
        }
    }

    // Print the encrypted message as text
    cout << "Ciphered Text: " << filtered_text << endl;
    // print the encrypted message as hexadecimal
    cout << "Hexadecimal Ciphered Text: ";
    for (char c : plain_text) {
        cout << hex << setw(2) << setfill('0') << static_cast<int>(c) << " ";
    }
    cout << endl;
}

string hex_to_ASCII(const string& hex) {
    stringstream ss;
    for (size_t i = 0; i < hex.length(); i += 2) {
        unsigned char byte = stoi(hex.substr(i, 2), nullptr, 16);
        ss << byte;
    }
    return ss.str();
}

void xor_decipher() {
    string xor_key;
    cout << "Enter your key: ";
    cin >> xor_key;
    cin.ignore(); // Clear the input buffer

    string hexString;
    cout << "Enter the ciphered hexadecimal message: ";
    getline(cin, hexString);

    stringstream filtered_Hex;
    for (char c : hexString) {
        if (isxdigit(c)) { // Check if the character is a hexadecimal digit
            filtered_Hex << c;
        }
    }

    string asciiString = hex_to_ASCII(filtered_Hex.str());

    stringstream ss;
    for (size_t i = 0; i < asciiString.length(); ++i) {
        ss << (char)(asciiString[i] ^ xor_key[i % xor_key.length()]);
    }

    string decipheredText = ss.str();
    cout << "Plain text: " << decipheredText << endl;
}

//*************************************RAIL FENCE CIPHER FUNCTIONS***************************************************//
void rail_fence_cipher(){
    string plain_text, modified, ciphered1, ciphered2, ciphered3;
    cout << "Enter your message (the secret key is 3): ";
    getline(cin, plain_text);

    for (int i = 0; i < plain_text.length(); i++){
        char letter = plain_text[i];
        if (isspace(letter)){ // ignoring spaces
            continue;
        }
        if (ispunct(letter)){ // ignoring special characters
            continue;
        }
        if (isdigit(letter)){ // ignoring numbers
            continue;
        }
        else {
            modified += letter;
        }
    }

    for (int i = 0; i < modified.length(); i+= 4){
        ciphered1 += modified[i];
    }
    for (int j = 1; j < modified.length(); j+= 2){
        ciphered2 += modified[j];
    }
    for (int k = 2; k < modified.length(); k+= 4){
        ciphered3 += modified[k];
    }
    cout << ciphered1 << ciphered2 << ciphered3;
}

void rail_fence_decipher() {
    cout << "Enter the ciphered message (the secret key is 3): ";
    string ciphered, modified;
    getline(cin, ciphered);

    for (int i = 0; i < ciphered.length(); i++){
        char letter = ciphered[i];
        if (isspace(letter)){ // ignoring spaces
            continue;
        }
        if (ispunct(letter)){ // ignoring special characters
            continue;
        }
        if (isdigit(letter)){
            continue;
        }
        else {
            modified += letter;
        }
    }

    if (modified.length() % 4 != 0) {
        string ciphered1 = modified.substr(0, ((modified.length() / 4) + 1));
        string ciphered2 = modified.substr((modified.length() / 4) + 1, (modified.length() / 2));
        string ciphered3 = modified.substr((3 * (modified.length()) / 4) + 1, ((modified.length() / 4) + 1));
        string plain(modified.length(), ' ');
        for (int i = 0; i < ciphered1.length(); i++) {
            plain[4*i] = ciphered1[i];
        }

        for (int i = 0; i < ciphered2.length(); i++){
            plain[2*i + 1] = ciphered2[i];
        }
        for (int i = 0; i < ciphered3.length(); i++){
            plain[4*i + 2] = ciphered3[i];
        }
        for (int i = 0; i < modified.length(); i++){
            cout << plain[i];
        }
    }
    if (modified.length() % 4 == 0){
        string ciphered1 = modified.substr(0, ((modified.length() / 4)));
        string ciphered2 = modified.substr((modified.length() / 4), (modified.length() / 2));
        string ciphered3 = modified.substr((3 * (modified.length()) / 4), ((modified.length() / 4) + 1));
        string plain(modified.length(), ' ');

        for (int i = 0; i < ciphered1.length(); i++) {
            plain[4*i] = ciphered1[i];
        }

        for (int i = 0; i < ciphered2.length(); i++){
            plain[2*i + 1] = ciphered2[i];
        }
        for (int i = 0; i < ciphered3.length(); i++){
            plain[4*i + 2] = ciphered3[i];
        }
        for (int i = 0; i < modified.length(); i++){
            cout << plain[i];
        }
    }
}

int main()
{
    // start of running program
    int choice1, choice2;
    do {
        // Display menu 1 and get user choice
        menu1();
        // get user choice with validation
        choice1 = get_User_Choice(1, 3);

        switch(choice1) {

            // in case of choose to cipher
            case 1:

                // Display menu 2 and get user choice for cipher selection
                menu2();
                choice2 = get_User_Choice(1, 10);

                cin.ignore(); // Ignore newline character from previous input

                // Depending on the choice from menu 2
                switch(choice2) {


                    case 1:
                        Affine_Cipher();
                        break;
                    case 2:
                        Route_cipher();
                        break;
                    case 3:
                        Atbash_Cipher();
                        break;
                    case 4:
                        vignere_Cipher();
                        break;
                    case 5:
                        baconian_cipher();
                        break;
                    case 6:
                        simple_substitution_cipher();
                        break;
                    case 7:
                        polybius_cipher();
                        break;
                    case 8:
                        Morse_cipher();
                        break;
                    case 9:
                        xor_cipher();
                        break;
                    case 10:
                        rail_fence_cipher();
                        break;
                }
                break;
                // in case of choosing to decipher
            case 2:
                // Display menu 2 and get user choice for decipher selection
                menu2();
                // get user choice with validation
                choice2 = get_User_Choice(1, 10);

                cin.ignore(); // Ignore newline character from previous input

                // Depending on the choice from menu 2
                switch(choice2) {
                    case 1:
                        Affine_deCipher();
                        break;
                    case 2:
                        Route_decipher();
                        break;
                    case 3:
                        Atbash_Cipher();
                        break;
                    case 4:
                        Vigenere_Decipher();
                        break;
                    case 5:
                        baconian_decipher();
                        break;
                    case 6:
                        simple_substitution_decipher();
                        break;
                    case 7:
                        polybius_decipher();
                        break;
                    case 8:
                        Morse_decipher();
                        break;
                    case 9:
                        xor_decipher();
                        break;
                    case 10:
                        rail_fence_decipher();
                        break;
                }
                break;
            case 3:
                cout << "Exiting program....... Goodbye!\n";
                break;
        }
    } while(choice1 != 3); // Loop until the user chooses to exit
    return 0;
}