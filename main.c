#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"

int hex_dec(char* hex, char* dec) {

    char bal[10][100];
    double tmp[10];
    int i = 0, j = 0, len = 0, bal_len[10] = { 0, };
    int step = 0, hex_len = 0;
    int isLong = 0;
    double digit[10] = { 1.0, };
    double ret = 0.0;

    len = strlen(hex);
    memset(&bal, 0x00, sizeof(bal));
    if (len > 10) {
        if ((len - 2) % 6 > 3) {
            step = (len - 2) / 6;
        }
        else {
            step = ((len - 2) / 6) - 1;
        }
        for (j = 0; j < step + 1; j++) {
            
            if (j == step) {
                strncpy_s(bal[j], 100, hex + hex_len + 2, strlen(hex) - hex_len - 2);
                hex_len += (strlen(hex) - hex_len - 2 );
            }
            else if (j == 0) {
                strncpy_s(bal[0], 100, hex + 2, 6);
                hex_len += 6;
            }
            else {
                strncpy_s(bal[1], 100, hex + hex_len + 2, 6);
                hex_len += 6;
            }
            digit[step - j] = 0.000000000000000001;
            printf("%d\n", hex_len - 6);
            for (i = 0; i < hex_len - 6; i++) {
                digit[step - j] *= 16;
            }
            
        }
        isLong = 1;
    }
    if (isLong) {
        for (j = 0; j < step + 1; j++) {
            printf("bal[%d] = %s / digits[%d] = %.18lf, bal_len[%d] = %d\n", j, bal[j], j, digit[j], j, bal_len[j]);
            tmp[j] = (double)strtol((const char*)bal[j], NULL, 16);
            printf("bal[%d] = %.18lf, digit[%d] = %.18lf\n", j, tmp[j], j, digit[j]);
            tmp[j] = tmp[j] * digit[j];
            printf("bal[%d] = %.18lf\n", j, tmp[j]);
            //log_debug("!!!! %.8lf * %.8lf = %.8lf", tmp1, tmp2, tmp1 + tmp2);
            ret += tmp[j];
        }
        sprintf_s(hex, 100, "%.4lf", ret);
    }
    else {
        tmp[0] = (double)strtol((const char*)hex, NULL, 16);
        sprintf_s(hex, 100, "%.4lf", tmp[0] * 0.000000000000000001);
    }
    strcpy_s(dec, 100, hex);

    return 1;
}

int hex_dec2(char* hex, char* dec) {

    double tmp;
    int i = 0, len = 0;
    double digit = 1.0;
    double bal_tmp = 0.0;
    double bal_ret = 0.0;
    char hex_tmp[100];
    char temp[100];

    memset(&hex_tmp, 0x00, sizeof(hex_tmp));

    len = strlen(hex);
    if (len > 10) {
        for (i = len-1; i >= 2; i--) {
            strncpy_s(hex_tmp, 100, hex + i, 1);
            //printf("%s\n", hex_tmp);
            bal_tmp += ((double)strtol((const char*)hex_tmp, NULL, 16));
            bal_tmp *= (digit * 0.000000000000000001);
            digit *= 16;

            bal_ret += bal_tmp;
            bal_tmp = 0.0;

        }
        sprintf_s(temp, 100, "%.8lf", bal_ret);
    }
    else {
        tmp = (double)strtol((const char*)hex, NULL, 16);
        sprintf_s(temp, 100, "%.8lf", tmp * 0.000000000000000001);
    }
    strcpy_s(dec, 100, temp);

    return 1;
}

int dec_hex(char* bin, char* hex) {

    char bal[100][5];
    int i,len = 0;
    int index = 0;
    int chg = 0;
    int c = 0;
    
    memset(&bal, 0x00, sizeof(bal));
    len = strlen(bin);
    chg = len % 4;
    printf("len = %d chg = %d\n", len, chg);
    for (i = 0; i < (len / 4) + 1; i++) {
        if (len % 4 != 0) {
            if (i == 0) {
                if (chg == 1) {
                    bal[i][0] = '0';
                    bal[i][1] = '0';
                    bal[i][2] = '0';
                    bal[i][3] = bin[0];
                }else if (chg == 2) {
                    bal[i][0] = '0';
                    bal[i][1] = '0';
                    bal[i][2] = bin[0];
                    bal[i][3] = bin[1];
                }else if (chg == 3) {
                    bal[i][0] = '0';
                    bal[i][1] = bin[0];
                    bal[i][2] = bin[1];
                    bal[i][3] = bin[2];
                }
            }
            else {
                c = chg + (4 * (i - 1));
                printf("ÀÚ¸´¼ö : %d", c);
                strncpy_s(bal[i], 5, bin + c, 4);
            }
            index++;
        }
        else {
            if (i == (len / 4)) {
                break;
            }
            strncpy_s(bal[i], 5, bin + (4 * i), 4);
            index++;
        }
        printf("bal[%d] = %s\n", i, bal[i]);
    }

    hex[0] = '0';
    hex[1] = 'x';

    for (i = 0; i < index; i++) {
        int a = 0;
        if (bal[i][0] == '1') {
            a += 8;
        }
        if (bal[i][1] == '1') {
            a += 4;
        }
        if (bal[i][2] == '1') {
            a += 2;
        }
        if (bal[i][3] == '1') {
            a += 1;
        }

        if (a >= 0 && a < 10) {
            hex[i + 2] = a + 48;
        }
        else {
            if(a == 10){
                hex[i + 2] = 'a';
            }else if (a == 11) {
                hex[i + 2] = 'b';
            }
            else if (a == 12) {
                hex[i + 2] = 'c';
            }
            else if (a == 13) {
                hex[i + 2] = 'd';
            }
            else if (a == 14) {
                hex[i + 2] = 'e';
            }
            else if (a == 15) {
                hex[i + 2] = 'f';
            }
        }

    }



    return 1;
}

int main() {
    char hex[100] = "0x662eeb62b696d4000";
    char dec[100];
    char input[201] = "1000000000000000000";
    char ret[256];
    char decToHex[100];

    memset(&ret, 0x00, sizeof(ret));
    memset(&decToHex, 0x00, sizeof(decToHex));

    makeBinary(input, ret);

    printf("%s\n", ret);

    reverseChar(ret, strlen(ret));

    printf("reversed = %s\n", ret);

    dec_hex(ret, decToHex);

    printf("dec to hex result = %s\n", decToHex);

    hex_dec2(hex, dec);

    printf("hex = %s / dec = %s\n", hex, dec);

    return 0;
}