
#include "../types/Adjustment.h"
#include "../constants/Musical_Note_Constants.h"
#include "../headers/get_divisor_wrap_from_note.h"

Adjustment get_divisor_wrap_from_note(char note[3]){

    static Adjustment adjustment; 

    if(note[2] == '0'){

        if(note[0] == 'C'){
                 if(note[1] == '-') {adjustment.wrap = C_0_WRAP; adjustment.divisor = C_0_DIVIDER;}
            else if(note[1] == '#') {}
            else                    {  }
        }

        else if(note[0] == 'D'){
            if(note[1] == '-') {}
            else if(note[1] == '#') {}
            else {}
        }
        else if(note[0] == 'E'){
            if(note[1] == '-') {}
            else if(note[1] == '#') {}
            else {}
        }
        else if(note[0] == 'F'){
            if(note[1] == '-') {}
            else if(note[1] == '#') {}
            else {}
        }
        else if(note[0] == 'G'){
            if(note[1] == '-') {}
            else if(note[1] == '#') {}
            else {}
        }
        else if(note[0] == 'A'){
                 if(note[1] == '-') {  }
            else if(note[1] == '#') {}
            else {}
        }
        else if(note[0] == 'B'){
            if(note[1] == '-') {}
            else if(note[1] == '#') {}
            else {}
        }

    }    

    printf("adjustment.divisor = %.3f - adjustment.wrap = %d \n", adjustment.divisor , adjustment.wrap);
 
    return adjustment;

}

