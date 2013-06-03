#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>

void printHex(u_char * bytes, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%0x, ", bytes[i]);
    }
    printf("\n");
}

void reverseWCharBytes2(wchar_t *wchar)
{
    u_char *ptr = (u_char *) wchar;
    u_char top = ptr[1];
    u_char bot = ptr[0];
    //printf("Top byte is: %x - %p\n", top, &ptr[1]);
    //printf("Bot byte is: %x - %p\n", bot, &ptr[0]);
    ptr[0] = top;
    ptr[1] = bot;
    //printf("Address of wchar: %p\n", wchar);
    printHex((u_char *) wchar, 8);

}

void reverseWCharThreeBytes(wchar_t *wchar)
{
    u_char *ptr = (u_char *) wchar;
    u_char top = ptr[2];
    u_char bot = ptr[0];
    ptr[0] = top;
    ptr[2] = bot;
    //printHex((u_char *) wchar, 8);

}

void printSizes()
{
    printf("Sizes of data types:\n");
    printf("char: %ld\n", sizeof(char));
    printf("unsigned char: %ld\n", sizeof(u_char));
    printf("short: %ld\n", sizeof(short));
    printf("unsigned short: %ld\n", sizeof(u_short));
    printf("int: %ld\n", sizeof(int));
    printf("long: %ld\n", sizeof(long));
    printf("long long: %ld\n", sizeof(long long));
    printf("wchar_t: %ld\n", sizeof(wchar_t));
}

int main(int argc, char **argv)
{
    char * str = "\xc2\xa2 \xE2\x98\xA0 \xc2\xa5";
    printf("Print 3 unicode chars with all bytes non-null, length is: %ld\n", strlen(str));
    printf("%s\n", str);
    printf("The bytes are: ");
    printHex((u_char *) str, strlen(str));
    str = "\xc2\xa2 \xE2\x98\xA0 \x00\x41 \xc2\xa5";
    printf("Print 4 unicode chars with third char is ascii 'A', length is: %ld\n", strlen(str));
    printf("%s\n", str);
    printf("The bytes are: ");
    printHex((u_char *) str, strlen(str));
    int myInt = 0xdeadbeef;
    u_char *myCharPtr = (u_char *) &myInt;
    printf("\nPrint an int 0xdeadbeef %0x\n", *((int *) myCharPtr));
    printHex(myCharPtr, 4);
    printf("\n");
    printf("Now for a wide char: - Notice that this one prints out with the bytes reversed\n");
    int dummy = 0xaaaa;
    //wchar_t wchar = 0xc2a5; // This is a utf-8 char that takes 2 bytes 1100 0010 1010 0010
    //             Notice, this translates into a unicode decimal value of 162
    // Remove the top two bits of first byte and top 1 bit of second byte. Then move remaining
    // bits in the top bit down by two                                   0000 0000 1010 0010 
    wchar_t wchar = 0xe298a5; // This is a utf-8 char that takes 3 bytes 1110 0010 1001 1000 1010 0000
    // Notice that if you apply the above algorythm, (but remove 3 bits from the top and move
    // remaining first byte bits by 4 and middle byte bits by 2, you get a value of 0x2620
    // Note: escaping a utf-8 byte sequence in a char * string will produce the desired effect
    // when printing the string AND !!!!!!!! the bytes are stored byte per byte so they are
    // unaffected by endiannes. HOWEVER !!!!! If you initialize a wchar_t with the literal version
    // (i.e. something like 0xe298a0), and then hexdump the contents of the wide char, you will
    // see that the bytes are swapped on a little endian machine. I'm not sure what happens if
    // you build a string with a keyboard that can "create" these wierd characters. But, I'm thinking
    // they will be byteswapped
    printf("Strlen of our wchar is: %ld\n", strlen((const char *) &wchar));
    printf("Size of size_t: %ld\n", sizeof(size_t));
    printf("Addresses of wchar: %p, dummy: %p\n", &wchar, &dummy);
    printHex((u_char *) &wchar, 16);
    //wchar_t wchar = 0xa5c2;
    printf("We have a wide char: %s\n", (u_char *) &wchar);
    printf("The unreversed bytes: ");
    printHex((u_char *) &wchar, 3);
    reverseWCharThreeBytes(&wchar);
    //reverseWCharBytes2(&wchar);
    printf("The reversed bytes: ");
    // Notice that the wchar is a two
    printHex((u_char *) &wchar, 3);
    printf("We have a wide char: %s\n", (u_char *) &wchar);
    //printSizes();
    char * myCharWhatRepresentation = "\xE2\x98\xA0 0x41";
    printHex((u_char *) myCharWhatRepresentation, 5);
    //wchar = 0xe298a0;
    wchar = 0xe298a0;
    char * wcharPtr = (char *) &wchar;
    printf("Trying to print a widechar\n");
    printHex((u_char *) wcharPtr, 4);
}
