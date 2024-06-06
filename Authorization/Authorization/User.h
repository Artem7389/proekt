using namespace System;

public ref class User {
public:
    User(int id, String^ name, String^ email, String^ phone, String^ address, String^ password) :
        id(id), name(name), email(email), phone(phone), address(address), password(password) {}

    property int Id {
        int get() { return id; }
    }

    property String^ Name {
        String^ get() { return name; }
        void set(String^ value) { name = value; }
    }

public:
    int id;
    System::String^ name;
    System::String^ email;
    System::String^ phone;
    System::String^ address;
    System::String^ password;

    // Конструктор по умолчанию
    User() {
        // Инициализация полей, если это необходимо
    }
};