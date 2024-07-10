# Database Simulation Software

## Project Description
This project is a C++ software system designed for simulating database operations. The system allows users to create and manage databases, execute queries, and export databases. It supports interaction via a text-based menu.

## Features
- **Database Management**:
  - Create and delete databases.
  - Execute DDL (CREATE TABLE, DROP TABLE) and DML (SELECT, INSERT, UPDATE, DELETE) queries.
- **Database Export**:
  - Export databases to custom-defined formats or SQL files.
- **Error Handling**:
  - Detailed error messages to assist in resolving issues.

## Installation
1. Clone the repository:
    ```sh
    git clone https://github.com/tomicmilos57/cppsql
    ```
2. Compile the project using a C++ compiler:
    ```sh
    g++ -o cppsql src/*.cpp
    ```
    or
    ```sh
    ./script
    ```

## Usage
1. Run the compiled executable:
    ```sh
    ./cppsql
    ```
2. Follow the on-screen instructions to interact with the database system.

### Example Commands
- **Create Table**:
    ```
    CREATE TABLE table_name (column1, column2, column3);
    ```
- **Insert Data**:
    ```
    INSERT INTO table_name (column1, column2, column3) VALUES ('value1', 'value2', 'value3');
    ```
- **Select Data**:
    ```
    SELECT column1, column2 FROM table_name WHERE column1 = 'value1';
    ```

## Classes and Methods
The system is built using various C++ classes to encapsulate the functionality of database operations. Key classes include:

- `Database`: Manages tables and executes queries.
- `Table`: Represents a database table.
- `Query`: Parses and executes SQL-like commands.

## Exporting and Saving
The software supports exporting databases in two formats:
1. **Custom Format**: Designed for internal use.
2. **SQL Format**: Generates a `.sql` file with SQL commands to recreate the database.

## Example
![slika](https://github.com/tomicmilos57/cppsql/assets/144954915/978b1dec-a0fd-421d-a458-6cc62d51d7ed)
