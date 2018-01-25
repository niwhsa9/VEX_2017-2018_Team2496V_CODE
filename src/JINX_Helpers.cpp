#include "main.h"
#include "JINX.h"
#include "robot.h"


#define MSG "Hello JINX!"

//*************This space reserved for user-defined functions***************
    //Example of user defined JINX helper function.
    //Since it is at the top of this file, it can be called from anywhere else in this file.
    //Good practice is to put its prototype in JINX.h, though.
    void handleGet(JINX *inStr) {
        //Get the first token from the sent command
        getToken(inStr, 1);

        //Host outgoing messages
        char *message = (char*)malloc(sizeof(char) * (strlen(inStr->token) + 30));
        if (strcmp(inStr->token, "DEBUG_JINX") == 0) {
            writeJINXMessage("Asked for Debug");
            sprintf(message, "%s, %d", inStr->token, DEBUG_JINX);
        } else {
            sprintf(message, "%s %s", inStr->token, " was unable to be gotten.");
        }

        //Free malloc'd string
        writeJINXMessage(message);
        free(message);
        message = NULL;
    }

    //Returns positive integer parsed from character buffer
    int parseInt(const char *intString) {
        char digit;

        //Limit to 32 digit integer. Please don't send 32 digit integers
        char tempStr[33] = "";

        int len = strlen(intString);

        //Catch empty string
        if (len == 0) {
            char errorMessage[100];
            sprintf(errorMessage, "Error, unable to parse integer: %s", intString);
            writeJINXData("Error ", errorMessage);
        }

        for (int i = 0; i < len; i++) {
            digit = intString[i];
            if ((digit < '0') || (digit > '9')) {
                char errorMessage[100];
                sprintf(errorMessage, "Error, unable to parse integer: %s", intString);
                writeJINXData("Error", errorMessage);
                return -1;
            }

            tempStr[i] = digit;
        }

        return atoi(tempStr);
    }
//**************************************************************************

double atof(char* num)
 {
     if (!num || !*num)
         return 0;
     double integerPart = 0;
     double fractionPart = 0;
     int divisorForFraction = 1;
     int sign = 1;
     bool inFraction = false;
     /*Take care of +/- sign*/
     if (*num == '-')
     {
         ++num;
         sign = -1;
     }
     else if (*num == '+')
     {
         ++num;
     }
     while (*num != '\0')
     {
         if (*num >= '0' && *num <= '9')
         {
             if (inFraction)
             {
                 /*See how are we converting a character to integer*/
                 fractionPart = fractionPart*10 + (*num - '0');
                 divisorForFraction *= 10;
             }
             else
             {
                 integerPart = integerPart*10 + (*num - '0');
             }
         }
         else if (*num == '.')
         {
             if (inFraction)
                 return sign * (integerPart + fractionPart/divisorForFraction);
             else
                 inFraction = true;
         }
         else
         {
             return sign * (integerPart + fractionPart/divisorForFraction);
         }
         ++num;
     }
     return sign * (integerPart + fractionPart/divisorForFraction);
 }


//Example parse. User can and should replace with own body.
void parseMessage(JINX *inStr) {
    //Echo entire recieved message
    //writeJINXMessage("MESSAGE -ASH:");
    //writeJINXMessage(inStr->command);
    //Set inStr->token to first token (space-delimated word)
    getToken(inStr, 0);
    //writeJINXMessage(inStr->token);
    if (strcmp(inStr->token, "Option_1") == 0) {
        //Do option 1
        writeJINXMessage("Option 1 chosen.");
    } else if(strcmp(inStr->token, "get") == 0) {
        //Call another function to handle "get"
        handleGet(inStr);
    } else if(strcmp(inStr->token, "P") ==0) {
      getToken(inStr, 1);
      float f = atof(inStr->token);
      lift->setConst('P', (float)f);
      char buf[10];
      sprintf(buf, "P %f", f);
      writeJINXMessage(buf);
    }  else if(strcmp(inStr->token, "D") ==0) {
      getToken(inStr, 1);
      float f = atof(inStr->token);
      lift->setConst('D', (float)f);
      char buf[10];
      sprintf(buf, "D %f", f);
      writeJINXMessage(buf);
    }
    else {
        //Do default
        writeJINXMessage("No comparison found");
    }
}
