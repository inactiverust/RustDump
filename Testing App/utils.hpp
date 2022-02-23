#pragma once
namespace Utils {
    //Reads file to bytes
    bool read_file_to_memory(const std::string& file_path, std::vector<uint8_t>* out_buffer)
    {
        std::ifstream file_ifstream(file_path, std::ios::binary);

        if (!file_ifstream)
            return false;

        out_buffer->assign((std::istreambuf_iterator<char>(file_ifstream)), std::istreambuf_iterator<char>());
        file_ifstream.close();

        return true;
    }
    //bad custom way of sigscanning
    uint64_t sigScan(std::vector<uint8_t> mask) {
        std::vector<uint8_t> out_buffer;
        std::string path = "UnityPlayer.dll";
        read_file_to_memory(path, &out_buffer);
        if (out_buffer.size() == 0) {
            std::cout << "UnityPlayer.dll Error File May Be Missing";
        }
        for (int i = 0; i < out_buffer.size(); i++) {
            for (int a = 0; a < mask.size(); a++) {
                if (mask.at(a) == 0)
                    continue;
                if (out_buffer.at(i + a) != mask.at(a))
                    break;
                if (a == mask.size() - 1)
                    return i;
            }
        }
        return 0;
    }
    //searches dump.json for address
    std::string findAddress(std::string dumped, std::string searchParam) {
        std::string returnStr = "";
        int counter = 0;
        size_t index = dumped.find(searchParam);
        std::string temp = dumped.substr(0, index);
        index = temp.find_last_of("Address:");
        for (counter = index - 100; counter < index; counter++) {
            if (isdigit(temp.at(counter))) {
                returnStr = returnStr + temp.at(counter);
            }
        }
        return returnStr;
    }
    //outputs the filelist array to a file
    void strArrToFile(std::vector<std::string> arr) {
        std::string out = "";
        for (int i = 0; i < arr.size(); i++) {
            out = out + arr.at(i) + "\n";
        }
        std::ofstream file("offsets.hpp");
        file << out;
        file.close();
    }
}