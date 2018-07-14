#include <iostream>
#include <signal.h>
#include <cups/cups.h>
#include <cups/raster.h>
#include <fstream>
#include <cstring>
#include <vector>

int main(const int argc, const char **argv) {
    if (argc < 6 || argc > 7) {
        std::cerr << "invalid arguments" << std::endl;
        return 1;
    }

    cups_option_t *options;
    int num_options = cupsParseOptions(argv[5], 0, &options);

    cups_raster_t *raster;
    raster = cupsRasterOpen(0, CUPS_RASTER_READ);
    if (raster == nullptr) {
        std::cerr << "raster == nullptr" << std::endl;
        return 2;
    }

    cups_page_header2_t header;
    std::ofstream logFile("/tmp/log", std::ios_base::out);

    for (int page = 0; cupsRasterReadHeader2(raster, &header); page++) {
        std::vector<unsigned char> buffer;

        logFile << "CupsHeight: " << header.cupsHeight << std::endl;
        logFile << "CupsWidth: " << header.cupsWidth << std::endl;
        logFile << "CupsBytesPerLine: " << header.cupsBytesPerLine << std::endl;
        logFile << "Buffer size: " << buffer.size() << std::endl;
        logFile << "Bits per Color: " << header.cupsBitsPerColor << std::endl;
        logFile << "Colorspace: " << header.cupsColorSpace << std::endl;

        buffer.resize(header.cupsHeight * header.cupsBytesPerLine -2);

        for (int x = 0; x < header.cupsHeight; x++) {
            cupsRasterReadPixels(raster, buffer.data() + (header.cupsBytesPerLine -2) * x, header.cupsBytesPerLine);
        }

        const char eject[] = {0x1d, 0x65, 0x05, 0};
        const char totalCut[] = {0x1b, 0x69, 0};

        const char selectBitImageMode[] = {0x1d, 0x76, 0x30, 0};
        const char normalBitImageMode = 48;

        const char printBitImage[] = {0x0a, 0x0d, 0x1b, 0x4a, 0};

        std::cout << eject;

        std::cout << selectBitImageMode << normalBitImageMode;
        std::cout << (char)(header.cupsBytesPerLine - 2) << (char)((header.cupsBytesPerLine - 2) >> 8); // nL & nH
        std::cout << (char)(header.cupsHeight) << (char)(header.cupsHeight >> 8);
        std::cout.write(reinterpret_cast<char*>(buffer.data()), buffer.size());
        std::cout << printBitImage;

        std::cout << totalCut << eject;

        std::cout.flush();
    }

}


