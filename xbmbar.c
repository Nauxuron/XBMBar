#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void parse_percentage(unsigned char *result, const int percentage) {
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
	int percentage;
        int perc_flag = 0;
	while ((opt = getopt(argc, argv, "hp:")) != -1) {
		switch (opt) {
			case 'h':
				printf("xbmbar [-h] [-x WIDTH] [-h HEIGHT] [-p PERCENTAGE]\n");
				exit(0);
			case 'p':
				percentage = atoi(optarg);
                                perc_flag = 1;
				break;
		}
	}
        if (perc_flag != 1) {
            fprintf(stderr, "%s: %s", argv[0], "Try 'xbmbar -h' for more information.\n");
            exit(1);
        }

        int width = 104;
        int height = 8;

	printf("%s %d\n", "#define xbmbar_width", width);
	printf("%s %d\n", "#define xbmbar_height", height);
	printf("%s\n", "static unsigned char xbmbar_bits[] = {");

	for (int i = 0; i < height/4; i++) {
                printf("\t");
                for (int j = 0; j < width/8; j++) {
                    printf("%s, ", "0xff");
                }
                printf("\n");
	}
        
	unsigned char *bar = calloc(1, width);
	parse_percentage(bar, percentage);

	for (int i = 0; i < height/2; i++) {
                printf("\t");
		for (int j = 0; j < width/8; j++) {
			printf("0x%02x, ", bar[j]);
		}
		printf("\n");
	}
    
        free(bar);

        for (int i = 0; i < (height/4 - 1); i++) {
                printf("\t");
                for (int j = 0; j < width/8; j++) {
                    printf("%s, ", "0xff");
                }
                printf("\n");
	}
        printf("\t");
        for (int j = 0; j < (width/8 - 1); j++) {
                printf("%s, ", "0xff");
        }
        printf("0xff");
	printf(" %s\n", "};");

	return 0;
}
