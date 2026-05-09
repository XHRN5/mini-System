# Advanced Auth System (V1)

A modular C++ authentication and data protection system focused on secure session handling, encrypted in-memory storage, and backup recovery mechanisms.

---

# Features

### Dynamic XOR Encryption

User credentials are encrypted using a dynamically generated XOR key derived from the user's email length. This creates a unique encryption behavior for each account session.

### Modular Architecture

The project is separated into multiple header files and logical components for better maintainability and scalability.

### Backup & Recovery System

Supports exporting encrypted account data into external backup files and restoring sessions through an import system.

### Password Validation

Includes configurable password rules such as:

* Minimum length
* Required digits
* Required special characters

### Runtime Session Protection

Sensitive account data becomes accessible only during active authenticated sessions.

---

# Tech Stack

* **Language:** C++
* **Core Concepts:**

  * Object-Oriented Programming (OOP)
  * File I/O
  * Runtime Data Handling
  * Basic Encryption Logic
  * Modular Software Design

---

# Project Structure

* `Account.h` → Account data and access control
* `Auth.h` → Authentication system
* `Checker.h` → Password validation engine
* `Encryption.h` → XOR encryption/decryption logic
* `Settings.h` → Account settings and backup management

---

# How to Use

1. Register a new account
2. Log into the system
3. Use Export Backup to save encrypted account data
4. Use Import Backup to restore saved sessions
5. Modify account settings during authenticated sessions

---

# Notes

This project focuses on demonstrating:

* Secure data flow concepts
* Runtime access control
* Basic obfuscation techniques
* Modular software architecture

The system is designed for educational and academic purposes and does not aim to replace industry-standard cryptographic systems such as AES or RSA.

#
