#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <string>

enum class CharType { Letters, Numbers, Symbols };

std::map<CharType, std::string> components = {
    {CharType::Letters, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"},
    {CharType::Numbers, "0123456789"},
    {CharType::Symbols, "!@#$%^&*()"}};

std::string generatePassword(int passLength) {
  if (passLength <= 0) {
    std::cerr << "Error: Invalid password length.\n";
    return "";
  }

  std::string charpool = components[CharType::Letters] +
                         components[CharType::Numbers] +
                         components[CharType::Symbols];

  if (charpool.empty()) {
    std::cerr << "Error: Character pool is empty.\n";
    return "";
  }

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<> dist(0, charpool.size() - 1);

  std::string password;
  for (int i = 0; i < passLength; ++i) {
    password += charpool[dist(rng)];
  }
  return password;
}

int main() {
  int passLength;
  std::string socialMedia;
  std::string accountName;
  std::fstream myPasswords;
  myPasswords.open("Passwords.txt", std::ios::out);

  std::cout << "Please enter the name of the social media: ";
  std::getline(std::cin, socialMedia);

  std::cout << "Please enter the name of the account: ";
  std::getline(std::cin, accountName);
  // Request user input
  std::cout << "Please enter the length of the password: ";
  if (!(std::cin >> passLength)) { // Check for valid input
    std::cerr << "Error: Invalid input. Please enter an integer.\n";
    return 1;
  }

  // Generate and display the password
  std::string password = generatePassword(passLength);
  if (!password.empty()) {
    std::cout << "Your password is: " << password << "\n";
  } else {
    std::cerr << "Failed to generate password.\n";
  }
  if (myPasswords.is_open()) {
    myPasswords << socialMedia << " Account Name: " << accountName
                << " password: " << password << std::endl;
  }

  return 0;
}
