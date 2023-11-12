CREATE table IF NOT EXISTS Employees (
    employee_id INT PRIMARY KEY,
    name VARCHAR(255),
    department VARCHAR(255),
    manager_id INT,
    FOREIGN KEY (manager_id) REFERENCES Employees(employee_id)
);

