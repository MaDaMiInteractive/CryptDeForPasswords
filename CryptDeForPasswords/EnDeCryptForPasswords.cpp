#include "Headers.h"
using namespace std;

int main()
{
    const string pathpassword = "passwords.txt";
    setlocale(LC_ALL,"RUS");
    Menu menu;
    Function funct;
    int input;
    string password, username;
    string inputstr;
    while (1) {
        menu.ClearMenu();
        menu.PrintMainMenu();
        cin >> input;
        switch (input)
        {
        case 1:
            
            menu.ClearMenu();
            menu.PrintAddPassword(0);
            cin >> username;

            menu.ClearMenu();
            menu.PrintAddPassword(1);
            cin >> password;

            funct.AddPassword(pathpassword, funct.MaxId(pathpassword), username, password);
            break;
        case 2:
            menu.ClearMenu();
            menu.PrintDelPassword();
            cin >> input;
            funct.RemovePassword(pathpassword, input);
            menu.Pause();
            break;
        case 3:
            menu.ClearMenu();
            menu.PrintEncrypt();
            cin >> input;

            cout << "Пароль для расшифровки (запишите его, иначе вы не сможете восстановить): " << funct.EncryptPassword(pathpassword, input) << endl;
            menu.Pause();
            break;
        case 4:
            menu.ClearMenu();
            menu.PrintDecrypt();
            cin >> input;
            cin.ignore();
            cout << "Введите код от пароля: ";
            getline(cin, inputstr);
            funct.DecryptPassword(pathpassword, input, inputstr);
            menu.Pause();
            break;
        case 5:
            menu.ClearMenu();
            menu.PrintSettings();
            cin >> input;
            break;
        case 6:

            menu.ClearMenu();
            menu.PrintHelp();
            cin >> input;
            switch (input)
            {
            case 1:
                menu.ClearMenu();
                funct.OutputFile("ERRORSIDS.txt");
                menu.Pause();
                break;
            case 2:
                menu.ClearMenu();
                funct.OutputFile("FAQ.txt");
                menu.Pause();
                break;
            default:
                menu.PrintSuccessFiled(0, 1);
                menu.Pause();
                break;
            }
            break;
        case 7:
            menu.ClearMenu();
            funct.OutputFile(pathpassword);
            menu.Pause();
            break;
        case 8:
            menu.Pause();
            return 0;
        default:
            menu.PrintSuccessFiled(0, 1);
            menu.Pause();
            break;
        }
    }
}
