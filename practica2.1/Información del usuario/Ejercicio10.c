#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>

int main(int argc, char **argv){

	uid_t uid = getuid();
	uid_t euid = geteuid();
	struct passwd *infoUser = getpwuid(uid);
	//struct passwd *infoUserReal(euid) = getpweuid();


	printf("UID real: %i \nUID efectivo: %i \n", uid, euid);
	printf("Nombre usuario: %s \nDirectorio home: %s \nDescripcion de usuario: %s \n", infoUser->pw_name, infoUser->pw_dir, infoUser->pw_gecos);

	return 0;
}
