#include <windows.h>
#include <commdlg.h>  // For file dialog
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

// Function to select a file using a file dialog
std::string openFileDialog() {
    OPENFILENAME ofn;       // common dialog box structure
    char szFile[260];       // buffer for file name

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = GetConsoleWindow(); // Set owner window to console
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "DLL Files\0*.dll\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFile[0] = '\0';
    ofn.lpstrTitle = "Select DLL File";

    // Display the file dialog
    if (GetOpenFileName(&ofn) == TRUE) {
        return std::string(ofn.lpstrFile);
    }
    return "";
}

// Function to execute a command and print its output (for debugging)
void executeCommand(const std::string& cmd) {
    std::cout << "Running: " << cmd << std::endl;
    int result = system(cmd.c_str());
    if (result != 0) {
        std::cerr << "Error: Command failed with result code " << result << std::endl;
    }
}

// Convert DLL to LIB file
void convertDLLToLib(const std::string& dllPath) {
    // Dynamically generate def file name based on DLL name
    std::string defFile = dllPath.substr(dllPath.find_last_of("\\/") + 1);  // Extract the DLL file name
    defFile = defFile.substr(0, defFile.find_last_of(".")) + ".def"; // Change extension to .def
    
    // Dynamically generate lib file name based on DLL name
    std::string libFile = defFile.substr(0, defFile.find_last_of(".")) + ".lib";

    std::cout << "Generated Def and Lib File Names: " << defFile << " | " << libFile << std::endl;

    // Step 1: Generate .def file from DLL
    std::string dumpbinCmd = "dumpbin /EXPORTS \"" + dllPath + "\" > \"" + defFile + "\"";
    executeCommand(dumpbinCmd);

    // Step 2: Modify .def file to ensure it's properly formatted
    std::ofstream defOut(defFile, std::ios::app);
    if (defOut) {
        defOut << "LIBRARY " << dllPath.substr(dllPath.find_last_of("\\/") + 1) << "\nEXPORTS\n"; // Using DLL name
        defOut.close();
    } else {
        std::cerr << "Error: Failed to write to " << defFile << std::endl;
        return;
    }

    // Step 3: Convert .def to .lib using lib.exe
    std::string libCmd = "lib /DEF:\""+ defFile + "\" /OUT:\""+ libFile + "\"";
    executeCommand(libCmd);

    // Verify the .lib file was created
    if (GetFileAttributes(libFile.c_str()) != INVALID_FILE_ATTRIBUTES) {
        std::cout << "Conversion complete! Generated: " << libFile << std::endl;
    } else {
        std::cerr << "Error: " << libFile << " was not created." << std::endl;
    }
}

int main() {
    // Get DLL file path from file dialog
    std::string dllPath = openFileDialog();
    if (dllPath.empty()) {
        std::cout << "No file selected." << std::endl;
        return 1;
    }

    // Confirm DLL file path
    std::cout << "Selected DLL: " << dllPath << std::endl;

    // Proceed with the conversion
    convertDLLToLib(dllPath);

    return 0;
}
