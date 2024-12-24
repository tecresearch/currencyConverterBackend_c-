# Currency Converter Using C++ with CGI (Backend)

This project demonstrates how to build a currency converter using **C++** as the backend and connect it to a web interface via CGI (Common Gateway Interface). Below are the detailed steps to set up, compile, and run the project on a Windows environment using XAMPP.

---

## Prerequisites

- **XAMPP**: Download and install from [https://www.apachefriends.org/](https://www.apachefriends.org/).
- **C++ Compiler**: MinGW or any compatible C++ compiler.
- **Web Browser**: To test the application.

---

## Installation Steps

### Step 1: Install XAMPP
1. Download XAMPP from [https://www.apachefriends.org/](https://www.apachefriends.org/).
2. During installation, ensure **Apache** is selected.

### Step 2: Enable CGI Module in Apache
1. Open the XAMPP control panel and click **Config** for Apache.
2. Select **httpd.conf** to edit the Apache configuration file.
3. Enable the CGI module by uncommenting the following line (remove the `#` if present):
   ```apache
   LoadModule cgi_module modules/mod_cgi.so
   ```
4. Add the following configuration block for the `cgi-bin` directory:
   ```apache
   <Directory "C:/xampp/cgi-bin">
       Options +ExecCGI
       AddHandler cgi-script .cgi .exe
       Require all granted
   </Directory>
   ```
5. Save the file and restart Apache from the XAMPP control panel.

### Step 3: Write and Compile the C++ Code
1. Create a C++ script `currency_converter.cpp` with your currency conversion logic.

#### Complete Code for `currency_converter.cpp`
```cpp
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>

void printHTMLHeader() {
    std::cout << "Content-type: text/html\n\n";
    std::cout << "<!DOCTYPE html>\n";
    std::cout << "<html>\n<head>\n<title>Currency Converter</title>\n</head>\n<body>\n";
}

void printHTMLFooter() {
    std::cout << "</body>\n</html>\n";
}

int main() {
    printHTMLHeader();

    std::map<std::string, double> exchangeRates = {
        {"USD_TO_INR", 82.75},
        {"EUR_TO_INR", 89.34},
        {"GBP_TO_INR", 102.56}
    };

    const char* queryString = getenv("QUERY_STRING");
    if (queryString) {
        std::string query(queryString);
        std::string fromCurrency, toCurrency;
        double amount = 0.0;

        size_t fromPos = query.find("from=");
        size_t toPos = query.find("to=");
        size_t amountPos = query.find("amount=");

        if (fromPos != std::string::npos && toPos != std::string::npos && amountPos != std::string::npos) {
            fromCurrency = query.substr(fromPos + 5, toPos - fromPos - 6);
            toCurrency = query.substr(toPos + 3, amountPos - toPos - 4);
            amount = std::stod(query.substr(amountPos + 7));

            std::string key = fromCurrency + "_TO_" + toCurrency;

            if (exchangeRates.find(key) != exchangeRates.end()) {
                double convertedAmount = amount * exchangeRates[key];
                std::cout << "<h1>Converted Amount: " << convertedAmount << " " << toCurrency << "</h1>\n";
            } else {
                std::cout << "<h1>Error: Unsupported currency conversion.</h1>\n";
            }
        } else {
            std::cout << "<h1>Error: Invalid query string.</h1>\n";
        }
    } else {
        std::cout << "<h1>Error: No query string found.</h1>\n";
    }

    printHTMLFooter();
    return 0;
}
```

2. Open a command prompt and navigate to the directory containing `currency_converter.cpp`.
3. Compile the script using MinGW:
   ```bash
   g++ currency_converter.cpp -o currency_converter.exe
   ```
4. Move the compiled file to the `cgi-bin` directory:
   ```bash
   move currency_converter.exe C:/xampp/cgi-bin/
   ```

### Step 4: Create the HTML File
1. Create an HTML file `index.html` with the required form fields for currency conversion.

#### Complete Code for `index.html`
```html
<!DOCTYPE html>
<html>
<head>
    <title>Currency Converter</title>
</head>
<body>
    <h1>Currency Converter</h1>
    <form action="/cgi-bin/currency_converter.exe" method="GET">
        <label for="from">From Currency:</label>
        <input type="text" id="from" name="from" required><br>

        <label for="to">To Currency:</label>
        <input type="text" id="to" name="to" required><br>

        <label for="amount">Amount:</label>
        <input type="number" id="amount" name="amount" step="0.01" required><br>

        <button type="submit">Convert</button>
    </form>
</body>
</html>
```

2. Save the file in the `htdocs` directory of your XAMPP installation:
   ```bash
   C:/xampp/htdocs/index.html
   ```

### Step 5: Test CGI Execution
1. Open your browser and navigate to:
   ```
   http://localhost/cgi-bin/currency_converter.exe
   ```
2. If properly configured, the output of the CGI script will be displayed.

### Step 6: Connect HTML and C++ (Currency Converter)
1. Load the form in your browser:
   ```
   http://localhost/index.html
   ```
2. Fill in the form fields and submit.
3. The form sends a GET request to `currency_converter.exe`, processes the request, and returns the result.

---

## Troubleshooting Tips

- Ensure the `cgi-bin` folder is properly configured in `httpd.conf`.
- Ensure the `.exe` file has execution permissions.
- Check Apache error logs for debugging:
  ```
  C:/xampp/apache/logs/error.log
  ```

---

## Commands Summary

### Install XAMPP
```bash
# Download XAMPP from the official site
https://www.apachefriends.org/
```

### Enable CGI in Apache
```bash
# Open Apache configuration
LoadModule cgi_module modules/mod_cgi.so

<Directory "C:/xampp/cgi-bin">
    Options +ExecCGI
    AddHandler cgi-script .cgi .exe
    Require all granted
</Directory>
```

### Compile C++ Code
```bash
# Navigate to the directory containing your script
cd path/to/your/script

# Compile the script
g++ currency_converter.cpp -o currency_converter.exe

# Move the compiled executable to the cgi-bin directory
move currency_converter.exe C:/xampp/cgi-bin/
```

### Run Application
```bash
# Test CGI Execution
http://localhost/cgi-bin/currency_converter.exe

# Access the HTML Form
http://localhost/index.html
```

---

### Author
Created by **Mr.Brijesh Nishad (Software Developer) **.
