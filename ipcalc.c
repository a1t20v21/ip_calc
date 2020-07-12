#define _GNU_SOURCE
#include "ipcalc.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>

unsigned int get_extended_subnetmask(int subnet_mask);
void integral_to_dotted_decimal(unsigned int broadcast_addr, char *output_buffer);

unsigned int get_extended_subnetmask(int subnet_mask){
    int word = CHAR_BIT * 4; // 32-bit
    unsigned int mask_bit = 1;
    for(int i = 0; i < subnet_mask; i++){
        mask_bit = mask_bit << 1;
        mask_bit = mask_bit + 1;
    }
    mask_bit = mask_bit << (word - subnet_mask);
    return mask_bit;
}

void integral_to_dotted_decimal(unsigned int broadcast_addr, char *output_buffer){
    unsigned int octet;
    int word;
    unsigned int mask_bit;
    for(int j = 1; j <= 4; j++){
        mask_bit = 1;
        word = CHAR_BIT * j;
        for(int i = 0; i < CHAR_BIT - 1; i++){
            mask_bit = mask_bit << 1;
            mask_bit = mask_bit + 1;
        }
        mask_bit = mask_bit << 32 - word;
        octet = broadcast_addr & mask_bit;
        octet = octet >> 32 - word;
        sprintf(output_buffer + (j - 1) * 8, "%d", octet);
    }
}

void get_broadcast_address(char *ip_addr, char *subnet_mask, char *output_buffer){
    assert(ip_addr);
    assert(subnet_mask);
    assert(output_buffer);
    unsigned int mask_ones_complement;
    unsigned int broadcast_addr;

    unsigned int ip_decimal = get_integral_equivalent(ip_addr);
    unsigned int subnet_mask_decimal = atoi(subnet_mask);
    mask_ones_complement = ~(get_extended_subnetmask(subnet_mask_decimal));
    broadcast_addr = ip_decimal | mask_ones_complement;
    integral_to_dotted_decimal(broadcast_addr, output_buffer);
}

/*
* Example:
* ip_addr = "86.163.180.79" = "a.b.c.d"
* 86 = 01010110 = a
* shift 'a' left 24 times, a = 01010110000000000000000000000000 = 1442840576
* 163 = 10100011 = b
* shift 'b' left 16 times, b = 101000110000000000000000 = 10682368
* 180 = 10110100 = c
* shift 'c' 8 times, c = 1011010000000000 = 46080
* 79 = 1001111 = d
* shift 'd' 0 times, c = 79
* The IP in decimal = 1442840576 + 10682368 + 46080 + 79 = 1453569103
*/
unsigned int get_integral_equivalent(char *ip_addr){
    assert(ip_addr);
    
    int i, octet_align_size;
    
    char *str1, *token, *delim, *saveptr;
    delim = ".";
    str1 = calloc(1, sizeof(char));
    strncpy(str1, ip_addr, strlen(ip_addr));
    unsigned int ip_decimal = 0;
    
    for(i = 4, str1; i>0; i--, str1 = NULL){
        octet_align_size = CHAR_BIT * (i - 1);

        token = strtok_r(str1, delim, &saveptr);
        if(token == NULL) {
            break;
        }
        unsigned int octet;
        octet = atoi(token);
        octet = octet << octet_align_size;
        ip_decimal = ip_decimal + octet;
    }

    return ip_decimal;
}