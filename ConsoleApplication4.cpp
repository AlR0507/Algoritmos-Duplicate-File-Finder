#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

void list_directory(const wstring& directory, int level = 0) {
    wstring indent(level * 4, L' ');

    wstring search_path = directory + L"\\*";

    WIN32_FIND_DATAW find_data;
    HANDLE hFind = FindFirstFileW(search_path.c_str(), &find_data);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::wcerr << indent << L"Error al abrir el directorio: " << directory << L'\n';
        return;
    }

    do {
        const wstring file_name = find_data.cFileName;

        if (file_name == L"." || file_name == L"..") {
            continue;
        }

        wcout << indent << L"|-- " << file_name << L'\n';

        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            list_directory(directory + L"\\" + file_name, level + 1);
        }

    } while (FindNextFileW(hFind, &find_data) != 0);

    FindClose(hFind);
}

int main() {
    wstring path;
    wcout << L"Introduce el directorio inicial: ";
    wcin >> path;

    wcout << L"Estructura del directorio:\n";
    list_directory(path);

    return 0;
}
