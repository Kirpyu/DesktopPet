#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Pet.h"

#include <windows.h>
#include <commdlg.h>
#include <iostream>

#include <Dwmapi.h>
#pragma comment (lib, "Dwmapi.lib")

int main() {

    sf::RenderWindow window(sf::VideoMode(72, 72), "Desktop Cat",sf :: Style :: None);

    MARGINS margins;
    margins.cxLeftWidth = -1;

    SetWindowLong(window.getSystemHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
    DwmExtendFrameIntoClientArea(window.getSystemHandle(), &margins);

    //creates a variable named pet and uses its constructor, similar to Pet pet = new Pet(window)
    widget::Pet pet(window);
    pet.initPet();

    //OPENFILENAME ofn;
    //wchar_t szFile[260] = L"";

    //// Initialize OPENFILENAME
    //ZeroMemory(&ofn, sizeof(ofn));
    //ofn.lStructSize = sizeof(ofn);
    //ofn.hwndOwner = NULL;  // Handle to the parent window (NULL for none)
    //ofn.lpstrFile = szFile;
    //ofn.lpstrFile[0] = '\0';  // Initialize with an empty string
    //ofn.nMaxFile = sizeof(szFile);
    //ofn.lpstrFilter = L"All Files\0*.*\0Text Files\0*.TXT\0";  // File filters
    //ofn.nFilterIndex = 1;  // Default filter index
    //ofn.lpstrFileTitle = NULL;
    //ofn.nMaxFileTitle = 0;
    //ofn.lpstrInitialDir = NULL;  // Initial directory
    //ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;  // Flags

    //// Display the Open dialog box
    //if (GetOpenFileName(&ofn)) {
    //    std::cout << "Selected file: " << ofn.lpstrFile << std::endl;
    //}
    //else {
    //    std::cout << "No file selected or dialog canceled." << std::endl;
    //}

    

    return 0;
}