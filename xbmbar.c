#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void parse_percentage(unsigned char *result, int percentage) {
	int temp_per = percentage + 2;
        int counter = 0;
	while (temp_per >= 8) {
		result[counter] |= 0xff;
		temp_per -= 8;
                counter++;
	}
        result[counter] |= (1 << temp_per) - 1;
        result[12] |= 0xc0;
            
}

int main(int argc, char *argv[]) {
	char opt;
	int width, height, percentage;
	while ((opt = getopt(argc, argv, "hp:")) != -1) {
		switch (opt) {
			case 'h':
				printf("xbmbar [-h] [-x WIDTH] [-h HEIGHT] [-p PERCENTAGE]\n");
				exit(0);
			case 'x':
				width = atoi(optarg);
				break;
			case 'y':
				height = atoi(optarg);
				break;
			case 'p':
				percentage = atoi(optarg);
				break;
		}
	}
	printf("%s\n", "#define xbmbar_width 104");
	printf("%s\n", "#define xbmbar_height 8");
	printf("%s\n", "static unsigned char xbmbar_bits[] = {");

	for (int i = 0; i < 2; i++) {
		printf("\t%s\n", "0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,");
	}
        
        int bar_size = 13 * 8;
	unsigned char *bar = calloc(1, bar_size);
	parse_percentage(bar, percentage);

	for (int i = 0; i < 4; i++) {
                printf("\t");
		for (int j = 0; j < 13; j++) {
			printf("0x%x, ", bar[j]);
		}
		printf("\n");
	}
    
        free(bar);

	printf("\t%s\n", "0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,");
	printf("\t%s\n", "0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff");

	printf("%s\n", "};");

	return 0;
}
