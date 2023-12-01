#include <queue>
#include <string>
#include <iostream>

using namespace std;

#define CUBETYPE "2x2"
#define NUM_FACE_TILES 4

// X = turn face on X side by 90 degrees clockwise, 
// Xp = turn face on X side by 90 degrees counter-clockwiseb 
enum Move { U, Up, R, Rp, L, Lp, B, Bp, F, Fp, D, Dp };

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

/**
 * Scramble is a string of NUM_FACE_TILES * 6 chars. 
 * Face order is: top -> front -> right -> back -> left -> bottom.
 * On each face, tile order is left to right and top to bottom. For example:
 * -------------
 * |     |     |
 * |  0  |  1  |
 * |     |     |
 * -------------
 * |     |     |
 * |  2  |  3  |
 * |     |     |
 * -------------
 * 
*/
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

/**
 * Makes a move on the given cube scramble.
*/
string cubeMove(string originalScramble, Move move) {
    if (originalScramble.length() != NUM_FACE_TILES * 6) {
        cout << "INVALID SCRAMBLE LENGTH\n";
    }
    char temp, tempLeft, tempRight;
    switch(move) {
        case U:
            // shift top face
            temp = originalScramble[0];
            originalScramble[0] = originalScramble[2];
            originalScramble[2] = originalScramble[3];
            originalScramble[3] = originalScramble[1];
            originalScramble[1] = temp;

            // shift side faces
            tempLeft = originalScramble[4];
            tempRight = originalScramble[5];

            originalScramble[4] = originalScramble[8];
            originalScramble[5] = originalScramble[9];

            originalScramble[8] = originalScramble[12];
            originalScramble[9] = originalScramble[13];

            originalScramble[12] = originalScramble[16];
            originalScramble[13] = originalScramble[17];

            originalScramble[16] = tempLeft;
            originalScramble[17] = tempRight;
            break;
        case Up:
            // shift top face
            temp = originalScramble[0];
            originalScramble[0] = originalScramble[1];
            originalScramble[1] = originalScramble[3];
            originalScramble[3] = originalScramble[2];
            originalScramble[2] = temp;

            // shift side faces
            tempLeft = originalScramble[4];
            tempRight = originalScramble[5];

            originalScramble[4] = originalScramble[16];
            originalScramble[5] = originalScramble[17];

            originalScramble[16] = originalScramble[12];
            originalScramble[17] = originalScramble[13];

            originalScramble[12] = originalScramble[8];
            originalScramble[13] = originalScramble[9];

            originalScramble[8] = tempLeft;
            originalScramble[9] = tempRight;
            break;
        case F:
            // front face
            temp = originalScramble[4];
            originalScramble[4] = originalScramble[6];
            originalScramble[6] = originalScramble[7];
            originalScramble[7] = originalScramble[5];
            originalScramble[5] = temp;

            // shift side faces
            tempLeft = originalScramble[2];
            tempRight = originalScramble[3];

            originalScramble[2] = originalScramble[19];
            originalScramble[3] = originalScramble[17];

            originalScramble[19] = originalScramble[21];
            originalScramble[17] = originalScramble[20];
            
            originalScramble[21] = originalScramble[8];
            originalScramble[20] = originalScramble[10];

            originalScramble[8] = tempLeft;
            originalScramble[10] = tempRight;
            break;
        case Fp:
            // front face
            temp = originalScramble[4];
            originalScramble[4] = originalScramble[5];
            originalScramble[5] = originalScramble[7];
            originalScramble[7] = originalScramble[6];
            originalScramble[6] = temp;

            // shift side faces
            tempLeft = originalScramble[2];
            tempRight = originalScramble[3];

            originalScramble[2] = originalScramble[8];
            originalScramble[3] = originalScramble[10];

            originalScramble[8] = originalScramble[21];
            originalScramble[10] = originalScramble[20];
            
            originalScramble[21] = originalScramble[19];
            originalScramble[20] = originalScramble[17];

            originalScramble[19] = tempLeft;
            originalScramble[17] = tempRight;
            break;
        case R:
            // right face
            temp = originalScramble[8];
            originalScramble[8] = originalScramble[10];
            originalScramble[10] = originalScramble[11];
            originalScramble[11] = originalScramble[9];
            originalScramble[9] = temp;

            // shift adjacent faces
            tempLeft = originalScramble[3];
            tempRight = originalScramble[1];

            originalScramble[3] = originalScramble[7];
            originalScramble[1] = originalScramble[5];

            originalScramble[7] = originalScramble[23];
            originalScramble[5] = originalScramble[21];

            originalScramble[23] = originalScramble[12];
            originalScramble[21] = originalScramble[14];

            originalScramble[12] = tempLeft;
            originalScramble[14] = tempRight;
            break;
        case Rp:
            // right face
            temp = originalScramble[8];
            originalScramble[8] = originalScramble[9];
            originalScramble[9] = originalScramble[11];
            originalScramble[11] = originalScramble[10];
            originalScramble[10] = temp;

            // shift adjacent faces
            tempLeft = originalScramble[3];
            tempRight = originalScramble[1];

            originalScramble[3] = originalScramble[12];
            originalScramble[1] = originalScramble[14];

            originalScramble[12] = originalScramble[23];
            originalScramble[14] = originalScramble[21];

            originalScramble[23] = originalScramble[7];
            originalScramble[21] = originalScramble[5];

            originalScramble[7] = tempLeft;
            originalScramble[5] = tempRight;
            break; 
        case L:
            // left face
            temp = originalScramble[16];
            originalScramble[16] = originalScramble[18];
            originalScramble[18] = originalScramble[19];
            originalScramble[19] = originalScramble[17];
            originalScramble[17] = temp;

            // shift adjacent faces
            tempLeft = originalScramble[0];
            tempRight = originalScramble[2];

            // TODO, NOT DONE YET
            originalScramble[0] = originalScramble[19];
            originalScramble[2] = originalScramble[17];

            originalScramble[19] = originalScramble[22];
            originalScramble[17] = originalScramble[2];

            originalScramble[23] = originalScramble[7];
            originalScramble[21] = originalScramble[5];

            originalScramble[7] = tempLeft;
            originalScramble[5] = tempRight;
            break;
        default:
            cout << "NOT IMPLEMENTED YET\n"; 
    }

    return originalScramble;
}

int main(void) {
    printScrambleHelp();
    string scramble = readScramble();
    cout << scramble << "\n";
    cout << "U: " << cubeMove(scramble, U) << '\n';
    cout << "Up: " << cubeMove(scramble, Up) << '\n';
    cout << "F: " << cubeMove(scramble, F) << '\n';
    cout << "Fp: " << cubeMove(scramble, Fp) << '\n';
    return 0; 
}