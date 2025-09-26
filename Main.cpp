#include "ConsoleMenu.h"

using namespace std;
int main() {

    FileRepository repo;
    ConsoleMenu menu(repo);

    string storageFile = "database.txt";

    menu.Show();

    return 0;
}
