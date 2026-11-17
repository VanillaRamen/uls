/* +--------------------------------------+
 * | uls:                                 |
 * | simple program to use as an example  |
 * | of how to interface with directories |
 * | using <dirent.h>                     |
 * |                                      |
 * | author: vanillaramen                 |
 * +--------------------------------------+
 */

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>


int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: %s <dirpath>\n", argv[0]);
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		DIR *dirp = opendir(argv[i]);

		if (dirp == NULL) {
			switch (errno) {
				case ENOTDIR:
					printf("NOTDIR %s\n\n", argv[i]);
					continue;
					break;
				default:
					perror(argv[i]);
					return 1;
					break;
			}
		}

		// dir printing
		printf("DIR %s\n", argv[i]);

		size_t longest_filename_length = 0;
		int errno_pre = errno;
		struct dirent *ent;
		while ( (ent = readdir(dirp) ) != NULL) { // go through the entries
			if (ent->d_name[0] == '.') continue;

			switch (ent->d_type) {
				case DT_UNKNOWN:
					printf("\x1b[38;5;40m"); // 256 green
					printf("| ? ");
					break;
				case DT_BLK:
					printf("\x1b[38;5;208m"); // 256 orange
					printf("| # ");
					break;
				case DT_LNK:
					printf("\x1b[38;5;159m");  // 256 bright blue
					printf("| = ");
					break;
				case DT_DIR:
					printf("\x1b[38;5;81m"); // 256 indigo
					printf("| $ ");
					break;
				case DT_REG:
					printf("\x1b[38;5;189m"); // 256 faint blue
					printf("| - ");
					break;
				default:
					printf("| @ ");
					break;
			}

			printf("%s", ent->d_name);

			if (ent->d_type == DT_DIR) putchar('/');

			printf("\x1b[0m"); // reset styling and coloring
			putchar('\n');

			if (strlen(ent->d_name) > longest_filename_length) {
				longest_filename_length = strlen(ent->d_name);
			}
		}
		if (errno_pre ^ errno) {
			perror("readdir");
			return 1;
		}

		closedir(dirp);

		printf("\x1b[38;5;225m");
		putchar('+');
		for (size_t i = 0; i < longest_filename_length + 1 + 3; i++)
			putchar('-'); // ^ accounts for the prefix lengths
		putchar('+');
		printf("\x1b[0m");
		putchar('\n');

		if (i + 1 < argc) putchar('\n');
	}

	return 0;
}
