#include <queue>
#include <string>
#include <iostream>

using namespace std;

#define CUBETYPE "2x2"
#define NUM_FACE_TILES 4


bool validColourCode(char colour) {
    if (
        colour != 'w' && colour != 'y' && colour != 'g' 
        && colour != 'b' && colour != 'r' && colour != 'o'
    ) {
        return false;
    } else {
        return true;
    }
}

void printScrambleHelp() {
    cout << "colour guide:\nw = white, y = yellow, g = green,\nb = blue, o = orange, r = red\n" << "\n";
    cout << "Enter the colours of the face from left to right, top to bottom while ";
    cout << "facing the given face.\n";
    cout << "example: white on top left, blue on top right, green on bottom left, red on bottom right\n";
    cout << "input: wbgr\n";
}

bool isValidFace(string face) {
    if (face.length() != NUM_FACE_TILES) {
        cout << "INVALID NUMBER OF TILES!\n";
        return false;
    } 

    for (int i = 0; i < NUM_FACE_TILES; i++) {
        if (!validColourCode(face[i])) {
            cout << "INVALID COLOUR!\n";
            return false;
        }
    }

    return true;
}

string readScramble() {
    
    string faceOutput[6] = {
        "Top face", "Front face", "Right face", 
        "Back face", "Left face", "Bottom face"
    };
    string scramble = "";

    for (int i = 0; i < 6; i++) {
        cout << faceOutput[i] << ": \n";
        string face = "";
        cin >> face;
        if(isValidFace(face)) {
            scramble += face;
        } else {
            i--;
        }
    }

    return scramble;
}

int main(void) {
    printScrambleHelp();
    string scramble = readScramble();
    cout << scramble << "\n";
    return 0; 
}