#include "ipcalc.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
    char *ip_addr1 = "86.163.180.79";
    char *mask1 = "24";
    char *output_buffer = calloc(1, sizeof(char));

    get_broadcast_address(ip_addr1, mask1, output_buffer);
    printf("Broadcast Address: %s.%s.%s.%s\n", output_buffer, output_buffer + 8, output_buffer + 16, output_buffer + 24);
    printf("Decimal Equivalent: %u\n", get_integral_equivalent(ip_addr1));
    
    char *ip_addr2 = "192.168.2.10";
    char *mask2 = "24";
    get_broadcast_address(ip_addr2, mask2, output_buffer);
    printf("Broadcast Address: %s.%s.%s.%s\n", output_buffer, output_buffer + 8, output_buffer + 16, output_buffer + 24);
    printf("Decimal Equivalent: %u\n", get_integral_equivalent(ip_addr2));
    
    char *ip_addr3 = "10.1.23.10";
    char *mask3 = "20";
    get_broadcast_address(ip_addr3, mask3, output_buffer);
    printf("Broadcast Address: %s.%s.%s.%s\n", output_buffer, output_buffer + 8, output_buffer + 16, output_buffer + 24);
    printf("Decimal Equivalent: %u\n", get_integral_equivalent(ip_addr3));
    
    free(output_buffer);
}