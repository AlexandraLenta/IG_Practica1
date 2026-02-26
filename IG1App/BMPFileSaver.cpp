#include "BMPFileSaver.h"
#include <string>
#include <fstream>

void
BMPFileSaver::saveToBmp(GLuint* pixels) {
    //float width = 600;
    //float height = 600;
    //std::string filename = "savefile";

    //// Calculate row padding (BMP requires rows to be 4-byte aligned)
    //int stride = (width * 3 + 3) & ~3; // Round up to next multiple of 4
    //BMPInfoHeader infoHeader{ .biWidth = width, .biHeight = height, .biSizeImage = stride * height };
    //BMPFileHeader fileHeader{ .bfSize = 54 + infoHeader.biSizeImage };

    //// Open file and write headers
    //std::ofstream file(filename, std::ios::binary);
    //if (!file) return false;
    //file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    //file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));

    //// Write pixel data with padding
    //const GLubyte* row = pixels;
    //for (int y = 0; y < height; y++) {
    //    file.write(reinterpret_cast<const char*>(row), width * 3); // Write row
    //    // Add padding (0s)
    //    GLubyte padding[3] = { 0, 0, 0 };
    //    file.write(reinterpret_cast<const char*>(padding), stride - width * 3);
    //    row += width * 3; // Next row
    //}
    //return true;
}