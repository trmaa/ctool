/*
 * Ctool
 *
 * Small C build tool to start projects and compile them easyly!
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

void help(int err)
{
	printf("USAGE: c <opts> <callbacks>\n");
	printf("Opts:\n");
	printf("\t-n name of the binary\n");
	printf("\t-f flags for libraries\n");
	printf("\t-h help\n");
	printf("Callbacks:\n");
	printf("\tinit: create a default C project\n");
	printf("\tclean: remove old binaries\n");
	printf("\tcompile: compile C files at src/\n");
	printf("\tlink: link binaries at objects/\n");
	printf("\tbuild: compile and link\n");
	printf("\tinstall: make the program runable from the shell\n");

	exit(err);
}

void fatal(char *msg, void (*callback)(int), int err) 
{
	fprintf(stderr, "\e[1;31m%s\e[0m\n", msg);
	callback(err);
}

void init();
void clean();
void compile();
void link();
void build();
void install();

void check_callbacks(char *cb)
{
	if (!strcmp(cb, "init")) { init(); return; }
	if (!strcmp(cb, "clean")) { clean(); return; }
	if (!strcmp(cb, "compile")) { compile(); return; }
	if (!strcmp(cb, "link")) { link(); return; }
	if (!strcmp(cb, "build")) { build(); return; }
	if (!strcmp(cb, "install")) { install(); return; }

	fatal("Wrong func", help, EXIT_FAILURE);
}

char g_name[32];
char g_flags[1025];

int main(int argc, char **argv)
{
	if (argc < 2)
		fatal("", help, EXIT_FAILURE);

	clock_t start, end;
	double elapsed;
	start = clock();

	strcpy(g_name, "app");

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			check_callbacks(argv[i]);	
			continue;
		}

		switch (argv[i][1]) {
		case 'n':
			strcpy(g_name, argv[++i]);
			break;
		case 'f':
			strcpy(g_flags, argv[++i]);
			break;
		case 'h':
			help(EXIT_SUCCESS);
			break;
		default: 
			fatal("Wrong opt!", help, EXIT_FAILURE);
		}
	}

	end = clock();
	elapsed = end - start;
	printf("Done in %d ms.\n", (int)elapsed);
}

void init() 
{
	system("mkdir src");
	system("mkdir include");
	system("touch src/main.c");

	FILE *main = fopen("src/main.c", "w");

	fprintf(main, "#include <stdio.h>\nint\nmain()\n{\n\tprintf(\"Hello\\n\");\n}");

	fclose(main);
}

void clean() 
{
	char *cmd = "rm -r objects";
	printf("%s\n", cmd);
	system(cmd);
}

void compile()
{
	char cmd[1025];

	DIR *src = opendir("src");

	if (src == NULL) {
		fatal("Unable to open directory 'src'", exit, 1);
	}

	struct dirent *entry;

	system("mkdir -p objects");

	while ((entry = readdir(src)) != NULL) {
		char *ext = strrchr(entry->d_name, '.');
		if (ext != NULL && !strcmp(ext, ".c")) {
			*ext = '\0';
			sprintf(cmd, "gcc -c src/%s.c -o objects/%s.o -Iinclude -Wall", entry->d_name, entry->d_name);	
			printf("\e[1;32mCompiling: %s.c\n\e[0m", entry->d_name);
			system(cmd);
		}
	}

	closedir(src);
}

void link()
{
	char cmd[4096];
	sprintf(cmd, "gcc objects/*.o -o %s %s", g_name, g_flags);
	printf("\e[1;32mLinking:\n");
	system("for f in objects/*.o; do echo -e \"\t${f/objects\\//}\"; done");
	printf("\e[0m");
	system(cmd);
}

void build()
{
	compile();
	link();
}

void install()
{
	char cmd[256];
	sprintf(cmd, "cp ./%s /usr/bin/", g_name);
	printf("\e[1;32m%s\e[38;0m\n", cmd);
	system(cmd);
}
