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
        out = "#pragma once\nDWORD64 automatic[]\n{\n\t1545779598, // AK;\n\t-1758372725, // Thompson\n\t1796682209, // SMG\n\t-1812555177,// LR\n\t1318558775, // MP5\n\t-2069578888, // M249\n};\nDWORD64 sniper[]\n{\n\t-778367295, // L96\n\t1588298435, // Bolt\n};\nDWORD64 eoka = -75944661;\nDWORD64 semiautomatic[]\n{\n\t-904863145, // SAR \n\t818877484, // SAP\n\t-852563019, // M92\n\t1373971859, // Python\n\t649912614, // Revolver\n\t28201841, // M39\n\t1953903201, // Nailgun\n\t-1123473824, // MGL\n};\n" + out;
        std::ofstream file("offsets.hpp");
        file << out;
        file.close();
    }
}