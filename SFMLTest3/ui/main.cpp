#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Pet.h"
#include "PetManager.h"

#include <thread>
#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <locale>
#include <codecvt>
#include <Dwmapi.h>
#pragma comment (lib, "Dwmapi.lib")

void createPet() {
    sf::RenderWindow window(sf::VideoMode(72, 72), "Desktop Cat",sf :: Style :: None);

    MARGINS margins;
    margins.cxLeftWidth = -1;

    SetWindowLong(window.getSystemHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
    DwmExtendFrameIntoClientArea(window.getSystemHandle(), &margins);

    //creates a variable named pet and uses its constructor, similar to Pet pet = new Pet(window)
    widget::Pet pet(window);

    pet.initPet();
}

std::vector<std::string> openFile() {

    std::vector<std::string> tempVector;

    OPENFILENAME ofn;       // common dialog box structure
    wchar_t szFile[260];       // buffer for file name

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Images\0*.png\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER;

    // Display the Open dialog box. 

    if (GetOpenFileName(&ofn) == TRUE) {
        wchar_t* str = ofn.lpstrFile;
        std::wstring directory = str;
        // goes to the file name, prints out the entire file name if pointer lands on it, starting from where it lands, +1 because there is a buffer of /0 which is null
        str += (directory.length() + 1);

        using convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_type, wchar_t> converter;

        //check if only one file is selected, because str would return false on loop start if only selecting one file
        // this works because str is already getting the next file, but since theres none, then itll return nothing

        if (!*str) {
            std::string convertedString = converter.to_bytes(directory);
            tempVector.push_back(convertedString);
        }

        while (*str) {

            //gets the current file name we are on
            std::wstring filename = str;

            ////since pointer does not move yet, print the current one, debugger
            //std::wcout << directory + L"\\" + str << std::endl;

            //setup converter

            //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
            std::string convertedString = converter.to_bytes(directory + L"\\" + str);

            tempVector.push_back(convertedString);

            //go to the next 
            str += (filename.length() + 1);
        }
    }

    return tempVector;
}

//std::vector<std::string> openFile() {
//
//    std::vector<std::string> tempVector;
//
//    OPENFILENAME ofn;       // common dialog box structure
//    char szFile[260];       // buffer for file name
//
//    // Initialize OPENFILENAME
//    ZeroMemory(&ofn, sizeof(ofn));
//    ofn.lStructSize = sizeof(ofn);
//    ofn.lpstrFile = szFile;
//    ofn.lpstrFile[0] = '\0';
//    ofn.nMaxFile = sizeof(szFile);
//    ofn.lpstrFilter = "Images\0*.png\0";
//    ofn.nFilterIndex = 1;
//    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER;
//
//    // Display the Open dialog box. 
//
//    if (GetOpenFileName(&ofn) == TRUE) {
//        char* str = ofn.lpstrFile;
//        std::string directory = str;
//        // goes to the file name, prints out the entire file name if pointer lands on it, starting from where it lands, +1 because there is a buffer of /0 which is null
//        str += (directory.length() + 1);
//
//        //check if only one file is selected, because str would return false on loop start if only selecting one file
//        // this works because str is already getting the next file, but since theres none, then itll return nothing
//
//        if (!*str) {
//            tempVector.push_back(directory);
//        }
//
//        while (*str) {
//
//            //gets the current file name we are on
//            std::string filename = str;
//
//            ////since pointer does not move yet, print the current one, debugger
//            //std::wcout << directory + L"\\" + str << std::endl;
//
//            //setup converter
//
//            //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
//
//            tempVector.push_back(directory + "\\" + str);
//
//            //go to the next 
//            str += (filename.length() + 1);
//        }
//    }
//
//    return tempVector;
//}

void createCustomPet() {

    std::vector<std::string>  selectedFile;
    selectedFile = openFile();
    if (selectedFile.size() >= 1) {
        sf::RenderWindow window(sf::VideoMode(72, 72), "Desktop Cat", sf::Style::None);

        MARGINS margins;
        margins.cxLeftWidth = -1;

        SetWindowLong(window.getSystemHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
        DwmExtendFrameIntoClientArea(window.getSystemHandle(), &margins);

        //creates a variable named pet and uses its constructor, similar to Pet pet = new Pet(window)
        widget::Pet pet(window);

        //to make this better in the future, change it the window size to whtever the selected sprite size is, then adjust from there
        pet.changeResource(selectedFile);
        pet.initPet();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(250,100), "Desktop Cat", sf::Style::Titlebar | sf::Style::Close);
    manager::PetManager manager(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::thread thread(&createPet);
                    thread.detach();
                }

                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::thread thread(&createCustomPet);
                    thread.detach();
                }
            }
        }
    }

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}

