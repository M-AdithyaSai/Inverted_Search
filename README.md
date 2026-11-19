# 🔍 Inverted Search Engine in C

## 📌 Overview

The **Inverted Search Engine** is a file indexing and searching application developed using the C programming language.

It uses the concept of an **Inverted Index** to efficiently search for words across multiple text files.

Instead of scanning every file whenever a search is performed, the application creates an index that stores each unique word along with the filenames in which it appears and its occurrence count.

This project demonstrates the practical implementation of Data Structures and Algorithms, particularly Hash Tables and Linked Lists, along with file handling and dynamic memory allocation.

## ✨ Features

- 🗂️ **Create Database:** Reads multiple `.txt` files and creates an inverted index.
- 📋 **Display Database:** Displays all indexed words, the number of files containing each word, and their occurrence counts.
- 🔎 **Search Word:** Searches for a specific word and displays the files containing it.
- 🔄 **Update Database:** Reconstructs the database using a previously saved database file.
- 💾 **Save Database:** Saves the indexed information into a text file for future use.
- 🛡️ **File Validation:** Validates file extensions, checks file accessibility, and prevents duplicate and empty file insertion.
- ⚙️ **Input Validation:** Handles invalid menu choices and file inputs.

## 🧠 Data Structures Used

### 1. Hash Table

A hash table containing 27 entries is used to organize words based on their first character.

- Index 0–25: A–Z
- Index 26: Other characters

This helps narrow down the search area when retrieving a word.

### 2. Main Linked List

Each main node stores:

- Unique word
- Number of files containing the word
- Pointer to the corresponding sub-linked list
- Pointer to the next main node

### 3. Sub Linked List

Each sub node stores:

- Filename
- Number of occurrences of the word in that file
- Pointer to the next sub node

### 📊 Database Structure

```text
                HASH TABLE
       +-------------------------+
       | Index 0  (A)            |
       | Index 1  (B)            |
       | Index 2  (C)            |
       |   ...                   |
       | Index 25 (Z)            |
       | Index 26 (Other)        |
       +-------------------------+
                  |
                  v
             MAIN NODE
          +-------------+
          | Word        |
          | File Count  |
          | Main Link   |
          | Sub Link    |
          +-------------+
                  |
                  v
             SUB NODE
          +-------------+
          | Filename    |
          | Word Count  |
          | Link        |
          +-------------+
                  |
                  v
             SUB NODE
```

## 🛠️ Technologies Used

- 💻 **Programming Language:** C
- 🧱 **Data Structures:** Hash Table, Singly Linked Lists
- 🔧 **Concepts:** File Handling, Dynamic Memory Allocation, String Manipulation, Pointers
- ⚙️ **Compiler:** GCC
- 📦 **Build Tool:** Makefile

## 📁 Project Structure

```text
Inverted_Search/
│
├── main.c
├── main.h
├── create.c
├── display.c
├── search.c
├── update.c
├── save.c
├── validate.c
├── Makefile
│
├── database.txt
├── f1.txt
├── f2.txt
├── f3.txt
└── empty.txt
```

## 🚀 Compilation and Execution

### 📋 Prerequisites

- GCC compiler
- Make utility
- Linux environment or Windows with MinGW

### Step 1: Clone the Repository

```bash
git clone https://github.com/M-AdithyaSai/Inverted_Search.git
```

### Step 2: Navigate to the Project Directory

```bash
cd Inverted_Search
```

### Step 3: Compile the Project

```bash
make
```

Alternatively, compile manually:

```bash
gcc *.c -o inverted_search
```

### Step 4: Run the Application

If compiled using Makefile:

```bash
./a.out
```

If compiled manually:

```bash
./inverted_search
```

## 🖥️ Application Menu

After execution, the application displays the following menu:

```text
========== Inverted Search Menu ==========

1. Create DataBase
2. Display DataBase
3. Update DataBase
4. Search a Word in DataBase
5. Save DataBase
6. Exit

==========================================

Enter your choice:
```

### ⚡ Operations

| Option | Operation |
|:---:|---|
| 1 | 🗂️ Create Database |
| 2 | 📋 Display Database |
| 3 | 🔄 Update Database |
| 4 | 🔎 Search a Word |
| 5 | 💾 Save Database |
| 6 | 🚪 Exit |

## 🎯 Learning Outcomes

Through this project, I gained practical experience in:

- Implementing Hash Tables and Linked Lists.
- Understanding the working principle of Inverted Indexing.
- Managing dynamically allocated memory.
- Performing file operations in C.
- Handling multiple text files.
- Implementing searching and indexing algorithms.
- Organizing a C project using multiple source files and header files.

## 👨‍💻 Author

**M. Adithya Sai**

🔗 GitHub: [M-AdithyaSai](https://github.com/M-AdithyaSai)

## 📜 License

This project is developed for educational purposes.
