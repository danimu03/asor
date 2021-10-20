#include <sys/utsname.h>
#include <iostream>
using namespace std;


int main(int argc, char **argv) {

	struct utsname buf;

	int ret = uname(&buf);

	if(ret == -1) { return -1; }

	cout << "Sysname: " << buf.sysname << endl;
	cout << "Nodename: " << buf.nodename << endl;

	return 0;
}