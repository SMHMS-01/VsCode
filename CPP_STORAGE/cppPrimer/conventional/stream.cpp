// #include <iostream>
// #include <windows.h>
// #include <iomanip>
// #include <stdexcept>

// using namespace std;

// int main()
// {
//     SetConsoleOutputCP(65001);

//     float a = -1.0;
//     cin.exceptions(ios::failbit);
//     try
//     {
//         cin >> a;
//     }
//     catch (const std::ios_base::failure &fail)
//     {
//         cout << "Get a error" << endl
//              << fail.what() << endl;
//     }
//     system("pause");
//     return 0;
// }

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    cout << "type an int ,a float and a string: ";
    int i;
    float f;
    cin >> i >> f;
    string stuff;
    getline(cin, stuff);
    ostringstream os;
    os << "integer = " << i << endl;
    os << "float = " << f << endl;
    os << "string = " << stuff << endl;
    string result = os.str();
    cout << result << endl;
    system("pause");
}
