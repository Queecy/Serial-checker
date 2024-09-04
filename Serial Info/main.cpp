#include <Windows.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>

void changeConsoleTitle(const std::string& newTitle) {
    SetConsoleTitleA(newTitle.c_str());
}

std::string runCommand(const std::string& command) {
    std::stringstream result;
    FILE* pipe = _popen(command.c_str(), "r");
    if (pipe) {
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result << buffer;
        }
        _pclose(pipe);
    }
    return result.str();
}

void printTitle(const std::string& title, bool found) {
    if (found) {
        std::cout << "\x1b[32m" << title << "\x1b[0m" << std::endl;
    }
    else {
        std::cout << "\x1b[31m" << title << "\x1b[0m" << std::endl;
    }
}

void fetchAndDisplayInfo(const std::vector<std::pair<std::string, std::string>>& commands) {
    for (const auto& commandPair : commands) {
        std::string output = runCommand(commandPair.second);
        printTitle(commandPair.first, !output.empty());
        std::cout << output << std::endl;
    }
}

int main() {
    changeConsoleTitle("Queecy serial checker");

    std::vector<std::pair<std::string, std::string>> commands = {
        {"DISK Serial Numbers", "wmic diskdrive get serialnumber"},
        {"BIOS Serial Number", "wmic bios get serialnumber"},
        {"CPU Serial Number", "wmic cpu get serialnumber"},
        {"Baseboard Serial Number", "wmic baseboard get serialnumber"},
        {"Memory Chip Serial Numbers", "wmic memorychip get serialnumber"},
        {"Desktop Monitor Information", "wmic desktopmonitor get Caption, MonitorType, MonitorManufacturer, Name"},
        {"Network Adapter MAC Addresses", "wmic networkadapter get MACAddress"},
        {"Printer Information", "wmic printers get Name, PortName, DriverName"},
        {"Sound Device Information", "wmic sounddev get Name, Manufacturer"},
        {"USB Controller Information", "wmic usbcontroller get Name, Manufacturer"},
        {"Graphics Card Description", "wmic path win32_videocontroller get Description"},
        {"CPU Name", "wmic cpu get Name"},
        {"Logical Disk Serial Numbers", "wmic logicaldisk get volumename, serialnumber"},
        {"Network Adapter IP Addresses", "wmic networkadapterconfiguration get IPAddress, MACAddress"},
        {"NIC Information", "wmic nic get Name, DeviceID"},
        {"Printer Device IDs", "wmic printer get Name, DeviceID"},
        {"IDE Controller Device IDs", "wmic idecontroller get Name, DeviceID"},
        {"Physical Media Serial Numbers", "wmic path win32_physicalmedia get SerialNumber"},
        {"Processor ID", "wmic path win32_processor get ProcessorId"},
        {"Installed Products", "wmic product get Name, Version, InstallDate"},
        {"Operating System Serial Number", "wmic path win32_operatingsystem get SerialNumber"},
        {"Computer Name", "wmic path win32_computersystem get Name"},
        {"EFI Number", "wmic path win32_computersystemproduct get IdentifyingNumber"},
        {"SMBIOS Number", "wmic path win32_bios get SerialNumber"}
    };

    fetchAndDisplayInfo(commands);

    std::cout << "Operation Completed." << std::endl;
    std::cin.get();
    return 0;
}
