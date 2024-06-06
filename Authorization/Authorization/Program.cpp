#include <sqlite3.h>
#include <exception>
#include "User.h"
#include "LoginForm.h"
#include "MainForm.h"
#include "RegisterForm.h"
#include <iostream>

namespace Authorization {
    public ref class LoginForm : public System::Windows::Forms::Form
    {
    public:
        bool switchToRegister = false;
        User^ user;

        void CheckCredentials(String^ username, String^ password)
        {
            try
            {
                using (auto db = sqlite::database::database("User.db"))
                {
                    auto query = db << "SELECT id, username, password FROM Users WHERE username = ? AND password = ?";
                    query.bind(1, marshal_as<const char*>(username));
                    query.bind(2, marshal_as<const char*>(password));

                    for (auto row : query)
                    {
                        // Проверка учетных данных
                        if (row["username"] == username && row["password"] == password)
                        {
                            // Retrieve the ID
                            int id = row["id"];

                            // Create a new User object with the ID
                            user = gcnew User(id, row["username"], row["password"]);
                            return;
                        }
                    }
                }
                // Учетные данные неверны
                MessageBox::Show("Invalid credentials", "Login Error", MessageBoxButtons::OK);
            }
            catch (const std::exception& e)
            {
                MessageBox::Show(gcnew String(e.what()), "Database Error", MessageBoxButtons::OK);
            }
        }
    };

    int main() {
        sqlite3* db;
        int rc = sqlite3_open("User.db", &db);

        if (rc) {
            std::cerr << "Can't open database:" << sqlite3_errmsg(db) << std::endl;
            return 1;
        }
        const char* sq1 = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, name TEXT);";
        rc = sqlite3_exec(db, sp1, nullptr, nullptr, nullptr);

        if (rc != SQLITE_OK) {
            std::cerr << "SQL error:" << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_close(db);
        return 0;
    }
}
